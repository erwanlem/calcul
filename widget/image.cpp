#include "image.hpp"

Image::Image(int x, int y, int w, int h, sf::Texture &t) {
    pos_X = x; pos_Y = y;
    width = w; height = h;
    texture = t;
    shape.setTexture(texture);
    shape.setPosition(pos_X, pos_Y);
    shape.scale(width*1./texture.getSize().x, height*1./texture.getSize().y);
}

void Image::setTextures(sf::Texture &t) {
    shape.setTexture(t);
}

void Image::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

bool Image::isOver(int pos_x, int pos_y) {
    if (pos_x > pos_X && pos_y > pos_Y && pos_x < pos_X + width && pos_y < pos_Y + height) {
        over = true;
        return true;
    } else {
        over = false;
        return false;
    }
}

void Image::setPos(int x, int y) {
    pos_X = x;
    pos_Y = y;
}

void Image::update() {
    shape.setPosition(pos_X, pos_Y);
}
