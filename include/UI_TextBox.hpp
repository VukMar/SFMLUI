/*

VUI-SFML TextBox for text display and text edit.

VUI-SFML
by
Vuk Maric
vuk.s.maric@gmail.com

*/

#ifndef UI_TEXTBOX
#define UI_TEXTBOX
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

namespace vui
{
class TextBox
{
public:

    bool debuging = false;
    bool MultiLine = false;
    bool TextHasOutilne = false;
    bool BoxHasOutilne = true;
    bool Scrollable = false;
    
    /*Default constructor.*/
    TextBox();

    /*Default destructor.*/
    ~TextBox();

    /*Will return true if box is active.*/
    bool isActive(sf::RenderWindow &win);
    
    /*Loads font from file.
    Accepts std::string type as file path.
    Will return true if file is loaded successfully.
    Make sure you load a font before creating the TextBox!*/
    bool setFontFromFile(std::string filePath);

    ///////////////////////////////////////////////////////////////////////
    /// @brief Sets font for textbox given the right data.
    /// @param data Data that stores font parameters.
    /// @return Retruns true if load was successful.
    ///////////////////////////////////////////////////////////////////////
    bool setFontFromMemory(std::vector<unsigned char> &data);

    /*Creates Box with given size and position.
    Size and Position are sf::Vector2f type!
    Font size is of float type.
    Make sure you loaded the font for TextBox before creating it!*/
    void create(sf::Vector2f Size, sf::Vector2f Posistion, float FontSize);

    /*If box is active and input is registered this will return true.*/
    void typeOn(sf::Event ev);

    /*Clears all text in TextBox!*/
    void clear();

    /*Append text to TextBox.
    Input string as parameter.
    Will return true if text is loaded.*/
    bool displayText(std::string TextToRead);

    /*Append text to TextBox.
    Input file path as parameter.
    Will return true if text is loaded.*/
    bool displayTextFromFile(std::string FilePath);

    //////////////////////////////////////////////////////
    /// @brief Get text from TextBox.
    /// @return Retruns text info in form of std::string.
    //////////////////////////////////////////////////////
    std::string getText();

    /*Set custom color for TextBox fill.*/
    void changeBoxFillColor(sf::Color Color);

    /*Set custom color for TextBox outilne.
    Make sure TextBox Outilne is enabled! - It is enabled by defaut.*/
    void changeBoxOutilneColor(sf::Color Color);

    /*Set the outline thickness of box in "px".*/
    void setBoxOutlineThickness(float Thickness);

    /*Set custom color for Text fill.*/
    void changeTextFillColor(sf::Color Color);

    /*Set custom color for Text outline.
    Make sure text Outilne is enabled! - It is disabled by default.*/
    void changeTextOutineColor(sf::Color Color);
    
    /*Set the outline thickness of text in "px".*/
    void setTextOutlineThickness(float Thickness);

    /*Displays box to render traget aka the window.*/
    void displayTo(sf::RenderWindow &win);

    /*Moves the TextBox across window*/
    void move(sf::Vector2f Offset);

    /*Moves the TextBox across window*/
    void move(float xOffset, float yOffset);

private:

    sf::Clock c;
    float seconds = 0;
    
    bool Active = false;
    bool wFocus = false;

    float charSize;

    /*Represents TextBox shape.*/
    sf::RectangleShape box;
    sf::RectangleShape Navbar;

    /*Represents TextBox text stored in string*/
    std::vector<std::string> textToDisplay;
    
    /*Represents TextBox text.*/
    std::vector<sf::Text> text;
    sf::Color textFillColor = sf::Color::Black;
    sf::Color textOutlineColor = sf::Color::Black;
    
    /*Represents TextBox font.*/
    sf::Font font;
    
    /*Index of selected character in "std::string textToDisplay".*/
    int index = 0;
    /*Index of selected row*/
    int rowSelected = 0;

    int NumberOfRows = 0;
    int MaxNumberofRows = 0;

    float BoxOutlineThickness = 5;
    float textOutlineThickness = 0;

    /*Will return true if mouse cursor hovers over box.*/
    bool mouseOverBox(sf::RenderWindow &win);

    /*Creates a new line of text*/
    bool createLine(float FontSize);

    /*Creates a navigation bar based on text parameters*/
    void createNavigationBar();

    /*Draws a navigation bar to window*/
    void drawNavBar(sf::RenderWindow &win);
    
    /*Outputs string to console for debug messages*/
    void consoleLog(std::string log);

    /*Will warp text to fit in box if box is not scrollable*/
    void warpText();
    
};



}
#endif