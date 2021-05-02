#ifndef TYPES_H_ 
#define TYPES_H_

#include <map>
#include <mutex>
#include <string>
#include <vector>

using StringFreqMap = std::map<std::string, uint32_t>;

// global
extern std::vector<std::exception_ptr> g_exceptions_transferred; // global "references" to thrown exceptions
extern std::mutex g_mutex; // mutex to protect the above exceptions vector

#endif
