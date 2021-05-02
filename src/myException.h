#ifndef myException_h_INCLUDED
#define myException_h_INCLUDED

#include <string>
#include <stdexcept>
#include <mutex>

// error codes
namespace
{
  const int16_t E_SUCCESS = 0;
  const int16_t E_OPTIONS = 1;
  const int16_t E_FILE = 2;
  const int16_t E_PARAMS = 3;
  const int16_t E_UNHANDLED_EXCEPTION = 23;
} // namespace 


class MyException : public std::exception {
public:

  MyException(std::string m = "Exception! ", int16_t err_num = 0) : msg_(m), error_number_(err_num) {};
  ~MyException() throw () {};

  const char* what() const throw () {
    return msg_.c_str();
  };

  int16_t getErrorNumber() {
    return error_number_;
  };
private:
  std::string msg_;
  int16_t error_number_;
};

#endif
