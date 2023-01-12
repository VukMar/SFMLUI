#include "../include/UI_Slider.hpp"

namespace vui
{
//Public:

Slider::Slider()
{

}

Slider::~Slider()
{

}

void Slider::create(float lenght, float thickness, sf::Vector2f Position)
{   
    if(thickness > lenght * 0.3)
        thickness = lenght * 0.3;
    
    headLength = thickness;
    SliderArea.setSize(sf::Vector2f(lenght, thickness));
    SliderHead.setSize(sf::Vector2f(thickness,thickness));
    SliderArea.setPosition(Position);
    SliderHead.setPosition(Position);
}

void Slider::Update(sf::RenderWindow &Window)
{
    checkAttributsChanges();

    CursorPos = sf::Vector2f(sf::Mouse::getPosition(Window));

    if(!mouseOverArea())
    {
        if(mouseLeftHeld())
            WFocus = true;
        else
        {
            WFocus = false;
        }
        
    }
    else if(mouseOverArea() && !WFocus)
    {
        if(sliderHeadGrabed())
        {
            CursorPos.y = SliderHead.getPosition().y + SliderHead.getSize().y / 2;
            sf::Mouse::setPosition(sf::Vector2i(CursorPos), Window);
            SliderHead.setPosition(CursorPos.x - SliderHead.getSize().x/2, SliderHead.getPosition().y);
        }
        else if(mouseLeftReleased())
        {
            SliderHead.setPosition(CursorPos.x - SliderHead.getSize().x/2, SliderHead.getPosition().y);
        }
    }
    sf::Vector2f HeadPos = SliderHead.getPosition();
    sf::Vector2f HeadSize = SliderHead.getSize();

    sf::Vector2f AreaPos = SliderArea.getPosition();
    sf::Vector2f AreaSize = SliderArea.getSize();

    if(HeadPos.x < AreaPos.x)
    {
        SliderHead.setPosition(AreaPos.x,HeadPos.y);
    }
    else if(HeadPos.x + HeadSize.x > AreaPos.x + AreaSize.x)
    {
        SliderHead.setPosition(AreaPos.x + AreaSize.x - HeadSize.x ,HeadPos.y);
    }
    
    percent = int(ceil(100*((HeadPos.x - AreaPos.x) / (AreaSize.x - HeadSize.x))));
}

void Slider::displayTo(sf::RenderWindow &Window)
{
    Window.draw(SliderArea);
    Window.draw(SliderHead);
}

int Slider::getPercentValue()
{
    return percent;
}

void Slider::setHeadColor(sf::Color Color)
{
    HeadColor = Color;
}

void Slider::setAreaColor(sf::Color Color)
{
    AreaColor = Color;
}

void Slider::setHeadOutlineThickness(float Thickness)
{
    HeadOutlineThickness = Thickness;
}

void Slider::setAreaOutlineThickness(float Thickness)
{
    AreaOutlineThickness = Thickness;
}

void Slider::setHeadOutlineColor(sf::Color Color)
{
    HeadOutlineColor = Color;
}

void Slider::setAreaOutlineColor(sf::Color Color)
{
    AreaOutlineColor = Color;
}

void Slider::setHeadLength(float Length)
{
    headLength = Length;
}

void Slider::setStartingValue(int value)
{
    sf::Vector2f HeadPos = SliderHead.getPosition();
    sf::Vector2f HeadSize = SliderHead.getSize();

    sf::Vector2f AreaPos = SliderArea.getPosition();
    sf::Vector2f AreaSize = SliderArea.getSize();
    
    value = (value > 100)? 100 : value;
    value = (value < 0)? 0 : value;
    
    percent = int(ceil(100*((HeadPos.x - AreaPos.x) / (AreaSize.x - HeadSize.x))));
    if(percent > value)
    {
        SliderHead.move(-1.f,0.f);
        setStartingValue(value);
    }
    if(percent < value)
    {
        SliderHead.move(1.f,0.f);
        setStartingValue(value);
    }
}

void Slider::checkAttributsChanges()
{
    //Slider head check
    if(SliderHead.getFillColor() != HeadColor)
        SliderHead.setFillColor(HeadColor);
    if(SliderHead.getOutlineColor() != HeadOutlineColor)
        SliderHead.setOutlineColor(HeadOutlineColor);
    if(SliderHead.getOutlineThickness() != HeadOutlineThickness)
        SliderHead.setOutlineThickness(HeadOutlineThickness);
    if(headLength != SliderHead.getSize().x)
    {
        if(headLength > SliderArea.getSize().x/4)
        {
            headLength = SliderArea.getSize().x/4;
        }
        SliderHead.setSize(sf::Vector2f(headLength, SliderHead.getSize().y));
    }

    //Slider area check
    if(SliderArea.getFillColor() != AreaColor)
        SliderArea.setFillColor(AreaColor);
    if(SliderArea.getOutlineColor() != AreaOutlineColor)
        SliderArea.setOutlineColor(AreaOutlineColor);
    if(SliderArea.getOutlineThickness() != AreaOutlineThickness)
        SliderArea.setOutlineThickness(AreaOutlineThickness);
    
}

sf::Color Slider::getHeadColor()
{
    return HeadColor;
}

sf::Color Slider::getAreaColor()
{
    return AreaColor;
}

float Slider::getHeadOutlineThickness()
{
    return HeadOutlineThickness;
}

float Slider::getAreaOutlineThickness()
{
    return AreaOutlineThickness;
}

sf::Color Slider::getHeadOutlineColor()
{
    return HeadOutlineColor;
}

sf::Color Slider::getAreaOutlineColor()
{
    return AreaOutlineColor;
}

//Private:

bool Slider::sliderHeadGrabed()
{
    if(mouseOverHead())
    {
        if(mouseLeftHeld())
            return true;
    }
    return false;
}

bool Slider::mouseOverHead()
{
    sf::Vector2f HeadPos = SliderHead.getPosition();
    sf::Vector2f HeadSize = SliderHead.getSize();
    
    if(CursorPos.x > HeadPos.x && CursorPos.x < HeadPos.x + HeadSize.x
    && CursorPos.y > HeadPos.y && CursorPos.y < HeadPos.y + HeadSize.y)
        return true;
    else
        return false;
}

bool Slider::mouseOverArea()
{
    sf::Vector2f AreaPos = SliderArea.getPosition();
    sf::Vector2f AreaSize = SliderArea.getSize();

    if(CursorPos.x > AreaPos.x && CursorPos.x < AreaPos.x + AreaSize.x
    && CursorPos.y > AreaPos.y && CursorPos.y < AreaPos.y + AreaSize.y)
        return true;
    else
        return false;
}

bool Slider::mouseLeftHeld()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        return true;
    }
    return false;
}

bool Slider::mouseLeftReleased()
{
    if(mouseLeftHeld())
    {
        leftMouseHeld = true;
        return false;
    }
    else if(leftMouseHeld)
    {
        leftMouseHeld = false;
        return true;
    }
    return false;
}

}