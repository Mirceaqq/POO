#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Bilet {
protected:
    string numar;
    int start, sf; // minute

public:
    Bilet(string n, int s, int f) {
        numar = n;
        start = s;
        sf = f;
    }

    float durata() {
        return (sf - start) / 60.0;
    }

    virtual float cost() = 0;
    virtual void afiseaza() = 0;

    virtual ~Bilet() {} 
};


// Standard
class BiletStandard : public Bilet {
public:
    BiletStandard(string n, int s, int f) : Bilet(n, s, f) {}

    float cost() { return durata() * 2; }

    void afiseaza() {
        cout << "Tip: Standard"
             << " | Numar: " << numar
             << " | Durata: " << durata() << " ore"
             << " | Cost: " << cost() << " lei\n";
    }
};


// Abonament
class Abonament : public Bilet {
public:
    Abonament(string n, int s, int f) : Bilet(n, s, f) {}

    float cost() { return 0; }

    void afiseaza() {
        cout << "Tip: Abonament"
             << " | Numar: " << numar
             << " | Durata: " << durata() << " ore"
             << " | Cost: " << cost() << " lei\n";
    }
};


// Reducere
class BiletReducere : public Bilet {
public:
    BiletReducere(string n, int s, int f) : Bilet(n, s, f) {}

    float cost() { return durata() * 1; }

    void afiseaza() {
        cout << "Tip: Reducere"
             << " | Numar: " << numar
             << " | Durata: " << durata() << " ore"
             << " | Cost: " << cost() << " lei\n";
    }
};


// Turistic
class BiletTuristic : public Bilet {
public:
    BiletTuristic(string n, int s, int f) : Bilet(n, s, f) {}

    float cost() { return 10; }

    void afiseaza() {
        cout << "Tip: Turistic"
             << " | Numar: " << numar
             << " | Durata: " << durata() << " ore"
             << " | Cost: " << cost() << " lei\n";
    }
};


int main() {
    ifstream f("bilete.txt");

    string tip, numar, oraStart, oraSf;

    Bilet* b[100]; 
    int n = 0;

    while (f >> tip >> numar >> oraStart >> oraSf) {
        int start = ((oraStart[0]-'0')*10 + (oraStart[1]-'0')) * 60 +
                    ((oraStart[3]-'0')*10 + (oraStart[4]-'0'));
        int sf = ((oraSf[0]-'0')*10 + (oraSf[1]-'0')) * 60 +
                 ((oraSf[3]-'0')*10 + (oraSf[4]-'0'));

        if (tip == "BiletStandard")
            b[n++] = new BiletStandard(numar, start, sf);
        else if (tip == "Abonament")
            b[n++] = new Abonament(numar, start, sf);
        else if (tip == "BiletReducere")
            b[n++] = new BiletReducere(numar, start, sf);
        else if (tip == "BiletTuristic")
            b[n++] = new BiletTuristic(numar, start, sf);
    }

    for (int i = 0; i < n; i++)
        b[i]->afiseaza();

    for (int i = 0; i < n; i++)
        delete b[i];

    return 0;
}
