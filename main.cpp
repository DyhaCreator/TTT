#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

class Graph{
public:
    bool isOpen = true;
    const int Width = 30;
    const int Height = 30;
    sf::Event ev;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(Width, Height), "ttt");
    sf::Image screen;
    Graph(){
        this->window.setFramerateLimit(4);
        screen.loadFromFile("1.png");
    }
    void update(){
        this->isOpen = this->window.isOpen();
        while(this->window.pollEvent(this->ev)){
            switch(this->ev.type){
            case sf::Event::Closed:
                this->window.close();
                break;
            }
        }
    }
    void render(){
        /*sf::Texture texture;
        texture.update(this->window);
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(50, 0);
        this->window.draw(sprite);*/
        this->window.display();
        //this->window.clear(sf::Color(0, 0, 0));
    }
    void clr() {
        //this->window.clear(sf::Color(0, 0, 0));
        screen.create(300, 300, sf::Color(0, 255, 0));
    }
};
Graph gr = Graph();

vector<vector<vector<int>>>maps = vector<vector<vector<int>>>();

vector<vector<int>> rm1(vector<vector<int>>m) {
    vector<vector<int>>m2 = m;
    m2[0][0] = m[0][2];
    m2[0][1] = m[1][2];
    m2[0][2] = m[2][2];
    m2[1][0] = m[0][1];
    m2[1][2] = m[2][1];
    m2[2][0] = m[0][0];
    m2[2][1] = m[1][0];
    m2[2][2] = m[2][0];
    return m2;
}

vector<vector<int>> rm2(vector<vector<int>>m) {
    vector<vector<int>>m2 = m;
    m2[0][0] = m[2][2];
    m2[0][1] = m[2][1];
    m2[0][2] = m[2][0];
    m2[1][0] = m[1][2];
    m2[1][2] = m[1][0];
    m2[2][0] = m[0][2];
    m2[2][1] = m[0][1];
    m2[2][2] = m[0][0];
    return m2;
}

vector<vector<int>> rm3(vector<vector<int>>m) {
    vector<vector<int>>m2 = m;
    m2[0][0] = m[2][0];
    m2[0][1] = m[1][0];
    m2[0][2] = m[0][0];
    m2[1][0] = m[2][1];
    m2[1][2] = m[0][1];
    m2[2][0] = m[2][2];
    m2[2][1] = m[1][2];
    m2[2][2] = m[0][2];
    return m2;
}

vector<vector<int>> mm(vector<vector<int>>m) {
    vector<vector<int>>m2 = m;
    m2[0][0] = m[0][2];
    m2[0][2] = m[0][0];
    m2[1][0] = m[1][2];
    m2[1][2] = m[1][0];
    m2[2][0] = m[2][2];
    m2[2][2] = m[2][0];
    return m2;
}

bool f2(vector<vector<int>>map) {
    vector<vector<int>>mapRM1 = rm1(map);
    vector<vector<int>>mapRM2 = rm2(map);
    vector<vector<int>>mapRM3 = rm3(map);
    vector<vector<int>>mapRM1M = mm(mapRM1);
    vector<vector<int>>mapRM2M = mm(mapRM2);
    vector<vector<int>>mapRM3M = mm(mapRM3);
    vector<vector<int>>mapM = mm(map);
    for (int i = 0; i < maps.size(); i++) {
        if (maps[i] == mapRM1 || maps[i] == mapRM2 || maps[i] == mapRM3 ||
            maps[i] == mapRM1M || maps[i] == mapRM2M || maps[i] == mapRM3M ||
            maps[i] == mapM) {
            return false;
        }
    }
    return true;
}

bool isFull(vector<vector<int>>map) {
    if (map[0][0] == 1 && map[0][1] == 1 && map[0][2] == 1) return true;
    if (map[1][0] == 1 && map[1][1] == 1 && map[1][2] == 1) return true;
    if (map[2][0] == 1 && map[2][1] == 1 && map[2][2] == 1) return true;
    if (map[0][0] == 1 && map[1][0] == 1 && map[2][0] == 1) return true;
    if (map[0][1] == 1 && map[1][1] == 1 && map[2][1] == 1) return true;
    if (map[0][2] == 1 && map[1][2] == 1 && map[2][2] == 1) return true;
    if (map[0][0] == 1 && map[1][1] == 1 && map[2][2] == 1) return true;
    if (map[0][2] == 1 && map[1][1] == 1 && map[2][0] == 1) return true;

    if (map[0][0] == 2 && map[0][1] == 2 && map[0][2] == 2) return true;
    if (map[1][0] == 2 && map[1][1] == 2 && map[1][2] == 2) return true;
    if (map[2][0] == 2 && map[2][1] == 2 && map[2][2] == 2) return true;
    if (map[0][0] == 2 && map[1][0] == 2 && map[2][0] == 2) return true;
    if (map[0][1] == 2 && map[1][1] == 2 && map[2][1] == 2) return true;
    if (map[0][2] == 2 && map[1][2] == 2 && map[2][2] == 2) return true;
    if (map[0][0] == 2 && map[1][1] == 2 && map[2][2] == 2) return true;
    if (map[0][2] == 2 && map[1][1] == 2 && map[2][0] == 2) return true;
    
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (map[y][x] == 0) {
                return false;
            }
        }
    }
    return true;
}

char f(int a, int x, int y) {
    if (a == 1) {
        sf::RectangleShape line(sf::Vector2f(140, 10));
        line.setPosition(10 + 100 * y, 0 + 100 * x);
        line.rotate(45);
        gr.window.draw(line);
        sf::RectangleShape line2(sf::Vector2f(140, 10));
        line2.setPosition(100 * y, 100 + 100 * x);
        line2.rotate(-45);
        gr.window.draw(line2);
        return 'X';
    }
    if (a == 2) {
        sf::CircleShape circle(50);
        circle.setPosition(100 * y, 100 * x);
        circle.setFillColor(sf::Color(0, 0, 0));
        circle.setOutlineThickness(-10);
        circle.setOutlineColor(sf::Color(255, 255, 255));
        gr.window.draw(circle);
        return 'O';
    }
    return ' ';
}

int num = 0;

void rec(vector<vector<int>>map, vector<int>hystory, int h) {
    if (isFull(map)) {
        num++;
        if (f2(map)) {
            for (auto x : hystory) {
                //cout << x << " ";
                if (x != 0) {
                    f(map[(x - 1) / 3][(x - 1) % 3], (x - 1) / 3, (x - 1) % 3);
                    sf::Texture texture;
                    texture.setImage(gr.screen);
                    cout << texture.getSize().x << endl;
                    sf::Image img;
                    img = texture.copyToImage();
                    for (int y = 0; y < 10; y++) {
                        for (int x = 0; x < 10; x++) {
                            sf::Color c = img.getPixel(x, y);
                            cout << c.r << " " << c.g << " " << c.b << "  ";
                        }
                        cout << endl;
                    }
                    gr.render();
                    gr.update();
                }
            }
            cout << endl;

            sf::RectangleShape rectangle(sf::Vector2f(120, 50));

            // change the size to 100x100
            rectangle.setSize(sf::Vector2f(100, 100));

            //cout << f(map[0][0], 0, 0) << f(map[0][1], 0, 1) << f(map[0][2], 0, 2) << endl;
            //cout << f(map[1][0], 1, 0) << f(map[1][1], 1, 1) << f(map[1][2], 1, 2) << endl;
            //cout << f(map[2][0], 2, 0) << f(map[2][1], 2, 1) << f(map[2][2], 2, 2) << endl;

            maps.push_back(map);
            cout << num << " " << maps.size() << endl;
            gr.render();
            gr.update();
            gr.clr();
        }
        //usleep((float)1000000/(float)60);
        return;
    }
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (map[y][x] == 0) {
                if (h % 2 == 0) {
                    map[y][x] = 1;
                    hystory[h] = y * 3 + x + 1;
                    rec(map, hystory, h + 1);
                    hystory[h] = 0;
                    map[y][x] = 0;
                } else {
                    map[y][x] = 2;
                    hystory[h] = y * 3 + x + 1;
                    rec(map, hystory, h + 1);
                    hystory[h] = 0;
                    map[y][x] = 0;
                }
            }
        }
    }
}

int main() {
    gr.screen.create(300, 300, sf::Color(0, 255, 0));
    /*vector<vector<int>>mp = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}
    };
    vector<vector<int>>mp2 = rm3(mp);
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            cout << mp2[y][x] << ' ';
        }
        cout << endl;
    }*/
    rec(vector<vector<int>>(3, vector<int>(3)), vector<int>(9), 0);
    /*while (gr.isOpen) {
        gr.update();
        gr.render();
    }*/
    return 0;
}