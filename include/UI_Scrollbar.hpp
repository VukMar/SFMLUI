#ifndef UI_SCROLLBAR
#define UI_SCROLLBAR

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "UI_Button.hpp"

namespace vui
{
namespace Orientation
{
enum Vertical
{
    Left = 1,
    Right = 2
};
enum Horizontal
{
    Top = 3,
    Bottom = 4
};
};


class ScrollBar
{
public:
    ScrollBar();
    ~ScrollBar();

    float Max = 0;

    //////////////////////////////
    /// Creates the scroll bar.
    /// \param Size Size of scroll bar, will apply to scroll bar based on orientation
    /// \param VisibleArea Visible area of scroll bar
    /// \param Orientation Combination of vui::Orientation enumerators
    /////////////////////////////////////////////////////////////////////////////////////
    void create(float size,sf::Vector2f VisibleArea , int Orientation);
    
    /////////////////////////////////////////////////////////////////////////////////////
    /// Displays scroll bar.
    /// \param win Render window to display to;
    /////////////////////////////////////////////////////////////////////////////////////
    void displayTo(sf::RenderWindow &win);
    
    void setPosition(float PositionX, float PositionY);

    void setSize(float Size);

    sf::Vector2f getPosition();
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Get offset for object movement
    /// @return Returns sf::Vector2f(OffsetX, OffsetY). If no change is detected the offsets will be 0.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    sf::Vector2f getOffset();
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Sets main color for ScrollBar.
    /// @param Color desired color.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void setMainColor(sf::Color Color);
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Sets on hover color for scroll bar.
    /// @param Color desired color.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void setOnHoverColor(sf::Color Color);
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief If function returns true it will also return an offset. Use getOffset() function to get offset.
    /// @return Returns true if slider is moved.
    /// @param win Render window where objects are rendered
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    bool barMoved(sf::RenderWindow &win);

    //////////////////////////////////////////////////////////////
    /// @brief Moves scroll bar.
    /// @param Offset how much movement.
    //////////////////////////////////////////////////////////////
    void moveBar(float Offset);
    

private:

    bool wFocus = false;

    bool SliderHeld = false;
    sf::Vector2f HeldAtDistance;

    bool Vertical = false;
    bool Horizontal = false;
    
    sf::Color MainColor;
    sf::Color HoverColor;

    float OffsetY = 0;
    float OffsetX = 0;

    sf::Vector2f StartingPosition;
    sf::Vector2f ButtonOnePosition;
    sf::Vector2f ScrollBarAreaSize;
    sf::Vector2f ScrollBarPosition;
    sf::Vector2f ScrollBarSize;
    sf::Vector2f ButtonTwoPosition;

    sf::RectangleShape ScrollBarArea;
    sf::RectangleShape Bar;
    
    Button UpOrLeft;
    Button DownOrRight;

    bool mouseOverBar(sf::RenderWindow &win);

    bool MouseOverScrollBarArea(sf::RenderWindow &win);
};
} // namespace vui




#endif
