#include "entry.hpp"
#include "graphics.hpp"


Entry::Entry(int pos_x, int pos_y, int w, int h, string t, sf::Color c, sf::Color tColor, bool write) {
    width = w, height = h;
    pos_X = pos_x, pos_Y = pos_y;
    pos_text_X = pos_x, pos_text_Y = pos_y;
    text = t;
    color = c;
    fontSize = 20;
    textPosition = Position::no;
    writeActiv = write;
    
    rect.setPosition(pos_x, pos_y);
    rect.setSize(sf::Vector2f(w, h));
    rect.setFillColor(color);

    font.loadFromFile("font.ttf");

    textDisplay.setString(text);
    textDisplay.setFont(font);
    textDisplay.setCharacterSize(fontSize);
    textDisplay.setPosition(pos_X, pos_Y);
    textDisplay.setFillColor(tColor);
}

string Entry::getText() const {
    return text;
}

void Entry::update() {
    rect.setPosition(pos_X, pos_Y);

    textDisplay.setFont(font);
    textDisplay.setString(text);
    textDisplay.setCharacterSize(fontSize);
    textDisplay.setPosition(pos_X, pos_Y);
}

void Entry::draw(sf::RenderWindow &window) {
    window.draw(rect);
    window.draw(textDisplay);
}


void Entry::setIntEntry(sf::Event &e, bool decimal) {
    if (!writeActiv) {
        return ;
    }

    // on gère le retour en arrière et la limite de taille de l'entrée
    if (sf::Keyboard::BackSpace == e.key.code && text.size() > 0) {
        text.pop_back();
        update();
        return ;
    } else if (text.size() >= maxSize) {
        return ;
    }

    // on vérifie si la touche est un chiffre
    switch (e.key.code)
    {
    case sf::Keyboard::Num0:
        text.append("0");
        update();
        break;
    case sf::Keyboard::Num1:
        text.append("1");
        update();
        break;
    case sf::Keyboard::Num2:
        text.append("2");
        update();
        break;
    case sf::Keyboard::Num3:
        text.append("3");
        update();
        break;
    case sf::Keyboard::Num4 :
        text.append("4");
        update();
        break;
    case sf::Keyboard::Num5:
        text.append("5");
        update();
        break;
    case sf::Keyboard::Num6:
        text.append("6");
        update();
        break;
    case sf::Keyboard::Num7:
        text.append("7");
        update();
        break;
    case sf::Keyboard::Num8:
        text.append("8");
        update();
        break;
    case sf::Keyboard::Num9:
        text.append("9");
        update();
        break;
    case sf::Keyboard::Numpad0 :
        text.append("0");
        update();
        break;
    case sf::Keyboard::Numpad1 :
        text.append("1");
        update();
        break;
    case sf::Keyboard::Numpad2 :
        text.append("2");
        update();
        break;
    case sf::Keyboard::Numpad3 :
        text.append("3");
        update();
        break;
    case sf::Keyboard::Numpad4 :
        text.append("4");
        update();
        break;
    case sf::Keyboard::Numpad5 :
        text.append("5");
        update();
        break;
    case sf::Keyboard::Numpad6 :
        text.append("6");
        update();
        break;
    case sf::Keyboard::Numpad7 :
        text.append("7");
        update();
        break;
    case sf::Keyboard::Numpad8 :
        text.append("8");
        update();
        break;
    case sf::Keyboard::Numpad9 :
        text.append("9");
        update();
        break;
    default:
        break;
    }
}


void Entry::clear() {
    text = "";
    update();
}

void Entry::setPos(int x, int y) {
    pos_X = x, pos_Y = y;
    update();
}


void Entry::setFontSize(int size) {
    fontSize = size;
    update();
}


void Entry::setTextPosition(Position pos) {
    if (pos == Position::center) {
        textPosition = Position::center;
        pos_text_X = pos_X + (width/2) - (textDisplay.getGlobalBounds().width/2);
        pos_text_Y = pos_Y + (height/2) - (textDisplay.getGlobalBounds().height);
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