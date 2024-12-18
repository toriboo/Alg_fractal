#include <SFML/Graphics.hpp>
#include <iostream>
#include < Windows.h>
#include <ctime>


struct Point { // координаты 
    float x;
    float y;
};
float array_time[15];

sf::RenderWindow window(sf::VideoMode(850, 800), "Sierpinski Triangle"); // создаем окно 

// начальные координаты
Point p1 = { 100, 620 };
Point p2 = { 400, 100 };
Point p3 = { 700, 620 };

int max_count = 10; // количество уровней отрисовки 

// константы цвета
const sf::Color start_color = sf::Color::Green;
const sf::Color color_tr1 = sf::Color::Red;
const sf::Color color_tr2 = sf::Color::Cyan;
const sf::Color color_tr3 = sf::Color::Magenta;
const sf::Color color_back = sf::Color::Black;

void ifs(Point p1, Point p2, Point p3, int count);

void draw_triangle(Point p1, Point p2, Point p3, const sf::Color color) { // функция для отрисовки тругольников определенного цвета
    sf::ConvexShape triangle;

    triangle.setPointCount(3);

    triangle.setPoint(0, sf::Vector2f(p1.x, p1.y));
    triangle.setPoint(1, sf::Vector2f(p2.x, p2.y));
    triangle.setPoint(2, sf::Vector2f(p3.x, p3.y));
    triangle.setFillColor(color); //  Цвет треугольника
    window.draw(triangle);

}
void ifs(Point p1, Point p2, Point p3, int count) {

    if (count <= 0) {
        return;
    }
    // координаты середин сторон треугольника
    Point middle_1, middle_2, middle_3;

    middle_1.x = (p1.x + p2.x) / 2;
    middle_1.y = (p1.y + p2.y) / 2;
    middle_2.x = (p2.x + p3.x) / 2;
    middle_2.y = (p2.y + p3.y) / 2;
    middle_3.x = (p1.x + p3.x) / 2;
    middle_3.y = (p1.y + p3.y) / 2;


    draw_triangle(p1, p2, p3, color_back);
    //отрисовка меньших тругольников 
    draw_triangle(p1, middle_1, middle_3, color_tr1);
    draw_triangle(middle_1, p2, middle_2, color_tr2);
    draw_triangle(middle_3, middle_2, p3, color_tr3);

    ifs(p1, middle_1, middle_3, count - 1);
    ifs(middle_1, p2, middle_2, count - 1);
    ifs(middle_3, middle_2, p3, count - 1);
}


int main() {

    // window.clear(color_back);
    draw_triangle(p1, p2, p3, start_color);
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        for (int i = 0; i < max_count; i++) {

            ifs(p1, p2, p3, i);
            window.display();
            Sleep(1500);

        }
        /*    for (int i = 0; i < 15; i ++) {
                float time = 0;
                for (int k = 0; k < 5; k++) {
                    float start_time = clock();
                    ifs(p1, p2, p3, i);
                    float end_time = clock();
                    time += end_time - start_time;
                    window.display();
                }
                array_time[i] = time / 5;

            }
            window.close();
        }
        for (int i = 0; i < 15; i++) {
            std::cout << array_time[i] << ' ';
        }*/
    }

    return 0;
}
