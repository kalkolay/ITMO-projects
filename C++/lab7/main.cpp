#pragma GCC target("avx2")

#include "circular_buffer.h"

#include <iostream>


/*
Реализовать к​ольцевой буфер в виде stl-совместимого контейнера
(например, может быть использован с стандартными алгоритмами),
обеспеченного итератором произвольного доступа.
Реализация не должна использовать ни одни из контейнеров STL.
Буфер должен обладать следующими возможностями:
1. Вставка и удаление в конец
2. Вставка и удаление в начало
3. Вставка и удаление в произвольное место по итератору
4. Доступ в конец, начало
5. Доступ по индексу
6. Изменение капасити
*/


template<typename T>
void print(circular_buffer<T> cb)
{
    std::cout << "circular_buffer:";
    for (size_t i = 0; i < cb.size(); ++i)
        std::cout << ' ' << cb[i];
    std::cout << std::endl;
    std::cout << "capacity = " << cb.capacity() << "; size = " << cb.size() << std::endl;
    std::cout << std::endl;
}


int main()
{
    std::ios_base::sync_with_stdio(false);

    circular_buffer<int> cb(4);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.push_back(4);
    print(cb);

    cb.push_back(5);
    cb.push_back(6);
    print(cb);

    cb.push_front(7);
    cb.push_front(8);
    print(cb);

    cb.pop_back();
    cb.pop_back();
    print(cb);

    cb.pop_front();
    cb.pop_front();
    print(cb);

    cb.set_capacity(5);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.push_back(4);
    print(cb);

    cb.push_back(5);
    cb.push_back(6);
    print(cb);

    cb.set_capacity(3);
    print(cb);

    auto it = cb.begin() + 1;
    cb.insert(it, 10);
    print(cb);

    it = cb.end() - 2;
    cb.erase(it);
    print(cb);

    return 0;
}