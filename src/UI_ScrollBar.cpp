#include "../include/UI_ScrollBar.hpp"
namespace vui
{

ScrollBar::ScrollBar(){
    HoverColor = sf::Color::White;
    MainColor = sf::Color::White;
    MainColor.a = 180;
}
ScrollBar::~ScrollBar(){}

void ScrollBar::create(float size,sf::Vector2f VisibleArea, int Orientation)
{
    switch(Orientation)
    {
        case vui::Orientation::Vertical::Left:
            Vertical = true;
            Max = (Max == 0 || Max < VisibleArea.y)? VisibleArea.y : Max;
            StartingPosition = sf::Vector2f(0.f, 0.f);
            ButtonOnePosition = sf::Vector2f(0.f, 0.f);
            ScrollBarAreaSize = sf::Vector2f(size, VisibleArea.y - (2 * size));
            ScrollBarPosition = sf::Vector2f(0.f, size);
            ScrollBarSize = sf::Vector2f(size, ScrollBarAreaSize.y * (ScrollBarAreaSize.y / Max));
            ButtonTwoPosition = sf::Vector2f(0.f, ScrollBarPosition.y + ScrollBarAreaSize.y);
            break;
        case vui::Orientation::Vertical::Right:
            Vertical = true;
            Max = (Max == 0 || Max < VisibleArea.y)? VisibleArea.y : Max;
            StartingPosition = sf::Vector2f(VisibleArea.x - size, 0.f);
            ButtonOnePosition = sf::Vector2f(VisibleArea.x - size, 0.f);
            ScrollBarAreaSize = sf::Vector2f(size, VisibleArea.y - (2 * size));
            ScrollBarPosition = sf::Vector2f(VisibleArea.x - size, size);
            ScrollBarSize = sf::Vector2f(size, ScrollBarAreaSize.y * (ScrollBarAreaSize.y / Max));
            ButtonTwoPosition = sf::Vector2f(VisibleArea.x - size, ScrollBarPosition.y + ScrollBarAreaSize.y);
            break;
        case vui::Orientation::Horizontal::Top:
            Horizontal = true;
            Max = (Max == 0 || Max < VisibleArea.x)? VisibleArea.x : Max;
            StartingPosition = sf::Vector2f(0.f, 0.f);
            ButtonOnePosition = sf::Vector2f(0.f, 0.f);
            ScrollBarAreaSize = sf::Vector2f(VisibleArea.x - (2 * size), size);
            ScrollBarPosition = sf::Vector2f(size, 0.f);
            ScrollBarSize = sf::Vector2f(ScrollBarAreaSize.x - (Max - VisibleArea.x), size);
            ButtonTwoPosition = sf::Vector2f(ScrollBarPosition.x + ScrollBarAreaSize.x, 0.f);
            break;
        case vui::Orientation::Horizontal::Bottom:
            Horizontal = true;
            Max = (Max == 0 || Max < VisibleArea.x)? VisibleArea.x : Max;
            StartingPosition = sf::Vector2f(0.f, VisibleArea.y - size);
            ButtonOnePosition = sf::Vector2f(0.f, VisibleArea.y - size);
            ScrollBarAreaSize = sf::Vector2f(VisibleArea.x - (2 * size), VisibleArea.y - size);
            ScrollBarPosition = sf::Vector2f(size, VisibleArea.y - size);
            ScrollBarSize = sf::Vector2f(ScrollBarAreaSize.x - (Max - VisibleArea.x), size);
            ButtonTwoPosition = sf::Vector2f(ScrollBarPosition.x + ScrollBarAreaSize.x, VisibleArea.y - size);
            break;
        default:
            create(size,VisibleArea, vui::Orientation::Vertical::Left);
            break;
    }
    //Button one creation
    UpOrLeft.create("",size*0.8f, sf::Vector2f(size,size), ButtonOnePosition, MainColor, HoverColor);
    //Scroll bar area creation
    ScrollBarArea.setSize(ScrollBarAreaSize);
    ScrollBarArea.setPosition(ScrollBarPosition);
    ScrollBarArea.setFillColor(sf::Color::Transparent);
    ScrollBarArea.setOutlineColor(MainColor);
    ScrollBarArea.setOutlineThickness(-2.f);
    //Slider bar creation
    Bar.setPosition(ScrollBarPosition);
    Bar.setSize(ScrollBarSize);
    Bar.setFillColor(MainColor);
    //Button 2 creation
    DownOrRight.create("",size*0.8f, sf::Vector2f(size,size), ButtonTwoPosition, MainColor, HoverColor);
}

void ScrollBar::displayTo(sf::RenderWindow &win)
{
    win.draw(ScrollBarArea);
    UpOrLeft.displayTo(win);
    if(UpOrLeft.isButtonHeldDown(win))
    {
        if(Vertical && Bar.getPosition().y - 1.f >= ScrollBarArea.getPosition().y) 
            Bar.move(0.f, -1.f);
        else if(Horizontal && Bar.getPosition().x - 1.f >= ScrollBarArea.getPosition().x)
            Bar.move(-1.f, 0.f);
    }
    DownOrRight.displayTo(win);
    if(DownOrRight.isButtonHeldDown(win))
    {
        if(Vertical 
        && Bar.getPosition().y + Bar.getSize().y + 1.f <= ScrollBarArea.getPosition().y + ScrollBarAreaSize.y) 
            Bar.move(0.f, 1.f);
        else if(Horizontal 
        && Bar.getPosition().x + Bar.getSize().x + 1.f <= ScrollBarArea.getPosition().x + ScrollBarAreaSize.x) 
            Bar.move(1.f, 0.f);
    }
    if(!mouseOverBar(win))
    {
        wFocus = (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))? true : false;
        if(MouseOverScrollBarArea(win) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if(Vertical)
            {
                Bar.setPosition(Bar.getPosition().x, sf::Mouse::getPosition(win).y-(Bar.getSize().y/2));
                if(Bar.getPosition().y < ScrollBarArea.getPosition().y)
                {
                    Bar.setPosition(ScrollBarArea.getPosition());
                }
                else if(Bar.getPosition().y + Bar.getSize().y > ScrollBarArea.getPosition().y + ScrollBarArea.getSize().y)
                {
                    Bar.setPosition(Bar.getPosition().x, ButtonTwoPosition.y - Bar.getSize().y);
                }
            }
            if(Horizontal)
            {
                Bar.setPosition(sf::Mouse::getPosition(win).x-(Bar.getSize().x/2), Bar.getPosition().y);
                if(Bar.getPosition().x < ScrollBarArea.getPosition().x)
                {
                    Bar.setPosition(ScrollBarArea.getPosition());
                }
                else if(Bar.getPosition().x + Bar.getSize().x > ScrollBarArea.getPosition().x + ScrollBarArea.getSize().x)
                {
                    Bar.setPosition(ButtonTwoPosition.x - Bar.getSize().x, Bar.getPosition().y);
                }

            }
        }
    }
    if(mouseOverBar(win))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !wFocus)
        {
            if(!SliderHeld)
            {
                HeldAtDistance.x = sf::Mouse::getPosition(win).x - Bar.getPosition().x;
                HeldAtDistance.y = sf::Mouse::getPosition(win).y - Bar.getPosition().y;
                SliderHeld = true;
            }
            sf::Vector2f CursorPos = sf::Vector2f(sf::Mouse::getPosition(win));
            if(Vertical)
            {
                float Y = (CursorPos.y - Bar.getPosition().y) - HeldAtDistance.y;
                sf::Mouse::setPosition(sf::Vector2i(HeldAtDistance.x + Bar.getPosition().x, sf::Mouse::getPosition(win).y), win);
                //Bottom side
                Bar.move(0.f, Y);
                if(Bar.getPosition().y < ScrollBarArea.getPosition().y)
                {
                    Bar.setPosition(ScrollBarArea.getPosition());
                }
                else if(Bar.getPosition().y + Bar.getSize().y > ScrollBarArea.getPosition().y + ScrollBarArea.getSize().y)
                {
                    Bar.setPosition(Bar.getPosition().x, ButtonTwoPosition.y - Bar.getSize().y);
                }
            }
            else if(Horizontal)
            {
                float X = (CursorPos.x - Bar.getPosition().x) - HeldAtDistance.x;
                sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition(win).x, HeldAtDistance.y + Bar.getPosition().y), win);
                //Right side
                Bar.move(X, 0.f);
                if(Bar.getPosition().x < ScrollBarArea.getPosition().x)
                {
                    Bar.setPosition(ScrollBarArea.getPosition());
                }
                else if(Bar.getPosition().x + Bar.getSize().x > ScrollBarArea.getPosition().x + ScrollBarArea.getSize().x)
                {
                    Bar.setPosition(ButtonTwoPosition.x - Bar.getSize().x, Bar.getPosition().y);
                }
            }
        }
        else
        {
            SliderHeld = false;
        }
    }
    if(!SliderHeld) Bar.setOrigin(0,0);
    win.draw(Bar);
}
    
void ScrollBar::setPosition(float PositionX, float PositionY)
{

}

void ScrollBar::setSize(float size)
{

}

sf::Vector2f ScrollBar::getPosition()
{
    return ScrollBarArea.getPosition();
}

sf::Vector2f ScrollBar::getOffset()
{
    sf::Vector2f toReturn = sf::Vector2f(OffsetX, OffsetY);
    OffsetX = 0;
    OffsetY = 0;
    return toReturn;
}

bool ScrollBar::barMoved(sf::RenderWindow &win)
{   
    if(Bar.getPosition().x != ScrollBarPosition.x)
    {
        OffsetX = (ScrollBarPosition.x - Bar.getPosition().x) * (Max / ScrollBarAreaSize.x);
        ScrollBarPosition = Bar.getPosition();
        return true;
    }
    if(Bar.getPosition().y != ScrollBarPosition.y)
    {
        OffsetY = (ScrollBarPosition.y - Bar.getPosition().y) * (Max / ScrollBarAreaSize.y);
        ScrollBarPosition = Bar.getPosition();
        return true;
    }
    return false;
}

void ScrollBar::moveBar(float Offset)
{
    if(Vertical)
    {
        Bar.move(0, Offset);
        if(Bar.getPosition().y < ScrollBarArea.getPosition().y)
        {
            Bar.setPosition(ScrollBarArea.getPosition());
        }
        else if(Bar.getPosition().y + Bar.getSize().y > ScrollBarArea.getPosition().y + ScrollBarArea.getSize().y)
        {
            Bar.setPosition(Bar.getPosition().x, ButtonTwoPosition.y - Bar.getSize().y);
        }
    }
    else if(Horizontal)
    {
        Bar.move(Offset, 0);
        if(Bar.getPosition().x < ScrollBarArea.getPosition().x)
        {
            Bar.setPosition(ScrollBarArea.getPosition());
        }
        else if(Bar.getPosition().x + Bar.getSize().x > ScrollBarArea.getPosition().x + ScrollBarArea.getSize().x)
        {
            Bar.setPosition(ButtonTwoPosition.x - Bar.getSize().x, Bar.getPosition().y);
        }
    }   
}

//==============================================================================================================

bool ScrollBar::mouseOverBar(sf::RenderWindow &win)
{
    sf::Vector2f MousePos = sf::Vector2f(sf:: Mouse::getPosition(win));

    if(MousePos.x > Bar.getPosition().x && MousePos.x < Bar.getPosition().x + Bar.getSize().x 
    && MousePos.y > Bar.getPosition().y && MousePos.y < Bar.getPosition().y + Bar.getSize().y)
    {
        Bar.setFillColor(HoverColor);
        return true;
    }
    else Bar.setFillColor(MainColor);
    return false;
}

bool ScrollBar::MouseOverScrollBarArea(sf::RenderWindow &win)
{
    sf::Vector2f MousePos = sf::Vector2f(sf:: Mouse::getPosition(win));

    if(MousePos.x > ScrollBarArea.getPosition().x && MousePos.x < ScrollBarArea.getPosition().x + ScrollBarArea.getSize().x 
    && MousePos.y > ScrollBarArea.getPosition().y && MousePos.y < ScrollBarArea.getPosition().y + ScrollBarArea.getSize().y)
    {
        return true;
    }
    return false;
}


}