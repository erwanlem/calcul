#include "calcul.hpp"

using namespace std;


bool operator==(const vector<bool> &a, const vector<bool> &b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (unsigned int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

Calcul::Calcul(int minimum, int maximum, vector<bool> operation)
{
    min = minimum;
    max = maximum;

    s = getRandOperation({operation[0], operation[1], operation[2], operation[3]});
    num_a = randomNumber(minimum, maximum);

    // pour les nombres non premiers on cherche des diviseurs autres que 1 et le nombre lui-même 
    if (s == Operation::division) {
        bool p = estPremier(num_a);
        int n = randomNumber(minimum, num_a);
        if (p) {
            while (num_a % n != 0) {
                n = randomNumber(minimum, num_a);
            }
        } else {
            while (num_a % n != 0 || n == 1 || n == num_a) {
                n = randomNumber(minimum, num_a);
            }
        }
        num_b = n;
    } else if (s == Operation::soustraction) {
        num_b = randomNumber(minimum, num_a);
    } else {
        num_b = randomNumber(minimum, maximum);
    }
    
    resultat = getResult(num_a, num_b, s);

    reponse = -1;
    valide = false;
}

Calcul::Calcul(int a, int o, int b, int res, int rep) {
    min = 0, max = 0;
    num_a = a, num_b = b;
    resultat = res;
    reponse = rep;
    s = Operation(o);
    valide = resultat == reponse;
}


int Calcul::randomNumber(int min, int max) {
    return min + (rand() % ((max - min) + 1));
}

int Calcul::getResult(int &a, int &b, Operation &s) {
    if (s == Operation::addition) {
        return a + b;
    } else if (s == Operation::soustraction) {
        return a - b;
    } else if (s == Operation::division) {
        return a / b;
    } else if (s == Operation::multiplication) {
        return a * b;
    } else {
        throw runtime_error("Erreur calcul, fonction getResult()");
        return 0;
    }
}


Operation Calcul::getRandOperation(vector<bool> op) {
    vector<bool> err = {false, false, false, false};
    if (op == err) {
        throw invalid_argument("Fonction getRandOperation() - Tableau non valide");
    }
    int r = rand() % 4;
    while (true)
    {
        if (op[r]) {
            switch (r) {
            case 0:
                return Operation::addition;
            case 1:
                return Operation::soustraction;
            case 2:
                return Operation::multiplication;
            case 3:
                return Operation::division;
            default:
                return Operation::addition;
            }
        }
        r = rand() % 4;
    }
}


void Calcul::cmdOutput() const {
    cout << num_a << " ";

    switch (s)
    {
    case Operation::addition:
        cout << "+";
        break;
    case Operation::soustraction:
        cout << "-";
        break;
    case Operation::division:
        cout << "/";
        break;
    case Operation::multiplication:
        cout << "*";
        break;
    default:
        cout << "?";
        break;
    }


    cout << " " << num_b << " = " << resultat << endl;
}

 void Calcul::cmdAnswertOutput() const {
    cout << reponse << " " << valide << " **" << endl;
 }


bool Calcul::estPremier(int n) const {
    if (n == 1) {
        return true;
    }
    int d = 2;
    while (d < n) {
        if (n % d == 0) {
            return false;
        }
        d++;
    }
    return true;
}


void Calcul::setReponse(int answer) {
    reponse = answer;
    if (reponse == resultat) {
        valide = true;
    } else {
        valide = false;
    }
}

int Calcul::getReponse() const {
    return reponse;
}


string Calcul::getStrOperation() const {
    string a = to_string(num_a);
    string b = to_string(num_b);
    string op;
    switch (s)
    {
    case Operation::addition:
        op = " + ";
        break;
    case Operation::soustraction:
        op = " - ";
        break;
    case Operation::multiplication:
        op = " x ";
        break;
    case Operation::division:
        op = " / ";
        break;
    default:
        op = " ? ";
        break;
    }
    string output = a + op + b + " =";
    return output;
}

string Calcul::getStrReponseOp() const {
    string a = to_string(num_a);
    string b = to_string(num_b);
    string rep;
    string op;

    if (reponse == -1) {
        rep = "?";
    } else {
        rep = to_string(reponse);
    }
    
    switch (s)
    {
    case Operation::addition:
        op = " + ";
        break;
    case Operation::soustraction:
        op = " - ";
        break;
    case Operation::multiplication:
        op = " x ";
        break;
    case Operation::division:
        op = " / ";
        break;
    default:
        op = " ? ";
        break;
    }
    string output = a + op + b + " = " + rep;
    return output;
}