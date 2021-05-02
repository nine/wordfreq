#ifndef ciLess_H_INCLUDED
#define ciLess_H_INCLUDED

#include <string>

// case-insensitive less-than operation
// in order to provide case-insensitive sorted std::map<std:string,T>

struct CiLess {
  // case-independent (ci) compare_less binary function
  struct NocaseCompare {
    bool operator() (const unsigned char& c1, const unsigned char& c2) const{ 
      return tolower (c1) < tolower (c2); 
    }
  };
  bool operator() (std::string const& s1, std::string const& s2) const {
    return std::lexicographical_compare
      (s1.begin (), s1.end (),   // source range
       s2.begin (), s2.end (),   // dest range
       NocaseCompare ());        // comparison
  }
};

#endif
