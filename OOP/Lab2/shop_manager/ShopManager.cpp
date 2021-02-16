#include "ShopManager.h"

#include <cmath>
#include <limits>

namespace shop_manager
{
    ShopManager::ShopManager(Shop& shop)
    {
        m_shopsCluster.insert( { shop.GetId(), shop } );
    }

    ShopManager::ShopManager(std::initializer_list<Shop>& shops)
    {
        for (size_t i = 0; i < shops.size(); ++i)
        {
            Shop shop = shops.begin()[i];
            m_shopsCluster.insert( { shop.GetId(), shop } );
        }
    }

    Shop& ShopManager::GetShopById(shopID_t shopId)
    {
        return m_shopsCluster[shopId];
    }

    ShopsCluster& ShopManager::GetShopsCluster()
    {
        return m_shopsCluster;
    }

    void ShopManager::SetPrice(Shop&       shop,
                               productID_t productId,
                               double      newPrice)
    {
        ProductWrapper& productWrapper = shop.GetProductsCluster()[productId];
        entities::ProductWrapper::SetPrice(productWrapper, newPrice);
    }

    void ShopManager::SetQuantity(Shop&       shop,
                                  productID_t productId,
                                  quantity_t  newQuantity)
    {
        ProductWrapper& productWrapper = shop.GetProductsCluster()[productId];
        entities::ProductWrapper::SetQuantity(productWrapper, newQuantity);
    }

    shopID_t ShopManager::FindCheapestProduct(productID_t productId)
    {
        shopID_t shopId;
        double minPrice = std::numeric_limits<double>::max();
        for (const auto& it : m_shopsCluster)
        {
            ProductsCluster currentProductCluster = it.second.GetProductsCluster();
            double currentPrice = currentProductCluster[productId].GetPrice();
            if (currentPrice < minPrice)
            {
                minPrice = currentPrice;
                shopId   = it.first;
            }
        }
        return shopId;
    }

    /// 5. Понять, какие товары можно купить в магазине на некоторую сумму
    ProductsCluster ShopManager::FindProductsByPrice(Shop&  shop,
                                                     double price)
    {
        ProductsCluster result;
        ProductsCluster productsCluster = shop.GetProductsCluster();
        for (auto& it : productsCluster)
        {
            int possibleQuantity = std::floor( price / it.second.GetPrice() );
            if ( possibleQuantity > 0 && possibleQuantity <= it.second.GetQuantity() )
            {
                ProductWrapper productWrapper = it.second;
                entities::ProductWrapper::SetQuantity(productWrapper, possibleQuantity);
                result.insert( { it.first, productWrapper } );
            }
        }
        return result;
    }

    /// 7.
    /// Найти, в каком магазине партия товаров (набор товар-количество) имеет наименьшую сумму (в целом).
    /// Например, «в каком магазине дешевле всего купить 10 гвоздей и 20 шурупов».
    /// Наличие товара в магазинах учитывается!
    shopID_t ShopManager::FindMinimalTotalPrice(std::vector<std::pair<productID_t, quantity_t>>& shipment)
    {
        shopID_t shopId;
        double minimalTotalPrice = std::numeric_limits<double>::max();
        for (auto &it : m_shopsCluster)
        {
            double currentTotalPrice = 0;
            ProductsCluster productsCluster = it.second.GetProductsCluster();
            for (auto &elem : shipment)
            {
                ProductWrapper productWrapper = productsCluster[elem.first];
                if (productWrapper.GetQuantity() >= elem.second)
                    currentTotalPrice += productWrapper.GetPrice() * productWrapper.GetQuantity();
            }
            if (currentTotalPrice < minimalTotalPrice)
            {
                minimalTotalPrice = currentTotalPrice;
                shopId = it.first;
            }
        }
        return shopId;
    }
}