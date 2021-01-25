 #include <SFML/Graphics.hpp>
#include <utility>
#include <iostream>
#include <cmath>
inline void add(std::vector<sf::Vertex> &v, double p[][2], size_t i, size_t j)
{
    v.push_back(sf::Vertex(sf::Vector2f(p[i][0],p[i][1])));
    v.push_back(sf::Vertex(sf::Vector2f(p[j][0],p[j][1])));
    return;
}
struct Point{
    double vx;
    double vy;
    double ax;
    double ay;
    double x;
    double y;
    Point(double x , double y, double vx = 0, double vy = 0, double ax = 0, double ay = 0) : x(x), y(y), vx(vx), vy(vy), ax(ax), ay(ay) {}
};
int main()
{
    constexpr size_t WIDTH = 800;
    constexpr size_t HEIGHT = 800;
    std::vector<Point> points;
    points.emplace_back(400, 100);
    points.emplace_back(300, 100);
    points.emplace_back(300, 600);
    std::vector<sf::Vertex> shape(points.size());
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "3D");
    constexpr double G = 10;
    while (window.isOpen()){
        for (int  i = points.size() - 1; i >=1; i--){
            Point &p = points[i];
            Point &prev = points[i - 1];
            double a = atan((p.x - prev.x) / (p.y - prev.y));
        }
        double a = atan((400 - x) / (y - 100));
        double cosa = cos(a);
        double sina = sin(a);
        double t =   (vx * vx + vy * vy)/  sqrt((x - 400) * (x - 400) + (y - 100) * (y - 100 )) + G * cosa;
        double ay = G - t * cosa;
        double ax = t * sina;
        double dt = 0.01;
        vx += ax * dt;
        vy += ay * dt;
        x += vx * dt;
        y += vy * dt;
        window.clear();
        shape[1] = sf::Vertex(sf::Vector2f(x, y));
        window.draw(&shape[0],shape.size(), sf::Lines);
        window.display();
        sf::sleep(sf::milliseconds(5));
    }    
    return 0;
}
