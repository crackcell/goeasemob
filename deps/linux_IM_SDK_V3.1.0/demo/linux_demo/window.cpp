#include "window.h"

#include <sstream>
#include <string>
#include <vector>

namespace Demo {

using std::string;
using std::stringstream;
using std::vector;

Window::Window()
{
    initscr();
    if (has_colors() == FALSE) {
        return;
    }
    main_first_line_ = true;
    log_first_line_ = true;
    start_color();
    use_default_colors();
    refresh();

    init_pair(1, COLOR_YELLOW, COLOR_BLUE);

    title_window_ = newwin(1, COLS, 0, 0);
    main_window_ = newwin(LINES-13, COLS, 1, 0);
    scrollok(main_window_, TRUE);
    status_bar_window_ = newwin(1, COLS, LINES-2, 0);
    input_window_ = newwin(1, COLS, LINES-1, 0);
    nodelay(input_window_,TRUE);
    log_window_ = newwin(10, COLS, LINES-12, 0);
    scrollok(log_window_, TRUE);

    wbkgd(title_window_, COLOR_PAIR(1));
    wbkgd(status_bar_window_, COLOR_PAIR(1));

    noecho();

    wrefresh(main_window_);
    wrefresh(status_bar_window_);
    wrefresh(title_window_);
    wrefresh(log_window_);
    wmove(input_window_, 0, 0);
    wrefresh(input_window_);
}

Window::~Window()
{
    endwin();
}

void Window::SetTitle(const string &title)
{
    werase(title_window_);
    waddstr(title_window_, title.c_str());
    wrefresh(title_window_);
    wmove(input_window_, 0, 0);
    wrefresh(input_window_);
}

void Window::UpdateStatus(const string &status)
{
    werase(status_bar_window_);
    waddstr(status_bar_window_, status.c_str());
    wrefresh(status_bar_window_);
    wmove(input_window_, 0, 0);
    wrefresh(input_window_);
}

void Window::AddOutput(const string &output)
{
    if (main_first_line_) {
        main_first_line_ = false;
    } else {
        waddstr(main_window_, "\n");
    }
    waddstr(main_window_, output.c_str());
    wrefresh(main_window_);
    wmove(input_window_, 0, 0);
    wrefresh(input_window_);
}

void Window::AddLogMessage(const string &output)
{
    if (log_first_line_) {
        log_first_line_ = false;
    } else {
        waddstr(log_window_, "\n");
    }
    waddstr(log_window_, output.c_str());
    wrefresh(log_window_);
    wmove(input_window_, 0, 0);
    wrefresh(input_window_);
}

char Window::GetInput()
{
    int input = wgetch(input_window_);
    if (input == ERR) {
        return '\0';
    } else if (input == '\n') {
        werase(input_window_);
        wmove(input_window_, 0, 0);
        wrefresh(input_window_);
        return (char) input;
    } else {
        if (input == 127) { // backspace
            int y, x;
            getyx(input_window_, y, x);
            if (x > 0) {
                mvwdelch(input_window_, y, --x);
            }
            wrefresh(input_window_);
        } else {
            waddch(input_window_, input);
            wrefresh(input_window_);
        }
        return (char) input;
    }
}

} // namespace Demo
