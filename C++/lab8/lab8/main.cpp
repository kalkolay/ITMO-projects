#pragma GCC target("avx2")

#include "viewer.h"

#include <iostream>

/**
 Лабораторная работа №8. Кубик Рубика.
 
 Спроектировать и реализовать программу, имитирующую сборку ​Кубика Рубика​ 3x3.
 К программе предъявляются следующие функциональные требования:
 - Сохранение и чтение состояния кубика рубика из файла;
 - Проверка корректности текущего состояния (инвариант состояний кубика);
 - Вывод в консоль текущего состояния;
 - Вращение граней кубика рубика с помощью вводимых команд;
 - Генерация случайного состояния Кубика Рубика, корректного с точки зрения инварианта состояний;
 - Нахождения “решения” для текущего состояния в виде последовательности поворотов граней.
 
 Нефункциональные требования:
 - Программа должны быть спроектирована с использованием ООП;
 - Логические сущности должны быть выделены в отдельные классы.
 
 Критерии оценки:
 - Логично выстроенная архитектура приложения;
 - Применение возможностей языка программирования С++, включая стандартную библиотеку.
 
 Дополнительно (за дополнительные баллы):
 - Реализовать графический интерфейс приложения, с использованием OpenGL Utility Toolkit.
 */

void Start()
{
    std::cout << "--------------------lab8: Rubik's Cube--------------------\n";
    std::cout << "Welcome! There are several commands you can use:\n";
    std::cout << "- Type \"1\" on your keyboard to read cube's state from a file;\n";
    std::cout << "- Type \"2\" on your keyboard to write cube's state to a file;\n";
    std::cout << "- Type \"C\" on your keyboard to check whether the current cube's state is correct;\n";
    std::cout << "- Press left mouse button (LMC) to print current cube's state;\n";
    std::cout << "- Press \"R\", \"L\", \"U\", \"D\", \"F\", \"B\" on your "
    "keyboard to rotate the cube's face clockwise;\n";
    std::cout << "- Press \"G\" on your keyboard to generate random cube's state;\n";
    std::cout << "- Press \"S\" on your keyboard to solve cube.\n";
    std::cout << "Fave fun!\n" << std::endl;
    
    Cube c = Cube();
    
    auto viewer = createOpenglViewer();
    viewer->init();
    viewer->setRotateDuration(0.7);
    viewer->setCube(c);
    std::cout << std::endl;
    
    viewer->run();
}


int main()
{
    Start();
    return 0;
}
