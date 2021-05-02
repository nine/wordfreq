// wordfreq
// Programmierbeispiel C++
// Erwin Nindl, 01.07.2014
// Email: <erwin@nindl.eu>


#include "file_reader.h"

#include <iostream>
#include <fstream>


FileReader::FileReader(
    Queue<std::string>& files,
    StringFreqMap& histogram,
    std::mutex &mx) :
  files_(files),
  histogram_(histogram),
  mx_(mx)
{
}


void FileReader::operator()() {
  try {
    StringFreqMap hist;
    while (true) {
      auto in_file = files_.pop();
      if (!in_file)
        break;

      std::string word;

      std::ifstream in_stream;
      in_stream.open(in_file.value());
      if (!in_stream.is_open())
        throw std::runtime_error("Failed opening file");

      while( in_stream >> word ) {    // should return single words
        hist[word]++;        // initialized with 0 if key not found
      }
      in_stream.close();
    }

    std::lock_guard<std::mutex> const scoped_lock(mx_);
    for (auto const& it : hist) {
      if ( histogram_[it.first] )
        histogram_[it.first] += it.second;
      else
        histogram_[it.first] = it.second;
    }
  } catch (...) {
    std::lock_guard<std::mutex> const l(g_mutex);
    g_exceptions_transferred.push_back(std::current_exception());
    return;
  }
}

//eof
