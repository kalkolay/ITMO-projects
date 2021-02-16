#pragma once

#include <chrono>
#include <sstream>
#include <fstream>
#include <filesystem>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace reports::data::utils
{
    template <typename T>
    std::string SerializeFromVectorToXML(const std::vector<T>& vec)
    {
        std::string result;
        boost::uuids::string_generator gen;
        std::string filename = to_string( gen("{01234567-89ab-cdef-0123-456789abcdef}") );
        std::ofstream out(filename);
        boost::archive::xml_oarchive xml_output_archive(out);
        xml_output_archive& BOOST_SERIALIZATION_NVP(vec);
        std::ostringstream ss;
        ss << out.rdbuf();
        result = ss.str();
        out.close();
        std::filesystem::remove(filename);
        return result;
    }

    template <typename T>
    std::vector<T> SerializeFromXMLToVector(const std::string& str)
    {
        std::vector<T> result;
        boost::uuids::string_generator gen;
        std::string filename = to_string( gen("{01234567-89ab-cdef-0123-456789abcdef}") );
        std::ofstream out(filename);
        out << str;
        out.close();
        std::ifstream in(filename);
        boost::archive::xml_iarchive xml_input_archive(in);
        xml_input_archive& BOOST_SERIALIZATION_NVP(result);
        in.close();
        std::filesystem::remove(filename);
        return result;
    }

    template <typename TP>
    std::time_t to_time_t(TP tp)
    {
        using namespace std::chrono;
        auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
                                                            + system_clock::now());
        return system_clock::to_time_t(sctp);
    }

    template <typename T>
    std::string time_to_string(T time)
    {
        std::time_t tt       = to_time_t(time);
        std::tm*    gmt      = std::gmtime(&tt);
        std::stringstream buffer;
        buffer << std::put_time(gmt, "%A, %d %B %Y %H:%M");
        return buffer.str();
    }
}