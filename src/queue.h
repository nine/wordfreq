#ifndef QUEUE_H_
#define QUEUE_H_

#include <deque>
#include <initializer_list>
#include <mutex>
#include <optional>


template <typename T>
class Queue {
public:
  Queue() = default;
  template< class InputIt >
  Queue(InputIt first, InputIt last) : queue_(first, last) {}
  Queue(std::initializer_list<T> l) : queue_(l) {}
  Queue(const Queue<T> &) = delete ;
  Queue& operator=(const Queue<T> &) = delete ;
  Queue(Queue<T>&& other) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_ = std::move(other.queue_);
  }
  virtual ~Queue() noexcept = default;

  std::size_t size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
  }

  std::optional<T> pop() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) {
      return {};
    }
    T const tmp = queue_.front();
    queue_.pop_back();
    return tmp;
  }

private:
  bool empty() const {
    return queue_.empty();
  }
  
  std::deque<T> queue_;
  mutable std::mutex mutex_;
};

#endif
