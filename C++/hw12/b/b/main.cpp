#include <iostream>
#include <algorithm>

void output(int permutations[], int n)
{
    for (int i = 0; i < n; ++i)
        std::cout << permutations[i] << " ";
    std::cout << "\n";
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    int n;
    std::cin >> n;
    
    int permutations[n];
    for (int i = 0; i < n; ++i)
        permutations[i] = i + 1;
    
    output(permutations, n);
    while (std::next_permutation(permutations, permutations+n))
        output(permutations, n);
    
    return 0;
}
