#include <iostream>
#include <string>
#include <cstring>
#include <set>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    std::set<int> mySet;
    char buffer[32];
    int n;
    std::string result = "";
    while (std::cin >> buffer >> n)
    {
        switch (buffer[0])
        {
            case 'i':
                mySet.insert(n);
                break;
            case 'd':
                mySet.erase(n);
                break;
            case 'e':
                result += (mySet.find(n) != mySet.end() ? "true\n" : "false\n");
                break;
            case 'n':
            {
                auto it = mySet.upper_bound(n);
                int res = 0;
                bool ans = it != mySet.end();
                if (ans)
                    res = *it;
                result += (!ans ? "none" : std::to_string(res));
                result += '\n';
            }
                break;
            case 'p':
            {
                auto it = mySet.lower_bound(n);
                int res = 0;
                bool ans = true;
                if (it == mySet.begin())
                    ans = false;
                else
                {
                    it--;
                    it == mySet.end() ? ans = false : res = *it;
                }
                result += (!ans ? "none" : std::to_string(res));
                result += '\n';
            }
                break;
            default:
                break;
        }
    }
    std::cout << result;
    return 0;
}
