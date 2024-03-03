#ifndef CALCUL_HPP
#define CALCUL_HPP

#include <iostream>
#include <random>
#include <time.h>
#include <vector>


using namespace std;

enum class Operation {addition, soustraction, division, multiplication};

class Calcul
{
private:
    int min, max;
    int num_a, num_b;
    Operation s;
    int resultat;

    int reponse;
    bool valide;

    /**
     * @brief calcule le résultat de l'opération
     * 
     * @param a le premier entier de l'opération
     * @param b le second entier de l'opération
     * @param s l'opérateur
     * @return int, le résultat de l'opération
     */
    int getResult(int &a, int &b, Operation &s);

    /**
     * @brief retourne un nombre pour le calcul
     * 
     * @param min le minimum possible
     * @param max le maximum possible
     * @return int l'entier aléatoire
     */
    int randomNumber(int min, int max);

    /**
     * @brief Get the Rand Operation object
     * 
     * @return Operation 
     */
    Operation getRandOperation(vector<bool> op);

public:
    /**
     * @brief Construct a new Calcul object
     * 
     * @param minimum 
     * @param maximum 
     */
    Calcul(int minimum, int maximum, vector<bool> operation);

    Calcul(int a, int o, int b, int res, int rep);

    Calcul() {}
    
    /**
     * @brief Get the Num A object
     * 
     * @return int 
     */
    int getNumA() const { return num_a; }
    
    /**
     * @brief Get the Num B object
     * 
     * @return int 
     */
    int getNumB() const { return num_b; }

    /**
     * @brief Get the Operator object
     * 
     * @return Operation 
     */
    Operation getOperator() const { return s; }

    /**
     * @brief Get the Resultat object
     *  
     * @return int 
     */
    int getResultatOperation() const {return resultat; }

    /**
     * @brief affichage en console
     * 
     */
    void cmdOutput() const;


    void cmdAnswertOutput() const;


    /**
     * @brief retourne vrai si le nombre est premier, faux sinon
     *        retourne vrai pour 1 (même si pas premier)
     * 
     * @param n le nombre
     * @return true 
     * @return false 
     */
    bool estPremier(int n) const;

    void setReponse(int answer);

    string getStrOperation() const;

    bool estValide() const {return valide;}

    int getReponse() const;

    string getStrReponseOp() const;
};


#endif