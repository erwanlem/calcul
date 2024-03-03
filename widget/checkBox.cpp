#include "checkBox.hpp"
#include <iostream>

CheckBox::CheckBox(int x, int y, int w, int h, string txt, bool c) {
    width = w; height = h;
    pos_X = x; pos_Y = y;
    caseX = pos_X + width - height; caseY = pos_Y;
    check = c;

    shape.setPosition(pos_X, pos_Y);
    shape.setSize(sf::Vector2f(width, height));
    
    font.loadFromFile("font.ttf");
    text.setFont(font);
    text.setString(txt);
    text.setCharacterSize(height);
    text.setPosition(pos_X, pos_Y + text.getGlobalBounds().height/2 - height/2);


    checkTexture.loadFromFile("img/coche-white.png");
    emptyTexture.loadFromFile("img/case-vide-white.png");
    
    if (check) {
        imgShape.setTexture(checkTexture);
        imgShape.scale(height*1./checkTexture.getSize().x, height*1./checkTexture.getSize().y);
        imgShape.setPosition(pos_X + width - height, pos_Y);
    } else {
        imgShape.setTexture(emptyTexture);
        imgShape.scale(height*1./emptyTexture.getSize().x, height*1./emptyTexture.getSize().y);
        imgShape.setPosition(pos_X + width - height, pos_Y);
    }
}

void CheckBox::setPosition(int x, int y) {
    pos_X = x;
    pos_Y = y;
    caseX = pos_X + width - height;
    caseY = pos_Y;
}

void CheckBox::setSize(int w, int h) {
    width = w;
    height = h;
}

void CheckBox::draw(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(imgShape);
    window.draw(text);
}

void CheckBox::setTextColor(sf::Color c) {
    text.setFillColor(c);
}

void CheckBox::setShapeColor(sf::Color c) {
    shape.setFillColor(c);
}

bool CheckBox::isOver(int pos_x, int pos_y) {
    if (pos_x > caseX && pos_x < caseX + height && pos_y > caseY && pos_y < caseY + height) {
        return true;
    } else {
        return false;
    }
}

void CheckBox::update() {
    shape.setPosition(pos_X, pos_Y);
    shape.setSize(sf::Vector2f(width, height));
    
    text.setCharacterSize(height);
    text.setPosition(pos_X, pos_Y + text.getGlobalBounds().height/2 - height/2);
    
    if (check) {
        imgShape.scale(height*1./checkTexture.getSize().x, height*1./checkTexture.getSize().y);
        imgShape.setPosition(caseX, pos_Y);
    } else {
        imgShape.scale(height*1./emptyTexture.getSize().x, height*1./emptyTexture.getSize().y);
        imgShape.setPosition(caseX, pos_Y);
    }
}

void CheckBox::switchCheck() {
    check = !check;
    if (check) {
        imgShape.setTexture(checkTexture);
        imgShape.setScale(height*1./checkTexture.getSize().x, height*1./checkTexture.getSize().y);
        imgShape.setPosition(pos_X + width - height, pos_Y);
    } else {
        imgShape.setTexture(emptyTexture);
        imgShape.setScale(height*1./emptyTexture.getSize().x, height*1./emptyTexture.getSize().y);
        imgShape.setPosition(pos_X + width - height, pos_Y);
    }
}