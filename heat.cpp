#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
int main()
{
    constexpr size_t WIDTH = 800;
    constexpr size_t HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "Thermal conductivity");
    double **u = new double*[WIDTH];
    double **ubuf = new double*[WIDTH]; 
    for(size_t i = 0; i < WIDTH; i++){
        u[i] = new double[HEIGHT];
        ubuf[i] = new double[HEIGHT];
    }
    for (size_t i = 0; i < WIDTH; i++){
        for (size_t j = 0; j < HEIGHT; j++){
            u[i][j] = 0;
            ubuf[i][j] =0;
        }
    }
    srand(228);
    for (size_t i = 0; i < WIDTH * 98 /100; i++){
        for (size_t j = 0; j < HEIGHT *98 / 100 ; j++){
            u[i][j] = (double) rand()/RAND_MAX;
        }
    }
    for (size_t i = 50; i < 100; i++){
        for (size_t j = 50; j < 100 ; j++){
            u[i][j] = 0;
        }
    }
    for (size_t i = 0; i < WIDTH; i++){
        u[i][0] = 0;
        u[i][HEIGHT - 1] =0;
    }
    for (size_t j = 0; j < HEIGHT; j++){
        u[0][j] =0;
        u[WIDTH - 1][j] = 0;
    }
    sf::Uint8 pixels[WIDTH * HEIGHT * 4] = {};
    for (size_t i = 0; i < WIDTH; i++){
        for (size_t j = 0; j < HEIGHT; j++){
            pixels[4 *(WIDTH *j + i) + 3] = 255;
        }
    }

    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    sf::Sprite sprite(texture);
    while (window.isOpen()){
        for (size_t i = 1; i < WIDTH - 1; i++){
            for (size_t j = 1; j < HEIGHT - 1; j++){
                double ddx = (u[i + 1][j] - 2 * u[i][j] + u[i - 1][j]);
                double ddy = (u[i][j + 1] - 2 * u[i][j] + u[i][j - 1]);
                double dt = 0.4* (ddx + ddy);
                ubuf[i][j] = u[i][j] +  dt;
                pixels[4 *(WIDTH *j + i)] = (uint8_t)(ubuf[i][j] * 255);
             }
        }
        for (size_t i = 1; i < WIDTH - 1; i++){
            for (size_t j = 1; j < HEIGHT - 1; j++){
                u[i][j] = ubuf[i][j];
            }   
        }
        texture.update(pixels);
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}