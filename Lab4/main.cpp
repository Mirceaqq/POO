#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class IBilet {
public:
    virtual int calculeazaDurata() const = 0;
    virtual double calculeazaCost() const = 0;
    virtual void afiseaza() const = 0;
    virtual ~IBilet() {}
};

class Bilet : public IBilet {
protected:
    string numarBilet;
    string oraStart;
    string oraSfarsit;

public:
    Bilet(string numar, string start, string sfarsit) {
        numarBilet = numar;
        oraStart = start;
        oraSfarsit = sfarsit;
    }

    int oraInMinute(string ora) const {
        int ore = (ora[0] - '0') * 10 + (ora[1] - '0');
        int minute = (ora[3] - '0') * 10 + (ora[4] - '0');
        return ore * 60 + minute;
    }

    int calculeazaDurata() const override {
        int startMin = oraInMinute(oraStart);
        int sfarsitMin = oraInMinute(oraSfarsit);
        return sfarsitMin - startMin;
    }

    void afiseaza() const override {
        cout << numarBilet << " " << oraStart << " " << oraSfarsit << " " << calculeazaDurata() << " minute " << calculeazaCost() << " lei" << endl;
    }

    string getNrBilet() const {
        return numarBilet;
    }
};

class BiletStandard : public Bilet {
private:
    double costPerOra;

public:
    BiletStandard(string numar, string start, string sfarsit)
        : Bilet(numar, start, sfarsit) {
        costPerOra = 2;
    }

    double calculeazaCost() const override {
        int durataMinute = calculeazaDurata();
        int oreRotunjite = (durataMinute + 59) / 60;
        return oreRotunjite * costPerOra;
    }

    void afiseaza() const override {
        cout << "BiletStandard ";
        Bilet::afiseaza();
    }
};

class Abonament : public Bilet {
private:
    double costLuna;
    double costExtraOra;

public:
    Abonament(string numar, string start, string sfarsit)
        : Bilet(numar, start, sfarsit) {
        costLuna = 50;
        costExtraOra = 2;
    }

    double calculeazaCost() const override {
        int durataMinute = calculeazaDurata();

        if (durataMinute > 43200) {
            double oreExtra = (durataMinute - 43200) / 60.0;
            return costLuna + oreExtra * costExtraOra;
        }

        return costLuna;
    }

    void afiseaza() const override {
        cout << "Abonament ";
        Bilet::afiseaza();
    }
};

class BiletReducere : public Bilet {
private:
    double costRedus;

public:
    BiletReducere(string numar, string start, string sfarsit)
        : Bilet(numar, start, sfarsit) {
        costRedus = 1;
    }

    double calculeazaCost() const override {
        int durataMinute = calculeazaDurata();
        int oreRotunjite = (durataMinute + 59) / 60;
        return oreRotunjite * costRedus;
    }

    void afiseaza() const override {
        cout << "BiletReducere ";
        Bilet::afiseaza();
    }
};

vector<Bilet*> citestedinFisier(string numeFisier) {
    vector<Bilet*> bilete;

    ifstream fisier(numeFisier);

    if (!fisier.is_open()) {
        cout << "EROARE: Nu s-a putut deschide fisierul " << numeFisier << endl;
        return bilete;
    }

    string tipBilet, numarBilet, oraStart, oraSfarsit;

    while (fisier >> tipBilet >> numarBilet >> oraStart >> oraSfarsit) {
        if (tipBilet == "BiletStandard") {
            bilete.push_back(new BiletStandard(numarBilet, oraStart, oraSfarsit));
        }
        else if (tipBilet == "Abonament") {
            bilete.push_back(new Abonament(numarBilet, oraStart, oraSfarsit));
        }
        else if (tipBilet == "BiletReducere") {
            bilete.push_back(new BiletReducere(numarBilet, oraStart, oraSfarsit));
        }
        else {
            cout << "Tip bilet necunoscut: " << tipBilet << endl;
        }
    }

    fisier.close();
    return bilete;
}

int main() {
    cout << "  SISTEM GESTIONARE BILETE TRANSPORT " << endl;
    cout << endl;

    vector<Bilet*> bilete = citestedinFisier("bilete.txt");

    if (bilete.empty()) {
        cout << "Nu s-au gasit bilete in fisier!" << endl;
        return 1;
    }

    cout << "S-au incarcat " << bilete.size() << " bilete." << endl;
    cout << endl;

    for (int i = 0; i < bilete.size(); i++) {
        cout << "--- Bilet #" << (i + 1) << " ---" << endl;
        bilete[i]->afiseaza();
        cout << endl;
    }

    for (int i = 0; i < bilete.size(); i++) {
        delete bilete[i];
    }
    bilete.clear();

    return 0;
}