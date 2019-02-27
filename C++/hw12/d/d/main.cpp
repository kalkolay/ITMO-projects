#include <iostream>
#include <stack>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    int m;
    std::cin >> m;
    
    std::stack<int> myStack;
    for (int i = 0; i < m; ++i)
    {
        char operation;
        std::cin >> operation;
        if (operation == '+')
        {
            long long number;
            std::cin >> number;
            myStack.push(number);
        }
        else
        {
            std::cout << myStack.top() << "\n";
            myStack.pop();
        }
    }
    
    return 0;
}
