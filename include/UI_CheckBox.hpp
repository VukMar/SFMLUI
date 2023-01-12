#ifndef UI_CHECKBOX
#define UI_CHECKBOX

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

namespace vui
{

enum Style
{
    Circle = 1,
    Square = 2,
    None = 0
};



class CheckBox
{
public:
    
    bool debuging = false;

    CheckBox();

    ~CheckBox();
    
    ///////////////////////////////////////////////////////////////////////////////////////
    /// @brief 
    /// Creates the CheckBox.
    /// Make sure you set the style of CheckBox by using vui::Style.
    /// If you use custom style, dont forget to create the rest of the CheckBox.
    /// @param Size The size of CheckBox
    /// @param Postition The position of CheckBox  
    /// @param Style  The style of CheckBox. - vui::Style - set to None for custom style
    ////////////////////////////////////////////////////////////////////////////////////////
    void create(float Size, sf::Vector2f Position, int Style);
    
    ////////////////////////////////////////////////////////////////////////////////////////
    /// @brief
    /// Modifies main box style only. - Only use if you have set style to None!
    /// @param Style 
    ////////////////////////////////////////////////////////////////////////////////////////
    void createMainBox(int Style);

    ////////////////////////////////////////////////////////////////////////////////////////
    /// @brief
    /// Modifies check marker style only. - Only use if you have set style to None!
    /// @param Style 
    ////////////////////////////////////////////////////////////////////////////////////////
    void createCheckMarker(int Style);

    ////////////////////////////////////////////////////////////////////////////////////////
    /// @brief
    /// Modifies the main color of check box - Default is white.
    /// @param Color sf::Color
    ////////////////////////////////////////////////////////////////////////////////////////
    void setMainColor(sf::Color Color);

    ////////////////////////////////////////////////////////////////////////////////////////
    /// @brief
    /// Modifies the check color of check box - Default is white.
    /// @param Color sf::Color
    ///////////////////////////////////////////////////////////////////////////////////////
    void setCheckColor(sf::Color Color);

    ////////////////////////////////////////////////////////////////////////////////////////
    /// @brief
    /// @return Returns true if box is checked.
    ////////////////////////////////////////////////////////////////////////////////////////
    bool isBoxChecked();

    /////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Unchecks checkbox.
    ///////////////////////////////////////////////////////////////////////////////////////////
    void uncheckBox();

    /////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Checks checkbox.
    ///////////////////////////////////////////////////////////////////////////////////////////
    void checkBox();

    ////////////////////////////////////////////////////////////////////////////////////////
    /// @brief
    /// Displays CheckBox to window
    /// @param win sf::RenderWindow
    ////////////////////////////////////////////////////////////////////////////////////////
    void displayTo(sf::RenderWindow &win);

private:

    bool isMouseLeftPressed = false;

    bool MainBoxCreated = false;
    bool CheckMarkCreated = false;

    bool CheckBoxFinished = false;

    bool isBoxCircle = false;
    bool isBoxSquare = false;

    bool isCheckCircle = false;
    bool isCheckSquare = false;

    float BoxSize;
    float CheckSize;
    sf::Vector2f BoxPosition;


    //vui::Style::Square:

    sf::RectangleShape CheckBoxT1;
    sf::RectangleShape CheckMarkT1;

    //vui::Style::Square:

    sf::CircleShape CheckBoxT2;
    sf::CircleShape CheckMarkT2;

    sf::Color MainColor;
    sf::Color CheckColor;

    bool isChecked = false;
    bool wFocus = false;

    void adjustOutline(bool ShowOutline);

    bool mouseOverCheckbox(sf::RenderWindow &win);

    bool mouseLeftCilckReleased();

    void consolelog(std::string log);

};



}


#endif