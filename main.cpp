// image.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

void input(Image image, std::vector<std::vector<std::vector<int>>> g,int x,int y) {
    for (int i = 0; i < x; i++) {
        for (int z = 0; z < y; z++) {
            Color h;
            h.r = g[i][z][0];
            h.g = g[i][z][1];
            h.b = g[i][z][2];
            image.setPixel(i, z, h);
        }
    }
}

void output(std::vector<std::vector<std::vector<int>>> g,Image image,int x,int y) {
    for (int i = 0; i < x; i++) {
        std::vector<std::vector<int>> l (y);
        for (int z = 0; z < y; z++) {
            Color f = image.getPixel(i, z);
            std::vector<int> j = { int(f.r),int(f.g),int(f.b) };
            l.push_back(j);
        }
        g.push_back(l);
    }
}

int ColorDist(int color,int maxDist,int minDist) {
    int y = color * (maxDist - minDist)/255 + minDist;
    return y;
}

bool CircleDist(int color,int maxDist,int minDist,int distX,int x, int y,int screenLong,Image image) {
    int r = ColorDist(color, maxDist, minDist);
    int startX = x - r;
    int endX = x + r;
    int startY = y - r;
    int bufer;
    if ((x - distX) < r)return false;
    if (startX < 0)startX = 0;
    if (endX >= screenLong)endX = screenLong-1;
    if (startY < 0)startY = 0;
    for (int i = startX; i < endX; i++) {
        for (int z = startY; z < y; z++) {
            bufer = image.getPixel(i, z).r;
            if (bufer == 0) {
                int dR =sqrt( pow(i - x, 2) + pow(z - y, 2));
                if (dR < r)return false;
               
            }
        }
    }
    return true;
}

int main()
{
    Image image; //создаем объект Image (изображение)
    image.loadFromFile("l.jpg");
    int x = image.getSize().x;
    int y = image.getSize().y;
 //   std::vector<std::vector<std::vector<int>>> g (x);
 //   output(g, image,x,y);
/*    for (int i = 0; i < image.getSize().x; i++) {
        g[i] = new int*[image.getSize().y];
        for (int z = 0; z < image.getSize().y; z++) {
            Color f = image.getPixel(i, z);
            g[i][z] = new int[3];
            g[i][z][0] = int(f.r);
            g[i][z][1] = int(f.g);
            g[i][z][2] = int(f.b);
        }
    }*/
    //work space
/*    for (int i = 0; i < x; i++) {
        for (int z = 0; z < y; z++) {
            int d = g[i][z][0] + g[i][z][1] + g[i][z][2];
            d =d/ 3;
            g[i][z][2] = 0;
            g[i][z][1] = 0;
            g[i][z][0] = 0;
        }
    }*/
    std::cout << x;







    //work space out
  //  input(image, g,x,y);
    /*
    for (int i = 0; i < image.getSize().x; i++) {
        for (int z = 0; z < image.getSize().y; z++) {
            Color h;
            h.r= g[i][z][0];
            h.g = g[i][z][1];
            h.b = g[i][z][2];
            image.setPixel(i, z, h);
        }
    }*/
    for (int i = 0; i < x; i++) {
        for (int z = 0; z < y; z++) {
            Color h = image.getPixel(i, z);
            int v = h.r + h.g + h.b;
            v /= 3;
            h.r = v;
            h.g = v;
            h.b = v;
            image.setPixel(i, z, h);
        }
    }
    int dist = -20;
    int minDist = 0;
    int maxDist = 5;
    Color b =Color(0, 0, 0, 255);
    Color w = Color(255, 255, 255, 255);
    /*
    for (int i = 0; i < y; i++) {
        image.setPixel(0,i,b);
        dist = 0;
        for (int z = 1; z < x; z++) {
            if ((z-dist)>ColorDist(image.getPixel(z,i).r,maxDist,minDist)) {
                image.setPixel(z, i, b);
                dist = z;
            }
            else {
                image.setPixel(z, i, w);
            }//it is work

     
        }
    }*/
    for (int i = 0; i < y; i++) {
        image.setPixel(0, i, b);
        dist = 0;
        std::cout << i;
        for (int z = 1; z < x; z++) {
            if (CircleDist(image.getPixel(z, i).r, maxDist, minDist, dist, z, i, x, image)) {
                image.setPixel(z, i, b);
                dist = z;
            }
            else {
                image.setPixel(z, i, w);
            }
        }
    }
    //CircleDist(image.getPixel(i,z).r,maxDist,minDist,dist,i,z,x,image)
    image.saveToFile("fff.jpg");

    RenderWindow window(VideoMode(image.getSize().x, image.getSize().y), "eeee"); //увеличили для удобства размер окна


    Texture herotexture;//создаем объект Texture (текстура)
    herotexture.loadFromImage(image);//передаем в него объект Image (изображения)

    Sprite herosprite;//создаем объект Sprite(спрайт)
    herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
    herosprite.setPosition(0, 0);//задаем начальные координаты появления спрайта

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(herosprite);//выводим спрайт на экран
        window.display();
    }

    return 0;
}
