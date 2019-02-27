#include <iostream>
#include <unordered_map>

int main()
{
    std::cin.tie(nullptr);
    std::ostream::sync_with_stdio(false);
    
    std::unordered_map<std::string, std::string> myMap;
    std::string result, search, key, number;
    while (std::cin >> search)
    {
        std::cin >> key;
        if (search[0] == 'p')
        {
            std::cin >> number;
            myMap[key] = number;
        }
        else if (search[0] == 'd')
            myMap.erase(key);
        else if (search[0] == 'g')
        {
            auto response = myMap.find(key);
            result += response != myMap.end() ? response->second + "\n" : "none\n";
        }
    }
    
    std::cout << result;
    return 0;
}
