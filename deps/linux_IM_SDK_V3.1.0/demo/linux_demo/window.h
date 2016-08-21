#ifndef DEMO_WINDOW_H_
#define DEMO_WINDOW_H_

#include <string>
#include <utility>
#include <vector>

#include <ncurses.h>

namespace Demo {

class Window {
public:
    void UpdateStatus(const std::string &status);
    void SetTitle(const std::string &title);
    void AddOutput(const std::string &output);
    void AddLogMessage(const std::string &message);

    char GetInput();

    Window();
    ~Window();
private:
    bool main_first_line_;
    bool log_first_line_;
    WINDOW *main_window_;
    WINDOW *title_window_;
    WINDOW *status_bar_window_;
    WINDOW *input_window_;
    WINDOW *log_window_;
};

} // namespace Demo

#endif // DEMO_WINDOW_H_
