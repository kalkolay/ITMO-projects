#include <iostream>
#include <vector>
#include <algorithm>

using triple = std::pair<std::pair<int, int>, int>;

bool cmp(const triple& a, const triple& b)
{
    if (a.first.first == b.first.first)
        if (a.first.second == b.first.second)
            return a.second < b.second;
        return a.first.second < b.first.second;
    return a.first.first > b.first.first;
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<triple> listOfWinners(n);
    for (int i = 0, problems, fines; i < n; ++i)
    {
        std::cin >> problems;
        std::cin >> fines;
        triple participant = std::make_pair(std::make_pair(problems, fines), i + 1);
        listOfWinners[i] = participant;
    }
    
    std::sort(listOfWinners.begin(), listOfWinners.end(), cmp);
    for (auto& i : listOfWinners)
        std::cout << i.second << " ";
    
    return 0 ;
}
