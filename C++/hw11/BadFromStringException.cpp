#include "BadFromStringException.h"
#include <string>

const char *BadFromStringException::what() const noexcept {
    return message.c_str();
}

BadFromStringException::BadFromStringException(const std::string data) : message(data) {}