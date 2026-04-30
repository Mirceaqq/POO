#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Mesaj {
public:
    int idExpeditor;
    string text;

    Mesaj(int id, string t) {
        idExpeditor = id;
        text = t;
    }
};

class Conversatie {
public:
    int idUtilizator;
    vector<Mesaj> mesaje;

    Conversatie(int id) {
        idUtilizator = id;
    }

    void adaugaMesaj(int idExpeditor, string text) {
        Mesaj m(idExpeditor, text);
        mesaje.push_back(m);
    }

    void afiseaza() {
        for (int i = 0; i < mesaje.size(); i++) {
            cout << "User " << mesaje[i].idExpeditor << ": "
                 << mesaje[i].text << endl;
        }
    }
};

class Utilizator {
public:
    int id;
    string nume;
    vector<Conversatie> conversatii;

    Utilizator(int i, string n) {
        id = i;
        nume = n;
    }

    int cautaConversatie(int idDest) {
        for (int i = 0; i < conversatii.size(); i++) {
            if (conversatii[i].idUtilizator == idDest)
                return i;
        }
        return -1;
    }

    void creareConversatie(int idDest) {
        if (cautaConversatie(idDest) == -1) {
            Conversatie c(idDest);
            conversatii.push_back(c);
        }
    }

    void adaugaMesaj(int idDest, string mesaj) {
        int poz = cautaConversatie(idDest);

        if (poz == -1) {
            creareConversatie(idDest);
            poz = conversatii.size() - 1;
        }

        conversatii[poz].adaugaMesaj(id, mesaj);
    }

    void vizualizeazaConversatie(int idDest) {
        int poz = cautaConversatie(idDest);

        if (poz == -1) {
            cout << "Nu exista conversatie!\n";
            return;
        }

        conversatii[poz].afiseaza();
    }
};

vector<Utilizator> utilizatori;
Utilizator* utilizatorCurent = NULL;

int cautaUtilizator(int id) {
    for (int i = 0; i < utilizatori.size(); i++) {
        if (utilizatori[i].id == id)
            return i;
    }
    return -1;
}

void salveaza() {
    ofstream f("utilizatori.txt");

    for (int i = 0; i < utilizatori.size(); i++) {
        f << utilizatori[i].id << " " << utilizatori[i].nume << endl;
    }

    f.close();
}

void incarca() {
    ifstream f("utilizatori.txt");

    int id;
    string nume;

    while (f >> id >> nume) {
        Utilizator u(id, nume);
        utilizatori.push_back(u);
    }

    f.close();
}

void inregistrare() {
    int id;
    string nume;

    cout << "ID: ";
    cin >> id;

    if (cautaUtilizator(id) != -1) {
        cout << "ID deja exista!\n";
        return;
    }

    cout << "Nume: ";
    cin >> nume;

    Utilizator u(id, nume);
    utilizatori.push_back(u);

    salveaza();
}

void login() {
    int id;
    cout << "ID: ";
    cin >> id;

    int poz = cautaUtilizator(id);

    if (poz == -1) {
        cout << "Utilizator inexistent!\n";
        return;
    }

    utilizatorCurent = &utilizatori[poz];
    cout << "Logat cu succes!\n";
}

void trimiteMesaj() {
    if (utilizatorCurent == NULL) {
        cout << "Nu esti logat!\n";
        return;
    }

    int idDest;
    string mesaj;

    cout << "ID destinatar: ";
    cin >> idDest;

    if (cautaUtilizator(idDest) == -1) {
        cout << "Utilizator nu exista!\n";
        return;
    }

    cout << "Mesaj: ";
    cin.ignore();
    getline(cin, mesaj);

    if (mesaj == "") {
        cout << "Mesaj gol!\n";
        return;
    }

    utilizatorCurent->adaugaMesaj(idDest, mesaj);

    cout << "Mesaj trimis!\n";
}

void vizualizare() {
    if (utilizatorCurent == NULL) {
        cout << "Nu esti logat!\n";
        return;
    }

    int idDest;
    cout << "ID destinatar: ";
    cin >> idDest;

    utilizatorCurent->vizualizeazaConversatie(idDest);
}

void stergeCont() {
    if (utilizatorCurent == NULL) {
        cout << "Nu esti logat!\n";
        return;
    }

    int id = utilizatorCurent->id;

    for (int i = 0; i < utilizatori.size(); i++) {
        if (utilizatori[i].id == id) {
            utilizatori.erase(utilizatori.begin() + i);
            break;
        }
    }

    utilizatorCurent = NULL;
    salveaza();

    cout << "Cont sters!\n";
}

int main() {
    incarca();

    int opt;

    do {
        cout << "\n1.Inregistrare\n2.Login\n3.Trimite mesaj\n4.Vizualizare\n5.Sterge cont\n0.Iesire\n";
        cin >> opt;

        if (opt == 1) inregistrare();
        else if (opt == 2) login();
        else if (opt == 3) trimiteMesaj();
        else if (opt == 4) vizualizare();
        else if (opt == 5) stergeCont();

    } while (opt != 0);

    return 0;
}