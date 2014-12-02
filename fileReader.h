#ifndef fileReader_h_INCLUDED
#define fileReader_h_INCLUDED


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <string>
#include <map>
#include <mutex>

#include "myException.h"
#include "main.h"

class FileReader {
public:
  FileReader(std::string file, StringFreqMap* histogram);
  ~FileReader() {};
  void operator()();

private:
  static std::mutex mx_;    // shared mutex
  std::string file_;
  StringFreqMap* histogram_; 
};

#endif
