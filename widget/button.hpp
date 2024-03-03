#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "graphics.hpp"
#include <string.h>
#include <iostream>

using namespace std;


class Button
{
private:
    string text;
    wchar_t textAccent;
    bool click;
    int pos_X, pos_Y;
    int pos_text_X, pos_text_Y;
    int width, height;
    sf::Color color, textColor, mouseOverColor;
    sf::Font font;
    unsigned int fontSize;
    Position textPosition;

    sf::RectangleShape rect;
    sf::Text textDisplay;
public:
    Button(int pos_x, int pos_y, int w, int h, string t = "", sf::Color c = {255, 255, 255}, sf::Color tColor = {0, 0, 0});

    void setColor(int color[3]);
    void setSize(int w, int h);
    void setPos(int x, int y);
    void setText(string t);
    void setMouseOverColor(sf::Color c);
    bool isOver(int pos_x, int pos_y) const;
    void colorSwitch(bool mouseOver);
    void draw(sf::RenderWindow &window);
    void update();
    sf::RectangleShape getRect() const;
    sf::Text getText() const;
    void setFontSize(int size = 30);
    int getTextWidth() const {return textDisplay.getGlobalBounds().width;}
    int getPositionX() const {return pos_X;}
    int getPositionY() const {return pos_Y;}
    
    void setTextPosition(Position pos);
    void setTextPosition(int x, int y);
};


#endif