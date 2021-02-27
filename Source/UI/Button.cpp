#include "Button.h"

//{Constructor and Destructor}
Button::Button(float x, float y, float width, float height,
               sf::Font* font, std::string text, unsigned characterSize,
               sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    this->buttonState = BTN_IDLE;
    this->font = font;

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->textIdleColor = textIdleColor;
    this->textHoverColor = textHoverColor;
    this->textActiveColor = textActiveColor;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(this->idleColor);

    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(textIdleColor);
    this->text.setCharacterSize(characterSize);
    this->text.setPosition(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
                           this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height);
}

Button::~Button()
{

}
//}

//{Accessors}
const bool Button::isPressed() const
{
    if (this->buttonState == BTN_PRESSED)
        return true;
    return false;
}
//}

//{Functions}
void Button::update(const sf::Vector2f mousePos)
{
    //Idle
    this->buttonState = BTN_IDLE;

    //Hover
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = BTN_HOVER;

        //Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->buttonState = BTN_PRESSED;
        }
    }

    switch(this->buttonState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        this->text.setFillColor(this->textIdleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        this->text.setFillColor(this->textHoverColor);
        break;
    case BTN_PRESSED:
        this->shape.setFillColor(this->activeColor);
        this->text.setFillColor(this->textActiveColor);
        break;
    default:
        this->shape.setFillColor(sf::Color::Red);
        this->text.setFillColor(sf::Color::Blue);
        break;
    }
}

void Button::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    target->draw(this->text);
}
//}
