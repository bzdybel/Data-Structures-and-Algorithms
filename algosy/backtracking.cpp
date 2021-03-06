include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;
string napis1;
string napis2;
string napis3;

int r1, r2, r3, r4;

bool rekplus(int tab[26], bool free_value[10], int carry, int poz) {

    for (int i = poz; i < r4; i++) {
//----------------------------------------------/
        int w1 = -1;
        int w2 = -1;
        int w3 = -1;
        if (i < r1) {
            w1 = tab[napis1[i] - 'A'];//mapa[napis1[i]];
            if (w1 == -1) { // jesli mam nieprzypisyan¹ wartosc do litery
                bool ret1 = false;
                for (int j = 0; j < 10; j++) {
                    //szukam wolnej wartosci
                    if (free_value[j] == true) {
                        bool free_value_c[10];
                        for (int k = 0; k <
                                        10; k++) { //robie kopie obecnej tablicy, zeby moc wstawic informacje o tym ze zajelismy jedna wartosc
                            free_value_c[k] = free_value[k];
                        }

                        int tab_c[26];//
                        //kopia tablicy;
                        for (int l = 0; l < 26; l++) {
                            tab_c[l] = tab[l];
                        }
                        free_value_c[j] = false; // zaklepuje wartosc ktora znalazlem
                        tab_c[napis1[i] - 'A'] = j;  // map_c[napis1[i]] = j; //podstawiam wartosc pod litere

                        if (rekplus(tab_c, free_value_c, carry, i) == true) {
                            ret1 = true;
                        }
                    }
                }
                if (ret1 == false) {
                    return false;
                }
            }
        } else {
            w1 = 0;
        }
        //-/////////////////////////////////////////
        if (i < r2) {
            w2 = tab[napis2[i] - 'A'];//mapa[napis2[i]];
            if (w2 == -1) {
                bool ret2 = false;
                for (int j = 0; j < 10; j++) {
                    if (free_value[j] == true) {

                        bool free_value_c1[10];
                        for (int k = 0; k < 10; k++) {
                            free_value_c1[k] = free_value[k];
                        }
                        int tab1_c[26];//koppia tablicy jest koniecna zeby pamietac poprzedni stan
                        //kopia tablicy;
                        for (int l = 0; l < 26; l++) {
                            tab1_c[l] = tab[l];
                        }
                        free_value_c1[j] = false;
                        tab1_c[napis2[i] - 'A'] = j;
                        if (rekplus(tab1_c, free_value_c1, carry, i) == true) {
                            ret2 = true;
                        }
                    }
                }
                if (ret2 == false) {
                    return false;
                }
            }
        } else {
            w2 = 0;
        }
        //------------------------/
        if (i < r3) {
            w3 = tab[napis3[i] - 'A'];//mapa[napis3[i]];
            if (w3 == -1) {
                bool ret3 = false;
                for (int j = 0; j < 10; j++) {
                    if (free_value[j] == true) {

                        bool free_value_c2[10];
                        for (int k = 0; k < 10; k++) {
                            free_value_c2[k] = free_value[k];
                        }
                        free_value_c2[j] = false;

                        int tab2_c[26];//
                        //kopia tablicy;
                        for (int l = 0; l < 26; l++) {
                            tab2_c[l] = tab[l];
                        }
                        tab2_c[napis3[i] - 'A'] = j;
                        if (rekplus(tab2_c, free_value_c2, carry, i) == true) {
                            ret3 = true;
                        }
                    }
                }
                if (ret3 == false)
                    return false;
            }
        } else {
            w3 = 0;
        }
//przeniesienie

        if (w3 != (w1 + w2 + carry) % 10) {
            return false;
        }
        //warunek na pierwszy test litera P byla = 0 i test sie wypierdziela³
        if ( i== (r4-1) && w3 == 0){
            return false;
        }
        carry = (w1 + w2 + carry) / 10;
    }
    //?
    //8
    //8
    //-
    //06 
    if (carry != 0) {
        return false;
    }
    for (int i = 0; i < r1; i++) {
        cout << tab[napis1[r1 - i - 1] - 'A']; //wypisywanie od konca
    }
    cout << "+";
    for (int i = 0; i < r2; i++) {
        cout << tab[napis2[r2 - i - 1] - 'A']; //mapa[napis2[r2 - i - 1]];
    }
    cout << "=";
    for (int i = 0; i < r3; i++) {
        cout << tab[napis3[r3 - i - 1] - 'A'];//mapa[napis3[r3 - i - 1]];
    }

    exit(0);//konczenie pracy programu
}

bool rekminus(int tab[26], bool free_value[10], int carry, int poz) {

    for (int i = poz; i < r4; i++) {

        int w1 = -1;
        int w2 = -1;
        int w3 = -1;
        if (i < r1) {
            w1 = tab[napis1[i] - 'A']; //mapa[napis1[i]];
            if (w1 == -1) { // jesli mam nieprzypisyan¹ wartosc do litery
                bool ret1 = false;
                for (int j = 0; j < 10; j++) {
                    //szukam wolnej wartosci
                    if (free_value[j] == true) {
                        bool free_value_c[10];
                        for (int k = 0; k <
                                        10; k++) { //robie kopie obecnej tablicy, zeby moc wstawic informacje o tym ze zajelismy jedna wartosc
                            free_value_c[k] = free_value[k];
                        }

                        int tab_c[26];//map<char, int>map_c(mapa);//konsturktor kopiujacy
                        //kopia tablicy;
                        for (int l = 0; l < 26; l++) {
                            tab_c[l] = tab[l];
                        }
                        free_value_c[j] = false; // zaklepuje wartosc ktora znalazlem
                        tab_c[napis1[i] - 'A'] = j;
                        if (rekminus(tab_c, free_value_c, carry, i) == true) {
                            ret1 = true;
                        }
                    }
                }
                if (ret1 == false) {
                    return false;
                }
            }
        } else {
            w1 = 0;
        }
        //-/////////////////////////////////////////
        if (i < r2) {
            w2 = tab[napis2[i] - 'A'];//mapa[napis2[i]];
            if (w2 == -1) {
                bool ret2 = false;
                for (int j = 0; j < 10; j++) {
                    if (free_value[j] == true) {

                        bool free_value_c1[10];
                        for (int k = 0; k < 10; k++) {
                            free_value_c1[k] = free_value[k];
                        }
                        int tab1_c[26];//map<char, int>map_c(mapa);//konsturktor kopiujacy
                        //kopia tablicy;
                        for (int l = 0; l < 26; l++) {
                            tab1_c[l] = tab[l];
                        }
                        free_value_c1[j] = false;
                        tab1_c[napis2[i] - 'A'] = j;
                        if (rekminus(tab1_c, free_value_c1, carry, i) == true) {
                            ret2 = true;
                        }
                    }
                }
                if (ret2 == false) {
                    return false;
                }
            }
        } else {
            w2 = 0;
        }
        //------------------------/
        if (i < r3) {
            w3 = tab[napis3[i] - 'A'];//mapa[napis3[i]];
            if (w3 == -1) {
                bool ret3 = false;
                for (int j = 0; j < 10; j++) {
                    if (free_value[j] == true) {

                        bool free_value_c2[10];
                        for (int k = 0; k < 10; k++) {
                            free_value_c2[k] = free_value[k];
                        }
                        free_value_c2[j] = false;

                        int tab2_c[26];//map<char, int>map_c(mapa);//konsturktor kopiujacy
                        //kopia tablicy;
                        for (int l = 0; l < 26; l++) {
                            tab2_c[l] = tab[l];
                        }
                        tab2_c[napis3[i] - 'A'] = j;
                        if (rekminus(tab2_c, free_value_c2, carry, i) == true) {
                            ret3 = true;
                        }
                    }
                }
                if (ret3 == false)
                    return false;
            }
        } else {
            w3 = 0;
        }
        if (w1 > w2) {
            if (w3 != (w1 - w2 + carry)) {
                return false;
            }
            carry = 0;
        } else if (w2 > w1) {
            if (w3 != (w1 - w2 + carry + 10)) {
                return false;
            }
            carry = -1;
        } else if (w1 == w2) {
            if (carry == 0) {
                if (w3 != (w1 - w2 + carry)) {
                    return false;
                }
            }
            if (carry == -1) {
                if (w3 != w1 - w2 + carry + 10) {
                    return false;
                }
            }
        } else {
            exit(1);
        }

    }
    if (carry != 0) {
        return false;
    }
    for (int i = 0; i < r1; i++) {
        cout << tab[napis1[r1 - i - 1] - 'A'];// mapa[napis1[r1 - i - 1]];
    }
    cout << "-";
    for (int i = 0; i < r2; i++) {
        cout << tab[napis2[r2 - i - 1] - 'A'];//mapa[napis2[r2 - i - 1]];
    }
    cout << "=";
    for (int i = 0; i < r3; i++) {
        cout << tab[napis3[r3 - i - 1] - 'A'];//mapa[napis3[r3 - i - 1]];
    }

    exit(0);
}

//gdy znak jest nieprzypisany wywoluje rekurencje

int main() {
    ios_base::sync_with_stdio(false);
    string napis_2;

    cin >> napis1 >> napis_2 >> napis3;

    char znak = napis_2[0];


    r2 = napis_2.size() - 1;

    napis2.resize(r2);
    for (int i = 0; i < r2; i++) {
        napis2[i] = napis_2[i + 1];
    }

    r1 = napis1.size();
    r3 = napis3.size();
    r4 = max(max(r1, r2), r3);
//odwracanie napisu
    reverse(napis1.begin(), napis1.end());
    reverse(napis2.begin(), napis2.end());
    reverse(napis3.begin(), napis3.end());

//    cout << napis1 <<" "<< napis2<<" " << napis3<<" " << znak;
    int tab[26];// map<char, int>mapa;
    bool fv[10];
    //wypelanianie tablicy -1 - oznacza wolne pole
    for (int i = 0; i < 26; i++) {
        tab[i] = -1;
        //wyplenianie tablicy wolnych wartosci
        if (i < 10) {
            fv[i] = true;
        }
    }
    if (znak == '+') {
        rekplus(tab, fv, 0, 0);
    }
    if (znak == '-') {
        rekminus(tab, fv, 0, 0);
    }
    return 0;
}
