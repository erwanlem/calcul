#include <iostream>
#include "calcul.hpp"
#include <time.h>
#include <random>
#include "exercice.hpp"
#include "widget/graphics.hpp"
#include <vector>
#include "file.hpp"
#include <SFML/Graphics.hpp>
#include "animBackground.hpp"
#include "widget/slideBar.hpp"

using namespace std;

int MINI_INT_CALCUL;
int MAX_INT_CALCUL;

bool OPERATION_ADD = true;
bool OPERATION_DIV = true;
bool OPERATION_MUL = true;
bool OPERATION_SUB = true;

// Taille de l'affichage
int WINDOW_SIZE_X = sf::VideoMode::getDesktopMode().width;
int WINDOW_SIZE_Y = sf::VideoMode::getDesktopMode().height;
int EXO_SIZE = 10;

// Définition des fonctions d'affichage
int menu(sf::RenderWindow &window, sf::Event &event, sf::RectangleShape &background);
int exo(sf::RenderWindow &window, sf::Event &event, sf::RectangleShape &background);
int recap(sf::RenderWindow &window, sf::Event &event, sf::RectangleShape &background);
int historique(sf::RenderWindow &window, sf::Event &event, sf::RectangleShape &background);
int historyRecap(sf::RenderWindow &window, sf::Event &event, sf::RectangleShape &background, Exercice &r);


int main(int argc, char const *argv[])
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Fenetre");
    window.setFramerateLimit(50);
    window.setPosition(sf::Vector2i(-11, -11));
    
    sf::RectangleShape background;
    background.setFillColor(sf::Color{1, 38, 29});
    background.setSize(sf::Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y));


    sf::Event event;

    int state = menu(window, event, background);
    

    while (true) {
        if (state == 0) {
            window.close();
            break;
        } else if (state == 1) {
            state = menu(window, event, background);
        } else if (state == 2) {
            state = exo(window, event, background);
        } else if (state == 3) {
            state = recap(window, event, background);
        } else if (state == 4) {
            state = historique(window, event, background);
        }

    }
    
    return 0;
}






int menu(sf::RenderWindow &window, sf::Event &event, sf::RectangleShape &background) {
    // Initialisation de l'animation
    Animation a = Animation(WINDOW_SIZE_X, WINDOW_SIZE_Y, 90);
    a.initialMove();

    // Bouton commencer
    Button start = Button(toPercent(WINDOW_SIZE_X, 35), toPercent(WINDOW_SIZE_Y, 30), toPercent(WINDOW_SIZE_X, 30), toPercent(WINDOW_SIZE_Y, 15), "COMMENCER", {150, 150, 150, 200});
    start.setFontSize(40);
    start.setTextPosition(Position::center);
    start.setMouseOverColor(sf::Color{150, 150, 150, 255});

    // Bouton historique
    Button history = Button(toPercent(WINDOW_SIZE_X, 35), toPercent(WINDOW_SIZE_Y, 50), toPercent(WINDOW_SIZE_X, 30), toPercent(WINDOW_SIZE_Y, 15), "HISTORIQUE", {150, 150, 150, 200});
    history.setFontSize(40);
    history.setTextPosition(Position::center);
    history.setMouseOverColor(sf::Color{150, 150, 150, 255});

    // Paramètres
    sf::RectangleShape paramShape;
    paramShape.setFillColor(sf::Color{0, 0, 0, 230});
    paramShape.setSize(sf::Vector2f{float(toPercent(WINDOW_SIZE_X, 20)), float(toPercent(WINDOW_SIZE_Y, 30))});

    CheckBox check_add = CheckBox{toPercent(paramShape.getGlobalBounds().width, 15), toPercent(paramShape.getGlobalBounds().height, 5), toPercent(paramShape.getGlobalBounds().width, 70) , toPercent(paramShape.getGlobalBounds().height, 8), "Addition", true};
    check_add.setTextColor({255, 255, 255});
    check_add.setShapeColor({0, 0, 0, 0});

    CheckBox check_sub = CheckBox{toPercent(paramShape.getGlobalBounds().width, 15), toPercent(paramShape.getGlobalBounds().height, 15), toPercent(paramShape.getGlobalBounds().width, 70) , toPercent(paramShape.getGlobalBounds().height, 8), "Soustraction", true};
    check_sub.setTextColor({255, 255, 255});
    check_sub.setShapeColor({0, 0, 0, 0});

    CheckBox check_div = CheckBox{toPercent(paramShape.getGlobalBounds().width, 15), toPercent(paramShape.getGlobalBounds().height, 25), toPercent(paramShape.getGlobalBounds().width, 70) , toPercent(paramShape.getGlobalBounds().height, 8), "Division", true};
    check_div.setTextColor({255, 255, 255});
    check_div.setShapeColor({0, 0, 0, 0});

    CheckBox check_mult = CheckBox{toPercent(paramShape.getGlobalBounds().width, 15), toPercent(paramShape.getGlobalBounds().height, 35), toPercent(paramShape.getGlobalBounds().width, 70) , toPercent(paramShape.getGlobalBounds().height, 8), "Multiplication", true};
    check_mult.setTextColor({255, 255, 255});
    check_mult.setShapeColor({0, 0, 0, 0});

    Button writeEasy = Button{toPercent(paramShape.getGlobalBounds().width, 10), toPercent(paramShape.getGlobalBounds().height, 60), 0, 0, "Facile", {0, 0, 0}, {255, 255, 255}};
    Button writeHard = Button{toPercent(paramShape.getGlobalBounds().width, 78), toPercent(paramShape.getGlobalBounds().height, 60), 0, 0, "Difficile", {0, 0, 0}, {255, 255, 255}};
    SlideBar difficulty = SlideBar{toPercent(paramShape.getGlobalBounds().width, 15), toPercent(paramShape.getGlobalBounds().height, 70), toPercent(paramShape.getGlobalBounds().width, 70), 6, 4, 0, {255, 255, 255}};

    Button textTaille = Button{toPercent(paramShape.getGlobalBounds().width, 5), toPercent(paramShape.getGlobalBounds().height, 90), 0, 0, "Nombre questions: ", {0, 0, 0}, {255, 255, 255}};
    textTaille.setFontSize(toPercent(paramShape.getGlobalBounds().height, 6));
    CheckBox checkSize10 = CheckBox{toPercent(paramShape.getGlobalBounds().width, 55), toPercent(paramShape.getGlobalBounds().height, 91), toPercent(paramShape.getGlobalBounds().width, 14) , toPercent(paramShape.getGlobalBounds().height, 6), "10", true};
    CheckBox checkSize20 = CheckBox{toPercent(paramShape.getGlobalBounds().width, 75), toPercent(paramShape.getGlobalBounds().height, 91), toPercent(paramShape.getGlobalBounds().width, 14) , toPercent(paramShape.getGlobalBounds().height, 6), "20", false};
    checkSize10.setTextColor({255, 255, 255}); checkSize20.setTextColor({255, 255, 255});
    checkSize10.setShapeColor({0, 0, 0, 0}); checkSize20.setShapeColor({0, 0, 0, 0});

    while (true) {
        a.move();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return 0;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (start.isOver(event.mouseButton.x, event.mouseButton.y)) {
                    OPERATION_ADD = check_add.isCheck();
                    OPERATION_DIV = check_div.isCheck();
                    OPERATION_MUL = check_mult.isCheck();
                    OPERATION_SUB = check_sub.isCheck();
                    switch (difficulty.getOptNumber()) {
                    case 0:
                        MAX_INT_CALCUL = 10;
                        break;
                    case 1:
                        MAX_INT_CALCUL = 20;
                        break;
                    case 2:
                        MAX_INT_CALCUL = 100;
                        break;
                    case 3:
                        MAX_INT_CALCUL = 200;
                        break;
                    default:
                        MAX_INT_CALCUL = 10;
                        break;
                    }
                    if (checkSize10.isCheck()) {
                        EXO_SIZE = 10;
                    } else {
                        EXO_SIZE = 20;
                    }
                    return 2;
                }
                if (history.isOver(event.mouseButton.x, event.mouseButton.y)) {
                    return 4;
                }
                if (check_add.isOver(event.mouseButton.x, event.mouseButton.y)) {
                    check_add.switchCheck();
                }
                if (check_sub.isOver(event.mouseButton.x, event.mouseButton.y)) {
                    check_sub.switchCheck();
                }
                if (check_mult.isOver(event.mouseButton.x, event.mouseButton.y)) {
                    check_mult.switchCheck();
                }
                if (check_div.isOver(event.mouseButton.x, event.mouseButton.y)) {
                    check_div.switchCheck();
                }
                if (checkSize10.isOver(event.mouseButton.x, event.mouseButton.y) && !checkSize10.isCheck()) {
                    checkSize10.switchCheck();
                    checkSize20.switchCheck();
                }
                if (checkSize20.isOver(event.mouseButton.x, event.mouseButton.y) && !checkSize20.isCheck()) {
                    checkSize10.switchCheck();
                    checkSize20.switchCheck();
                }
                if (difficulty.isOver(event.mouseButton.x, event.mouseButton.y) != -1) {
                    difficulty.setOptNumber(difficulty.isOver(event.mouseButton.x, event.mouseButton.y));
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                start.colorSwitch(start.isOver(event.mouseMove.x, event.mouseMove.y));
                history.colorSwitch(history.isOver(event.mouseMove.x, event.mouseMove.y));
            }
            if (event.type == sf::Event::Resized) {
                WINDOW_SIZE_X = window.getSize().x;
                WINDOW_SIZE_Y = window.getSize().y;
                paramShape.setSize(sf::Vector2f{float(toPercent(WINDOW_SIZE_X, 20)), float(toPercent(WINDOW_SIZE_Y, 30))});
                start.setPos(toPercent(WINDOW_SIZE_X, 35), toPercent(WINDOW_SIZE_Y, 30));
                start.setSize(toPercent(WINDOW_SIZE_X, 30), toPercent(WINDOW_SIZE_Y, 15));
                history.setPos(toPercent(WINDOW_SIZE_X, 35), toPercent(WINDOW_SIZE_Y, 50));
                history.setSize(toPercent(WINDOW_SIZE_X, 30), toPercent(WINDOW_SIZE_Y, 15));
                /*checkSize10.setSize(toPercent(paramShape.getGlobalBounds().width, 14) , toPercent(paramShape.getGlobalBounds().height, 6));
                checkSize10.setPosition(toPercent(paramShape.getGlobalBounds().width, 55), toPercent(paramShape.getGlobalBounds().height, 91));
                checkSize10.update();
                checkSize20.setSize(toPercent(paramShape.getGlobalBounds().width, 14) , toPercent(paramShape.getGlobalBounds().height, 6));
                checkSize20.setPosition(toPercent(paramShape.getGlobalBounds().width, 75), toPercent(paramShape.getGlobalBounds().height, 91));
                checkSize20.update();
                check_add.setPosition(toPercent(paramShape.getGlobalBounds().width, 15), toPercent(paramShape.getGlobalBounds().height, 5));
                check_sub.setPosition(toPercent(paramShape.getGlobalBounds().width, 15), toPercent(paramShape.getGlobalBounds().height, 15));
                check_div.setPosition(toPercent(paramShape.getGlobalBounds().width, 15), toPercent(paramShape.getGlobalBounds().height, 25));
                check_mult.setPosition(toPercent(paramShape.getGlobalBounds().width, 15), toPercent(paramShape.getGlobalBounds().height, 35));*/
            }
        }
        window.clear(sf::Color{1, 38, 29});
        
        a.draw(window);
        
        window.draw(paramShape);
        start.draw(window);
        history.draw(window);

        check_add.draw(window);
        check_sub.draw(window);
        check_mult.draw(window);
        check_div.draw(window);
        textTaille.draw(window);
        checkSize10.draw(window);
        checkSize20.draw(window);
        difficulty.draw(window);
        writeEasy.draw(window);
        writeHard.draw(window);

        window.display();
    }
}






int exo(sf::RenderWindow &window, sf::Event &event, sf::RectangleShape &background) {
    Exercice e = Exercice(EXO_SIZE, {OPERATION_ADD, OPERATION_SUB, OPERATION_MUL, OPERATION_DIV}, MAX_INT_CALCUL);
    string calcTxt = ""; // récupère les calculs en str pour affichage

    int y_position = toPercent(WINDOW_SIZE_Y, 42);
    int x_position_ans = toPercent(WINDOW_SIZE_X, 24);

    // zone de question et zone d'écriture de la réponse
    Button question = Button(toPercent(WINDOW_SIZE_X, 20), y_position, 0, 0, "", {0, 0, 0}, {255, 255, 255});
    Entry answer = Entry(x_position_ans + question.getTextWidth(), y_position, 0,0, "", {0, 0, 0}, {255, 255, 255});

    answer.setMaxSize(5);
    question.setText(e.getQuestion());

    question.setFontSize(toPercent(WINDOW_SIZE_X, 10));
    answer.setFontSize(toPercent(WINDOW_SIZE_X, 10));

    answer.setPos(x_position_ans + question.getTextWidth(), y_position);
    answer.clear();

    // affichage de l'évolution dans la série ( ex: 1/20 )
    Button num_question = Button(0, 0, toPercent(WINDOW_SIZE_X, 10), toPercent(WINDOW_SIZE_Y, 10), to_string(e.getActivQuestion()) + '/' + to_string(e.getNbQuestions()), {0, 0, 0}, {255, 255, 255});
    num_question.setFontSize(toPercent(WINDOW_SIZE_Y, 5));
    num_question.setTextPosition(Position::center);

    // affichage du temps
    Button exo_time = Button(WINDOW_SIZE_X - toPercent(WINDOW_SIZE_X, 10), 0, toPercent(WINDOW_SIZE_X, 10), toPercent(WINDOW_SIZE_Y, 10), to_string(e.getActivQuestion()) + ':' + to_string(e.getNbQuestions()), {0, 0, 0}, {255, 255, 255});
    exo_time.setFontSize(toPercent(WINDOW_SIZE_Y, 5));
    exo_time.setTextPosition(Position::center);

    string timeText;

    e.switchActiv();
    while (true) {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                e.freeExo();
                return 0;
            }

            if (event.type == sf::Event::EventType::KeyPressed) {

                if (e.isActiv()) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        if ( answer.getText() == "" ) {
                            calcTxt = e.setAnswer(false);
                            if (calcTxt == "end") {
                                e.switchActiv();
                                e.freeExo();
                                return 3;
                            } else {
                                question.setText( calcTxt );
                            }
                            
                        } else {
                            calcTxt = e.setAnswer(stoi(answer.getText()));
                            if (calcTxt == "end") {
                                e.switchActiv();
                                e.freeExo();
                                return 3;
                            } else {
                                question.setText( calcTxt );
                            }
                        }

                        answer.clear();
                        answer.setPos(x_position_ans + question.getTextWidth(), y_position);

                        num_question.setText(to_string(e.getActivQuestion()) + '/' + to_string(e.getNbQuestions()));
                        num_question.setTextPosition(Position::center);
                    }
                    answer.setIntEntry(event);
                }
            }
            if (e.getTime() > 20) {
                if ( answer.getText() == "" ) {
                            calcTxt = e.setAnswer(false);
                            if (calcTxt == "end") {
                                e.switchActiv();
                                e.freeExo();
                                return 3;
                            } else {
                                question.setText( calcTxt );
                            }
                            
                            answer.clear();
                            answer.setPos(x_position_ans + question.getTextWidth(), y_position);
                } else {
                    calcTxt = e.setAnswer(stoi(answer.getText()));
                    if (calcTxt == "end") {
                        e.switchActiv();
                        e.freeExo();
                        return 3;
                    } else {
                        question.setText( calcTxt );
                    }
                }
                answer.clear();
                answer.setPos(x_position_ans + question.getTextWidth(), y_position);
                num_question.setText(to_string(e.getActivQuestion()) + '/' + to_string(e.getNbQuestions()));
                num_question.setTextPosition(Position::center);
            }
        }
        
        
        /* AFFICHAGE POUR TEMPS > 60 secondes
        timeText = "";
        if (e.getTime()/60 < 10) {
            timeText += '0';
            timeText += to_string(e.getTime()/60);
        } else {
            timeText += to_string(e.getTime()/60);
        }
        timeText += ':';
        if (e.getTime()%60 < 10) {
            timeText += '0';
            timeText += to_string(e.getTime()%60);
        } else {
            timeText += to_string(e.getTime()%60);
        }
        */
        exo_time.setText(to_string(20 - e.getTime()));

        window.clear(sf::Color{1, 38, 29});

        question.draw(window);
        answer.draw(window);
        num_question.draw(window);
        exo_time.draw(window);

        window.display();
    }

}




int recap(sf::RenderWindow &window, sf::Event &event, sf::RectangleShape &background) {

    vector<string> lines = readLines();
    Exercice r = readExercice(lines, lines.size()-1);

    // Chargement des images
    sf::Texture f, t;
    sf::Image im1, im2;
    im1.loadFromFile("img/wrong.png");
    im2.loadFromFile("img/right.png");
    f.loadFromImage(im1);
    t.loadFromImage(im2);

    vector<Button> correction = {};
    vector<Image> correction_image = {};
    Button b = Button{0, 0, 0, 0};
    Image image;
    int y_percent = 35;

    if (r.getNbQuestions() == 10) {
        for (int i = 0; i < 5; i++) {
            Calcul c = r.getQuestionId(i);

            b = Button{toPercent(WINDOW_SIZE_X, 22), toPercent(WINDOW_SIZE_Y, y_percent), 0, 0, c.getStrReponseOp(), {0, 0, 0}, {255, 255, 255}};
            b.setFontSize(toPercent(WINDOW_SIZE_Y, 6));
            correction.push_back( b ); 

            if (c.estValide()) {
                image = Image{ toPercent(WINDOW_SIZE_X, 24)+b.getTextWidth(), toPercent(WINDOW_SIZE_Y, y_percent), toPercent(WINDOW_SIZE_Y, 6), toPercent(WINDOW_SIZE_Y, 6), t};
                image.setTextures(t);
                correction_image.push_back(image);
            } else {
                image = Image{ toPercent(WINDOW_SIZE_X, 24)+b.getTextWidth(), toPercent(WINDOW_SIZE_Y, y_percent), toPercent(WINDOW_SIZE_Y, 6), toPercent(WINDOW_SIZE_Y, 6), f};
                image.setTextures(f);
                correction_image.push_back(image);
                b = Button{toPercent(WINDOW_SIZE_X, 26)+b.getTextWidth() + toPercent(WINDOW_SIZE_Y, 6), toPercent(WINDOW_SIZE_Y, y_percent), 0, 0, to_string(c.getResultatOperation()), {0, 0, 0}, {255, 255, 255}};
                b.setFontSize(toPercent(WINDOW_SIZE_Y, 6));
                correction.push_back(b);
            }

            y_percent += 10;
        }
        y_percent = 35;
        for (int i = 5; i < 10; i++) {
            Calcul c = r.getQuestionId(i);

            b = Button{toPercent(WINDOW_SIZE_X, 60), toPercent(WINDOW_SIZE_Y, y_percent), 0, 0, c.getStrReponseOp(), {0, 0, 0}, {255, 255, 255}};
            b.setFontSize(toPercent(WINDOW_SIZE_Y, 6));
            correction.push_back( b );

            if (c.estValide()) {
                image = Image{ toPercent(WINDOW_SIZE_X, 62)+b.getTextWidth(), toPercent(WINDOW_SIZE_Y, y_percent), toPercent(WINDOW_SIZE_Y, 6), toPercent(WINDOW_SIZE_Y, 6), t};
                image.setTextures(t);
                correction_image.push_back(image);
            } else {
                image = Image{ toPercent(WINDOW_SIZE_X, 62)+b.getTextWidth(), toPercent(WINDOW_SIZE_Y, y_percent), toPercent(WINDOW_SIZE_Y, 6), toPercent(WINDOW_SIZE_Y, 6), f};
                image.setTextures(f);
                correction_image.push_back(image);
                b = Button{toPercent(WINDOW_SIZE_X, 64)+b.getTextWidth() + toPercent(WINDOW_SIZE_Y, 6), toPercent(WINDOW_SIZE_Y, y_percent), 0, 0, to_string(c.getResultatOperation()), {0, 0, 0}, {255, 255, 255}};
                b.setFontSize(toPercent(WINDOW_SIZE_Y, 6));
                correction.push_back(b);
            }

            y_percent += 10;   
        }
    } else if (r.getNbQuestions() == 20) {
        int column = 10;
        int y_percent = 35;
        for (int i = 0; i < 20; i+=5) {
            for (int j = 0; j < 5; j++) {
                Calcul c = r.getQuestionId(i+j);
                b = Button{toPercent(WINDOW_SIZE_X, column), toPercent(WINDOW_SIZE_Y, y_percent), 0, 0, c.getStrReponseOp(), {0, 0, 0}, {255, 255, 255}};
                b.setFontSize(toPercent(WINDOW_SIZE_Y, 4));
                correction.push_back( b );

                if (c.estValide()) {
                    image = Image{ toPercent(WINDOW_SIZE_X, column+1)+b.getTextWidth(), toPercent(WINDOW_SIZE_Y, y_percent+1), toPercent(WINDOW_SIZE_Y, 3), toPercent(WINDOW_SIZE_Y, 3), t};
                    image.setTextures(t);
                    correction_image.push_back(image);
                } else {
                    image = Image{ toPercent(WINDOW_SIZE_X, column+1)+b.getTextWidth(), toPercent(WINDOW_SIZE_Y, y_percent+1), toPercent(WINDOW_SIZE_Y, 3), toPercent(WINDOW_SIZE_Y, 3), f};
                    image.setTextures(f);
                    correction_image.push_back(image);
                    b = Button{toPercent(WINDOW_SIZE_X, column+2)+b.getTextWidth() + toPercent(WINDOW_SIZE_Y, 3), toPercent(WINDOW_SIZE_Y, y_percent), 0, 0, to_string(c.getResultatOperation()), {0, 0, 0}, {255, 255, 255}};
                    b.setFontSize(toPercent(WINDOW_SIZE_Y, 4));
                    correction.push_back(b);
                }

                y_percent += 10;
            }
            column += 22;
            y_percent = 35;
        }
    }


    string noteText, timeText;
    // Affichage note de l'exercice
    noteText = "Ma note: " + to_string(r.getNbValideQuestions()) + '/' + to_string(r.getNbQuestions());

    Button note = Button(toPercent(WINDOW_SIZE_X, 35), toPercent(WINDOW_SIZE_Y, 8), toPercent(WINDOW_SIZE_X, 30), toPercent(WINDOW_SIZE_Y, 20), noteText, {200, 200, 200});
    note.setFontSize(toPercent(note.getRect().getGlobalBounds().height, 30));
    note.setTextPosition( note.getRect().getGlobalBounds().width/2 - note.getTextWidth()/2 , toPercent(note.getRect().getGlobalBounds().height, 20));
    note.getText().setLineSpacing(3);

    // Affichage temps -> ajout de 0 devan le nombre si < 10
    timeText = "Temps: ";
    if (r.getFinalTime()/60 < 10) {
        timeText += '0';
        timeText += to_string(r.getFinalTime()/60);
    } else {
        timeText += to_string(r.getFinalTime()/60);
    }
    timeText += ':';
    if (r.getFinalTime()%60 < 10) {
        timeText += '0';
        timeText += to_string(r.getFinalTime()%60);
    } else {
        timeText += to_string(r.getFinalTime()%60);
    }

    Button timeDisplay = Button(toPercent(WINDOW_SIZE_X, 35), note.getText().getPosition().y + toPercent(note.getRect().getSize().y, 50), toPercent(WINDOW_SIZE_X, 30), 0, timeText);
    timeDisplay.setFontSize(toPercent(note.getRect().getGlobalBounds().height, 20));
    timeDisplay.setTextPosition(Position::center);

    sf::Texture home, homeOver, replay, replayOver;
    home.loadFromFile("img/home_white.png");  homeOver.loadFromFile("img/home1_white.png");
    replay.loadFromFile("img/replay_white.png"); replayOver.loadFromFile("img/replay1_white.png");
    Image homeButton = Image(toPercent(WINDOW_SIZE_X, 28), toPercent(WINDOW_SIZE_Y, 14), toPercent(WINDOW_SIZE_Y, 8), toPercent(WINDOW_SIZE_Y, 8), home);
    Image replayButton = Image(toPercent(WINDOW_SIZE_X, 67), toPercent(WINDOW_SIZE_Y, 14), toPercent(WINDOW_SIZE_Y, 8), toPercent(WINDOW_SIZE_Y, 8), replay);

    while (true) {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                return 0;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (homeButton.isOver(event.mouseButton.x, event.mouseButton.y)) {
                    return 1;
                }
                if (replayButton.isOver(event.mouseButton.x, event.mouseButton.y)) {
                    return 2;
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                if (homeButton.isOver(event.mouseMove.x, event.mouseMove.y)) {
                    homeButton.setTextures(homeOver);
                } else {
                    homeButton.setTextures(home);
                }
                if (replayButton.isOver(event.mouseMove.x, event.mouseMove.y)) {
                    replayButton.setTextures(replayOver);
                } else {
                    replayButton.setTextures(replay);
                }
            }
        }
        window.clear(sf::Color{1, 38, 29});

        note.draw(window);
        timeDisplay.draw(window);
        homeButton.draw(window);
        replayButton.draw(window);

        for (unsigned int i = 0; i < correction.size(); i++) {
            correction[i].draw(window);
        }

        for (unsigned int i = 0; i < correction_image.size(); i++) {
            correction_image[i].draw(window);
        }

        window.display();
    }
}



int historique(sf::RenderWindow &window, sf::Event &event, sf::RectangleShape &background) {
    vector<Button> histList = {};
    vector<Image> smileyNote = {};
    vector<Button> timeList = {};

    sf::Texture back, backOver;
    back.loadFromFile("img/back_white.png");
    backOver.loadFromFile("img/back1_white.png");
    Image backImg = Image{toPercent(WINDOW_SIZE_Y, 2), toPercent(WINDOW_SIZE_Y, 2), toPercent(WINDOW_SIZE_Y, 9), toPercent(WINDOW_SIZE_Y, 9), back};

    sf::Texture smileyHappy, smileySad, smileyNeutral, smileyStar;
    smileyHappy.loadFromFile("img/smile.png");
    smileySad.loadFromFile("img/sad.png");
    smileyNeutral.loadFromFile("img/neutral.png");
    smileyStar.loadFromFile("img/star.png");
    
    vector<string> histStr = readLines();
    vector<Exercice> exoList = {};
    Button writeList = Button{0, 0, 0, 0};
    Image smileyImg;
    string timeText;

    if (histStr.size() == 0) {
        // Si save.txt est vide
        writeList = Button(toPercent(WINDOW_SIZE_X, 25), toPercent(WINDOW_SIZE_Y, 25), 0, 0, "L'historique est vide");
        writeList.setFontSize(toPercent(WINDOW_SIZE_Y, 10));
        writeList.setPos(toPercent(WINDOW_SIZE_X, 50) - writeList.getTextWidth()/2, toPercent(WINDOW_SIZE_Y, 25));
    } else {
        // Si il y a des exos enregistrés
        int y_position = toPercent(WINDOW_SIZE_Y, 10);
        for (unsigned int i = 0; i < histStr.size(); i++) {
            Exercice info = readExercice(histStr, histStr.size() - i - 1);
            exoList.push_back(info);
            writeList = Button(toPercent(WINDOW_SIZE_X, 25), y_position, toPercent(WINDOW_SIZE_X, 50), toPercent(WINDOW_SIZE_Y, 12), to_string(info.getNbValideQuestions()) + '/' + to_string(info.getNbQuestions()), {150, 150, 150});
            writeList.setFontSize(toPercent(WINDOW_SIZE_Y, 6));
            writeList.setTextPosition( Position::center );
            writeList.setMouseOverColor({120, 120, 120});

            histList.push_back(writeList);

            if (info.getNbValideQuestions()*1./info.getNbQuestions() < 0.4) {
                smileyImg = Image{toPercent(WINDOW_SIZE_X, 28), y_position + toPercent(WINDOW_SIZE_Y, 2), toPercent(WINDOW_SIZE_Y, 8), toPercent(WINDOW_SIZE_Y, 8), smileySad};
                smileyImg.setTextures(smileySad);
            } else if (info.getNbValideQuestions()*1./info.getNbQuestions() > 0.6 && info.getNbValideQuestions()*1./info.getNbQuestions() < 1) {
                smileyImg = Image{toPercent(WINDOW_SIZE_X, 28), y_position + toPercent(WINDOW_SIZE_Y, 2), toPercent(WINDOW_SIZE_Y, 8), toPercent(WINDOW_SIZE_Y, 8), smileySad};
                smileyImg.setTextures(smileyHappy);
            } else if (info.getNbValideQuestions()/info.getNbQuestions() == 1) {
                smileyImg = Image{toPercent(WINDOW_SIZE_X, 28), y_position + toPercent(WINDOW_SIZE_Y, 2), toPercent(WINDOW_SIZE_Y, 8), toPercent(WINDOW_SIZE_Y, 8), smileySad};
                smileyImg.setTextures(smileyStar);
            } else {
                smileyImg = Image{toPercent(WINDOW_SIZE_X, 28), y_position + toPercent(WINDOW_SIZE_Y, 2), toPercent(WINDOW_SIZE_Y, 8), toPercent(WINDOW_SIZE_Y, 8), smileySad};
                smileyImg.setTextures(smileyNeutral);
            }
            smileyNote.push_back(smileyImg);

            // Ecriture du temps
            timeText = "";
            if (info.getFinalTime()/60 < 10) {
                timeText += '0';
                timeText += to_string(info.getFinalTime()/60);
            } else {
                timeText += to_string(info.getFinalTime()/60);
            }
            timeText += ':';
            if (info.getFinalTime()%60 < 10) {
                timeText += '0';
                timeText += to_string(info.getFinalTime()%60);
            } else {
                timeText += to_string(info.getFinalTime()%60);
            }

            writeList = Button(toPercent(WINDOW_SIZE_X, 65), y_position + toPercent(WINDOW_SIZE_Y, 4), 0, 0, timeText);
            writeList.setFontSize(toPercent(WINDOW_SIZE_Y, 4));
            timeList.push_back(writeList);

            y_position += toPercent(WINDOW_SIZE_Y, 14);
        }
    }

    
    while (true) {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                for (unsigned int i = 0; i < exoList.size(); i++) {
                    exoList[i].freeExo();
                }
                return 0;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (backImg.isOver(event.mouseButton.x, event.mouseButton.y)) {
                    for (unsigned int i = 0; i < exoList.size(); i++) {
                        exoList[i].freeExo();
                    }
                    return 1;
                }
                for (unsigned int i = 0; i < histList.size(); i++) {
                    if (histList[i].isOver(event.mouseButton.x, event.mouseButton.y)) {
                        int r;
                        r = historyRecap(window, event, background, exoList[i]);
                        if (r == 0) {
                            for (unsigned int i = 0; i < exoList.size(); i++) {
                                exoList[i].freeExo();
                            }
                            return 0;
                        } else if (r == 1) {
                            for (unsigned int i = 0; i < exoList.size(); i++) {
                                exoList[i].freeExo();
                            }
                            return 1;
                        }
                    }
                }
            }

            // déroulement roulette
            if (histStr.size() != 0 && event.type == sf::Event::MouseWheelMoved) {
                if (event.mouseWheel.delta > 0 && histList[0].getPositionY() < toPercent(WINDOW_SIZE_Y, 10)) {
                    for (unsigned int i = 0; i < histList.size(); i++) {
                        histList[i].setPos(histList[i].getPositionX(), histList[i].getPositionY() + toPercent(WINDOW_SIZE_Y, 4) );
                        histList[i].update();

                        smileyNote[i].setPos(toPercent(WINDOW_SIZE_X, 28), histList[i].getPositionY() + toPercent(WINDOW_SIZE_Y, 2));
                        smileyNote[i].update();

                        timeList[i].setPos(timeList[i].getPositionX(), histList[i].getPositionY() + toPercent(WINDOW_SIZE_Y, 4));
                        timeList[i].setTextPosition(Position::no);
                        timeList[i].update();

                        histList[i].setTextPosition( Position::center );
                    }
                }
                if (event.mouseWheel.delta < 0 && histList[histList.size()-1].getPositionY() > toPercent(WINDOW_SIZE_Y, 70)) {
                    for (unsigned int i = 0; i < histList.size(); i++) {
                        histList[i].setPos(histList[i].getPositionX(), histList[i].getPositionY() - toPercent(WINDOW_SIZE_Y, 4) );
                        histList[i].update();

                        smileyNote[i].setPos(toPercent(WINDOW_SIZE_X, 28), histList[i].getPositionY() + toPercent(WINDOW_SIZE_Y, 2));
                        smileyNote[i].update();
                        
                        timeList[i].setPos(timeList[i].getPositionX(), histList[i].getPositionY() + toPercent(WINDOW_SIZE_Y, 4));
                        timeList[i].setTextPosition( Position::no );
                        timeList[i].update();

                        histList[i].setTextPosition( Position::center );
                    }
                }
            }

            // mouvement souris
            if (event.type == sf::Event::MouseMoved) {
                for (unsigned int i = 0; i < histList.size(); i++) {
                    histList[i].colorSwitch(histList[i].isOver(event.mouseMove.x, event.mouseMove.y));
                }
                if (backImg.isOver(event.mouseMove.x, event.mouseMove.y)) {
                    backImg.setTextures(backOver);
                } else {
                    backImg.setTextures(back);
                }
            }
            
        }

        window.clear(sf::Color{1, 38, 29});

        if (histStr.size() == 0) {
            // Si save.txt est vide
            writeList.draw(window);
        } else {
            // Si il y a des exos enregistrés
            for (unsigned int i = 0; i < histStr.size(); i++) {
                histList[i].draw(window);
                smileyNote[i].draw(window);
                timeList[i].draw(window);
            }
        }

        backImg.draw(window);

        window.display();
    }

    return 0;
}


int historyRecap(sf::RenderWindow &window, sf::Event &event, sf::RectangleShape &background, Exercice &r) {
    // Chargement des images
    sf::Texture f, t;
    sf::Image im1, im2;
    im1.loadFromFile("img/wrong.png");
    im2.loadFromFile("img/right.png");
    f.loadFromImage(im1);
    t.loadFromImage(im2);

    vector<Button> correction = {};
    vector<Image> correction_image = {};
    Button b = Button{0, 0, 0, 0};
    Image image;
    int y_percent = 35;

    if (r.getNbQuestions() == 10) {
        for (int i = 0; i < 5; i++) {
            Calcul c = r.getQuestionId(i);

            b = Button{toPercent(WINDOW_SIZE_X, 22), toPercent(WINDOW_SIZE_Y, y_percent), 0, 0, c.getStrReponseOp(), {0, 0, 0}, {255, 255, 255}};
            b.setFontSize(toPercent(WINDOW_SIZE_Y, 6));
            correction.push_back( b ); 

            if (c.estValide()) {
                image = Image{ toPercent(WINDOW_SIZE_X, 24)+b.getTextWidth(), toPercent(WINDOW_SIZE_Y, y_percent), toPercent(WINDOW_SIZE_Y, 6), toPercent(WINDOW_SIZE_Y, 6), t};
                image.setTextures(t);
                correction_image.push_back(image);
            } else {
                image = Image{ toPercent(WINDOW_SIZE_X, 24)+b.getTextWidth(), toPercent(WINDOW_SIZE_Y, y_percent), toPercent(WINDOW_SIZE_Y, 6), toPercent(WINDOW_SIZE_Y, 6), f};
                image.setTextures(f);
                correction_image.push_back(image);
                b = Button{toPercent(WINDOW_SIZE_X, 26)+b.getTextWidth() + toPercent(WINDOW_SIZE_Y, 6), toPercent(WINDOW_SIZE_Y, y_percent), 0, 0, to_string(c.getResultatOperation()), {0, 0, 0}, {255, 255, 255}};
                b.setFontSize(toPercent(WINDOW_SIZE_Y, 6));
                correction.push_back(b);
            }

            y_percent += 10;
        }
        y_percent = 35;
        for (int i = 5; i < 10; i++) {
            Calcul c = r.getQuestionId(i);

            b = Button{toPercent(WINDOW_SIZE_X, 60), toPercent(WINDOW_SIZE_Y, y_percent), 0, 0, c.getStrReponseOp(), {0, 0, 0}, {255, 255, 255}};
            b.setFontSize(toPercent(WINDOW_SIZE_Y, 6));
            correction.push_back( b );

            if (c.estValide()) {
                image = Image{ toPercent(WINDOW_SIZE_X, 62)+b.getTextWidth(), toPercent(WINDOW_SIZE_Y, y_percent), toPercent(WINDOW_SIZE_Y, 6), toPercent(WINDOW_SIZE_Y, 6), t};
                image.setTextures(t);
                correction_image.push_back(image);
            } else {
                image = Image{ toPercent(WINDOW_SIZE_X, 62)+b.getTextWidth(), toPercent(WINDOW_SIZE_Y, y_percent), toPercent(WINDOW_SIZE_Y, 6), toPercent(WINDOW_SIZE_Y, 6), f};
                image.setTextures(f);
                correction_image.push_back(image);
                b = Button{toPercent(WINDOW_SIZE_X, 64)+b.getTextWidth() + toPercent(WINDOW_SIZE_Y, 6), toPercent(WINDOW_SIZE_Y, y_percent), 0, 0, to_string(c.getResultatOperation()), {0, 0, 0}, {255, 255, 255}};
                b.setFontSize(toPercent(WINDOW_SIZE_Y, 6));
                correction.push_back(b);
            }

            y_percent += 10;
        }
    } else if (r.getNbQuestions() == 20) {
        int column = 10;
        int y_percent = 35;
        for (int i = 0; i < 20; i+=5) {
            for (int j = 0; j < 5; j++) {
                Calcul c = r.getQuestionId(i+j);
                b = Button{toPercent(WINDOW_SIZE_X, column), toPercent(WINDOW_SIZE_Y, y_percent), 0, 0, c.getStrReponseOp(), {0, 0, 0}, {255, 255, 255}};
                b.setFontSize(toPercent(WINDOW_SIZE_Y, 4));
                correction.push_back( b );

                if (c.estValide()) {
                    image = Image{ toPercent(WINDOW_SIZE_X, column+1)+b.getTextWidth(), toPercent(WINDOW_SIZE_Y, y_percent+1), toPercent(WINDOW_SIZE_Y, 3), toPercent(WINDOW_SIZE_Y, 3), t};
                    image.setTextures(t);
                    correction_image.push_back(image);
                } else {
                    image = Image{ toPercent(WINDOW_SIZE_X, column+1)+b.getTextWidth(), toPercent(WINDOW_SIZE_Y, y_percent+1), toPercent(WINDOW_SIZE_Y, 3), toPercent(WINDOW_SIZE_Y, 3), f};
                    image.setTextures(f);
                    correction_image.push_back(image);
                    b = Button{toPercent(WINDOW_SIZE_X, column+2)+b.getTextWidth() + toPercent(WINDOW_SIZE_Y, 3), toPercent(WINDOW_SIZE_Y, y_percent), 0, 0, to_string(c.getResultatOperation()), {0, 0, 0}, {255, 255, 255}};
                    b.setFontSize(toPercent(WINDOW_SIZE_Y, 4));
                    correction.push_back(b);
                }

                y_percent += 10;
            }
            column += 22;
            y_percent = 35;
        }
    }


    string noteText, timeText;
    // Affichage note de l'exercice
    noteText = "Ma note: " + to_string(r.getNbValideQuestions()) + '/' + to_string(r.getNbQuestions());

    Button note = Button(toPercent(WINDOW_SIZE_X, 35), toPercent(WINDOW_SIZE_Y, 8), toPercent(WINDOW_SIZE_X, 30), toPercent(WINDOW_SIZE_Y, 20), noteText, {200, 200, 200});
    note.setFontSize(toPercent(note.getRect().getGlobalBounds().height, 30));
    note.setTextPosition( note.getRect().getGlobalBounds().width/2 - note.getTextWidth()/2 , toPercent(note.getRect().getGlobalBounds().height, 20));
    note.getText().setLineSpacing(3);

    // Affichage temps -> ajout de 0 devan le nombre si < 10
    timeText = "Temps: ";
    if (r.getFinalTime()/60 < 10) {
        timeText += '0';
        timeText += to_string(r.getFinalTime()/60);
    } else {
        timeText += to_string(r.getFinalTime()/60);
    }
    timeText += ':';
    if (r.getFinalTime()%60 < 10) {
        timeText += '0';
        timeText += to_string(r.getFinalTime()%60);
    } else {
        timeText += to_string(r.getFinalTime()%60);
    }

    Button timeDisplay = Button(toPercent(WINDOW_SIZE_X, 35), note.getText().getPosition().y + toPercent(note.getRect().getSize().y, 50), toPercent(WINDOW_SIZE_X, 30), 0, timeText);
    timeDisplay.setFontSize(toPercent(note.getRect().getGlobalBounds().height, 20));
    timeDisplay.setTextPosition(Position::center);

    sf::Texture home, homeOver;
    home.loadFromFile("img/back_white.png");  homeOver.loadFromFile("img/back1_white.png");
    Image homeButton = Image(toPercent(WINDOW_SIZE_X, 28), toPercent(WINDOW_SIZE_Y, 14), toPercent(WINDOW_SIZE_Y, 9), toPercent(WINDOW_SIZE_Y, 9), home);

    while (true) {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                return 0;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (homeButton.isOver(event.mouseButton.x, event.mouseButton.y)) {
                    return 2;
                }
                
            }
            if (event.type == sf::Event::MouseMoved) {
                if (homeButton.isOver(event.mouseMove.x, event.mouseMove.y)) {
                    homeButton.setTextures(homeOver);
                } else {
                    homeButton.setTextures(home);
                }
                
            }
        }
        window.clear(sf::Color{1, 38, 29});

        note.draw(window);
        timeDisplay.draw(window);
        homeButton.draw(window);

        for (unsigned int i = 0; i < correction.size(); i++) {
            correction[i].draw(window);
        }

        for (unsigned int i = 0; i < correction_image.size(); i++) {
            correction_image[i].draw(window);
        }

        window.display();
    }
}
