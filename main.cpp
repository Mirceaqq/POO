#include <iostream>
#include <string>

using namespace std;

class Vehicul {
private:
    string marca;
    string model;
    int anFabricatie;
    int kilometriParcursi;

public:
    Vehicul() {
        marca = "N/A";
        model = "Model-Standard";
        anFabricatie = 2024;
        kilometriParcursi = 0;
    }

    Vehicul(string m, string mod, int an, int km) {
        marca = m;
        model = mod;
        anFabricatie = an;
        kilometriParcursi = km;
    }

    Vehicul(string m, string mod) {
        marca = m;
        model = mod;
        anFabricatie = 2024;
        kilometriParcursi = 0;
    }

    ~Vehicul() {
        cout << ">>> Scoatere din evidenta: " << marca << " " << model << "\n";
    }

    void adaugaKilometri(int km) {
        if (km > 0)
            kilometriParcursi += km;
    }

    void afisare() {
        cout << marca << " | " << model
             << " | Productie: " << anFabricatie
             << " | Odometru: " << kilometriParcursi << " km\n";
    }

    string getIdentitate() {
        return marca + " [" + model + "]";
    }
};

int main() {
    Vehicul parc[3] = {
        Vehicul("Mercedes", "G-Class", 2021, 45000),
        Vehicul("BMW", "M5", 2022, 30000),
        Vehicul("Audi", "RS6", 2023, 20000)
    };

    int unitate = 0, comanda, km;

    cout << "--- SISTEM GESTIUNE PARC AUTO ---\n";
    cout << "Identificati unitatea (0, 1, 2): ";
    cin >> unitate;

    if (unitate < 0 || unitate > 2)
        unitate = 0;

    do {
        cout << "\nUNITATE ACTIVA: " << parc[unitate].getIdentitate() << "\n";
        cout << ">> 1. Diagnostic (Afisare date)\n";
        cout << ">> 2. Actualizare Odometru (+km)\n";
        cout << ">> 3. Selectare alta unitate\n";
        cout << ">> 0. Deconectare\n";
        cout << "Prompt: ";

        cin >> comanda;

        switch (comanda) {
        case 1:
            parc[unitate].afisare();
            break;

        case 2:
            cout << "Valoare km parcursi: ";
            cin >> km;
            parc[unitate].adaugaKilometri(km);
            break;

        case 3:
            cout << "ID Unitate noua (0, 1, 2): ";
            cin >> unitate;
            if (unitate < 0 || unitate > 2)
                unitate = 0;
            break;

        case 0:
            cout << "Sistemul se inchide...\n";
            break;
        }
    } while (comanda != 0);

    return 0;
}
