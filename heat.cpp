#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
int main()
{
    constexpr size_t WIDTH = 800;
    constexpr size_t HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "Thermal conductivity");
    double **ux = new double*[WIDTH];
    double **uy = new double*[WIDTH];
    double **uxbuf = new double*[WIDTH];
    double **uybuf = new double*[WIDTH]; 
    for(size_t i = 0; i < WIDTH; i++){
        ux[i] = new double[HEIGHT];
        uxbuf[i] = new double[HEIGHT];
        uy[i] = new double[HEIGHT];
        uybuf[i] = new double[HEIGHT];
    }
    srand(228);
    for (size_t i = 0; i < WIDTH; i++){
        for (size_t j = 0; j < HEIGHT; j++){
            ux[i][j] = (double) rand()/RAND_MAX  * 0.5;
            uy[i][j] = (double) rand()/RAND_MAX * 0.5 ;
        }
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
                double ddx = (ux[i + 1][j] - 2 * ux[i][j] + ux[i - 1][j])/ 4;
                double ddy = (ux[i][j + 1] - 2 * ux[i][j] + ux[i][j - 1])/ 4;
                double dt = 0.1* (ddx + ddy);
                uxbuf[i][j] = ux[i][j] +  dt;
                ddx = (uy[i + 1][j] - 2 * uy[i][j] + uy[i - 1][j])/ 4;
                ddy = (uy[i][j + 1] - 2 * uy[i][j] + uy[i][j - 1])/ 4;
                dt = 0.1* (ddx + ddy);
                uybuf[i][j] = uy[i][j] +  dt;
                pixels[4 *(WIDTH *j + i)] = (uint8_t)((uxbuf[i][j] + uybuf[i][j]) * 255);
             }
        }
        for (size_t i = 0; i < WIDTH; i++){
            uxbuf[i][0] = uxbuf[i][1];
            uxbuf[i][HEIGHT - 1] =uxbuf[i][HEIGHT -2];
            uybuf[i][0] = uybuf[i][1];
            uybuf[i][HEIGHT - 1] =uybuf[i][HEIGHT -2];
        }
        for (size_t j = 0; j < HEIGHT; j++){
        uxbuf[0][j] =uxbuf[1][j];
        uxbuf[WIDTH - 1][j] = uxbuf[WIDTH -2][j];
        uybuf[0][j] =uybuf[1][j];
        uybuf[WIDTH - 1][j] = uybuf[WIDTH -2][j];
    }
        for (size_t i = 0; i < WIDTH ; i++){
            for (size_t j = 0; j < HEIGHT ; j++){
                ux[i][j] = uxbuf[i][j];
                uy[i][j] = uybuf[i][j];
            }   
        }
        texture.update(pixels);
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}