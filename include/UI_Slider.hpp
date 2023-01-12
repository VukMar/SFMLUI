#ifndef UI_SLIDER
#define UI_SLIDER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

namespace vui
{

class Slider
{

public:

Slider();

~Slider();

void create(float lenght, float thickness, sf::Vector2f Position);

void Update(sf::RenderWindow &Window);

void displayTo(sf::RenderWindow &Window);

int getPercentValue();

void setHeadColor(sf::Color Color);

void setAreaColor(sf::Color Color);

void setHeadOutlineThickness(float Thickness);

void setAreaOutlineThickness(float Thickness);

void setHeadOutlineColor(sf::Color Color);

void setAreaOutlineColor(sf::Color Color);

void checkAttributsChanges();

sf::Color getHeadColor();

sf::Color getAreaColor();

float getHeadOutlineThickness();

float getAreaOutlineThickness();

sf::Color getHeadOutlineColor();

sf::Color getAreaOutlineColor();

void setHeadLength(float Length);

private:

bool leftMouseHeld = false;
bool WFocus = false;

sf::Vector2f CursorPos;

float HeadOutlineThickness = 0;
float AreaOutlineThickness = 0;

sf::Color AreaColor;
sf::Color AreaOutlineColor;
sf::Color HeadColor;
sf::Color HeadOutlineColor;

float headLength;

sf::RectangleShape SliderArea;
sf::RectangleShape SliderHead;

int percent = 0;

bool sliderHeadGrabed();

bool mouseOverHead();

bool mouseOverArea();

bool mouseLeftHeld();

bool mouseLeftReleased();

};

}
#endif