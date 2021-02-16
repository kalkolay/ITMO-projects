#pragma once

#include "ProductWrapper.h"

namespace shop_manager::entities
{
    using shopID_t = boost::uuids::uuid;

    class Shop : public ProductWrapper
    {
    public:
        /// 1. Создать магазин
        Shop() = default;
        Shop(std::string name,
             std::string address);

        shopID_t    GetId     ();
        std::string GetName   ();
        std::string GetAddress();

        [[nodiscard]] ProductsCluster GetProductsCluster() const;

        Product GetProductById(productID_t productId);

        /// 3. Завезти партию товаров в магазин
        void AddProducts(ProductWrapperArray& productWrapperArray);

        /// 6. Купить партию товаров в магазине
        double BuyProducts(ProductWrapperArray& productWrapperArray);

        double     GetPrice   (Product& product);
        quantity_t GetQuantity(Product& product);

    private:
        shopID_t        m_id;
        std::string     m_name;
        std::string     m_address;
        ProductsCluster m_productsCluster;
    };

    using ShopsCluster = std::map<shopID_t, Shop>;
}