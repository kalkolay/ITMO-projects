#include <iostream>
#include <string>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    __gnu_pbds::tree<int, __gnu_pbds::null_type, std::greater<>,
    __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> myTree;
    
    int n;
    std::cin >> n;
    
    std::string command;
    int number;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> command >> number;
        switch (command[0])
        {
            case '+' :
                myTree.insert(number);
                break;
            case '1':
                myTree.insert(number);
                break;
            case '-' :
                myTree.erase(number);
                break;
            case '0':
                std::cout << *myTree.find_by_order(number - 1) << "\n";
        }
    }
    
    return 0;
}
