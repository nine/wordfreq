#ifndef fileReader_h_INCLUDED
#define fileReader_h_INCLUDED

#include <future>
#include <mutex>
#include <string>

#include "queue.h"
#include "types.h"

class FileReader {
public:
  FileReader(
      Queue<std::string>& files, 
      StringFreqMap& histogram, 
      std::mutex &mx
    );
  virtual ~FileReader() noexcept = default;
  void operator()();

private:
  Queue<std::string>& files_;
  StringFreqMap& histogram_; 
  std::mutex &mx_;
};

#endif
