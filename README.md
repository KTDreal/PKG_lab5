# PKG_lab5

Лабораторная работа №5 направлена на закрепление теоретического материала и практическое освоение основных методов и алгоритмов отсечения отрезков и многоугольников. В 8 варианте необходимо было написать приложение/веб-приложение, иллюстрирующее работу алгоритмов отсечения отрезков прямоугольным отсекателем (1 часть лабораторной работы) и многоугольником (часть 2). 1 часть была выполнена с помощью алгоритма Лианга-Барски, 2 часть - алгоритма Кируса-Бека.

# Функционал приложения и основная информация

Программа написана в Qt на языке программирования C++ с использованием класса QPainter, с помощью которого происходит отрисовка осей координат и фигур.
После запуска приложения в правой части окна появится система координат, слева снизу находятся кнопки выбора входного файла с данными ("Choose a file (polygon)..." для файла с данными для алгоритма Кируса-Бека, "Choose a file (rectangle)..." для выбора файла с данными для алгоритма Лианга-Барски). На координатной плоскости будет отображаться многоугольник-отсекатель (красный цвет), исходные отрезки (синий цвет), видимые части отрезков (зелёный цвет). Кроме этого, слева от координатной плоскости есть кнопки "zoom in" и "zoom out", с помощью которых масштабируется изображение.

# Формат входных данных

- Для 1 части лабораторной работы (алгоритм Лианга-Барски):

  n /**число отрезков**/
  
  X1_1 Y1_1 X2_1 Y2_1
  
  X1_2 Y1_2 X2_2 Y2_2
  
  ...
  
  X1_n Y1_n X2_n Y2_n /**координаты отрезков**/
  
  Xmin Ymin Xmax Ymax /**координаты отсекающего прямоугольного окна**/
  
- Для 2 части лабораторной работы (алгоритм Кируса-Бека):

  n k /**число отрезков и количествао вершин в многоугольнике-отсекателе соответственно**/
  
  X1_1 Y1_1 X2_1 Y2_1
  
  X1_2 Y1_2 X2_2 Y2_2
  
  ...
  
  X1_n Y1_n X2_n Y2_n /**координаты отрезков**/
  
  X_1 Y_1
  
  X_2 Y_2
  
  ...
  
  X_k Y_k /**координаты вершин отсекающего многоуголника в порядке левостороннего обхода**/
  
- Кроме этого, в данном репозитории имеются тестовые файлы input.txt, input2.txt для алгоритма Лианга-Барски, polygon.txt, poly2.txt для алгоритма Кируса-Бека.

# Дополнительная информация

- Важно отметить, что при созании файла с входными данными для алгоритма Кируса-Бека координаты вершин отсекающего многоуголника задаются именно в порядке левостороннего обхода;
- Изначальный масштаб: от -15 до 15 по осям X и Y.
- Максимальное отдаление при масштабировании - от -100 до 100 по осям X и Y, минимальное - от -5 до 5.

# Интерфейс приложения

![interface_lab5](https://github.com/KTDreal/PKG_lab5/assets/144488732/a810c45c-365a-4015-8727-4d5116afdd88)

