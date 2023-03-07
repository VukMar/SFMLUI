/* 
Button class for SFML UI by Vuk Maric - VUI
Private and public parts are seperated by a "comment line"(Upper being the public part)
This is version 3 of the button
Functions are described on header file
*/

#include "../include/UI_Button.hpp"

namespace vui
{

Button::Button()
{

}

Button::~Button()
{

}

bool Button::loadFontFromFile(std::string FilePath)
{
    return font.loadFromFile(FilePath);
}

bool Button::loadFontFromMemory(std::vector<unsigned char> &data)
{
    return font.loadFromMemory(data.data(),data.size());
}

void Button::create(std::string ButtonText, int TextSize, sf::Vector2f Size, sf::Vector2f Position, sf::Color ButtonColor, sf::Color ButtonHoverColor)
{
    ButtonPosition = Position;
    box.setSize(Size);
    box.setPosition(Position);
    changeButtonColor(ButtonColor);
    HoverColor = ButtonHoverColor;
    changeButtonTextColor(sf::Color::White);
    changeTextOutlineColor(sf::Color::White);
    sf::Text t;
    t.setFont(font);
    t.setCharacterSize(TextSize);
    t.setString(ButtonText);
    sf::FloatRect fr = t.getGlobalBounds();
    text = t;
    text.setPosition(Position.x + Size.x/2 - (fr.width+fr.left)/2, Position.y + Size.y/2 - (fr.height+fr.top)/2);
}

void Button::createFromSprite(sf::Vector2f Position, sf::Vector2f Size, sf::Texture &texture)
{
    ButtonPosition = Position;
    box.setSize(sf::Vector2f(Size));
    box.setPosition(Position);
    box.setTexture(&texture);
}

void Button::hasOutline(float Thickness)
{
    OutlineThickness = Thickness;
}

void Button::displayTo(sf::RenderWindow &win)
{
    win.draw(box);
    if(!Sprite)win.draw(text);
}

bool Button::isButtonPressed(sf::RenderWindow &win)
{
    //First make sure that mouse button is not pressed outside button
    if(!mouseOverButton(win))
    {
        wFocus = (sf::Mouse::isButtonPressed(sf::Mouse::Left))? true : false;
    }
    /*If wFocus is false we can proceed with the rest of the functions,
    if not the function will return false*/
    if(mouseOverButton(win) && ! wFocus && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        //This if statement makes sure the button click is registerd only once
        if(!ButtonPressed)
        {
            ButtonPressed = true;
            return true;
        }
        else return false;
    }
    ButtonPressed = false;
    return false;
}

bool Button::isButtonHeldDown(sf::RenderWindow &win)
{
    //First make sure that mouse button is not pressed outside button
    if(!mouseOverButton(win))
    {
        wFocus = (sf::Mouse::isButtonPressed(sf::Mouse::Left))? true : false;
    }
    /*If wFocus is false we can proceed with the rest of the functions,
    if not the function will return false*/
    if(mouseOverButton(win) && ! wFocus && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        //This if statement makes sure the button click is registerd only once
        if(!ButtonPressed)
        {
            c.restart().asSeconds();
            ButtonPressed = true;
            return true;
        }
        else
        {
            seconds += c.getElapsedTime().asSeconds();
            std::cout << seconds << "\n";
            if(seconds > 0.6f)
            {
                if(seconds > 0.7f) seconds = 0;
                return true;
            }
            return false;
        } 
            
    }
    ButtonPressed = false;
    return false;
    
}

void Button::move(sf::Vector2f Offset)
{
    sf::Vector2f Size = box.getSize();
    ButtonPosition += Offset;
    box.setPosition(ButtonPosition);
    if(Sprite) sprite.setPosition(ButtonPosition);
    else
    {
        sf::FloatRect fr = text.getGlobalBounds();
        text.move(Offset);
    }
}

void Button::move(float OffsetX, float OffsetY)
{
    ButtonPosition.x += OffsetX;
    ButtonPosition.y += OffsetY;
    sf::Vector2f Size = box.getSize();
    box.setPosition(ButtonPosition);
    if(Sprite) sprite.setPosition(ButtonPosition);
    else
    {
        sf::FloatRect fr = text.getGlobalBounds();
        text.move(OffsetX, OffsetY);
    }
}

void Button::changeButtonColor(sf::Color Color)
{
    box.setFillColor(Color);
    ButtonColor = Color;
}

void Button::changeButtonHoverColor(sf::Color Color)
{
    HoverColor = Color;
}

void Button::changeButtonOutlineColor(sf::Color Color)
{
    box.setOutlineColor(Color);
    OutlineColor = Color;
}

void Button::changeButtonTextColor(sf::Color Color)
{
    text.setFillColor(Color);
    TextColor = Color;
}

void Button::changeTextOutlineColor(sf::Color Color)
{
    text.setOutlineColor(Color);
    TextOutlineColor = Color;
}

//=================================================================================

bool Button::mouseOverButton(sf::RenderWindow &win)
{
    sf::Vector2f Cursor = win.mapPixelToCoords(sf::Mouse::getPosition(win), win.getView());
    


    if(Cursor.x > box.getPosition().x && Cursor.x < box.getPosition().x + box.getSize().x && Cursor.y > box.getPosition().y && Cursor.y < box.getPosition().y + box.getSize().y)
    {
        box.setOutlineThickness(OutlineThickness + 2);
        return true;
    }
    box.setOutlineThickness(OutlineThickness);
    return false;
}

}