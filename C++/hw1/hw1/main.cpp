#include <iostream>

using namespace std;

string someFunction(string name)
{
    return "Hello, " + name + "!\n";
}

int secondsPassed(int minutes, int seconds)
{
    return seconds + minutes * 60;
}

int secondsPassed(int hours, int minutes, int seconds)
{
    return seconds + minutes * 60 + hours * 3600;
}

void display(string name = "guest")
{
    cout << "Hello, " << name << "!\n";
}

void swapValue(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void swapReference(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

int arr[] = { 1, 2, 3, 4, 5 };

int& setValues(int i)
{
    return arr[i];
}

class MyClass       // class declaration
{
public:
    int age;
    
    void printAge()
    {
        cout << "Your age is: " << age << endl;
    }
};

class Construct
{
public:
    int a, b;
    
    Construct()
    {
        a = 100;
        b = 200;
    }
    
    Construct(int x, int y)
    {
        a = x;
        b = y;
    }
    
    int getA()
    {
        return a;
    }
    int getB()
    {
        return b;
    }
};


int main()
{
    cout << "1. Demonstration of a function:" << endl;
    string myName = "Nikolay";
    cout << someFunction(myName) << endl;
    
    cout << "2. Demonstration of a function overloading:" << endl;
    int hrs = 1, min = 11, sec = 36;
    cout << "Seconds passed: " << secondsPassed(min, sec) << endl;                 // two arguments
    cout << "Seconds passed: " << secondsPassed(hrs, min, sec) << endl << endl;    // three arguments
    
    cout << "3. Demonstration of default arguments:" << endl;
    display();
    display("John");    // no argument passed
    cout << endl;       // argument passed
    
    cout << "4. Demonstration of passing by value, passing by reference and returning by reference:" << endl;
    int x = 2, y = 3;
    cout << "Two numbers before change: " << x << ", " << y << endl;
    swapValue(x, y);
    cout << "Trying to swap your numbers with passing by value function: " << x << ", " << y << endl;
    swapReference(x, y);
    cout << "Trying to swap your numbers with passing by reference function: " << x << ", " << y << endl;
    cout << "Array before change: ";
    for (int i = 0; i < 5; ++i)
        cout << arr[i] << " ";
    setValues(1) = 10;
    setValues(3) = 20;
    cout << "\nArray after change (usage of returning by reference function): ";
    for (int i = 0; i < 5; ++i)
        cout << arr[i] << " ";
    cout << endl << endl;
    
    cout << "5. Demonstration of classes and objects:" << endl;
    MyClass obj;                                                // object declaration
    obj.age = 37;
    obj.printAge();
    cout << endl;
    
    cout << "6. Demonstration of constructors:" << endl;
    Construct constr;                                           // default constructor call
    Construct parameterConstr(228, 322);                        // parameterized constructor call
    cout << "a: " << constr.a << ", b: " << constr.b << endl;
    cout << "a: " << parameterConstr.getA() << ", b: " << parameterConstr.getB() << endl;
    
    return 0;
}
