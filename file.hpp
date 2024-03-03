#ifndef FILE_HPP
#define FILE_HPP

#include "exercice.hpp"
#include "calcul.hpp"
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>


/**
 * @brief écriture du résultat d'un exercice
 * 
 * @param e l'exercice à écrire
 */
void writeResult(Exercice e);


/**
 * @brief vide le fichier FILENAME
 * 
 */
void clearFile();


/**
 * @brief limitation du nombre d'exerices écrits dans le fichier de stockage
 * 
 * @param limit la limite de ligne - par défaut définie à 15
 */
void limitLines(int limit = 15);


/**
 * @brief récupère les exercices contenus dans FILENAME
 * 
 * @return vector<string> un vecteur d'exercices en string
 */
vector<string> readLines();


/**
 * @brief récupère le dernier score obtenu
 * 
 * @param data le vecteur de string contenant tous les exercices
 * @return string le score au dernier exercice enregistré
 */
string readLastScore(vector<string> data);


/**
 * @brief convertit une chaîne de caractère en objet de type Exercice
 * 
 * @param data le vecteur contenant la liste des exercices en chaine de caractère
 * @param n l'indice de l'exercice à convertir
 * @return Exercice l'exercice convertit
 */
Exercice readExercice(vector<string> data, int n);



#endif