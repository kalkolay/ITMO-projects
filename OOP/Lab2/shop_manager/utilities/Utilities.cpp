#include "Utilities.h"

#include <sstream>
#include <random>

#define PRODUCTS_MAX_PRICE    1000.
#define PRODUCTS_MAX_QUANTITY 100

namespace shop_manager::utilities
{
    void PrintProduct(Product&       product,
                      std::ofstream& out_log)
    {
        out_log << "\tID:\t\t  "   << product.GetId()
                << "\n\tName:\t  " << product.GetName()
                << std::endl;
    }

    void PrintArrayOfProducts(std::vector<Product>& products,
                              std::ofstream&        out_log)
    {
        size_t i = 1;
        for (auto& product : products)
        {
            out_log << "Product №" << i << ":\n";
            PrintProduct(product, out_log);
            ++i;
        }
    }

    void PrintProductWrapperArray(ProductWrapperArray& productWrapperArray,
                                  std::ofstream&       out_log)
    {
        for (size_t i = 0; i < productWrapperArray.size(); ++i)
        {
            out_log << "ProductWrapper №" << i + 1 << ":\n";
            Product product = productWrapperArray[i].GetProduct();
            PrintProduct( product, out_log );
            double     price    = productWrapperArray[i].GetPrice();
            quantity_t quantity = productWrapperArray[i].GetQuantity();
            out_log << "\tPrice:\t  "   << price
                    << "\n\tQuantity: " << quantity
                    << std::endl;
        }
    }

    void PrintProductsCluster(ProductsCluster& productsCluster,
                              std::ofstream&   out_log)
    {
        ProductWrapperArray ans;
        for (auto& product : productsCluster)
            ans.push_back(product.second);
        PrintProductWrapperArray(ans, out_log);
    }

    void PrintShop(Shop&          shop,
                   std::ofstream& out_log)
    {
        out_log << "\tID:\t\t "    << shop.GetId()
                << "\n\tName:\t "  << shop.GetName()
                << "\n\tAddress: " << shop.GetAddress()
                << std::endl;
    }

    void PrintShopManager(ShopManager&   shopManager,
                          std::ofstream& out_log)
    {
        size_t i = 1;
        for ( auto& shop : shopManager.GetShopsCluster() )
        {
            out_log << "Shop №" << i << ":\n";
            PrintShop(shop.second, out_log);
            ++i;
        }
    }

    void FillProducts(std::vector<Product>& products,
                      std::ofstream&        out_log)
    {
        for (size_t i = 1; i <= PRODUCTS_AMOUNT; ++i)
        {
            std::stringstream ss;
            ss << "Product №" << i;
            std::string name = ss.str();
            products.emplace_back(name);
        }
    }

    void FillProductWrapperArray(ProductWrapperArray&  productWrapperArray,
                                 std::vector<Product>& products,
                                 std::ofstream&        out_log)
    {
        std::default_random_engine             genDouble;
        std::uniform_real_distribution<double> distrDouble(0.1, PRODUCTS_MAX_PRICE);

        std::random_device              rd;
        std::mt19937                    genIntegral( rd() );
        std::uniform_int_distribution<> distrIntegral(1, PRODUCTS_MAX_QUANTITY);

        for (size_t i = 0; i < PRODUCTS_AMOUNT; ++i)
        {
            ProductWrapper productWrapper( products[i], distrDouble(genDouble), distrIntegral(genIntegral) );
            productWrapperArray.push_back(productWrapper);
        }
    }
}