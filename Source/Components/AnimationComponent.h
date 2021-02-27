#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

//{Includes}
#include <iostream>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
//}

class AnimationComponent
{
private:
    //{Animation private class}
    class Animation
    {
    public:
        //{Variables}
        sf::Texture& textureSheet;
        float speed;
        int width;
        int height;
        sf::IntRect startRect;
        sf::IntRect endRect;
        //}

        //{Constructor and Destructor}
        Animation(sf::Texture& textureSheet, float speed,
            int startX, int startY, int endX, int endY, int width, int height)
            : textureSheet(textureSheet), speed(speed), width(width), height(height)
        {
            this->startRect = sf::IntRect(startX, startY, width, height);
            this->endRect = sf::IntRect(endX, endY, width, height);
        }
        //}

        //{Functions}
        void update(const float& dt);
        void play();
        void pause();
        void reset();
        //}

    };
    //}

    //{Variables}
    std::map<std::string, Animation> animations;
    //}
public:
    //{Constructor and Destructor}
    AnimationComponent();
    virtual ~AnimationComponent();
    //}

    //{Functions}

    //}

};

#endif
