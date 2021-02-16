#pragma once

#include <string>

namespace ini_parser::utils
{
    /**
     * @brief Left trims a string.
     * This function doesn't modify the given str.
     */
    std::string LeftTrim(const std::string& str);

    /**
     * @brief Right trims a string.
     * This function doesn't modify the given str.
     */
    std::string RightTrim(const std::string& str);

    /**
     * @brief Trims a string (perform a left and right trims).
     * This function doesn't modify the given str.
     */
    std::string Trim(const std::string& str);

    /**
     * @brief Is a given string a section?
     * A section must be in the following format: [SECTION]
     */
    bool IsSection(const std::string& str);

    /**
     * @brief Parses a given string to get a section name.
     * ParseSection assumes a given string has a correct format.
     */
    std::string ParseSection(const std::string& str);

    /**
     * @brief Is a given string an option?
     * An option must be in the following format: key=value
     */
    bool IsOption(const std::string& str);

    /**
     * @brief Parses a given option into a pair of key and value.
     * ParseOption assumes a given string has a correct format.
     */
    std::pair<std::string, std::string> ParseOption(const std::string& str);

    /**
     * @brief Is a given string a comment?
     * A comment starts with ;
     */
    bool IsComment(const std::string& str);

    /**
     * @brief Is a given string empty?
     */
    bool IsEmptyLine(const std::string& str);
}