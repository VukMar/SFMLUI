#include "../include/UI_Slider.hpp"

//Public:

namespace vui
{

void Slider::Create(sf::Vector2f Position, sf::Vector2f Size, std::string Style, int Orientation)
{
    if(Style == "Basic" || Style == "Rounded")
    {
        SliderStyle = Style;
        Pos = Position;
        SliderSize = (Orientation == Orientation::Horizontal)? Size : sf::Vector2f(Size.y, Size.x);
        (Orientation == Orientation::Horizontal)? isHorizontal = true : isVertical = true;
        SliderArea.setSize(SliderSize);
        if(Style == "Basic")
        {
            SliderArea.setPosition(Position);
            Indicator.setSize(sf::Vector2f(0.f,0.f));
            Indicator.setPosition(Position);
            SliderHead1.setSize(sf::Vector2f(Size.y, Size.y));
            if(isHorizontal)
            {
                SliderHead1.setOrigin(0.f, Size.y / 2.f);
                SliderHead1.setPosition(Position.x, Position.y - SliderHead1.getSize().y/2.f);
            }
            else if(isVertical)
            {
                SliderHead1.setOrigin(Size.y / 2.f, 0.f);
                SliderHead1.setPosition(Position.x - SliderHead1.getSize().x/2.f, Position.y);
            }
        }
        else if(Style == "Rounded")
        {
            SliderHead2.setRadius(Size.y*0.6);
            EndPiece1_c.setRadius(Size.y*0.5);
            EndPiece2_c.setRadius(Size.y*0.5);
        }
        SliderCreated = true;
    }
}

void Slider::displayTo(sf::RenderWindow &win)
{
    if(SliderCreated)
    {
        if(SliderStyle == "Basic") drawBasic(win);
        else if(SliderStyle == "Rounded") drawRounded(win);
    }
}

//Private:

bool Slider::mouseLeftCilckReleased()
{
    return false;
}

void Slider::drawBasic(sf::RenderWindow &win)
{
    win.draw(SliderArea);
    win.draw(Indicator);
    win.draw(SliderHead1);
}

void Slider::drawRounded(sf::RenderWindow &win)
{

}


}