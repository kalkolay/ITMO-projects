#include <iostream>
#include <queue>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    int m;
    std::cin >> m;
    
    std::queue<int> myQueue;
    for (int i = 0; i < m; ++i)
    {
        char operation;
        std::cin >> operation;
        if (operation == '+')
        {
            int number;
            std::cin >> number;
            myQueue.push(number);
        }
        else
        {
            std::cout << myQueue.front() << "\n";
            myQueue.pop();
        }
    }
    
    return 0;
}
