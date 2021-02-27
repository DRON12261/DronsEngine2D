#include "FPSCounter.h"

//{Constructor and Destructor}
FPSCounter::FPSCounter(sf::Font& font)
{
    this->time2 = this->clock.getElapsedTime();
    Framerate = 0;
    this->text.setFont(font);
    this->text.setCharacterSize(18);
    this->text.setFillColor(sf::Color::White);
    this->text.setString("FPS: ");
    this->text.setPosition(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
}

FPSCounter::~FPSCounter()
{

}
//}

//{Accessors}
const int& FPSCounter::getFramerate() const
{
    return this->Framerate;
}
//}

//{Functions}
void FPSCounter::update()
{
    this->time1 = this->clock.getElapsedTime();
    this->Framerate = 1.f / (this->time1 - this->time2).asSeconds();
    this->time2 = this->time1;
}

void FPSCounter::render(sf::RenderTarget* target)
{
    if (this->renderTimer.getElapsedTime().asMilliseconds() > 250.f)
    {
        std::stringstream ss;
        ss << Framerate;
        this->text.setString("FPS: " + ss.str());
        this->renderTimer.restart();
    }
    target->draw(this->text);
}
//}
