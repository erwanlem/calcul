#include "file.hpp"


string FILENAME = "save.txt";

using namespace std;

void writeResult(Exercice e) {
    ofstream file;
    file.open(FILENAME, ios::app);
    file << e.getTime() << '/' << e.getNbValideQuestions() << ":" << e.getNbQuestions() << "?";
    for (int i = 0; i < e.getNbQuestions(); i++) {
        Calcul c = e.getQuestionId(i);
        file << c.getNumA() << ":" << int(c.getOperator()) << ":" << c.getNumB() << ":" << c.getResultatOperation() << ":" << c.getReponse() <<  ";";
    }
    file << "\n";
    file.close();
}

void clearFile() {
    ofstream file;
    file.open(FILENAME, ios::trunc);
    file.close();
}


void limitLines(int limit) {
    vector<string> txt = readLines();

    if (txt.size() > limit) {
        ofstream file;
        file.open(FILENAME);
    
        for (unsigned int i = txt.size() - limit; i < txt.size(); i++) {
            file << txt[i] << "\n";
        }
    
        file.close();
    }
}


vector<string> readLines() {
    string line;
    vector<string> lines = {};
    ifstream file;
    file.open(FILENAME);
    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }

    return lines;
}


string readLastScore(vector<string> data) {
    string lastData = data[data.size()-1];
    string scoreA = "", scoreB = "";
    unsigned int i = 0;
    while (lastData[i] != '/') {
        i++;
    }
    i++;
    
    while (lastData[i] != ':') {
        scoreA.push_back(lastData[i]);
        i++;
        if (i > 40 || i >= lastData.size()) {
            throw runtime_error("Fichier \"" + FILENAME + "\" corrompu");
            return "";
        }
    }
    i++;
    while (lastData[i] != '?') {
        scoreB.push_back(lastData[i]);
        i++;
        if (i > 40 || i >= lastData.size()) {
            throw runtime_error("Fichier \"" + FILENAME + "\" corrompu");
            return "";
        }
    }

    return scoreA + "/" + scoreB;
}


Exercice readExercice(vector<string> data, int n) {
    string d = data[n];
    string taille;
    string time;
    unsigned int i = 0;

    while (d[i] != '/') {
        time += d[i];
        i++;
        if (i > 20) {
            throw runtime_error("Ficher \"" + FILENAME + "\" corompu");
        }
    }
    i++;

    while (d[i] != ':') {
        i++;
        if (i > 40) {
            throw runtime_error("Ficher \"" + FILENAME + "\" corompu");
        }
    }
    i++;
    while (d[i] != '?') {
        taille += d[i];
        i++;
        if (i > 40) {
            throw runtime_error("Ficher \"" + FILENAME + "\" corompu");
        }
    }
    i++;

    Exercice e = Exercice(stoi(taille));
    e.setTime(stoi(time));

    int q = 0;
    string a;
    while (i < d.size()) {
        vector<int> c = {};
        a = "";
        while (d[i] != ';'  && i < d.size()) {
            if (d[i] == ':') {
                c.push_back(stoi(a));
                a = "";
            } else {
                a += d[i];
            }
            i++;
        }
        c.push_back(stoi(a));

        i++;
        if (c.size() != 5) {
            cout << "Taille calcul: " << c.size() << endl;
            throw runtime_error("Ficher \"" + FILENAME + "\" corompu, taille du calcul");
        } else {
            e.setCalcul(Calcul{c[0], c[1], c[2], c[3], c[4]}, q);
            q++;
        }
    }  

    return e;
}