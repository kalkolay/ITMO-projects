#include "Product.h"

#include <utility>

namespace shop_manager::entities
{
    Product::Product(std::string name)
        : m_name( std::move(name) )
    {
        boost::uuids::random_generator uuid_gen;
        m_id = uuid_gen();
    }

    productID_t Product::GetId()
    {
        return m_id;
    }

    std::string Product::GetName()
    {
        return m_name;
    }
}