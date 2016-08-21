#include "chat.h"
#include "message/emmessage.h"
#include "message/emtextmessagebody.h"
#include "emclient.h"
#include "emchatmanager_interface.h"
#include "emcontactmanager_interface.h"
#include "emcontactlistener.h"
#include "emcallback.h"
#include "emerror.h"
#include "mycontactlistener.h"
#include "emnetworklistener.h"
#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include <list>

#ifdef __linux__
#include "unistd.h"
#include <string.h>       // strncpy
#include <sys/ioctl.h>    // SIOCGIFFLAGS
#include <errno.h>        // errno
#include <netinet/in.h>   //IPPROTO_IP
#include <net/if.h>       // IFF_*, ifreq
#include <linux/sockios.h>
#include <linux/ethtool.h>
#endif

using namespace easemob;

namespace Demo {

using std::string;
using std::stringstream;
using std::list;
using std::vector;
using std::endl;
using std::cout;

using easemob::EMError;
using easemob::EMClient;
using easemob::EMChatManagerInterface;


#ifdef __linux__
bool checkNetwork(const char *ifname) {
    int socketId = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if(socketId < 0) return false;

    struct ifreq if_req;

    (void) strncpy(if_req.ifr_name, ifname, sizeof(if_req.ifr_name));

    int rv = ioctl(socketId, SIOCGIFFLAGS, &if_req);
    close(socketId);

    if ( rv == -1) return false;

    return (if_req.ifr_flags & IFF_UP) && (if_req.ifr_flags & IFF_RUNNING);
}
#endif

Chat::Chat(const std::string &resourcePath, const std::string &workPath):
event_loop_(new EventLoop())
{
    log_file_.open (workPath + "/log");
    easemob::EMChatConfigsPtr configPtr = easemob::EMChatConfigsPtr(new easemob::EMChatConfigs(resourcePath, workPath, "easemob-demo#chatdemoui"));
    configPtr->setEnableConsoleLog(false);
    chatClient = easemob::EMClient::create(configPtr);
    chatClient->getChatManager().addListener(this);

    window_ = new Window();
    window_->SetTitle("Easemob demo ver 0.1");
    window_->UpdateStatus("Disconnected");
    window_->AddOutput("Please use below command to start:");
    window_->AddOutput("1. /register username password");
    window_->AddOutput("2. /login username password");
    window_->AddOutput("3. /logout");
    window_->AddOutput("4. /msg target_username your_message");
    window_->AddOutput("5. /addcontact contact_name invitation_message");
    window_->AddOutput("6. /listcontact");
    window_->AddOutput("7. /deletecontact contact_name");
    window_->AddOutput("8. /getblacklist");
    window_->AddOutput("8. /addtoblacklist contact_name");
    window_->AddOutput("9. /removefromblacklist contact_name");
    window_->AddOutput("10. /acceptcontact contact_name");
    window_->AddOutput("11. /declinecontact contact_name");

    chatClient->getContactManager().registerContactListener(
        new MyContactListener([=] (const std::string &str) {window_->AddOutput(str);}));

    event_loop_->AddEvent([this](){CheckInput();});
   
    chatClient->addConnectionListener(this);
    
#ifdef __linux__
    mNetState = checkNetwork("eth0");
#endif
}

Chat::~Chat()
{
    chatClient->removeConnectionListener(this);
    chatClient->getChatManager().removeListener(this);
    log_file_.close();
    delete window_;
    delete chatClient;
}

void Chat::onConnect()
{
    window_->AddOutput("connected"); 
}

void Chat::onDisconnect(easemob::EMErrorPtr error)
{
    window_->AddOutput("disconnected: " + error->mDescription);
}

void Chat::onPong()
{
    window_->AddOutput("---> get Pong from server");    
}
void Chat::onReceiveMessages(const easemob::EMMessageList &messages)
{
    window_->AddOutput("---> onReceiveMessage");
    if(messages.size() > 0) {
        for(auto m: messages) { 
            if (m->bodies().size() > 0 && m->bodies()[0]->type() == easemob::EMMessageBody::TEXT)
            {
                string text = static_cast<easemob::EMTextMessageBody*>(m->bodies()[0].get())->text();
                window_->AddOutput(m->from() + " -> " + m->to() + ": " + text);
            }
        }
    }
}

void Chat::HandleCommand(string command_string)
{
    if (command_string.size() > 0) {
        string buf;
        stringstream ss(command_string);
        vector<string> command;
        while (ss >> buf) {
            command.push_back(buf);
        }

        if (command[0].compare("/register") == 0) {
            if (command.size() == 3) {
                window_->AddOutput("Registering...");
                window_->UpdateStatus("Registering...");
                easemob::EMErrorPtr result = chatClient->createAccount(command[1], command[2]);
                if(result->mErrorCode == EMError::EM_NO_ERROR) {
                    window_->AddOutput("Register success");
                } else {
                    window_->AddOutput(result->mDescription);
                }
            } else {
                window_->AddOutput("Need both username and password.");
            }
        } else if (command[0].compare("/login") == 0) {
            if (command.size() == 3) {
                window_->AddOutput("Logging in...");
                window_->UpdateStatus("Logging in...");

                easemob::EMErrorPtr result = chatClient->login(command[1], command[2]);
                if(result->mErrorCode == EMError::EM_NO_ERROR) {
                    window_->AddOutput("login success");
                    mLogedin =  true;
                     // start to monitor the network state
#ifdef __linux__
                     if(monitor == nullptr) { 
                        monitor.reset(new thread([this]{
                            networkMonitor();
                        }));
                     }
#endif
                } else {
                    window_->AddOutput(result->mDescription);
                }
                loginUser = command[1];
            } else {
                window_->AddOutput("Need username and password.");
            }
        } else if(command[0].compare("/logout") == 0) {
            window_->AddOutput("Logging out...");
            window_->UpdateStatus("Logging out...");

            chatClient->logout();
            mLogedin = false;
            // stop network monitor
#ifdef __linux__
            if (monitor->joinable())
            {
                monitor->detach();
            }
#endif
            window_->AddOutput("Logged out");
            window_->UpdateStatus("Logged out");
        } else if (command[0].compare("/msg") == 0) {
            if (command.size() < 3) {
                window_->AddOutput("Need recipient and message...");
            } else {
                string to = command[1];
                auto msg_pos = command_string.find_first_of(" ");
                msg_pos = command_string.find_first_not_of(" ", msg_pos);
                msg_pos = command_string.find_first_of(" ", msg_pos);
                msg_pos = command_string.find_first_not_of(" ", msg_pos);
                easemob::EMTextMessageBodyPtr body =  easemob::EMTextMessageBodyPtr( new easemob::EMTextMessageBody(command_string.substr(msg_pos)));
                easemob::EMMessagePtr msg = easemob::EMMessage::createSendMessage(loginUser, to, body);
                easemob::EMCallbackPtr callback(new easemob::EMCallback(mHandle, [=]()->bool{
                    window_->AddOutput("Msg send success");
                    return true;
                }, [=](const easemob::EMErrorPtr error)->bool{
                    window_->AddOutput( "Send message failed: " + error->mDescription);
                    return true;
                }));
               msg->setCallback(callback);
                chatClient->getChatManager().sendMessage(msg);
                window_->AddOutput(msg->from() + " -> " + msg->to() + ": " + command_string.substr(msg_pos));
            }
        } else if (command[0].compare("/addcontact") == 0) {
            window_->AddOutput("add contact: " + command[1]);
            if (command.size() == 3) {
                easemob::EMError err;
                chatClient->getContactManager().inviteContact(command[1], command[2], err);
            } else {
               window_->AddOutput("Need user name and message");
            }

        } else if (command[0].compare("/listcontact") == 0) {
            window_->AddOutput("fetch the contact list...");
            easemob::EMError err;
            vector<string> contacts = chatClient->getContactManager().getContactsFromServer(err);
            if(contacts.size() > 0) {
                window_->AddOutput("my friend list: ");
                for(auto c: contacts) {
                     window_->AddOutput(c);
                }
            }else {
                window_->AddOutput("no friend, please add one");
            }
        } else if (command[0].compare("/deletecontact") == 0) {
            if (command.size() == 2) {
                window_->AddOutput("delete contact: ");
                easemob::EMError err;
				chatClient->getContactManager().deleteContact(command[1], err);
            }else {
                window_->AddOutput("Need contact name");
            }
        } else if (command[0].compare("/getblacklist") == 0) {
			window_->AddOutput("get blacklist ");
            easemob::EMError err;
			vector<string> blacklist = chatClient->getContactManager().getBlackListFromServer(err);
			for (string username : blacklist) {
				 window_->AddOutput(string("\t") + username);
			}
        } else if (command[0].compare("/addtoblacklist") == 0) {
            if (command.size() == 2) {
				window_->AddOutput("addToBlackList");
                easemob::EMError err;
				chatClient->getContactManager().addToBlackList(command[1], true, err);
			} else {
                window_->AddOutput("Need contact name");
            }
        } else if (command[0].compare("/removefromblacklist") == 0) {
            if (command.size() == 2) {
				window_->AddOutput("removeFromBlackList");
                easemob::EMError err;
				chatClient->getContactManager().removeFromBlackList(command[1], err);
			} else {
                window_->AddOutput("Need contact name");
            }
        } else if (command[0].compare("/acceptcontact") == 0) {
            if (command.size() == 2) {
				window_->AddOutput("acceptcontact: " + command[1]);
                easemob::EMError err;
				chatClient->getContactManager().acceptInvitation(command[1], err);
			} else {
                window_->AddOutput("Need contact name");
            }
        } else if (command[0].compare("/declinecontact") == 0) {
            if (command.size() == 2) {
				window_->AddOutput("declinecontact: " + command[1]);
                easemob::EMError err;
				chatClient->getContactManager().declineInvitation(command[1], err);
			} else {
                window_->AddOutput("Need contact name");
            }
          } else if (command[0].compare("/quit") == 0) {
            delete this;
        } else if (command[0].compare("/test") == 0) {
        
        } else if (command[0].compare("/voicecall") == 0){
            //TODO: voice call
            window_->AddOutput("make voice call...");
            
        }  else if (command[0].compare("/videocall") == 0){
            //TODO: video call
            window_->AddOutput("make video call...");
        } else {
            window_->AddOutput("Unkown command:");
            window_->AddOutput(command_string);
        }
    }
}

void Chat::Run()
{
    event_loop_->Start();
}

void Chat::CheckInput()
{
    char input = window_->GetInput();
    if (input == '\n') {
        HandleCommand(input_command_buffer_.str());
        input_command_buffer_.str("");
        input_command_buffer_.clear();
    } else if (input == '\0') {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    } else if (input == 127) { // backspace
        string s = input_command_buffer_.str();
        while (s.size() > 0) {
            char c = s.back();
            s.pop_back();

            // If we found an initial character, we're done
            if ((c & 0xC0) != 0x80) {
                break;
            }
        }
        input_command_buffer_.str("");
        input_command_buffer_.clear();
        input_command_buffer_ << s;
    } else {
        input_command_buffer_ << input;
    }
    event_loop_->AddEvent([this](){CheckInput();});
}

void Chat::Log(const string &message)
{
    log_file_ << message << endl;
    window_->AddLogMessage(message);
}

#ifdef __linux__
void Chat::networkMonitor()
{
    bool state = true;
    while(1) {
        if(!mLogedin) break;

        state = checkNetwork("eth0");
        if(!state && mNetState) {
            mNetState = state;
            window_->AddOutput(" checkNetwork: on->off");
            chatClient->onNetworkChanged(EMNetworkListener::NONE);
        }

        if(state && !mNetState) {
            mNetState = state;
            window_->AddOutput(" checkNetwork: off->on");
            chatClient->onNetworkChanged(EMNetworkListener::CABLE);
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}
#endif

} // namespace Demo
