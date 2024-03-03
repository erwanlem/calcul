#ifndef ENTRY_HPP
#define ENTRY_HPP

#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include "graphics.hpp"

using namespace std;


class Entry
{
private:
    string text;
    int pos_X, pos_Y;
    int pos_text_X, pos_text_Y;
    int width, height;

    unsigned int maxSize = 1000;
    sf::Color color, textColor;
    sf::Font font;
    bool writeActiv;
    unsigned int fontSize;
    Position textPosition;

    sf::RectangleShape rect;
    sf::Text textDisplay;
public:
    /**
     * @brief Construct a new Entry object
     * 
     * @param pos_x la position en X du widget
     * @param pos_y la position en Y du widget
     * @param w la largeur de l'objet 
     * @param h la hauteur de l'objet
     * @param t le texte contenu dans l'entrée (vide par défaut)
     * @param c la couleur du fond
     * @param tColor la couleur du texte
     */
    Entry(int pos_x, int pos_y, int w, int h, string t = "", sf::Color c = {255, 255, 255}, sf::Color tColor = {0, 0, 0}, bool write = true);
    
    /**
     * @brief retourne le texte que contient le widget
     * 
     * @return string 
     */
    string getText() const;

    /**
     * @brief Get the Rect object
     * 
     * @return sf::RectangleShape 
     */
    sf::RectangleShape getRect() const;

    /**
     * @brief écrit les entrées clavier de type Int (et backspace)
     * 
     * @param e l'object evenement
     */
    void setIntEntry(sf::Event &e, bool decimal = false);


    /**
     * @brief mise à jour de l'objet
     * 
     */
    void update();

    /**
     * @brief affichage de l'objet dans la fenêtre
     * 
     * @param window l'objet de type sf::RenderWindow
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief Set the Pos object
     * 
     * @param x la coordonnée X
     * @param y la coordonnée Y
     */
    void setPos(int x, int y);

    /**
     * @brief Set the Color object
     * 
     * @param color un tableau {r, g, b}
     */
    void setColor(int color[3]);

    /**
     * @brief définit l'entrée comme active ou non (true/false)
     *        Par défaut inactive
     */
    void setActiv() {writeActiv = !writeActiv;}

    /**
     * @brief Set the Max Size object
     * 
     * @param s le nombre maximum de caractères possibles
     */
    void setMaxSize(unsigned int s) {maxSize = s;}

    /**
     * @brief vide la zone de texte
     * 
     */
    void clear();

    /**
     * @brief définit la taille du texte
     * 
     * @param size la nouvelle taille du texte
     */
    void setFontSize(int size = 30);

    /**
     * @brief retourne la largeur du texte
     * 
     * @return la largeur du texte en pixel
     */
    int getTextWidth() const {return textDisplay.getGlobalBounds().width;}

    /**
     * @brief définit la position du texte dans le cadre
     * 
     * @param pos de type Position: center pour centrer le texte, no pour position en (0,0)
     */
    void setTextPosition(Position pos);
};


#endif