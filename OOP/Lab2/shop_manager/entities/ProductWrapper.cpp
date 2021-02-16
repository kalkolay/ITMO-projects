#include "ProductWrapper.h"

namespace shop_manager::entities
{
    ProductWrapper::ProductWrapper(const Product& product,
                                   double         price,
                                   quantity_t     quantity)
        : m_product (product),
          m_price   (price),
          m_quantity(quantity)
    {}

    Product ProductWrapper::GetProduct()
    {
        return m_product;
    }

    double ProductWrapper::GetPrice()
    {
        return m_price;
    }

    quantity_t ProductWrapper::GetQuantity()
    {
        return m_quantity;
    }

    void ProductWrapper::SetPrice(ProductWrapper& productWrapper,
                                  double          newPrice)
    {
        productWrapper.m_price = newPrice;
    }

    void ProductWrapper::SetQuantity(ProductWrapper& productWrapper,
                                     quantity_t      newQuantity)
    {
        productWrapper.m_quantity = newQuantity;
    }
}