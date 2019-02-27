#include <iostream>
#include <sstream>
#include <unordered_set>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    std::string command;
    std::unordered_set<int> mySet;
    
    std::stringstream result;
    
    while (getline(std::cin, command))
        switch (command[0])
        {
            case('i'):
                mySet.insert(atoi(&command[7]));
                break;
            case ('e'):
                mySet.count(atoi(&command[7])) ? result << "true\n" : result << "false\n";
                break;
            case ('d'):
                mySet.erase(atoi(&command[7]));
                break;
        }
    
    std::cout << result.str();
    
    return 0;
}
