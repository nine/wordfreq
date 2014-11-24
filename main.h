#ifndef main_h_INCLUDED
#define main_h_INCLUDED

#include <vector>
#include <list>
#include <string>
#include <mutex>

//#include "ciLess.h" // for case-insensitive string compare

typedef std::vector<std::string> StringVector;
typedef std::list<std::string> StringList;
typedef std::map<std::string, uint32_t> StringFreqMap; 
//typedef std::map<std::string, uint32_t, CiLess> StringFreqMap; // case-insensitive map

// global
extern std::vector<std::exception_ptr> g_exceptions_transferred; // global "references" to thrown exceptions
extern std::mutex g_mutex; // mutex to protect the above exceptions vector

#endif
