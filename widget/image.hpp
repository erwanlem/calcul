#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include "graphics.hpp"

using namespace std;


class Image
{
private:
    int pos_X, pos_Y;
    int width, height;

    sf::Sprite shape;
    sf::Texture texture;
    bool over;
public:
    /**
     * @brief Construct a new Image object
     * 
     * @param x position en x de l'image
     * @param y position en y de l'image
     * @param w largeur de l'image
     * @param h hauteur de l'image
     * @param image le chemin d'accès à l'image
     */
    Image(int x, int y, int w, int h, string path);

    Image(int x, int y, int w, int h, sf::Texture &t);

    Image() {};

    /**
     * @brief modifier la taille de l'image
     * 
     * @param w largeur en pixel
     * @param h hauteur en pixel
     */
    void resize(int w, int h);

    /**
     * @brief pos_x et pos_y au dessus de l'image TRUE/FALSE
     * 
     * @param pos_x la position en x
     * @param pos_y la position en y
     * @return true si les coordonnées sont au-dessus de l'image
     * @return false 
     */
    bool isOver(int pos_x, int pos_y);

    /**
     * @brief Get the Pos X object
     * 
     * @return int 
     */
    int getPosX() const {return pos_X;}

    /**
     * @brief Get the Pos Y object
     * 
     * @return int 
     */
    int getPosY() const {return pos_Y;}

    /**
     * @brief Get the Width object
     * 
     * @return int 
     */
    int getWidth() const {return width;}

    /**
     * @brief Get the Height object
     * 
     * @return int
     */
    int getHeight() const {return height;}

    /**
     * @brief Set the Pos object
     * 
     * @param x 
     * @param y 
     */
    void setPos(int x, int y);

    /**
     * @brief Set the Size object
     * 
     * @param w 
     * @param h 
     */
    void setSize(int w, int h);

    void draw(sf::RenderWindow &window) ;

    void setTextures(sf::Texture &t);

    void update();
};

#endif