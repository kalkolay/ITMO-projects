#pragma once

#include <string>
#include <map>

namespace ini_parser
{
    /**
     * Class for parsing INI files
     */
    class INIParser
    {
    public:
        /**
         * @brief Parses an INI file.
         *
         * If there is a problem in file subsystem, an INIReaderException will be thrown.
         * If a file has wrong format, an INIFormatException will be thrown.
         */
        static INIParser Parse(const std::string& filename);

        /**
         * @brief Tries to get an option with integer type.
         *
         * If the section name/option name does not exist, an InvalidOptionException will be thrown.
         * If an option cannot be casted to integer type, an InvalidTypeException will be thrown.
         */
        [[nodiscard]] int TryGetIntegerOption(const std::string& sectionName,
                                              const std::string& optionName) const;

        /**
         * @brief Tries to get an option with double type.
         *
         * If the section name/option name does not exist, an InvalidOptionException will be thrown.
         * If an option cannot be casted to double type, an InvalidTypeException will be thrown.
         */
        [[nodiscard]] double TryGetDoubleOption(const std::string& sectionName,
                                                const std::string& optionName) const;

        /**
         * @brief Tries to get an option with string type.
         *
         * If the section name/option name does not exist, an InvalidOptionException will be thrown.
         */
        [[nodiscard]] std::string TryGetStringOption(const std::string& sectionName,
                                                     const std::string& optionName) const;

    private:
        // key --> section name
        // value --> map (key --> option name, value --> option value)
        std::map<std::string, std::map<std::string, std::string>> data;

        /**
         * @brief Checks if a section exists.
         */
        [[nodiscard]] bool HasSection(const std::string& sectionName) const;

        /**
         * @brief Checks if an option exists.
         */
        [[nodiscard]] bool HasOption(const std::string& sectionName,
                                     const std::string& optionName) const;

        /**
         * @brief Adds a new section.
         *
         * If the section name exists, a DuplicateSectionException will be thrown.
         */
        void AddSection(const std::string& sectionName);

        /**
         * @brief Adds a new option.
         *
         * If the section name does not exist, an InvalidSectionException will be thrown.
         * If the option name exists, a DuplicateOptionException will be thrown.
         */
        void AddOption(const std::string& sectionName,
                       const std::string& optionName,
                       const std::string& optionValue);

        /**
         * @brief Throws InvalidSectionName if section name doesn't exist.
         */
        inline void ValidateSection(const std::string& sectionName) const;

        /**
         * @brief Throws InvalidOptionName if section name/option name doesn't exist.
         */
        inline void ValidateOption(const std::string& sectionName,
                                   const std::string& optionName) const;
    };
}