#include <iostream>

using namespace std;
int n;
int *baza, *liczba1, *liczba2;

void dodawanie() {
    for (int i = 0; i < n; i++) {
        liczba1[i] = (liczba1[i] + liczba2[i]) % baza[i];
    }
}

void odejmowanie() {
    for (int i = 0; i < n; i++) {
        int result = (liczba1[i] - liczba2[i]);
        if (result < 0) result += baza[i];
        liczba1[i] = result % baza[i];
    }
}

void mnozenie() {
    for (int i = 0; i < n; i++) {
        liczba1[i] = (liczba1[i] * liczba2[i]) % baza[i];
    }
}

int euklides(int liczba, int bazOdwr) {
    int mulInv, b;
    int bo = bazOdwr;
    int y = 0;
    int odwrotnosc = 1;

    if (bazOdwr == 1) {
        return 0;
    }
    while (liczba > 1) {
        mulInv = liczba / bazOdwr;
        b = bazOdwr;

        bazOdwr = liczba % bazOdwr;
        liczba = b;
        b = y;
        y = odwrotnosc - mulInv * y;
        odwrotnosc = b;
    }
    if (odwrotnosc < 0)
        odwrotnosc += bo;

    return odwrotnosc;
}
/*
 
 */
void potegowanie(int argument) {
    for (int i = 0; i < n; i++) {
        int l2 = liczba2[i];
        int l1 = liczba1[i];
        int b = baza[i];

        if (l1 == 1 || l1 == 0) {
            continue; // 0^n =0 , 1^n =1
        }
        // l2 jest kopia l1 (main) i ono nigdy sie tutaj nie zmienia
        //argument -1 poniewaz, zaczynam mnozenie od liczba^1 a nie liczba ^0
        
        for (int j = 0; j < argument - 1 ; j++) {
            l1 = (l1 * l2) % b;
        }

        liczba1[i] = l1;
    }
}
// dzielenie a /b
void dzielenie() {
    for (int i = 0; i < n; i++) {
        liczba1[i] = (liczba1[i] * euklides(liczba2[i], baza[i])) % baza[i];
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    int liczbaOperacji;
    cin >> n >> liczbaOperacji;

    baza = new int[n];
    liczba1 = new int[n];
    liczba2 = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> baza[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> liczba1[i];
    }
    for (int j = 0; j < liczbaOperacji; j++) {
        char znak;
        int argument;
        cin >> znak >> argument;
        for (int i = 0; i < n; i++) {
            liczba2[i] = argument % baza[i];
        }
        switch (znak) {
            case '+':
                dodawanie();
                break;
            case '-':
                odejmowanie();
                break;
            case '*':
                mnozenie();
                break;
            case '^':
                for (int i = 0; i < n; ++i) liczba2[i] = liczba1[i];
                potegowanie(argument);
                break;
            case '/':
                dzielenie();
                break;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << liczba1[i] << " ";
    }
    return 0;
}
