#include <typeinfo>
#include "cmake-build-debug/Array.cpp"
#include <tuple>

void print_values() {}

template<typename T, typename... A>
void print_values(const T& value, const A... args)
{
    std::cout << typeid(value).name() << ": " << value << '\n';
    print_values(args...);
}


template<typename T>
void print(const Array<T>& array)
{
	for (int i = 0; i < array.size(); ++i)
		std::cout << array[i] << ' ';
	std::cout << '\n';
}


template<int F, int S, typename... A>
auto to_pair(const std::tuple<A...> t)
-> decltype(std::make_pair(std::get<F>(t), std::get<S>(t)))
{
    return {std::get<F>(t), std::get<S>(t)};
}


int main()
{
    int A[2] = {2, 1};
    print_values(0, 3.5, "Hello", 119, A);
    std::cout << '\n';


	Array<int> a(5);
	Array<int> b(Array<int>(3));
	b[2] = -3;
	a[0] = 1;
	a[1] = b[2];
	Array<int> c = a;
	a[4] = 18;

	std::cout << "a is: ";
	print(a);
	std::cout << "b is: ";
	print(b);
	std::cout << "c is: ";
	print(c);

	Array<int> d = std::move(a);

	std::cout << "a is: ";
	print(a);
	std::cout << "d is: ";
	print(d);

	Array<int> e = b;

	std::cout << "b is: ";
	print(b);
	std::cout << "e is: ";
	print(e);

	Array<int> f(std::move(d));

	std::cout << "d is: ";
	print(d);
	std::cout << "f is: ";
	print(f);

	Array<double> g = Array<double> (7);
	Array<double> h(g);
	g[6] = -5.8;

	std::cout << "g is: ";
	print(g);
	std::cout << "h is: ";
	print(h);
    std::cout << '\n';

    auto t = std::make_tuple(0, 3.5, "Hello");

    std::pair<double, const char*> firstPair = to_pair<1, 2>(t);
    std::cout << firstPair.first << ' ' << firstPair.second << '\n';

    std::pair<int, double> secondPair = to_pair<0, 1>(t);
    std::cout << secondPair.first << ' ' << secondPair.second;

	return 0;
}
