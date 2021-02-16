#pragma once

#include <initializer_list>

#include "entities/Shop.h"

using namespace shop_manager::entities;

namespace shop_manager
{
    class ShopManager : public ProductWrapper
    {
    public:
        ShopManager(const ShopManager&)             = delete;
        ShopManager& operator =(const ShopManager&) = delete;

        explicit ShopManager(Shop& shop);
        ShopManager(std::initializer_list<Shop>& shops);

        Shop& GetShopById(shopID_t shopId);

        ShopsCluster& GetShopsCluster();

        static void SetPrice   (Shop&       shop,
                                productID_t productId,
                                double      newPrice);
        static void SetQuantity(Shop&       shop,
                                productID_t productId,
                                quantity_t  newQuantity);

        /// 4. Найти магазин, в котором определенный товар самый дешевый
        shopID_t FindCheapestProduct(productID_t productId);

        /// 5. Понять, какие товары можно купить в магазине на некоторую сумму
        static ProductsCluster FindProductsByPrice(Shop&  shop,
                                                   double price);

        /// 7.
        /// Найти, в каком магазине партия товаров (набор товар-количество) имеет наименьшую сумму (в целом).
        /// Например, «в каком магазине дешевле всего купить 10 гвоздей и 20 шурупов».
        /// Наличие товара в магазинах учитывается!
        shopID_t FindMinimalTotalPrice(std::vector<std::pair<productID_t, quantity_t>>& shipment);

    private:
        ShopsCluster m_shopsCluster;
    };
}