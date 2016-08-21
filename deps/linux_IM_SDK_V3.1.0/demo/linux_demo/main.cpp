#include "chat.h"

int main()
{
    Demo::Chat *chat = new Demo::Chat(".", ".");
    chat->Run();
    //delete chat;
}
