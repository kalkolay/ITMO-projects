#ifndef HW11_BADFROMSTRINGEXCEPTION_H
#define HW11_BADFROMSTRINGEXCEPTION_H


#include <exception>
#include <string>

class BadFromStringException : public std::exception
{
public:
    explicit BadFromStringException(std::string);
    ~BadFromStringException() override = default;
    const char* what() const noexcept override;

    const std::string message;
};



#endif //HW11_BADFROMSTRINGEXCEPTION_H
