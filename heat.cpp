#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    constexpr size_t WIDTH = 800;
    constexpr size_t HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "Thermal conductivity");
    vector<vector<double>> ux(WIDTH, vector<double>(HEIGHT));
    vector<vector<double>> uy(WIDTH, vector<double>(HEIGHT));
    vector<vector<double>> uxtemp(WIDTH, vector<double>(HEIGHT));
    vector<vector<double>> uytemp(WIDTH, vector<double>(HEIGHT));
    srand(228);
    for (size_t i = 0; i < ux.size(); i++){
        for (size_t j = 0; j < ux[0].size(); j++){
            ux[i][j] = (double) rand()/RAND_MAX;
            uy[i][j] = (double) rand()/RAND_MAX;
        }
    }
    double m = 0;
    for (size_t i = 0; i < WIDTH; i++){
        for (size_t j = 0; j < HEIGHT; j++){
            double x = ux[i][j] * ux[i][j]  + uy[i][j] *  uy[i][j];
            if (x > m){
                m = x;
            }
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
                double dt = 1 *(ddx + ddy);
                uxtemp[i][j] = ux[i][j] +  dt;
                ddx = (uy[i + 1][j] - 2 * uy[i][j] + uy[i - 1][j])/ 4;
                ddy = (uy[i][j + 1] - 2 * uy[i][j] + uy[i][j - 1])/ 4;
                dt = 1 * (ddx + ddy);
                uytemp[i][j] = uy[i][j] +  dt;
             }
        }
        for (size_t i = 0; i < WIDTH; i++){
            uxtemp[i][0] = uxtemp[i][1];
            uxtemp[i][HEIGHT - 1] =uxtemp[i][HEIGHT -2];
            uytemp[i][0] = uytemp[i][1];
            uytemp[i][HEIGHT - 1] =uytemp[i][HEIGHT -2];
        }
        for (size_t j = 0; j < HEIGHT; j++){
            uxtemp[0][j] =uxtemp[1][j];
            uxtemp[WIDTH - 1][j] = uxtemp[WIDTH -2][j];
            uytemp[0][j] =uytemp[1][j];
            uytemp[WIDTH - 1][j] = uytemp[WIDTH -2][j];
        }
        ux = uxtemp;
        uy = uytemp;
        for (size_t i = 100; i < 300; i++){
            for (size_t j = 100; j < 300; j++){
                   // ux[i][j] = 0;
                    //uy[i][j] = 0;
            }
        }
        for (size_t i = 0; i < WIDTH; i++){
            for (size_t j = 0; j < HEIGHT; j++){
                pixels[4 *(WIDTH *j + i) + 1] = (uint8_t)((ux[i][j] * ux[i][j]  + uy[i][j] *  uy[i][j]) / m * 255);
            }
        }
        cout << uy[301][100] << endl;
        texture.update(pixels);
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}