#pragma once

#include <fstream>

#include "../ShopManager.h"

#define PRODUCTS_AMOUNT 10

namespace shop_manager::utilities
{
    void PrintProduct            (Product&              product,
                                  std::ofstream&        out_log);
    void PrintArrayOfProducts    (std::vector<Product>& products,
                                  std::ofstream&        out_log);
    void PrintProductWrapperArray(ProductWrapperArray&  productWrapperArray,
                                  std::ofstream&        out_log);
    void PrintProductsCluster    (ProductsCluster&      productsCluster,
                                  std::ofstream&        out_log);

    void PrintShop               (Shop&                 shop,
                                  std::ofstream&        out_log);
    void PrintShopManager        (ShopManager&          shopManager,
                                  std::ofstream&        out_log);

    void FillProducts            (std::vector<Product>& products,
                                 std::ofstream&         out_log);
    void FillProductWrapperArray (ProductWrapperArray&  productWrapperArray,
                                 std::vector<Product>&  products,
                                 std::ofstream&         out_log);
}