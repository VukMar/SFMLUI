/*Button class by Vuk Maric - VUI-SFML*/

#ifndef UI_BUTTON
#define UI_BUTTON
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
namespace vui
{
/*VUI-SFML button input.
Used for user confirmation inputs.*/
class Button
{
public:

    //Default constructor(Will never take Arguments, but only used to load nesesary stuff for button functionality)
    Button();

    //Default destructor
    ~Button();

    /////////////////////////////////////////////////////////////////////////
    /// @brief Loads font for button text.
    /// @param FilePath path to font file.
    /////////////////////////////////////////////////////////////////////////
    bool loadFontFromFile(std::string FilePath);

    /////////////////////////////////////////////////////////////////////////
    /// @brief Loads font for button text.
    /// @param data data with font information.
    /////////////////////////////////////////////////////////////////////////
    bool loadFontFromMemory(std::vector<unsigned char> &data);
    
    /////////////////////////////////////////////////////////////////////////
    /// @brief Creates button with given parameters.
    /// @param ButtonText 
    /// @param TextSize 
    /// @param Size size of button.
    /// @param Position position of a button.
    /// @param ButtonColor color of a button.
    /// @param ButtonHoverColor color of a button on cursor hover.
    /////////////////////////////////////////////////////////////////////////
    void create(std::string ButtonText, int TextSize, sf::Vector2f Size, sf::Vector2f Position, sf::Color ButtonColor, sf::Color ButtonHoverColor);
    
    /////////////////////////////////////////////////////////////////////////
    /// @brief Creates button using texture.
    /// @param Position 
    /// @param Size 
    /// @param texture 
    /////////////////////////////////////////////////////////////////////////
    void createFromSprite(sf::Vector2f Position, sf::Vector2f Size, sf::Texture &texture);

    /////////////////////////////////////////////////////////////////////////
    /// @brief Makes Button outline
    /// @param OutlineThickness 
    /////////////////////////////////////////////////////////////////////////
    void hasOutline(float Thickness);
    
    /////////////////////////////////////////////////////////////////////////
    /// @brief 
    /// @param win 
    /////////////////////////////////////////////////////////////////////////
    void displayTo(sf::RenderWindow &win);

    /////////////////////////////////////////////////////////////////////////
    /// @brief 
    /// @param win 
    /// @return 
    /////////////////////////////////////////////////////////////////////////
    bool isButtonPressed(sf::RenderWindow &win);
    
    /////////////////////////////////////////////////////////////////////////
    /// @brief 
    /// @param win 
    /// @return 
    /////////////////////////////////////////////////////////////////////////
    bool isButtonHeldDown(sf::RenderWindow &win);

    /////////////////////////////////////////////////////////////////////////
    /// @brief Moves button position by a given offset.
    /// @param Offset sf::Vector2f for offset value.
    /////////////////////////////////////////////////////////////////////////
    void move(sf::Vector2f Offset);

    /////////////////////////////////////////////////////////////////////////
    /// @brief Moves button position by a given offset.
    /// @param OffsetX float for x offset.
    /// @param OffsetY float for y offset.
    /////////////////////////////////////////////////////////////////////////
    void move(float OffsetX, float OffsetY);

    /////////////////////////////////////////////////////////////////////////
    /// @brief Gets position and size of a button.
    /// @return Returns sf::FloatRect and position and size of a button.
    /////////////////////////////////////////////////////////////////////////
    sf::FloatRect getBounds();

    void changeButtonColor(sf::Color Color);

    void changeButtonHoverColor(sf::Color Color);

    void changeButtonOutlineColor(sf::Color Color);

    void changeButtonTextColor(sf::Color Color);

    void changeTextOutlineColor(sf::Color Color);

private:

    sf::Clock c;
    float seconds = 0;

    sf::Vector2f ButtonPosition;

    
    //Representing the shape of Button
    sf::RectangleShape box;
    
    //Button text
    sf::Text text;
    
    //Font to be used for Button text
    sf::Font font;
    
    //Default color of button
    sf::Color ButtonColor;
    
    //Button color on hover
    sf::Color HoverColor;

    //Button outline color
    sf::Color OutlineColor;
    
    //Color of text fill
    sf::Color TextColor;
    
    //Color of text outline
    sf::Color TextOutlineColor = sf::Color::White;
    
    //Sprite for sprite button
    sf::Sprite sprite;
    
    //Checks focus on window
    bool wFocus;
    
    //Button press check
    bool ButtonPressed;
    
    float OutlineThickness = 0;

    bool Sprite = false;

    int frameCount = 0;

    //Checks if mouse is over button
    bool mouseOverButton(sf::RenderWindow &win);

};

}

#endif