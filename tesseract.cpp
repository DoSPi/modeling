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
    double cube[][4] =
    {
        {1,1,-1,1},
        {1,-1,-1,1},
        {-1,-1, -1,1},
        {-1, 1, -1,1},
        {1 ,1 , 1,1},
        {1,-1, 1,1},
        {-1,-1, 1,1},
        {-1,1, 1,1},

        {1,1,-1,-1},
        {1,-1,-1,-1},
        {-1,-1, -1,-1},
        {-1, 1, -1,-1},
        {1 ,1 , 1,-1},
        {1,-1, 1,-1},
        {-1,-1, 1,-1},
        {-1,1, 1,-1},
    };
    std::vector<sf::Vertex> shape;
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "Tesseract");
    double a = 0;
    for (size_t i = 0; i < 16; i++){ //const rot
        auto yold = cube[i][0];
        auto zold = cube[i][2];
        cube[i][0] = yold * cos(1) - zold * sin(1);
        cube[i][2] = yold * sin(1) + zold * cos(1);
    }
    constexpr double alpha = 0.03;
    while (window.isOpen()){
        for (size_t i = 0; i < 16; i++){ // rot
            auto yold = cube[i][2];
            auto zold = cube[i][3];
            cube[i][2] = yold * cos(alpha) - zold * sin(alpha);
            cube[i][3] = yold * sin(alpha) + zold * cos(alpha);
        }
        for (size_t i = 0; i < 16; i++){ // rot
            auto yold = cube[i][0];
            auto zold = cube[i][3];
            cube[i][0] = yold * cos(alpha) - zold * sin(alpha);
            cube[i][3] = yold * sin(alpha) + zold * cos(alpha);
        }
        double projection_3d[16][3];
       for (size_t i = 0; i < 16; i++){
            projection_3d[i][0] =  cube[i][0] *(-0.25 * cube[i][3] + 0.75);
            projection_3d[i][1] =  cube[i][1] * (-0.25 * cube[i][3] + 0.75);
            projection_3d[i][2] =  cube[i][2] * (-0.25 * cube[i][3] + 0.75);
        }
        double projection_2d[16][2];
        for (size_t i = 0; i < 16; i++){
            projection_2d[i][0] =  200 *projection_3d[i][0] * (-0.25 *projection_3d[i][2] + 0.75) + 400;
            projection_2d[i][1] = 200* projection_3d[i][1] * (-0.25 * projection_3d[i][2] + 0.75)+ 400;
        }
        shape.clear();
        // loop ?
        add(shape, projection_2d, 0, 1);
        add(shape, projection_2d, 1, 2);
        add(shape, projection_2d, 2, 3);
        add(shape, projection_2d, 3, 0);
        add(shape, projection_2d, 4, 5);
        add(shape, projection_2d, 5, 6);
        add(shape, projection_2d, 6, 7);
        add(shape, projection_2d, 7, 4);
        add(shape, projection_2d, 0, 4);
        add(shape, projection_2d, 1, 5);
        add(shape, projection_2d, 2, 6);
        add(shape, projection_2d, 3, 7);
        //
        add(shape, projection_2d, 8, 9);
        add(shape, projection_2d, 9, 10);
        add(shape, projection_2d, 10, 11);
        add(shape, projection_2d, 11, 8);
        add(shape, projection_2d, 12, 13);
        add(shape, projection_2d, 13, 14);
        add(shape, projection_2d, 14, 15);
        add(shape, projection_2d, 15, 12);
        add(shape, projection_2d, 8, 12);
        add(shape, projection_2d, 9, 13);
        add(shape, projection_2d, 10, 14);
        add(shape, projection_2d, 11, 15);
        //
        for (size_t i = 0; i < 8; i++){
            add(shape,projection_2d,i, i+ 8);
        }
        window.clear();
        window.draw(&shape[0],shape.size(), sf::Lines);
        window.display();
        sf::sleep(sf::milliseconds(50));
    }    
    return 0;
}