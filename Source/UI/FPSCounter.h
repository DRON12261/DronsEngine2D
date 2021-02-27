#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

//{Includes}
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include <stddef.h>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
//}

class FPSCounter
{
private:
    //{Variables}
    sf::Clock clock;
    sf::Time time1;
    sf::Time time2;
    sf::Clock renderTimer;
    sf::Text text;
    int Framerate;
    //}
public:
    //{Constructor and Destructor}
    FPSCounter(sf::Font& font);
    virtual ~FPSCounter();
    //}

    //{Accessors}
    const int& getFramerate() const;
    //}

    //{Functions}
    void update();
    void render(sf::RenderTarget* target);
    //}
};

#endif
