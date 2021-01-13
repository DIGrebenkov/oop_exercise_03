/*
    Гребенков Д. И.
    Группа М8О-207Б-19
    Вариант 12

Разработать классы согласно варианту задания, классы должны наследоваться от базового класса Figure.
Все классы должны поддерживать набор общих методов:
1. Вычисление геометрического центра фигуры;
2. Вывод в стандартный поток вывода std::cout координат вершин фигуры; 
3. Вычисление площади фигуры.
Создать программу, которая позволяет:
• Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
• Сохранять созданные фигуры в динамический массив std::vector<Figure*>.
• Вызывать для всего массива общие функции (1-3 см. выше).Т.е. распечатывать для каждой фигуры в массиве 
геометрический центр, координаты вершин и площадь.
• Необходимо уметь вычислять общую площадь фигур в массиве.
• Удалять из массива фигуру по индексу.
Фигуры: трапеция, ромб, 5-угольник.
*/

#include <iostream>
#include <vector>
#include <cmath>

const double pi = 3.14159;

class Coordinates {
    public:
        double x;
        double y;
        Coordinates () {}
        Coordinates (double a, double b) {
            x = a;
            y = b;
        }
};

class Figure {
    public:
        virtual Coordinates centre () = 0;
        virtual void vertices () = 0;
        virtual double square () = 0;
        virtual ~Figure () {};
};

class Trapezoid: public Figure {
    private:
        Coordinates lt;
        Coordinates lb;
        Coordinates rb;
    public:
        Trapezoid (Coordinates a, Coordinates b, Coordinates c) {
            lt = a;
            lb = b;
            rb = c;
        }
        virtual Coordinates centre () {
            Coordinates result;
            result.x = lb.x + ((rb.x - lb.x) / 2.0);
            result.y = lt.y - (((lt.y - lb.y) * (3 * rb.x - lb.x - 2 * lt.x)) / 
            (6.0 * (rb.x - lt.x)));
            return result;
        }
        virtual void vertices () {
            std::cout << "(" << lt.x << ", " << lt.y << ")" << std::endl;
            std::cout << "(" << lb.x << ", " << lb.y << ")" << std::endl;
            std::cout << "(" << rb.x << ", " << rb.y << ")" << std::endl;
            Coordinates rt (rb.x - lt.x + lb.x, lt.y);
            std::cout << "(" << rt.x << ", " << rt.y << ")" << std::endl;
        }
        virtual double square () {
            return ((rb.x - lt.x) * (lt.y - lb.y));
        }
        virtual ~Trapezoid () {};
};

class Rhombus: public Figure {
    private:
        Coordinates l;
        Coordinates b;
    public:
        Rhombus (Coordinates v1, Coordinates v2) {
            l = v1;
            b = v2;
        }
        virtual Coordinates centre () {
            return (Coordinates (b.x, l.y));
        }
        virtual void vertices () {
            std::cout << "(" << l.x << ", " << l.y << ")" << std::endl;
            std::cout << "(" << b.x << ", " << b.y << ")" << std::endl;
            std::cout << "(" << 2 * b.x - l.x << ", " << l.y << ")" << std::endl;
            std::cout << "(" << b.x << ", " << 2 * l.y - b.y << ")" << std::endl;
        }
        virtual double square () {
            return (2 * (b.x - l.x) * (l.y - b.y));
        }
        virtual ~Rhombus () {};
};

class Pentagon: public Figure {
    private:
        Coordinates center;
        double radius;
    public:
        Pentagon (Coordinates c, double r) {
            center = c;
            radius = r;
        }
        virtual Coordinates centre () {
            return center;
        }
        virtual void vertices () {
            std::cout << "(" << center.x - radius * sin (72 * pi / 180) << ", " <<
            center.y + radius * cos (72 * pi / 180) << ")" << std::endl;
            std::cout << "(" << center.x << ", " << center.y + radius << ")" << std::endl;
            std::cout << "(" << center.x + radius * sin (72 * pi / 180) << ", " <<
            center.y + radius * cos (72 * pi / 180) << ")" << std::endl;
            std::cout << "(" << center.x + radius * sin (36 * pi / 180) << ", " <<
            center.y - radius * cos (36 * pi / 180) << ")" << std::endl;
            std::cout << "(" << center.x - radius * sin (36 * pi / 180) << ", " <<
            center.y - radius * cos (36 * pi / 180) << ")" << std::endl;
        }
        virtual double square () {
            return (5 * pow (radius, 2) * sin (72 * pi / 180.0) / 2.0);
        }
        virtual ~Pentagon () {};
};

void show_options () {
    std::cout << "Menu:" << std::endl;
    std::cout << "0. Print menu." << std::endl;
    std::cout << "1. Enter trapezoid." << std::endl;
    std::cout << "2. Enter rhombus." << std::endl;
    std::cout << "3. Enter pentagon." << std::endl;
    std::cout << "4. Print center, vertices and square of all figures." << std::endl;
    std::cout << "5. Print sum of squares of all figures in array." << std::endl;
    std::cout << "6. Delete figure." << std::endl;
    std::cout << "7. Quit the program." << std::endl;
}

int main () {
    std::vector <Figure*> data;
    int option = 0;
    show_options ();
    while (option != 7) {
        std::cout << "Choose option: ";
        std::cin >> option;
        switch (option) {
            case 0: {
                show_options ();
                break;
            }
            case 1: {
                Coordinates a, b, c;
                std::cout << "Enter coordinates of left-top, left-bottom and right-bottom vertices: "
                << std::endl;
                std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
                Trapezoid* alpha = new Trapezoid (a, b, c);
                data.push_back (alpha);
                break;
            }
            case 2: {
                Coordinates a, b;
                std::cout << "Enter coordinates of left and bottom vertices: ";
                std::cin >> a.x >> a.y >> b.x >> b.y;
                Rhombus* beta = new Rhombus (a, b);
                data.push_back (beta);
                break;
            }
            case 3: {
                Coordinates o;
                double r;
                std::cout << "Enter coordinates of center: ";
                std::cin >> o.x >> o.y;
                std::cout << "Enter radius of the circumscribed circle: ";
                std::cin >> r;
                Pentagon* gamma = new Pentagon (o, r);
                data.push_back (gamma);
                break;
            }
            case 4: {
                if (data.empty () != true) {
                    for (unsigned int i = 0; i < data.size (); i ++) {
                        std::cout << "Figure [" << i << "]:" << std::endl;
                        std::cout << "Center: (" << data [i]->centre ().x <<
                        ", " << data [i]->centre ().y << ");" << std::endl;
                        std::cout << "Vertices of this figure:" << std::endl;
                        data [i]->vertices ();
                        std::cout << "Square: " << data [i]->square () << std::endl;
                    }
                }
                else {
                    std::cout << "Array is empty." << std::endl;
                }
                break;
            }
            case 5: {
                if (data.empty () != true) {
                    double sq = 0;
                    for (unsigned int i = 0; i < data.size (); i ++) {
                        sq += data [i]->square ();
                    }
                    std::cout << "Sum of squares of all figures in array: " << sq << std::endl;
                }
                else {
                    std::cout << "Error: array is empty." << std::endl;
                }
                break;
            }
            case 6: {
                int idx;
                std::cout << "Enter index: ";
                std::cin >> idx;
                if ((idx >= 0) && (idx < int (data.size ()))) {
                    if (data [idx] != nullptr) {
                        delete data [idx];
                        data.erase (data.begin () + idx);
                    }
                }
                else {
                    std::cout << "Error: incorrect index." << std::endl;
                }
            }
            case 7: {
                break;
            }
            default: {
                std::cout << "Error: incorrect option." << std::endl;
            }
        }
    }
    for (unsigned int i = 0; i < data.size (); i ++) {
        delete data [i];
    }
    data.clear ();
    return 0;
}