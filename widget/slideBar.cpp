#include "slideBar.hpp"


SlideBar::SlideBar(int x, int y, int w, int h, int optNumber, int defaultOpt, sf::Color color, sf::Color selectColor) {
    pos_X = x; pos_Y = y;
    width = w; height = h;
    option = defaultOpt;
    lineColor = color;
    buttonColor = selectColor;
    sf::CircleShape b;
    for (int i = 0; i < optNumber; i++) {
        b.setRadius(height + height/2);
        b.setPointCount(50);
        b.setPosition(sf::Vector2f{float(pos_X + (i * (width / (optNumber-1)))), float(pos_Y - b.getRadius()/2)});
        if (i == defaultOpt) {
            b.setFillColor(selectColor);
        } else {
            b.setFillColor(color);
        }
        optButton.push_back(b);
    }
    line.setPosition(sf::Vector2f{float(pos_X), float(pos_Y)});
    line.setSize(sf::Vector2f(float(width), float(height)));
    line.setFillColor(color);
}

int SlideBar::isOver(int posX, int posY) const {
    for (int i = 0; i < optButton.size(); i++) {
        if (posX >= optButton[i].getPosition().x && posY >= optButton[i].getPosition().y && posX <= optButton[i].getPosition().x + optButton[i].getGlobalBounds().width && posY <= optButton[i].getPosition().y + optButton[i].getGlobalBounds().height) {
            return i;
        }
    }
    return -1;
}

void SlideBar::setOptNumber(int nb) {
    if (nb != option) {
        optButton[option].setFillColor(lineColor);
        option = nb;
        optButton[option].setFillColor(buttonColor);
    }
}

void SlideBar::draw(sf::RenderWindow &window) {
    window.draw(line);
    for (int i = 0; i < optButton.size(); i++) {
        window.draw(optButton[i]);
    }
}

int SlideBar::getOptNumber() const {
    return option;
}

