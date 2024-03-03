#include <SFML/Graphics.hpp>

using namespace std;

class CheckBox
{
private:
    bool check;
    sf::Texture checkTexture, emptyTexture;
    sf::Sprite imgShape;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape shape;
    int width, height;
    int pos_X, pos_Y, caseX, caseY;
public:
    CheckBox(int x, int y, int w, int h, string txt = "", bool c = false);
    bool isCheck() const {return check;}
    void switchCheck();
    void setFontSize(int size);
    void setText(string text);
    void setPosition(int x, int y);
    void setSize(int w, int h);
    int getTextWidh() const {return text.getGlobalBounds().width;}
    int getWidth() const {return width;}
    int getHeight() const {return height;}
    int getPosX() const {return shape.getPosition().x;}
    int getPosY() const {return shape.getPosition().y;}
    void draw(sf::RenderWindow &window);
    bool isOver(int pos_x, int pos_y) ;
    void setTextColor(sf::Color c);
    void setShapeColor(sf::Color c);
    void update();
};


