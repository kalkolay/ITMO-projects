#include "Shop.h"

#include <utility>

namespace shop_manager::entities
{
    Shop::Shop(std::string name,
               std::string address)
        : m_name   (std::move(name)),
          m_address(std::move(address))
    {
        boost::uuids::random_generator uuid_gen;
        m_id = uuid_gen();
    }

    shopID_t Shop::GetId()
    {
        return m_id;
    }

    std::string Shop::GetName()
    {
        return m_name;
    }

    std::string Shop::GetAddress()
    {
        return m_address;
    }

    ProductsCluster Shop::GetProductsCluster() const
    {
        return m_productsCluster;
    }

    Product Shop::GetProductById(productID_t productId)
    {
        return m_productsCluster[productId].GetProduct();
    }

    void Shop::AddProducts(ProductWrapperArray& productWrapperArray)
    {
        for (auto& productWrapper : productWrapperArray)
        {
            Product product = productWrapper.GetProduct();
            auto ret = m_productsCluster.insert( { product.GetId(), productWrapper } );
            if (!ret.second)  /// Element already existed
            {
                ProductWrapper oldProductWrapper = m_productsCluster.find( product.GetId() )->second;
                SetPrice   ( oldProductWrapper,
                        productWrapper.GetPrice() );
                SetQuantity( oldProductWrapper,
                        productWrapper.GetQuantity() + oldProductWrapper.GetQuantity() );
            }
        }
    }

    /// Купить партию товаров в магазине (параметры - сколько каких товаров купить,
    /// метод возвращает общую стоимость покупки либо её невозможность, если товара
    /// не хватает)
    double Shop::BuyProducts(ProductWrapperArray& productWrapperArray)
    {
        double totalPrice = 0;
        for (auto& productWrapper : productWrapperArray)
        {
            Product product = productWrapper.GetProduct();
            ProductWrapper existingProductWrapper = m_productsCluster.find( product.GetId() )->second;
            quantity_t quantityDiff = existingProductWrapper.GetQuantity() - productWrapper.GetQuantity();
            if ( quantityDiff < 0 )
            {
                return -1;
            }
            else
            {
                SetQuantity( existingProductWrapper, quantityDiff );
                totalPrice += existingProductWrapper.GetPrice() * productWrapper.GetQuantity();
            }
        }
        return totalPrice;
    }

    double Shop::GetPrice(Product& product)
    {
        return m_productsCluster[ product.GetId() ].GetPrice();
    }

    quantity_t Shop::GetQuantity(Product& product)
    {
        return m_productsCluster[ product.GetId() ].GetQuantity();
    }
}