#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;
string M;

struct para {
    string miejsce;
    int kroki;
//przeciazony operator porownywania
    bool operator<(para p1) const {
        if (p1.kroki == kroki) {
//      return p1.miejsce.compare(miejsce) == 1;
            return p1.miejsce > miejsce;
        }

        return kroki < p1.kroki;
    }
};

int magicznPiatki(para* tab, int n, int k) {

    if (n <= 10) {
        sort(tab, tab + n);
        M = tab[k].miejsce;
        return tab[k].kroki;
    } else {
        //dla piatek gdzie jest rowno po piec elementow
        int liczbaPiatek = ceil(n / 5.0);
        for (int i = 0; i < liczbaPiatek - 1; i++) {
            //wskazuje na pierwszy element  i na element jeden za ostatnim
            sort(tab + i * 5, tab + (i + 1) * 5);
            swap(tab[i], tab[i * 5 + 2]); //indeks drugi jest w srodku

        }//dla ostatniej piatki gdzie neikoniecznie jest 5 elementow
        sort(tab + (liczbaPiatek - 1) * 5, tab + n);

        int dlugoscOstatniego = (n - (liczbaPiatek - 1) * 5);
        int przesuniecieOstatniego = dlugoscOstatniego / 2;
        int medianaOstatniego = (liczbaPiatek - 1) * 5 + przesuniecieOstatniego;
        swap(tab[liczbaPiatek - 1], tab[medianaOstatniego]);

//rekurencyjne wywolanie dla mediany median
        int medianaMedian =
                magicznPiatki(tab, liczbaPiatek, liczbaPiatek / 2.0 - 1);

        int mniejsze = 0;
        int rowne = 0;
        int wieksze = 0;

        for (int i = 0; i < n; i++) {
            //dzielenie na wieksze mniejsze rowne
            if (tab[i].kroki > medianaMedian) wieksze++;
// wieksze mniejsze rowne moga byc rowniez wtedy gdy kroki sa rowne ale leksykograficzny napis jest rozny
            if (tab[i].kroki == medianaMedian) {
                if (tab[i].miejsce < M) {
                    mniejsze++;
                } else if (tab[i].miejsce > M) {
                    wieksze++;
                } else {
                    rowne++;
                }
            }

            if (tab[i].kroki < medianaMedian) mniejsze++;
        }

        if (k < mniejsze) {
            int w = 0;
            para* mniejszetab = new para[mniejsze];

            for (int i = 0; i < n; i++) {
                if (tab[i].kroki < medianaMedian || (tab[i].kroki == medianaMedian && tab[i].miejsce < M)) {
                    mniejszetab[w] = tab[i];
                    w++;
                }
            }
            int wynik = magicznPiatki(mniejszetab, mniejsze, k);
            delete[] mniejszetab;
            return wynik;

        } else if (k < mniejsze + rowne) {
            return medianaMedian;

        } else {
            int w = 0;
            para* wiekszetab = new para[wieksze];

            for (int i = 0; i < n; i++) {
                if (tab[i].kroki > medianaMedian || (tab[i].kroki == medianaMedian && tab[i].miejsce > M)) {
                    wiekszetab[w] = tab[i];
                    w++;
                }
            }
            int wynik = magicznPiatki(wiekszetab, wieksze, k - rowne - mniejsze);
            delete[] wiekszetab;
            return wynik;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int iloscMiejsc;
    int limitKrokow;
    int liczbaWybranychMiejsc;
    cin >> iloscMiejsc;
    int pozycja;

    para Pair[iloscMiejsc];


    for (int i = 0; i < iloscMiejsc; i++) {
        cin >> Pair[i].miejsce >> Pair[i].kroki;
        Pair[i].kroki = Pair[i].kroki * 2;
    }
    cin >> limitKrokow >> liczbaWybranychMiejsc;

    while (liczbaWybranychMiejsc > 0) {
        cin >> pozycja;
        pozycja = iloscMiejsc - pozycja - 1;
        int akt = magicznPiatki(Pair, iloscMiejsc, pozycja);
//dopok mozna odejmowac to odejmuj i wypisuj
        if (limitKrokow - akt >= 0) {
            limitKrokow = limitKrokow - akt;
            cout << M << " ";

        } else {
            cout << "NIE ";
        }

        liczbaWybranychMiejsc--;
    }


    return 0;
}
