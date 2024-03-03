#ifndef EXERCICE_HPP
#define EXERCICE_HPP

#include <iostream>
#include <vector>
#include "calcul.hpp"
#include <SFML/System/Clock.hpp>

class Exercice
{
private:
    vector<Calcul*> calc_list;
    int nombreQuestions, reponsesValides, activQuestion;
    bool activ = false;
    sf::Clock tmps; // temps de l'exo
    sf::Time elapsed; // temps de l'exo
    int intElapsed;
public:
    /**
     * @brief Construct a new Exercice object
     * 
     * @param taille
     */
    Exercice(int taille, vector<bool> operations, int maxiInt);

    /**
     * @brief Construct a new Exercice object
     * 
     * @param taille
     */
    Exercice(int taille);

    
    /**
     * @brief libere la mémoire utilisé par les calculs
     * 
     */
    void freeExo();

    /**
     * @brief récupère la réponse et la stock dans l'objet calcul correspondant
     * 
     * @param answer un entier, la réponse entrée
     * @return le calcul suivant  en chaine de caractère
     */
    string setAnswer(int answer);

    /**
     * @brief définit la  réponse comme non valide si l'élément entré n'est pas un entier (résultat vide)
     * 
     * @param answer un booleen indiquant une entrée non valide
     * @return le calcul suivant  en chaine de caractère
     */
    string setAnswer(bool answer);

    /**
     * @brief retourne le calcul sous forme de chaine de caractères
     * 
     * @return string le calcul
     */
    string getQuestion();

    /**
     * @brief vérifie si le calcul est déjà présent dans l'exercice
     * 
     * @param c le calcul à comparer
     * @return true 
     * @return false 
     */
    bool doublons(Calcul c);
    
    /**
     * @brief retourne la question pour un id donné
     * 
     * @return Calcul 
     */
    Calcul getQuestionId(int id) const;

    /**
     * @brief Set the Begin of the exercise
     * 
     */
    void switchActiv();

    /**
     * @brief retourne true si l'exercice est commencé, false sinon
     * 
     * @return true 
     * @return false 
     */
    bool isActiv() {return activ;}

    /**
     * @brief modifie le calcul à une position donné dans le vecteur
     * 
     * @param c le calcul à ajouter
     * @param pos la position dans l'ecercice (0 : taille-1)
     */
    void setCalcul(Calcul c, int pos);

    /**
     * @brief affichage des calculs en ligne de commande
     * 
     */
    void cmdResultOutput() const;

    /**
     * @brief Get the Nb Questions object
     * 
     * @return int la taille de l'exercice
     */
    int getNbQuestions() const {return nombreQuestions;}

    /**
     * @brief Get the Nb Valide Questions object
     * 
     * @return int le nombre de bonnes réponses dans l'exercice
     */
    int getNbValideQuestions();

    /**
     * @brief Get the Activ Question object
     * 
     * @return int le numéro de la question courante
     */
    int getActivQuestion() const {return activQuestion;}

    int getTime() ;

    void setTime(int time) {intElapsed = time;}

    int getFinalTime() const;
};


#endif