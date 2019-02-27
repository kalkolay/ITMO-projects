#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> myVector(n);
    for (int i = 0, number; i < n; ++i)
    {
        std::cin >> number;
        myVector[i] = number;
    }
    
    int m;
    std::cin >> m;
    for (int i = 0, number; i < m; ++i)
    {
        std::cin >> number;
        auto l = std::lower_bound(myVector.begin(), myVector.end(), number);
        auto r = std::upper_bound(myVector.begin(), myVector.end(), number);
        myVector[l - myVector.begin()] != number ? std::cout << "-1 -1\n" : std::cout << l - myVector.begin() + 1 << ' ' << r - myVector.begin()  << '\n';
    }
    
    return 0;
}
