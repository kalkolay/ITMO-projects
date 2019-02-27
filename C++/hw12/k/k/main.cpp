#include <iostream>
#include <ext/rope>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    __gnu_cxx::rope<int> myRope;
    
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i)
        myRope.push_back(i + 1);
    
    for (int i = 0, left, right; i < m; ++i)
    {
        std::cin >> left >> right;
        -- left;
        -- right;
        __gnu_cxx::rope<int> line = myRope.substr(left, right - left + 1);
        myRope.erase(left, right - left + 1);
        myRope.insert(myRope.mutable_begin(), line);
    }
    
    for (auto i : myRope)
        std::cout << i << " ";
    
    return 0;
}
