#include "../include/UI_TextBox.hpp"
/*

Public and private components of TextBox class are seperated by a comment.

VUI-SFML , the sfml UI, 
by 
Vuk Maric
vuk.s.maric@gmail.com


*/
namespace vui
{

TextBox::TextBox()
{

}

TextBox::~TextBox()
{

}

bool TextBox::isActive(sf::RenderWindow &win)
{
    if(!mouseOverBox(win))
    {
        wFocus = sf::Mouse::isButtonPressed(sf::Mouse::Left)? true : false;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) Active = false;
    }
    if(mouseOverBox(win) && !wFocus && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Active = true;
    }
    return Active;
}

bool TextBox::setFontFromFile(std::string filePath)
{   
    return font.loadFromFile(filePath);
}

bool TextBox::setFontFromMemory(std::vector<unsigned char> &data)
{   
    return font.loadFromMemory(data.data(), data.size());
}

void TextBox::create(sf::Vector2f Size, sf::Vector2f Posistion, float FontSize)
{
    box.setSize(Size);
    box.setPosition(Posistion);
    charSize = FontSize;
    MaxNumberofRows = ((Size.y-10)/charSize)+1;
    createLine(FontSize);
}

void TextBox::typeOn(sf::Event ev)
{
    //Keys for navigation around text box.
    if(ev.type == sf::Event::KeyPressed)
    {
        if(ev.key.code == sf::Keyboard::Left)
        {
            if(index != 0)
                index--;
            else if(rowSelected != 0)
            {
                rowSelected--;
                index = textToDisplay[rowSelected].length();
            }
        }  
        else if(ev.key.code == sf::Keyboard::Right) 
        {
            if(index < textToDisplay[rowSelected].length())
                index++;
            else if(rowSelected < NumberOfRows-1)
            {
                rowSelected++;
                index = 0;
            }
        }
        if(MultiLine)
        {
            if(ev.key.code == sf::Keyboard::Up && rowSelected != 0)
            {
                rowSelected--;
                if(index > textToDisplay[rowSelected].length()) index = textToDisplay[rowSelected].length();
            }    
            else if(ev.key.code == sf::Keyboard::Down && rowSelected < NumberOfRows - 1)
            {
                rowSelected++;
                if(index > textToDisplay[rowSelected].length()) index = textToDisplay[rowSelected].length();
            }
        }
        consoleLog("String length is: " + std::to_string(textToDisplay[rowSelected].length()) + "\n");
        consoleLog("Index selected is: " + std::to_string(index) + "\n");
        consoleLog("Row selected: " + std::to_string(rowSelected) + "\n");
        consoleLog("Number of rows: " + std::to_string(NumberOfRows) + "\n");
    }
    //Text input handle
    else if(ev.type == sf::Event::TextEntered)
    {
        if(ev.text.unicode < 128)
        {
            //Check if bakspace key is pressed for character erasing
            if(ev.text.unicode == 8)
            {
                if(!textToDisplay[rowSelected].empty() && index != 0)
                {
                    textToDisplay[rowSelected].erase(index-1,1);
                    index--;
                }
                else if(index == 0)
                {
                    std::string temp;
                    if(!textToDisplay[rowSelected].empty() && rowSelected != 0)
                        temp = textToDisplay[rowSelected];
                    
                    if(NumberOfRows > 1 && rowSelected != 0)
                    {
                        textToDisplay.erase(textToDisplay.begin()+rowSelected);
                        text.erase(text.begin()+rowSelected);
                    }
                    if(rowSelected != 0)
                    {
                        rowSelected--;
                        index = textToDisplay[rowSelected].length();
                    }
                    if(!temp.empty())textToDisplay[rowSelected] += temp;
                }
                NumberOfRows = text.size();
            }
            //Check if enter key is pressed for new line creation
            else if(ev.text.unicode == 13)
            {
                if(MultiLine)
                {
                    if(createLine(charSize))
                    {
                        rowSelected++;
                        if(index < textToDisplay[rowSelected-1].length())
                        {
                            std::string leftover;
                            for(int i = index; i < textToDisplay[rowSelected-1].length(); i++)
                            {
                                leftover += textToDisplay[rowSelected-1][i];
                            }
                            textToDisplay[rowSelected-1].erase(index, textToDisplay[rowSelected-1].length() - index);
                            consoleLog("Leftover: " + leftover + "\n");
                            consoleLog("Modified row: " + textToDisplay[rowSelected-1] + "\n");
                            text[rowSelected-1].setString(textToDisplay[rowSelected-1]);
                            textToDisplay[rowSelected] = leftover;
                        }
                        index = 0;
                    }
                }
            }
            //Any other key is added to string at the respective line and index
            else
            {
                if(index == textToDisplay[rowSelected].length())
                {
                    index++;
                    textToDisplay[rowSelected] += ev.text.unicode;
                }
                else
                { 
                    textToDisplay[rowSelected].insert(textToDisplay[rowSelected].begin()+index, ev.text.unicode);
                    index++;
                }
            }
        }
        
        //Debug info:
        consoleLog("String length is: " + std::to_string(textToDisplay[rowSelected].length()) + "\n");
        consoleLog("Index selected is: " + std::to_string(index) + "\n");
        consoleLog("Row selected: " + std::to_string(rowSelected) + "\n");
        consoleLog("Number of rows: " + std::to_string(NumberOfRows) + "\n");
        
        text[rowSelected].setString(textToDisplay[rowSelected]);
        if(!Scrollable)
        {
            warpText();
        }
        
    }
}

void TextBox::clear()
{
    index = 0;
    rowSelected = 0;
    NumberOfRows = 0;
    textToDisplay.clear();
    text.clear();
    createLine(charSize);
}

bool TextBox::displayText(std::string TextToRead)
{
    clear();
    int control = 0;
    for(int i = 0; i < TextToRead.length(); i++)
    {
        if(TextToRead[i] != '\n')
        {
            textToDisplay[rowSelected] += TextToRead[i];
            text[rowSelected].setString(textToDisplay[rowSelected]);
            if(!Scrollable)
            {
                warpText();
            }
        }
        else 
        {
            createLine(charSize);
            rowSelected++;
        }
        
        control++;
    }
    return control == TextToRead.length();
}

bool TextBox::displayTextFromFile(std::string FilePath)
{
    clear();
    std::string line;
    std::ifstream file;
    file.open(FilePath);
    if(file.is_open())
    {
        while(std::getline(file, line))
        {
            consoleLog("Reading line: " + line + "\n");
            for(int i = 0; i < line.length(); i++)
            {
                textToDisplay[rowSelected] += line[i];
                text[rowSelected].setString(textToDisplay[rowSelected]);
                if(!Scrollable) warpText();
            }
            createLine(charSize);
            rowSelected++;
        }
        consoleLog("File Loaded Successfully!\n");
        return true;
    }
    else consoleLog("File Not Loaded!\n");
    return false;
}

std::string TextBox::getText()
{
    std::string re;
    for(auto s : text)
    {
        re += s.getString() + "\n";
    }
    re.pop_back();
    return re;
}

void TextBox::changeBoxFillColor(sf::Color Color)
{
    box.setFillColor(Color);
}

void TextBox::changeBoxOutilneColor(sf::Color Color)
{
    box.setOutlineColor(Color);
}

void TextBox::setBoxOutlineThickness(float Thickness)
{
    BoxOutlineThickness = Thickness;
}

void TextBox::changeTextFillColor(sf::Color Color)
{
    textFillColor = Color;
}

void TextBox::changeTextOutineColor(sf::Color Color)
{
    textOutlineColor = Color;
}

void TextBox::setTextOutlineThickness(float Thickness)
{
    textOutlineThickness = Thickness;
}

void TextBox::displayTo(sf::RenderWindow &win)
{
    win.draw(box);
    for(int i = 0; i < text.size(); i++)
    {
        if(text[i].getFillColor() != textFillColor) text[i].setFillColor(textFillColor);
        if(text[i].getOutlineColor() != textOutlineColor) text[i].setOutlineColor(textOutlineColor);
        text[i].setPosition(box.getPosition().x + 5, box.getPosition().y + 5 + (charSize*i));
        win.draw(text[i]);
    }
    drawNavBar(win);
}

void TextBox::move(sf::Vector2f Offset)
{
    box.move(Offset);
}

void TextBox::move(float xOffset, float yOffset)
{
    box.move(xOffset, yOffset);
}

//===============================================================================================================================================

bool TextBox::mouseOverBox(sf::RenderWindow &win)
{
    sf::Vector2f cursor = sf::Vector2f(sf::Mouse::getPosition(win));

    if(cursor.x > box.getPosition().x && cursor.x < box.getPosition().x + box.getSize().x && cursor.y > box.getPosition().y && cursor.y < box.getPosition().y + box.getSize().y)
    {
        if(BoxHasOutilne && !Active) box.setOutlineThickness(BoxOutlineThickness);
        return true;
    }
    if(!Active)box.setOutlineThickness(0);
    return false;
}

bool TextBox::createLine(float FontSize)
{
    if(NumberOfRows + 1 < MaxNumberofRows || Scrollable)
    {
        std::string s;
        sf::Text t;
        t.setFont(font);
        t.setCharacterSize(FontSize);
        t.setFillColor(textFillColor);
        t.setOutlineColor(textOutlineColor);
        if(rowSelected < NumberOfRows - 1)
        {
            text.insert(text.begin()+rowSelected+1, t);
            textToDisplay.insert(textToDisplay.begin()+rowSelected+1,s);
        }
        else
        {
            text.push_back(t);
            textToDisplay.push_back(s);
        }
        NumberOfRows = text.size();
        return true;
    }
    else return false;
}

void TextBox::createNavigationBar()
{
    std::string s;
    sf::Text t;
    t.setFont(font);
    t.setCharacterSize(charSize);
    for(int i = 0; i < index; i++)
    {
        s+=textToDisplay[rowSelected][i];
    }
    t.setString(s);
    sf::FloatRect fr = t.getGlobalBounds();
    Navbar.setSize(sf::Vector2f(2, charSize));
    Navbar.setPosition(fr.width + text[rowSelected].getPosition().x, text[rowSelected].getPosition().y);
    Navbar.setFillColor(sf::Color::Black);
}

void TextBox::drawNavBar(sf::RenderWindow &win)
{
    seconds += c.getElapsedTime().asSeconds();
    if(Active)
    {
        createNavigationBar();
        if(seconds > 0.2)
        {
            win.draw(Navbar);
            if(seconds > 0.6) seconds = 0;
        }
    }
    c.restart().asSeconds();
}

void TextBox::consoleLog(std::string log)
{
    if(debuging)std::cout << log;
}

void TextBox::warpText()
{
    sf::FloatRect fr = text[rowSelected].getGlobalBounds();
    if(fr.width + 10 > box.getSize().x)
    {
        if(MultiLine && NumberOfRows + 1 < MaxNumberofRows)
        {
            char c = textToDisplay[rowSelected].back();
            if(createLine(charSize))
            {
                index = 0;
                textToDisplay[rowSelected].pop_back();
                text[rowSelected].setString(textToDisplay[rowSelected]);
                rowSelected++;
                textToDisplay[rowSelected] += c;                    
                text[rowSelected].setString(textToDisplay[rowSelected]);
                index++;
            }
        }
        else
        {
            textToDisplay[rowSelected].erase(index-1,1);
            index--;
            text[rowSelected].setString(textToDisplay[rowSelected]);
        }
    }
}

}