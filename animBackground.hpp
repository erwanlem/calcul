#ifndef BACKGROUND
#define BACKGROUND

#include <vector>
#include <SFML/Graphics.hpp>
#include "widget/graphics.hpp"
#include <random>
#include <cmath>
#include <string>


using namespace std;

class animNumber;

class Animation
{
private:
    vector<animNumber> numbers;
    int tailleX, tailleY;
    int tailleVect;
    int rayon;
    sf::Font font;
public:
    Animation(int windowX, int windowY, int nbrElement);
    Animation() {}
    void move();
    void initialMove();
    void draw(sf::RenderWindow &window);
};





class animNumber
{
private:
    int tailleX, tailleY;
    int x, y;
    string value;
    float rayon, rayonDepart;
    double angle, size;
    int transMovment, spiraleMovment;

    sf::Font font;
    sf::Text numberText;
public:
    /**
     * @brief Construct a new animNumber object
     * 
     * @param t_x la largeur de la fenêtre
     * @param t_y la hauteur de la fenêtre
     */
    animNumber(int t_x, int t_y);

    /**
     * @brief Construct a new animNumber object
     * Constructeur par défaut
     */
    animNumber() {}

    /**
     * @brief mouvement de l'animation vers le centre
     * 
     * @param dist la vitesse de l'animation -> nombre de pixel de moins en rayon
     */
    void move(double dist);

    /**
     * @brief affiche le nombre sur la fenêtre
     * 
     * @param window la fenêtre d'affichage
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief réinitialise l'animation de la lettre au début
     * 
     */
    void reset();
};



#endif