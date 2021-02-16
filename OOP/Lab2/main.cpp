#include <iostream>

#include "shop_manager/ShopManager.h"
#include "shop_manager/utilities/Utilities.h"

using namespace shop_manager;
using namespace shop_manager::entities;
using namespace shop_manager::utilities;


int main()
{
    std::ofstream out_log("out.log");

    //__________________________________TASK 1__________________________________//

    out_log << "\n==================== TASK 1 ====================\n" << std::endl;

    Shop shop1("PokemonGo", "Onion street, 4");
    Shop shop2("Bob Shop", "Hydra avenue, 6");
    Shop shop3("ICE KING", "Dark boulevard, 33");

    std::initializer_list<Shop> shops = { shop1, shop2, shop3 };
    ShopManager shopManager(shops);

    out_log << shops.size() << " shops created successfully:" << std:: endl;
    PrintShopManager(shopManager, out_log);
    std::cout << "1.\tShops created successfully." << std::endl;

    //__________________________________TASK 2__________________________________//

    out_log << "\n==================== TASK 2 ====================\n" << std::endl;

    std::vector<Product> products;
    FillProducts(products, out_log);

    out_log << products.size() << " products created successfully:" << std::endl;
    PrintArrayOfProducts(products, out_log);
    std::cout << "2.\tProducts created successfully." << std::endl;

    //__________________________________TASK 3__________________________________//

    out_log << "\n==================== TASK 3 ====================\n" << std::endl;

    ProductWrapperArray productWrapperArray1;
    FillProductWrapperArray(productWrapperArray1, products, out_log);
    out_log << "ProductWrapperArray for shop №1:" << std::endl;
    PrintProductWrapperArray(productWrapperArray1, out_log);

    shop1.AddProducts(productWrapperArray1);
    out_log << "Added current productWrapperArray for shop №1" << std::endl;

    ProductWrapperArray productWrapperArray2;
    FillProductWrapperArray(productWrapperArray2, products, out_log);
    out_log << "ProductWrapperArray for shop №2:" << std::endl;
    PrintProductWrapperArray(productWrapperArray2, out_log);

    shop2.AddProducts(productWrapperArray2);
    out_log << "Added current productWrapperArray for shop №2" << std::endl;

    ProductWrapperArray productWrapperArray3;
    FillProductWrapperArray(productWrapperArray3, products, out_log);
    out_log << "ProductWrapperArray for shop №3:" << std::endl;
    PrintProductWrapperArray(productWrapperArray3, out_log);

    shop3.AddProducts(productWrapperArray3);
    out_log << "Added current productWrapperArray for shop №3" << std::endl;

    std::cout << "3.\tProducts added to shops successfully." << std::endl;

    //__________________________________TASK 4__________________________________//

    out_log << "\n==================== TASK 4 ====================\n" << std::endl;

    shopID_t cheapestShopID = shopManager.FindCheapestProduct( products[0].GetId() );

    out_log << "The cheapest product is in the following shop:" << std::endl;
    PrintShop( shopManager.GetShopById(cheapestShopID), out_log );
    std::cout << "4.\tThe cheapest product is in the shop with ID = " << cheapestShopID << std::endl;

    //__________________________________TASK 5__________________________________//

    out_log << "\n==================== TASK 5 ====================\n" << std::endl;

    ProductsCluster productsCluster = ShopManager::FindProductsByPrice(shop2, 228);

    out_log << "Products that can be bought in this shop on given price:" << std::endl;
    PrintProductsCluster(productsCluster, out_log);
    std::cout << "5.\tFindProductsByPrice() successfully executed." << std::endl;

    //__________________________________TASK 6__________________________________//

    out_log << "\n==================== TASK 6 ====================\n" << std::endl;

    double totalPrice = shop3.BuyProducts(productWrapperArray3);
    if (totalPrice == -1)
    {
        out_log   << "Unable to buy these products (lack of amount in current shop)"   << std::endl;
        std::cout << "6.\tUnable to buy these products (lack of amount in current shop)" << std::endl;
    }
    else
    {
        out_log   << "Products successfully bought. Total price: "   << totalPrice << std::endl;
        std::cout << "6.\tProducts successfully bought. Total price: " << totalPrice << std::endl;
    }

    //__________________________________TASK 7__________________________________//

    out_log << "\n==================== TASK 7 ====================\n" << std::endl;

    std::vector<std::pair<productID_t, quantity_t>> shipment;
    shipment.emplace_back(products[5].GetId(), 3);
    shipment.emplace_back(products[2].GetId(), 11);
    shopID_t ans = shopManager.FindMinimalTotalPrice(shipment);

    out_log << "The following shop has minimal total price for these products:" << std::endl;
    PrintShop( shopManager.GetShopById(ans), out_log );
    std::cout << "7.\tMinimal total price for these products is in the shop with ID = " << ans << std::endl;

    return 0;
}
