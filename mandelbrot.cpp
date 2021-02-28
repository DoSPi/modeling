#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <vector>
#include <complex>
#include <fstream>
using namespace std;
    constexpr size_t WIDTH = 400;
    constexpr size_t HEIGHT = 400;
    double LX = -2 -1;
    double RX = 1 - 1;
    double LY = -1;
    double RY = 1;
    constexpr int N = 1000;
void update(vector<vector<int>> &grid)
{
    #pragma omp parallel
    #pragma omp for
    for (size_t i = 0; i < WIDTH; i++){
        for (size_t j = 0; j < HEIGHT; j++){
            grid[i][j] = N - 1;
            complex<double> c(LX + (double)(RX - LX) * i / WIDTH, LY + (double)(RY - LY) * j / HEIGHT);
            complex<double> z0 = 0;
            for (int t = 0; t < N; t++){
                complex<double> z1 = z0 * z0 + c;
                if (norm(z1) > 4){
                    grid[i][j] = t;
                    break;
                }
                z0 = z1;

            }
        }
    }   
}
void ppmwrite(const sf::Uint8 *pixels, const string &s)
{
    constexpr auto dimx = WIDTH, dimy = HEIGHT;
    using namespace std;
    ofstream ofs(s + ".ppm", ios_base::out | ios_base::binary);
    ofs << "P6" << endl << dimx << ' ' << dimy << endl << "255" << endl;
    for (auto j = 0u; j < dimy; ++j)
        for (auto i = 0u; i < dimx; ++i)
            ofs << (char) (pixels[4 *(WIDTH *j + i)]) << (char) (pixels[4 *(WIDTH *j + i) + 1]) << (char) (pixels[4 *(WIDTH *j + i) + 2]);       // red, green, blue
    ofs.close();
    return;
}
int main()
{
    srand(228);
    vector<vector<int>> grid(WIDTH, vector<int>(HEIGHT, N - 1));
    update(grid);
    vector<int> rcolor(N);
    vector<int> gcolor(N);
    vector<int> bcolor(N);
    for (int i = 0; i < N; i++){
        rcolor[i] = random()  % 255;
         gcolor[i] = random()  % 255;
          bcolor[i] = random()  % 255;

    }
           rcolor[N - 1] = 0;
         gcolor[N-1] = 0;
          bcolor[N-1] = 0;
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "Mandelbrot set");
    window.setFramerateLimit(10);
    srand(228);
    sf::Uint8 *pixels = new sf::Uint8[WIDTH * HEIGHT * 4];
    update(grid);
    for (size_t i = 0; i < WIDTH; i++){
        for (size_t j = 0; j < HEIGHT; j++){
            pixels[4 *(WIDTH *j + i) + 3] = 255;
        }
    }
    for(int z = 0; z < 100; z++){
        for (size_t i = 0; i < WIDTH; i++){
            for (size_t j = 0; j < HEIGHT; j++){
                pixels[4 *(WIDTH *j + i) + 0] = rcolor[grid[i][j]];
                pixels[4 *(WIDTH *j + i) + 1] = gcolor[grid[i][j]];
                pixels[4 *(WIDTH *j + i) + 2] = bcolor[grid[i][j]];
            }
        }
        ppmwrite(pixels, to_string(z));
        double xcenter = (LX + RX) /2;
        double ycenter = (LY + RY)/2;
        double xl = (RX - LX);
        double yl = (RY - LY);
        LX = xcenter -  (xl - 0.1) / 2 ;
        RX = xcenter + (xl -0.1) / 2;
        LY = ycenter - (yl -0.1) / 2;
        RY = ycenter + (yl - 0.1) / 2;
        update(grid);

    }
    return 0;
    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    sf::Sprite sprite(texture);
    int mx = 0;
    int my = 0;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled){
                float delta = event.mouseWheelScroll.delta;
                if (delta > 0){
                    delta =  0.9;
                    LX *=  delta;
                    RX *= delta;
                    LY *= delta;
                    RY *= delta;
                } else {
                    delta = 1.1;
                    LX *= delta;
                    RX *= delta;
                    LY *= delta;
                    RY *= delta;
                }
                update(grid);
            }
            
        }
        for (size_t i = 0; i < WIDTH; i++){
            for (size_t j = 0; j < HEIGHT; j++){
                pixels[4 *(WIDTH *j + i) + 0] = rcolor[grid[i][j]];
                pixels[4 *(WIDTH *j + i) + 1] = gcolor[grid[i][j]];
                pixels[4 *(WIDTH *j + i) + 2] = bcolor[grid[i][j]];
            }
        }
        return 0;
        texture.update(pixels);
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}