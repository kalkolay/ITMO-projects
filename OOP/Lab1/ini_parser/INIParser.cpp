#include "INIParser.h"
#include "utils/Utilities.h"
#include "exceptions/Exceptions.h"

#include <fstream>

namespace ini_parser
{
    bool INIParser::HasSection(const std::string& sectionName) const
    {
        return data.find(sectionName) != data.end();
    }

    bool INIParser::HasOption(const std::string& sectionName,
                              const std::string& optionName) const
    {
        if ( !HasSection(sectionName) )
            return false;
        const std::map<std::string, std::string>& options = data.at(sectionName);
        return options.find(optionName) != options.end();
    }

    void INIParser::ValidateSection(const std::string& sectionName) const
    {
        if ( !HasSection(sectionName) )
        {
            std::string msg = "Section (" + sectionName + ") not found";
            throw exceptions::InvalidSectionException( msg.c_str() );
        }
    }

    void INIParser::ValidateOption(const std::string& sectionName,
                                   const std::string& optionName) const
    {
        if ( !HasOption(sectionName, optionName) )
        {
            std::string msg = "Section (" + sectionName + "), Option (" + optionName + ") not found";
            throw exceptions::InvalidOptionException( msg.c_str() );
        }
    }

    void INIParser::AddSection(const std::string& sectionName)
    {
        if ( HasSection(sectionName) )
        {
            std::string msg = "Duplicate section (" + sectionName + ") found";
            throw exceptions::DuplicateSectionException( msg.c_str() );
        }
        std::map<std::string, std::string> emptyMap;
        data[sectionName] = emptyMap;
    }

    void INIParser::AddOption(const std::string& sectionName,
                              const std::string& optionName,
                              const std::string& optionValue)
    {
        ValidateSection(sectionName);

        std::map<std::string, std::string>& options = data[sectionName];
        if ( HasOption(sectionName, optionName) )
        {
            std::string msg = "Duplicate option (" + optionName + ") found";
            throw exceptions::DuplicateOptionException( msg.c_str() );
        }
        options[optionName] = optionValue;
    }

    INIParser INIParser::Parse(const std::string& filename)
    {
        if (filename.substr(filename.find_last_of('.') + 1) != "ini")
        {
            std::string msg = "File " + filename + " has wrong format";
            throw exceptions::INIFormatException( msg.c_str() );
        }
        std::ifstream in;
        in.open(filename.c_str(), std::ios::binary);
        if ( !in.is_open() )
        {
            std::string msg = "Unable to read " + filename;
            throw exceptions::INIReaderException( msg.c_str() );
        }

        INIParser parser;
        std::string section;
        try
        {
            std::string line;
            while ( getline(in, line) )
            {
                if ( utils::IsEmptyLine(line) || utils::IsComment(line) ) {}
                else if ( utils::IsSection(line) )
                {
                    section = utils::ParseSection(line);
                    parser.AddSection(section);
                }
                else if ( utils::IsOption(line) )
                {
                    std::pair<std::string, std::string> option = utils::ParseOption(line);
                    parser.AddOption(section, option.first, option.second);
                }
                else
                {
                    std::string msg = "Invalid line: " + line;
                    throw exceptions::INIReaderException( msg.c_str() );
                }
            }
            in.close();
        }
        catch (...)
        {
            in.close();
            throw;
        }

        return parser;
    }

    std::string INIParser::TryGetStringOption(const std::string& sectionName,
                                              const std::string& optionName) const
    {
        ValidateOption(sectionName, optionName);

        const std::map<std::string, std::string>& options = data.at(sectionName);
        return options.at(optionName);
    }

    int INIParser::TryGetIntegerOption(const std::string& sectionName,
                                       const std::string& optionName) const
    {
        const std::string& value = TryGetStringOption(sectionName, optionName);
        try
        {
            return std::stoi(value);
        }
        catch (std::invalid_argument&)
        {
            std::string msg = "Invalid type: cannot cast \"" + value + "\" to int";
            throw exceptions::InvalidTypeException( msg.c_str() );
        }
    }

    double INIParser::TryGetDoubleOption(const std::string& sectionName,
                                         const std::string& optionName) const
    {
        const std::string& value = TryGetStringOption(sectionName, optionName);
        try
        {
            return std::stod(value);
        }
        catch (std::invalid_argument&)
        {
            std::string msg = "Invalid type: cannot cast \"" + value + "\" to double";
            throw exceptions::InvalidTypeException( msg.c_str() );
        }
    }
}
