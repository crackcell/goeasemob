#ifndef DEMO_CHAT_H_
#define DEMO_CHAT_H_

#include "emclient.h"
#include "emchatmanager_listener.h"
#include "emcallback.h"
#include "window.h"
#include "event_loop.h"

#include <sstream>
#include <string>
#include <fstream>
#include <thread>

namespace Demo {

class Chat : public easemob::EMChatManagerListener, public easemob::EMConnectionListener {
public:
    Chat(const std::string &resourcePath, const std::string &workPath);
    ~Chat();

    virtual void onReceiveMessages(const easemob::EMMessageList &messages);

    void onConnect();
    void onDisconnect(easemob::EMErrorPtr error);
    void onPong();

    void Run();
private:

    void CheckInput();

    void Log(const std::string &message);
    void HandleCommand(std::string command);
    void networkMonitor();

    easemob::EMClient *chatClient;
    Window *window_;

    std::stringstream input_command_buffer_;

    std::ofstream log_file_;
    std::string loginUser;

    std::unique_ptr<EventLoop> event_loop_;
    easemob::EMCallbackObserverHandle mHandle;
    
#ifdef __linux__
    std::unique_ptr<std::thread> monitor;
    bool mNetState;
#endif
    bool mLogedin;
};


} // namespace Demo

#endif // DEMO_WINDOW_H_
