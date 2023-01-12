#ifndef UI_SLIDER
#define UI_SLIDER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace vui
{

enum Orientation
{
    Horizontal = 1,
    Vertical = 2
};

class Slider
{

public:

    Slider();

    ~Slider();
    
    //////////////////////////////////////////////////////////////
    /// @brief Creates a slider
    /// @param Position Position of the Slider
    /// @param Size Size.x is Thickness and Size.y is Length
    /// @param Style Has two Styles : "Basic" or "Rounded"
    /// @param Orientation Use vui::Orientation
    //////////////////////////////////////////////////////////////
    void Create(sf::Vector2f Position, sf::Vector2f Size, std::string Style, int Orientation);

    //////////////////////////////////////////////////////////////
    /// @brief Displays Slider to sf::RenderWindow
    /// @param win sf::RenderWindow that will display the Slider
    //////////////////////////////////////////////////////////////
    void displayTo(sf::RenderWindow &win);

private:
    
    sf::Vector2f Pos;
    sf::Vector2f SliderSize;
    
    std::string SliderStyle;

    bool SliderCreated = false;

    bool isHorizontal = false;
    bool isVertical = false;
    bool EndPieces = false;
    bool ShowIndicator = true;
//Basic:
    sf::RectangleShape SliderArea;
    sf::RectangleShape Indicator;
    sf::RectangleShape SliderHead1;
//Rounded:
    sf::CircleShape SliderHead2;
    sf::CircleShape EndPiece1_c;
    sf::CircleShape EndPiece2_c;

    bool mouseLeftCilckReleased();
    
    void drawBasic(sf::RenderWindow &win);

    void drawRounded(sf::RenderWindow &win);
};

}
#endif