#include "../include/UI_CheckBox.hpp"

namespace vui
{

CheckBox::CheckBox()
{
    MainColor = sf::Color::White;
    CheckColor = sf::Color::Black;
}
CheckBox::~CheckBox(){}

void CheckBox::create(float Size, sf::Vector2f Position, int Style)
{
    BoxSize = Size;
    BoxPosition = Position;
    switch(Style)
    {
    case vui::Style::Circle:
        createMainBox(vui::Style::Circle);
        createCheckMarker(vui::Style::Circle);
        consolelog("Created Circle Checkbox!");
        break;
    case vui::Style::Square:
        createMainBox(vui::Style::Square);
        createCheckMarker(vui::Style::Square);
        consolelog("Created Square Checkbox!");
        break;
    case vui::Style::None:
        MainBoxCreated = false;
        CheckMarkCreated = false;
        consolelog("Custom Checkbox!");
        break;
    }

}

void CheckBox::createMainBox(int Style)
{
    if(!MainBoxCreated)
    {
        switch(Style)
        {
            case vui::Style::Square:     
                CheckBoxT1.setSize(sf::Vector2f(BoxSize, BoxSize));
                CheckBoxT1.setPosition(BoxPosition);
                CheckBoxT1.setFillColor(MainColor);
                CheckBoxT1.setOutlineColor(CheckColor);
                isBoxSquare = true;
                consolelog("Square CheckBox created...");
                break;
            case vui::Style::Circle:
                CheckBoxT2.setRadius(BoxSize/2);
                CheckBoxT2.setPosition(BoxPosition);
                CheckBoxT2.setFillColor(MainColor);
                CheckBoxT2.setOutlineColor(CheckColor);
                isBoxCircle = true;
                consolelog("Circle CheckBox created...");
                break;
        }
        MainBoxCreated = true;
    }
}

void CheckBox::createCheckMarker(int Style)
{
    if(!CheckMarkCreated)
    {
        switch(Style)
        {
            case vui::Style::Square:
                CheckMarkT1.setSize(sf::Vector2f(BoxSize * 0.6, BoxSize * 0.6));
                CheckMarkT1.setOrigin(CheckMarkT1.getSize().x/2, CheckMarkT1.getSize().x/2);
                CheckMarkT1.setPosition(BoxPosition.x + BoxSize/2, BoxPosition.y + BoxSize/2);
                CheckMarkT1.setFillColor(CheckColor);
                isCheckSquare = true;
                consolelog("Square CheckMark created...");
                break;
            case vui::Style::Circle:
                CheckMarkT2.setRadius((BoxSize * 0.6) / 2);
                CheckMarkT2.setOrigin(CheckMarkT2.getRadius(), CheckMarkT2.getRadius());
                CheckMarkT2.setPosition(BoxPosition.x + BoxSize/2, BoxPosition.y + BoxSize/2);
                CheckMarkT2.setFillColor(CheckColor);
                isCheckCircle = true;
                consolelog("Circle CheckMark created...");
                break;
        }
        CheckMarkCreated = true;
    }
}

void CheckBox::setMainColor(sf::Color Color)
{
    MainColor = Color;
}

void CheckBox::setCheckColor(sf::Color Color)
{
    CheckColor = Color;
}

bool CheckBox::isBoxChecked()
{
    return isChecked;
}

void CheckBox::uncheckBox()
{
    if(isChecked) isChecked = false;
}

void CheckBox::checkBox()
{
    if(!isChecked) isChecked = true;
}

void CheckBox::displayTo(sf::RenderWindow &win)
{
    CheckBoxFinished = (CheckMarkCreated && MainBoxCreated);
    if(CheckBoxFinished)
    {
        //Check mouse states:
        if(!mouseOverCheckbox(win))
        {
            wFocus = (sf::Mouse::isButtonPressed(sf::Mouse::Left))? true : false;
        }
        else if(mouseLeftCilckReleased() && !wFocus)
        {
            isChecked = (!isChecked);
            consolelog("Left click released!");
            consolelog((isChecked)? "CheckBox - Checked!" : "CheckBox - Unchecked!");
        }
            
        //Draw main box:
        (isBoxSquare)? win.draw(CheckBoxT1) : win.draw(CheckBoxT2);

        
        //Draw CheckMark:
        (isCheckSquare)? win.draw(CheckMarkT1) : win.draw(CheckMarkT2);
    }
}

void CheckBox::adjustOutline(bool ShowOutline)
{
    if(isBoxSquare)
    {
        (ShowOutline)? CheckBoxT1.setOutlineThickness(2) : CheckBoxT1.setOutlineThickness(0);
        if(CheckColor != CheckBoxT1.getOutlineColor()) CheckBoxT1.setOutlineColor(CheckColor);
    }
    else if(isBoxCircle)
    {
        (ShowOutline)? CheckBoxT2.setOutlineThickness(2) : CheckBoxT2.setOutlineThickness(0);
        if(CheckColor != CheckBoxT2.getOutlineColor()) CheckBoxT2.setOutlineColor(CheckColor);
    }
}

bool CheckBox::mouseOverCheckbox(sf::RenderWindow &win)
{
    sf::Vector2f CursorPos = sf::Vector2f(sf::Mouse::getPosition(win));

    if(CursorPos.x > BoxPosition.x && CursorPos.x < BoxPosition.x + BoxSize && CursorPos.y > BoxPosition.y && CursorPos.y < BoxPosition.y + BoxSize)
    {
        if(!isChecked)
            {
                CheckColor.a = 100;
                (isCheckSquare)? CheckMarkT1.setFillColor(CheckColor) : CheckMarkT2.setFillColor(CheckColor);
                adjustOutline(true);
            }
            else
            {
                adjustOutline(true);
                CheckColor.a = 255;
                (isCheckSquare)? CheckMarkT1.setFillColor(CheckColor) : CheckMarkT2.setFillColor(CheckColor);
            }
            MainColor.a = 200;
            (isBoxSquare)? CheckBoxT1.setFillColor(MainColor) : CheckBoxT2.setFillColor(MainColor);
            return true;
    }
    else
    {
        MainColor.a = 255;
        (isBoxSquare)? CheckBoxT1.setFillColor(MainColor) : CheckBoxT2.setFillColor(MainColor);
        if(!isChecked)
        {
            adjustOutline(false);
            CheckColor.a = 0;
            (isCheckSquare)? CheckMarkT1.setFillColor(CheckColor) : CheckMarkT2.setFillColor(CheckColor);
        }
        isMouseLeftPressed = false;
    }
    return false;
}

bool CheckBox::mouseLeftCilckReleased()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        isMouseLeftPressed = true;
        return false;
    }
    else if(isMouseLeftPressed)
    {
        isMouseLeftPressed = false;
        return true;
    }
    return false;
}

void CheckBox::consolelog(std::string log)
{
    if(debuging)
    {
        std::cout << log << "\n";
    }
}

}