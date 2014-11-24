// wordfreq
// für Anton Paar Shapetec
// Erwin Nindl, 01.07.2014
// Email: <erwin@nindl.eu>


#include "fileReader.h"

// static 
boost::mutex FileReader::mx_;

FileReader::FileReader(std::string file, StringFreqMap* histogram) : 
  file_(file), histogram_(histogram) {
}

void FileReader::operator()() {
  try {
    std::string word;

    std::ifstream in_stream;
    in_stream.open(file_.c_str());

    if(!in_stream.is_open()) {
      throw MyException("Error opening file", E_FILE);
    }
    while( in_stream >> word ) {    // should return single words
      boost::mutex::scoped_lock scoped_lock(mx_);
      (*histogram_)[word]++;        // initialized with 0 if key not found
    }
    in_stream.close();
  }
  catch(std::exception& e) {
    // exception has to be transferred to main program 
    // obtain exclusive access to g_exceptions_transferred
    std::lock_guard<std::mutex> lock(g_mutex);
    // store in global exception references
    g_exceptions_transferred.push_back(std::current_exception());
    return; // implicitly terminate this thread.
  }
  // normal exit
}

//eof
