#include "../include/UI_Console.hpp"

namespace vui
{

//Public:

Console::Console(){ }

Console::~Console(){ }

void Console::ShowConsole()
{
    Visible = (Visible)? false : true;
}

void Console::setFont(sf::Font &Font)
{
    font = Font;
}

bool Console::loadFontFromFile(std::string filePath)
{
    return font.loadFromFile(filePath);
}

bool Console::loadFontFromMemory(std::vector<unsigned char> &data)
{
    return font.loadFromMemory(data.data(), data.size());
}

void Console::create(sf::Vector2f Position, sf::Vector2f Size, float CharSize)
{
    StartingLinePos = sf::Vector2f(Position.x + 2, Position.y + 2);
    //Set the respective sizes
    Input.setSize(sf::Vector2f(Size.x , CharSize * 1.2));
    Log.setSize(sf::Vector2f(Size.x, Size.y - Input.getSize().y));
    Log.setOutlineThickness(1.f);
    //Set the respective positions
    Log.setPosition(Position);
    Input.setPosition(Position.x , Position.y + Log.getSize().y);
    //Setup input line for input text display
    InputLine.setFont(font);
    InputLine.setPosition(Input.getPosition().x + 2, Input.getPosition().y + 2);
    InputLine.setCharacterSize(CharSize);
    //Color set
    Log.setOutlineColor(OutlineColor);
    Log.setFillColor(BoxColor);
    Input.setOutlineColor(OutlineColor);
    Input.setFillColor(BoxColor);
    InputLine.setFillColor(TextColor);
}

void Console::Update(sf::RenderWindow &Window)
{
    Out();
    checkColorChanges();
    if(Visible)
    { 
        //Check our focus on window
        if(!cursorOverInputBox(Window))
        {
            WindowFocus = (MouseButtonPressed(Window, sf::Mouse::Button::Left) || 
                        MouseButtonPressed(Window, sf::Mouse::Button::Right))? true : false;
            if(WindowFocus) Selected = false;
        }
        if(cursorOverInputBox(Window))
        {
            Input.setOutlineThickness(2);
            if(MouseButtonReleased(Window, sf::Mouse::Left) && !WindowFocus)
                Selected = true;
        }
        else if(!Selected)Input.setOutlineThickness(0);
        
        checkLinePositions();
        
        //Scroll
        if(cursorOverLogBox(Window))
        { 
            if(WheelDir != 0)
            {
                Offset = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))?
                    InputLine.getCharacterSize() *2 : InputLine.getCharacterSize();
                
                if(WheelDir < 0 && outOfBounds(Line.front())) 
                    StartingLinePos.y += Offset;
                else if(WheelDir > 0 && outOfBounds(Line.back())) 
                    StartingLinePos.y -= Offset;
                
                checkLinePositions();
                WheelDir = 0;
            }
        }
        else
        {
            WheelDir = 0;
        }
    }
    else if(Selected) Selected = false;
}

void Console::DisplayTo(sf::RenderWindow &Window)
{
    if(Visible)
    {
        //First draw LogBox
        Window.draw(Log);
        //AjustPostions and draw text
        if(!Line.empty())
        {
            for(int i = 0; i < Line.size(); i++)
            {
                if(!outOfBounds(Line[i]))Window.draw(Line[i]);
            }
        }
        //Second draw InputBox
        Window.draw(Input);
        Window.draw(InputLine);
        drawNavBar(Window);
    }
}

void Console::typedOn(sf::Event Event)
{
    if(Selected)
    {
        if(Event.type == sf::Event::KeyPressed)
        {
            if(Event.key.code == sf::Keyboard::Left && index != 0)
                index--;
            
            else if(Event.key.code == sf::Keyboard::Right && index < InputText.length())
                index++;
            
            else if(Event.key.code == sf::Keyboard::Enter)
            {
                Command = InputText;
                std::cout << Command;
                while(!InputText.empty() && index != 0)
                {
                    InputText.erase(index-1,1);
                    index--;
                }
                InputLine.setString(InputText);
            }
        }
        else if(Event.type == sf::Event::TextEntered)
        {
            if(Event.text.unicode < 128 && Event.text.unicode != 13 && Event.text.unicode != 96)
            {
                std::cout << Event.text.unicode << '\n';
                //Check if backspace key is pressed for character erasing
                if(Event.text.unicode == 8)
                {
                    if(!InputText.empty() && index != 0)
                    {
                        InputText.erase(index-1,1);
                        index--;
                    }
                }
                //Any other key is added to string at the respective line and index
                else
                {
                    if(index == InputText.length())
                    {
                        index++;
                        InputText += Event.text.unicode;
                    }
                    else
                    { 
                        InputText.insert(InputText.begin()+index, Event.text.unicode);
                        index++;
                    }
                }
            }
            InputLine.setString(InputText);
            sf::FloatRect fr = InputLine.getGlobalBounds();
            if(fr.width + 10 > Input.getSize().x)
            {
                InputText.erase(index-1,1);
                index--;
                InputLine.setString(InputText);
            }
        
        }
    }
}

void Console::CheckWheelMovement(sf::Event Event)
{
    if(Event.type == sf::Event::MouseWheelScrolled)
    {
        std::cout << Event.mouseWheel.x << '\n';
        WheelDir = Event.mouseWheel.x;
    }
}

bool Console::inputBoxActive()
{
    return Selected;
}

void Console::Out()
{
    if(!output.empty())
    {
        float CharSize = InputLine.getCharacterSize();
        sf::Text t;
        t.setCharacterSize(CharSize);
        t.setFont(font);
        t.setFillColor(TextColor);
        if(Line.empty()) t.setPosition(Log.getPosition().x+2, Log.getPosition().y + 2);
        std::string finalString;
        std::string stringToTest;
        std::string tempString;
        std::stringstream ss(output);
        while (std::getline(ss, tempString, ' '))
        {
            sf::Text tempT;
            tempT.setCharacterSize(CharSize);
            tempT.setFont(font);
            stringToTest += ' ' + tempString;
            tempT.setString(stringToTest);
            if(tempT.getGlobalBounds().width > Log.getSize().x-4)
            {
                t.setString(finalString);
                Line.push_back(t);
                LineText.push_back(finalString);
                stringToTest.clear();
                stringToTest += ' ' + tempString;
            }
            else finalString = stringToTest;
        }
        t.setString(finalString);
        Line.push_back(t);
        LineText.push_back(finalString);
        output.clear();
        checkLinePositions();
        while(outOfBounds(Line.back()))
        {
            checkLinePositions();
            StartingLinePos.y -= InputLine.getCharacterSize();
        }
    }

}

std::string Console::getCommand()
{
    return Command;
}

void Console::clearCommand()
{
    Command.clear();
}

void Console::setTextColor(sf::Color Color)
{
    TextColor = Color;
}

void Console::setBoxColor(sf::Color Color)
{
    BoxColor = Color;
}

void Console::setOutineColor(sf::Color Color)
{
    OutlineColor = Color;
}

void Console::Select()
{
    Selected = true;
}
//Private

bool Console::MouseButtonReleased(sf::RenderWindow &Window, sf::Mouse::Button Key)
{
    if(MouseButtonPressed(Window, Key))
    {
        if(!buttonPressed)std::cout << "Button Pressed!\n";
        buttonPressed = true;
        return false;
    }
    else if(buttonPressed)
    {
        std::cout << "Button Released!\n";
        buttonPressed = false;
        return true;
    }
    return false;
}

bool Console::MouseButtonPressed(sf::RenderWindow &Window, sf::Mouse::Button Key)
{
    if(sf::Mouse::isButtonPressed(Key)) return true;
    return false;
}


bool Console::cursorOverInputBox(sf::RenderWindow &Window)
{
    sf::Vector2f Cursor = sf::Vector2f(sf::Mouse::getPosition(Window));

    bool xAxisCheck = Cursor.x > Input.getPosition().x 
                      && Cursor.x < Input.getPosition().x + Input.getSize().x;
    bool yAxisCheck = Cursor.y > Input.getPosition().y 
                      && Cursor.y < Input.getPosition().y + Input.getSize().y;

    return (xAxisCheck && yAxisCheck);
}

bool Console::cursorOverLogBox(sf::RenderWindow &Window)
{
    sf::Vector2f Cursor = sf::Vector2f(sf::Mouse::getPosition(Window));

    bool xAxisCheck = Cursor.x > Log.getPosition().x 
                      && Cursor.x < Log.getPosition().x + Log.getSize().x;
    bool yAxisCheck = Cursor.y > Log.getPosition().y 
                      && Cursor.y < Log.getPosition().y + Log.getSize().y;

    return (xAxisCheck && yAxisCheck);
}

bool Console::outOfBounds(sf::Text LineToTest)
{
    return(LineToTest.getPosition().y > Input.getPosition().y - LineToTest.getCharacterSize() 
           || LineToTest.getPosition().y < Log.getPosition().y);
}

void Console::createNavigationBar()
{
    float charSize = InputLine.getCharacterSize();
    std::string s;
    sf::Text t;
    t.setFont(font);
    t.setCharacterSize(charSize);
    for(int i = 0; i < index; i++)
    {
        s+=InputText[i];
    }
    t.setString(s);
    sf::FloatRect fr = t.getGlobalBounds();
    Navbar.setSize(sf::Vector2f(2, charSize));
    Navbar.setPosition(fr.width + InputLine.getPosition().x, InputLine.getPosition().y);
    Navbar.setFillColor(sf::Color::Black);
}

void Console::drawNavBar(sf::RenderWindow &Window)
{
    seconds += c.getElapsedTime().asSeconds();
    if(Selected)
    {
        createNavigationBar();
        if(seconds > 0.2)
        {
            Window.draw(Navbar);
            if(seconds > 0.6) seconds = 0;
        }
    }
    c.restart().asSeconds();
}

void Console::checkColorChanges()
{
    //Log
    if(!Line.empty())
    {
        for(auto &a : Line)
        {
           if(a.getFillColor() != TextColor) a.setFillColor(TextColor);
        }
    }
    if(Log.getFillColor() != BoxColor) Log.setFillColor(BoxColor);
    if(Log.getOutlineColor() != OutlineColor) Log.setOutlineColor(OutlineColor);
    //Input
    if(InputLine.getFillColor() != TextColor) InputLine.setFillColor(TextColor);
    if(Input.getFillColor() != BoxColor) Input.setFillColor(BoxColor);
    if(Input.getOutlineColor() != OutlineColor) Input.setOutlineColor(OutlineColor);
}

void Console::checkLinePositions()
{
    if(!Line.empty())
    {
        for(int i = 0; i < Line.size(); i++)
        {
            Line[i].setPosition(StartingLinePos.x, StartingLinePos.y + i * InputLine.getCharacterSize());
        }
    }
}

}