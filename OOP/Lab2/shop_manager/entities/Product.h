#pragma once

#include <string>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace shop_manager::entities
{
    using productID_t = boost::uuids::uuid;

    class Product
    {
    public:
        /// 2. Создать товар
        Product() = default;
        Product(const Product& other) = default;
        explicit Product(std::string name);

        productID_t GetId  ();
        std::string GetName();

    private:
        productID_t m_id;
        std::string m_name;
    };
}