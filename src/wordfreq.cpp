// wordfreq
// Programmierbeispiel C++
// Erwin Nindl, 01.07.2014
// Email: <erwin@nindl.eu>

#include "types.h"
#include "myException.h"
#include "file_reader.h"
#include "queue.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <optional>
#include <fstream>
#include <mutex>
#include <thread>
#include <set>
#include <deque>

#include <lyra/lyra.hpp>


// global, for multi-thread exception handling
std::vector<std::exception_ptr> g_exceptions_transferred; // global "references" to thrown exceptions
std::mutex g_mutex; // mutex to protect the above exceptions vector


static std::optional<std::vector<std::string>>
parse_args(int argc, char** argv)
{
  bool show_help;
  std::vector<std::string> in_files;
  auto cli = lyra::cli()
    | lyra::help(show_help)
    | lyra::opt(in_files, "files")
          ["-f"]["--files"]("Text files (required)");
  auto result = cli.parse({ argc, argv });
  if (!result) {
    std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
    std::cerr << cli << "\n";
    return std::nullopt;
  }
  if (show_help) {
    std::cout << cli << "\n";
    return std::nullopt;
  }
  return in_files;
}

int main(int argc, char** argv)
{

  g_exceptions_transferred.clear(); // establish no exception state

  auto const args = parse_args(argc, argv);
  std::vector<std::string> const in_files{ args ? args.value() : std::vector<std::string>{} };

  try {
    Queue<std::string> in_file_queue{ std::cbegin(in_files), std::cend(in_files) };
    StringFreqMap histogram;

    // one reader-thread per input-file
    std::vector<FileReader> readers;
    std::vector<std::thread> reader_threads;
    std::mutex mx;
    std::uint32_t const num_threads{
      std::min(std::thread::hardware_concurrency(), static_cast<std::uint32_t>(in_files.size())) };
    for (std::uint32_t idx = 0; idx < num_threads; idx++ ) {
      readers.emplace_back(in_file_queue, histogram, mx);
      std::thread reader_thread(readers.back());
      reader_threads.push_back(std::move(reader_thread));
    }
    // join the threads with the main thread
    for( auto &t: reader_threads ) {
      t.join();
    }
    // handle the (first) transferred exceptions if any
    for (const std::exception_ptr& ep : g_exceptions_transferred) {
      if( ep!=nullptr ) {
        std::rethrow_exception(ep);
      }
    }

    // generate output
    // header
    std::cout << std::setw(23) << std::left << "word" << std::setw(23) << "frequency" << std::endl;
    // table
    for( auto const &it : histogram) {
      std::cout << std::setw(23) << std::left << it.first << std::setw(23) << it.second << std::endl;
    }
  }
  catch(std::exception& e) {
    std::cerr << "Error: "
      << e.what() << ", application will now exit" << std::endl;
    return E_UNHANDLED_EXCEPTION;
  }

  return E_SUCCESS;
}


