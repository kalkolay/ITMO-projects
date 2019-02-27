#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int n, k, A, B, C;
    std::cin >> n >> k;
    std::vector<int> a(n);
    std::cin >> A >> B >> C >> a[0] >> a[1];
    
    for (int i = 2; i < n; ++i)
        a[i] = A * a[i - 2] + B * a[i - 1] + C;
    nth_element(a.begin(), a.begin() + k - 1, a.end());
    std::cout << a[k - 1];
    
    return 0;
}
