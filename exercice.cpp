#include "exercice.hpp"
#include "file.hpp"
#include <SFML/System/Clock.hpp>

bool operator==(const Calcul &a, const Calcul &b) {
    if (a.getNumA() == b.getNumA() && a.getNumB() == b.getNumB() && a.getOperator() == b.getOperator()) {
        return true;
    } else {
        return false;
    }
}

Exercice::Exercice(int taille, vector<bool> operations, int maxiInt)
{
    calc_list = {};
    tmps.restart();
    for (int i = 0; i < taille; i++ ) {
        Calcul *c = (Calcul*)malloc(sizeof(Calcul));
        *c = Calcul(1, maxiInt, operations);
        while (doublons(*c)) {
            *c = Calcul(1, maxiInt, operations);
        }
        calc_list.push_back(c);
    }
    nombreQuestions = taille;
    activQuestion = 0;
}

Exercice::Exercice(int taille) 
{
    calc_list = {};
    tmps.restart();
    for (int i = 0; i < taille; i++ ) {
        Calcul *c = (Calcul*)malloc(sizeof(Calcul));
        *c = Calcul();
        calc_list.push_back(c);
    }
    nombreQuestions = taille;
    activQuestion = 0;
}

void Exercice::freeExo() {
    for (unsigned int i = 0; i < calc_list.size(); i++) {
        free(calc_list[i]);
    }
}

string Exercice::setAnswer(int answer) {
    calc_list[activQuestion-1]->setReponse(answer);
    return getQuestion();
}

string Exercice::setAnswer(bool answer) {
    calc_list[activQuestion-1]->setReponse(-1);
    return getQuestion();
}

string Exercice::getQuestion() {
    if (activQuestion < nombreQuestions) {
        tmps.restart();
        string c = calc_list[activQuestion]->getStrOperation();
        activQuestion++;
        return c;
    } else {
        elapsed = tmps.getElapsedTime();
        intElapsed = elapsed.asSeconds();
        writeResult(*this);
        limitLines();
        return "end";
    }
}

// Verif doublons
bool Exercice::doublons(Calcul c) {
    for (unsigned int i = 0; i < calc_list.size(); i++){
        if (*(calc_list[i]) == c) {
            return true;
        }
    }
    return false;
}


void Exercice::cmdResultOutput() const {
    for (int i = 0; i < nombreQuestions; i++) {
        calc_list[i]->cmdOutput();
        calc_list[i]->cmdAnswertOutput();
    }
}


int Exercice::getNbValideQuestions() {
    reponsesValides = 0;
    for (int i = 0; i < getNbQuestions(); i++) {
        if (calc_list[i]->estValide()) {
            reponsesValides++;
        }
    }
    return reponsesValides;
}


Calcul Exercice::getQuestionId(int id) const {
    if (id >= 0 && id < nombreQuestions){
        return *calc_list[id];
    } else {
        throw runtime_error("Identifiant non valide");
    }
}

int Exercice::getTime() {
    elapsed = tmps.getElapsedTime();
    intElapsed = elapsed.asSeconds();
    return intElapsed;
}

int Exercice::getFinalTime() const {
    return intElapsed;
}

void Exercice::setCalcul(Calcul c, int pos) {
    *calc_list[pos] = c;
}

void Exercice::switchActiv() {
    activ = !activ;
    tmps.restart();
}