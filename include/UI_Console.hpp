#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

namespace vui
{


class Console
{

public:

Console();

~Console();

template <class DATA>
Console& operator<<(const DATA &data)
{
    std::stringstream ss;
    ss << data;
    this->output += ss.str();
    return *this;
}

void ShowConsole();

void setFont(sf::Font &Font);

bool loadFontFromFile(std::string filePath);

bool loadFontFromMemory(std::vector<unsigned char> &data);

void create(sf::Vector2f Position, sf::Vector2f Size, float CharSize);

void Update(sf::RenderWindow &Window);

void DisplayTo(sf::RenderWindow &Window);

void typedOn(sf::Event Event);

void CheckWheelMovement(sf::Event Event);

bool inputBoxActive();

void Out();

std::string getCommand();

void clearCommand();

void setTextColor(sf::Color Color);

void setBoxColor(sf::Color Color);

void setOutineColor(sf::Color Color);

void Select();

private:

std::string output;

sf::Clock c;
float seconds = 0;

sf::RectangleShape Navbar;

sf::Font font;

sf::Color TextColor = sf::Color::Black;
sf::Color BoxColor = sf::Color::White;
sf::Color OutlineColor = sf::Color::White;

int index = 0;

sf::Vector2f StartingLinePos;
int WheelDir = 0;
float Offset = 10;

bool WindowFocus = false;
bool buttonPressed = false;
bool Selected = false;
bool Visible = false;

sf::RectangleShape Log;
sf::RectangleShape Input;

std::vector<sf::Text> Line;
std::vector<std::string> LineText;

sf::Text InputLine;
std::string InputText;
std::string Command;

bool MouseButtonReleased(sf::RenderWindow &Window, sf::Mouse::Button Key);

bool MouseButtonPressed(sf::RenderWindow &Window, sf::Mouse::Button Key);

bool cursorOverInputBox(sf::RenderWindow &Window);

bool cursorOverLogBox(sf::RenderWindow &Window);

bool outOfBounds(sf::Text LineToTest);

void createNavigationBar();

void drawNavBar(sf::RenderWindow &Window);

void checkColorChanges();

void checkLinePositions();

};

inline Console con;

}
#endif