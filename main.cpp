// wordfreq
// Programmierbeispiel C++
// Erwin Nindl, 01.07.2014
// Email: <erwin@nindl.eu>

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <mutex>
#include <thread>

#include "boost/program_options.hpp" 

#include "main.h"
#include "myException.h"
#include "fileReader.h"


// global, for multi-thread exception handling
std::vector<std::exception_ptr> g_exceptions_transferred; // global "references" to thrown exceptions
std::mutex g_mutex; // mutex to protect the above exceptions vector


void parseProgramOptions(int argc, char** argv, StringVector* files);



int main(int argc, char** argv) 
{ 
  StringVector in_files;

  g_exceptions_transferred.clear(); // establish no exception state

  try 
  { 
    parseProgramOptions(argc, argv, &in_files);

    StringVector lines;
    StringFreqMap histogram;
   
    // one reader-thread per input-file
    std::vector<std::thread> reader_threads;
    for( auto it = in_files.begin() ; it != in_files.end(); ++it ) {
      FileReader reader(*it, &histogram);
      reader_threads.push_back(std::thread(reader));
    }
    // join the threads with the main thread
    for( auto &t: reader_threads ) {
      t.join();
    }
    // handle the (first) transferred exceptions if any
    for( const std::exception_ptr& ep : g_exceptions_transferred ) {
      if( ep!=nullptr ) { 
        std::rethrow_exception(ep);
      }
    }

    // generate output
    // header
    std::cout << std::setw(23) << std::left << "Wort" << std::setw(23) << "Anzahl" << std::endl;
    // table
    for( auto it = histogram.begin(); it != histogram.end(); it++ ) {
      std::cout << std::setw(23) << std::left << it->first << std::setw(23) << it->second << std::endl;
    }
  }
  catch(MyException& e) {
    if(e.getErrorNumber() != E_SUCCESS) {
      std::cerr << e.what() << std::endl;
    }
    return e.getErrorNumber();
  }
  catch(std::exception& e) { 
    std::cerr << "Unhandled exception reached the top of main: " 
      << e.what() << ", application will now exit" << std::endl; 
    return E_UNHANDLED_EXCEPTION; 
  } 
  
  return E_SUCCESS;
}



void parseProgramOptions(int argc, char** argv, StringVector* files) {
  // parse program options
  namespace po = boost::program_options; 
  po::options_description desc("Options"); 
  desc.add_options() 
    ("help,h", "Print help messages")
    ("files,f", po::value<StringVector>(files)->multitoken(), "Text files (required)");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);

  if(vm.count("help")) {
    std::cout << desc << std::endl;
    throw MyException("", E_SUCCESS);
  }
  po::notify(vm);    

  if(!vm.count("files")) {
    throw MyException("Option --files missing", E_PARAMS );
  }
}

