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
int main()
{
    constexpr size_t WIDTH = 800;
    constexpr size_t HEIGHT = 800;
    double cube[][3] =
    {
        {1,1,-1},
        {1,-1,-1},
        {-1,-1, -1},
        {-1, 1, -1},
        {1 ,1 , 1},
        {1,-1, 1},
        {-1,-1, 1},

        {-1,1, 1},
    };
    std::vector<sf::Vertex> shape;
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "3D");
    constexpr double alpha = 0.1;
    while (window.isOpen()){
        for (size_t i = 0; i < 8; i++){ //rotation
            auto yold = cube[i][0];
            auto zold = cube[i][2];
            cube[i][0] = yold * cos(alpha) - zold * sin(alpha);
            cube[i][2] = yold * sin(alpha) + zold * cos(alpha);
        }
        double projection[8][2];
        for (size_t i = 0; i < 8; i++){
            projection[i][0] =  200 *cube[i][0] * (-0.25 *cube[i][2] + 0.75) + 400;
            projection[i][1] = 200* cube[i][1] * (-0.25 * cube[i][2] + 0.75)+ 400;
        }
        shape.clear();
        add(shape, projection, 0, 1);
        add(shape, projection, 1, 2);
        add(shape, projection, 2, 3);
        add(shape, projection, 3, 0);
        add(shape, projection, 4, 5);
        add(shape, projection, 5, 6);
        add(shape, projection, 6, 7);
        add(shape, projection, 7, 4);
        add(shape, projection, 0, 4);
        add(shape, projection, 1, 5);
        add(shape, projection, 2, 6);
        add(shape, projection, 3, 7);
        window.clear();
        window.draw(&shape[0],shape.size(), sf::Lines);
        window.display();
        sf::sleep(sf::milliseconds(50));
    }    
    return 0;
}