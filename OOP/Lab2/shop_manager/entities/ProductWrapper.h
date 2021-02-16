#pragma once

#include <cstdint>
#include <map>
#include <vector>

#include "Product.h"

namespace shop_manager::entities
{
    using quantity_t = uint32_t;

    class ProductWrapper
    {
    public:
        ProductWrapper() = default;

        ProductWrapper(const Product& product,
                       double         price,
                       quantity_t     quantity);

        ProductWrapper(const ProductWrapper&) = default;
        ProductWrapper& operator =(const ProductWrapper&) = default;

        Product    GetProduct ();
        double     GetPrice   ();
        quantity_t GetQuantity();

    private:
        Product    m_product;
        double     m_price;
        quantity_t m_quantity;

    protected:
        static void SetPrice   (ProductWrapper& productWrapper,
                                double          newPrice);
        static void SetQuantity(ProductWrapper& productWrapper,
                                quantity_t      newQuantity);
    };

    using ProductsCluster     = std::map<productID_t, ProductWrapper>;
    using ProductWrapperArray = std::vector<ProductWrapper>;
}