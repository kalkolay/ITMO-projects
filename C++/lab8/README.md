# Лабораторная работа №8. Кубик Рубика

Спроектировать и реализовать программу, имитирующую сборку [Кубика Рубика](https://ru.wikipedia.org/wiki/Кубик_Рубика) 3x3х3.\
К программе предъявляются следующие функциональные требования:
- Сохранение и чтение состояния кубика рубика из файла;
- Проверка корректности текущего состояния (инвариант состояний кубика);
- Вывод в консоль текущего состояния;
- Вращение граней кубика рубика с помощью вводимых команд;
- Генерация случайного состояния Кубика Рубика, корректного с точки зрения инварианта состояний;
- Нахождение “решения” для текущего состояния в виде последовательности поворотов граней.
 
Нефункциональные требования:
- Программа должны быть спроектирована с использованием ООП;
- Логические сущности должны быть выделены в отдельные классы.
 
Критерии оценки:
- Логично выстроенная архитектура приложения;
- Применение возможностей языка программирования С++, включая стандартную библиотеку.
 
Дополнительно (за дополнительные баллы):
- Реализовать графический интерфейс приложения, с использованием OpenGL Utility Toolkit.

___________________________________________________________________________________________________

Данная работа выполнена в Xcode (*-std=c++17*, *-lglwf3*, *-framework OpenGL*) в виде десктопного приложения, состоящего из следующих файлов:
-	**lab8/cube.h** – заголовочный файл, в котором описан кубик (в виде массива позиции/ориентации рёбер и углов, так как центры кубика инвариантны);
-	**lab8/cube.cpp** – его реализация;
-	**lab8/algo.h** – файл интерфейса для алгоритма (был выбран [алгоритм Коцембы](https://ru.wikipedia.org/wiki/Математика_кубика_Рубика#Двухфазный_алгоритм_Коцембы) *(двухфазная модификация алгоритма Тистлетуэйта)*, так как он находит одно из самых оптимальных решений);
-	**lab8/search.hpp** – описание и многопоточная реализация алгоритма [IDA*](https://ru.wikipedia.org/wiki/Информированный_метод_поиска#IDA*) для таблицы поиска, необходимой для реализации алгоритма Коцембы;
-	**lab8/heuristic.hpp** – описание и реализация эвристических функций для алгоритма IDA*;
-	**lab8/algo_kociemba.h** – описание класса, реализующего сам алгоритм Коцембы;
-	**lab8/algo_kociemba.cpp** – его реализация;
-	**lab8/virtual_rotate.h** – заголовочный файл-помощник для визуализации (описывает траекторию поворота граней кубика);
-	**lab8/virtual_rotate.cpp** – его реализация;
-	**lab8/viewer.h** – файл интерфейса, описывающий класс-визуализатор;
-	**lab8/viewer_gl.cpp** – его реализация, использовались библиотеки *glfw3.h* и *gl.h*, был добавлен ввод команд с помощью левой кнопки мыши и некоторых клавиш;
-	**lab8/main.cpp** – основной исполняемый файл;
- **lab8.xcodeproj** – сгенерированный Xcode файл проекта с различными настройками;
- **DerivedData/** - папка, сгенерированная Xcode, в которой, помимо прочего, по адресу *~/Build/Products/Debug/* находятся исполняемый файл проекта **./lab8**, а также файлы с состояниями кубика Рубика:
  - **cube_state.txt** - файл, в который записывается текущее состояние кубика;
  - **cube_state_solved.txt** - файл, в который записано состояние собранного кубика;
  - **cube_state_wrong.txt** - файл, в который записано некорректное состояние кубика (неправильная ориентация у двух углов).



___________________________________________________________________________________________________

[Пример работы программы](https://drive.google.com/open?id=1PEAdkzWgjfLGxT2xwGjYXt99JOIGFGlt)\
(при её работе последовательно нажимались клавиши *G, S, R, D, F, U, B, L, 2, 0, 1, 9, C, S, 0, C, ЛКМ*)

Вывод в консоль:
```
--------------------lab8: Rubik's Cube--------------------
Welcome! There are several commands you can use:
- Type "1" on your keyboard to read cube's state from a file;
- Type "2" on your keyboard to write cube's state to a file;
- Type "C" on your keyboard to check whether the current cube's state is correct;
- Press left mouse button (LMC) to print current cube's state;
- Press "R", "L", "U", "D", "F", "B" on your keyboard to rotate the cube's face clockwise;
- Press "G" on your keyboard to generate random cube's state;
- Press "S" on your keyboard to solve cube.
Fave fun!

2020-05-13 11:09:47.278705+0300 lab8[12001:1045750] Metal API Validation Enabled

Random cube's state was generated.
Solution: D'FR2F2RU2BRUF2U2R2L2DF2R2B2F2DU2B2
This solution needs 21 steps.
Cube's state was successfully wrote to the file cube_state.txt
Cube's state was successfully read from the file cube_state_solved.txt
Cube's state was successfully read from the file cube_state.txt
Cube's state was successfully read from the file cube_state_wrong.txt
Is cube's current state correct? false
Solution: LFRDB'LF2UB2L2UL2DB2F2D2F2L2DF2
This solution needs 20 steps.
Cube's state was successfully read from the file cube_state_solved.txt
Is cube's current state correct? true
Corners' position & orientation:
0 0
1 0
2 0
3 0
4 0
5 0
6 0
7 0
Edges' position & orientation:
0 0
1 0
2 0
3 0
4 0
5 0
6 0
7 0
8 0
9 0
10 0
11 0
Cube's current state was successfully printed out.
Program ended with exit code: 0
```
