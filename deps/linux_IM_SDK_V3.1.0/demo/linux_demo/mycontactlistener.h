#ifndef MYCONTACTLISTENER_H_
#define MYCONTACTLISTENER_H_

#include <string>
#include <functional>
#include <emcontactlistener.h>

namespace Demo {
    /**
     * register & remove contact listener
     */
    class MyContactListener : public easemob::EMContactListener {
    public:

        MyContactListener(const std::function<void(const std::string &)> &func) { logFunc = func; }

        virtual void onContactAdded(const std::string &username) {
            logFunc("onContactAdded");
            logFunc(std::string("\t") + username);
        }

        virtual void onContactDeleted(const std::string &username) {
            logFunc("onContactDeleted");
            logFunc(std::string("\t") + username);
        }

        virtual void onContactInvited(const std::string &username, std::string &reason) {
            logFunc("onContactInvited");
            logFunc(std::string("\t") + username + "   \treason:" + reason);
        }

        virtual void onContactAgreed(const std::string &username) {
            logFunc(std::string("onContactAgreed:\t") + username);
        }

        virtual void onContactRefused(const std::string &username) {
            logFunc(std::string("onContactRefused:\t") + username);
        }
    private:
        std::function<void(const std::string&)> logFunc;
    };
 }
 
#endif

