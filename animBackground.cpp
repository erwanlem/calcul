#include "animBackground.hpp"
#include <cmath>

using namespace std;


animNumber::animNumber(int t_x, int t_y) {
    tailleX = t_x; tailleY = t_y;

    rayon = sqrt((int(tailleX/2))*(int(tailleX/2)) + (int(tailleY/2))*(int(tailleY/2)));
    rayonDepart = rayon;
    angle = (rand() % 360) * (180/(2 * acos(0.0)));
    x = (int(tailleX/2)) + (cos(angle) * rayon);
    y = (int(tailleY/2)) + (sin(angle) * rayon);
    size = 90;
    transMovment = (rand() % 6) - 3;
    spiraleMovment = 1; // movement en spirale en dégrès par image

    value = to_string( rand() % 20 );
    font.loadFromFile("animFont.ttf");
    numberText.setFont(font);
    numberText.setCharacterSize(size);
    numberText.setFillColor(sf::Color{255, 255, 255, 200});
    numberText.setString(value);
}


void animNumber::move(double dist) {
    if (rayon < 1) {
        reset();
        return ;
    } else {
        angle += dist * ((2 * acos(0.0))/180);

        size = (rayon * 100 / rayonDepart) / 100;
        
        if (angle > (2 * acos(0.0))) {
            rayon -= dist;
        } else {
            rayon += dist;
        }
        x = int((tailleX/2) + cos(angle) * rayon);
        y = int((tailleY/2) + sin(angle) * rayon);

        numberText.setScale(size, size);
        numberText.setPosition(x, y);
        numberText.rotate(transMovment);

    }
}


void animNumber::draw(sf::RenderWindow &window) {
    window.draw(numberText);
}


void animNumber::reset() {
    rayon = rayonDepart + (rand() % 20) + 20;

    angle = (rand() % 360) * (180/(2 * acos(0.0)));
    x = int((tailleX/2) + cos(angle) * rayon);
    y = int((tailleY/2) + sin(angle) * rayon);
    transMovment = (rand() % 6) - 3;

    value = to_string( rand() % 20 );
    numberText.setFont(font);
    numberText.setString(value);
}




Animation::Animation(int windowX, int windowY, int nbrElement) {
    tailleVect = nbrElement;
    tailleX = windowX;
    tailleY = windowY;

    rayon = sqrt((int(tailleX/2))*(int(tailleX/2)) + (int(tailleY/2))*(int(tailleY/2)));

    for (int i = 0; i < nbrElement; i++) {
        numbers.push_back( animNumber(tailleX, tailleY) );
    }
    for (int i = 0; i < nbrElement; i++) {
        numbers[i].reset();
    }
}

void Animation::move() {
    for (int i = 0; i < tailleVect; i++) {
        numbers[i].move(0.6);
    }
}

void Animation::initialMove() {
    for (int i = 0; i < tailleVect; i++) {
        numbers[i].move(rand() % tailleX);
    }
}


void Animation::draw(sf::RenderWindow &window) {
    for (int i = 0; i < tailleVect; i++) {
        numbers[i].draw(window);
    }
}