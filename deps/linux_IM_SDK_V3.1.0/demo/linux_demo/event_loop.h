#ifndef EASEMOB_EASEMOB_EVENT_LOOP_THREAD_H_
#define EASEMOB_EASEMOB_EVENT_LOOP_THREAD_H_

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

namespace Demo {

class EventLoop {
public:
    void AddEvent(std::function<void()> event);
    void Start();
    void Stop();
    EventLoop() : running_(true) {}
private:
    std::mutex event_queue_lock_;
    std::condition_variable event_queue_signal_;
    std::queue<std::function<void()>> event_queue_;
    bool running_;
};

} // namespace easemob_internal

#endif // EASEMOB_EASEMOB_EVENT_LOOP_THREAD_H_
