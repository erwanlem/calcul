#include "button.hpp"
#include "graphics.hpp"


Button::Button(int pos_x, int pos_y, int w, int h, string t, sf::Color c, sf::Color tColor) {
    width = w, height = h;
    pos_X = pos_x, pos_Y = pos_y;
    pos_text_X = pos_X, pos_text_Y = pos_Y;
    text = t;
    color = c;
    fontSize = 20;
    mouseOverColor = color;
    textPosition = Position::no;


    
    rect.setPosition(pos_X, pos_Y);
    rect.setSize(sf::Vector2f(w, h));
    rect.setFillColor(color);

    font.loadFromFile("font.ttf");

    textDisplay.setString( text );
    textDisplay.setFont(font);
    textDisplay.setCharacterSize(fontSize);
    textDisplay.setPosition(pos_text_X, pos_text_Y);
    textDisplay.setFillColor(tColor);
}

void Button::setTextPosition(Position pos) {
    if (pos == Position::center) {
        textPosition = Position::center;
        pos_text_X = pos_X + (width/2) - textDisplay.getGlobalBounds().width/2;
        pos_text_Y = pos_Y + (height/2) - textDisplay.getGlobalBounds().height/2;
        textDisplay.setOrigin(textDisplay.getLocalBounds().left, textDisplay.getLocalBounds().top);
        textDisplay.setPosition(pos_text_X, pos_text_Y);
        update();
    } else {
        textPosition = Position::no;
        pos_text_X = pos_X;
        pos_text_Y = pos_Y;
        textDisplay.setPosition(pos_text_X, pos_text_Y);
        update();
    }
}

void Button::setTextPosition(int x, int y) {
    textPosition = Position::custom;
    pos_text_X = pos_X + x;
    pos_text_Y = pos_Y + y;
    textDisplay.setPosition(pos_text_X, pos_text_Y);
}


sf::RectangleShape Button::getRect() const {
    return rect;
}

sf::Text Button::getText() const {
    return textDisplay;
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(rect);
    window.draw(textDisplay);
}

void Button::setPos(int x, int y) {
    pos_X = x;
    pos_Y = y;
}

void Button::setSize(int w, int h) {
    width = w;
    height = h;
}


bool Button::isOver(int pos_x, int pos_y) const {
    if (pos_x > pos_X && pos_x < pos_X + width && pos_y > pos_Y && pos_y < pos_Y + height) {
        return true;
    } else {
        return false;
    }
}

void Button::setText(string t) {
    text = t;
    update();
}

void Button::update() {
    rect.setPosition(pos_X, pos_Y);

    textDisplay.setPosition(pos_text_X, pos_text_Y);
    textDisplay.setFont(font);
    textDisplay.setString(text);
    textDisplay.setCharacterSize(fontSize);
}

void Button::setFontSize(int size) {
    fontSize = size;
    setTextPosition(textPosition);
    update();
}


void Button::colorSwitch(bool mouseOver) {
    if (mouseOver) {
        rect.setFillColor(mouseOverColor);
    } else {
        rect.setFillColor(color);
    }
}

void Button::setMouseOverColor(sf::Color c) {
    mouseOverColor = c;
}


