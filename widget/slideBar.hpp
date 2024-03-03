#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class SlideBar
{
private:
    sf::RectangleShape line;
    vector<sf::CircleShape> optButton;
    int option;
    int width, height;
    int pos_X, pos_Y;
    sf::Color lineColor, buttonColor;
public:
    SlideBar(int x, int y, int w, int h, int optNumber, int defaultOpt = 0, sf::Color = {0, 0, 0}, sf::Color selectColor = {255, 0, 0});
    SlideBar() {} // Constructeur par défaut
    void setOptNumber(int nb);
    void setPosX(int x);
    void setPosY(int y);
    void setWidth(int w);
    void setHeight(int h);
    int getOptNumber() const;
    int getPosX() const;
    int getPosY() const;
    int getWidth() const;
    int getHeight() const;
    int isOver(int posX, int posY) const;
    void draw(sf::RenderWindow &window);
};