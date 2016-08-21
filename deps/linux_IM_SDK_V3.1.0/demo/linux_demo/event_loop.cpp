#include "event_loop.h"

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

namespace Demo {

using std::function;
using std::lock_guard;
using std::move;
using std::mutex;
using std::unique_lock;
using std::queue;

void EventLoop::Start()
{
    running_ = true;
    while (running_) {
        function<void()> event;
        {
            unique_lock<mutex> queue_lock(event_queue_lock_);
            if (event_queue_.size() == 0) {
                event_queue_signal_.wait(queue_lock);
                if (!running_) {
                    break;
                }
            }
            event = move(event_queue_.front());
            event_queue_.pop();
        }
        event();
    }
}

void EventLoop::Stop()
{
    running_ = false;
    {
        lock_guard<mutex> queue_lock(event_queue_lock_);
        if (event_queue_.size() > 0) {
            event_queue_ = queue<function<void()>>();
        }
    }
    event_queue_signal_.notify_one();
}

void EventLoop::AddEvent(function<void()> event)
{
    {
        lock_guard<mutex> queue_lock(event_queue_lock_);
        event_queue_.push(event);
    }
    event_queue_signal_.notify_one();
}

} // namespace easemob_internal
