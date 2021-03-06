#include <iostream>
int maxAktywnosc;
using namespace std;
struct elem {
    string miasto;
    int poz_aktywn;
    int index;
};

class Kopiec {
public:
    elem *tab;
    int size;
    int sizeZmienny = 1;
    // size zmmienny jest licznikiemelementow i ustawiony jest na 1, poniewaz
    //pry obliczaniu synow w uzywamy mnozenia a zero by nam je wyzerowalo

    Kopiec(int size) {
        this->size = size;
        tab = new elem[size + 1];
        //skoro size zmienny jest od 1 wiec indeksujemy tablice od jeden wiec analogicznie musimy
        //wydluizyc ja o jeden
    }

    void push(elem element) {
        int i = sizeZmienny, indexOjca;
        tab[sizeZmienny] = element;
        // tu size zmienny =1
        sizeZmienny++;
        //tu 2
        elem pom;
        indexOjca = i / 2;
        // jesli jest rowny dwa tzn ze tablica byla pusta wiec nie musimy przesiewac
        if (sizeZmienny == 2) {
            return;
        }
        // przesiewanie - syn wieksyz od ojca - zamiana
        while (element.poz_aktywn >= tab[indexOjca].poz_aktywn && i != 1) {
            //DODAC PRIORYTET INDEKSU
            //
            if ( element.poz_aktywn == tab[indexOjca].poz_aktywn && element.index > tab[indexOjca].index) {
                break;
            }
            // to samo co wyzej
            /*if ( element.poz_aktywn == tab[indexOjca].poz_aktywn && element.index < tab[indexOjca].index) {
                zamiana
            }
            */

            pom = tab[indexOjca];
            tab[indexOjca] = element;
            tab[i] = pom;

            i = indexOjca;
            indexOjca = i / 2;
        }
    }

    void pop() {
        //zdejmuje element z kopca z gory na koniec
        //biore pierwszy element zmianiam go z ostatnim
        //inba z aktywnoscia
        //zmniejszam tablice
        //naprawianie kopca
        if (tab[1].poz_aktywn <= maxAktywnosc) {
            //zdejmowanie korzenia
            //aktualizacja aktywnosci
            maxAktywnosc = maxAktywnosc - tab[1].poz_aktywn;
            cout << tab[1].miasto<<" ";
        }
        tab[1] = tab[sizeZmienny-1];
        sizeZmienny--;
        //zamiana z ostatnim elementem
        // po wywolaniu tej funkcji trzeba koneicznie naprawic kopiec
    }

    void naprawa() {
        //SPRAWDZAM CZY ELEMENT JEST wiekszy od obu swoich dzieci jesli nie
        //to go zamieniam z jednym z dzieci- wieksyzm od niego
        //dziecko musi byc wieksze oraz musi byc w kopcu
        int i = 1;
        /*
         Przypadki kiedy wykonuje się petla:
         1.bracia mieszcza sie w rozmiarze
         1. lbrat > ojciec
         2. l brat == ojciec i lbrat.index < ojciec.index
         3. pbrat > ojciec
         2. p brat == ojciec i pbrat.index < ojciec.index
         */
        while (
                (i * 2 < sizeZmienny
                 && ((tab[i * 2].poz_aktywn > tab[i].poz_aktywn)
                     || (tab[i * 2].poz_aktywn == tab[i].poz_aktywn && tab[i * 2].index < tab[i].index)))
                || (i * 2 + 1 < sizeZmienny
                    && ((tab[i * 2 + 1].poz_aktywn > tab[i].poz_aktywn)
                        || (tab[i * 2 + 1].poz_aktywn == tab[i].poz_aktywn && tab[i * 2 + 1].index < tab[i].index))))
        {
            int lbratPozakt = tab[i * 2].poz_aktywn;
            int pbratPozakt = tab[i * 2 + 1].poz_aktywn;
            int oPozakt = tab[i].poz_aktywn;

                // do tego warunku wchodzimy jesli bracia sa rowni ojcu i rozpatrujemy w nim poszczegolnych braci
            if (((i * 2 < sizeZmienny && lbratPozakt == oPozakt) && (i * 2 + 1 < sizeZmienny && pbratPozakt == oPozakt))) {
                    // lewy syn  rowny ojciec , mniejszy indeks od ojca i mniejszy indeks od brata
                if (tab[i * 2].index < tab[i].index && tab[i * 2].index < tab[i * 2 + 1].index) {
                    swap(tab[i], tab[i * 2]);
                    i = i * 2;
                    continue;
                }
                // prawy syn  rowny ojciec , mniejszy indeks od ojca i mniejszy indeks od brata
                if (tab[i * 2 + 1].index < tab[i].index && tab[i * 2].index > tab[i * 2 + 1].index) {
                    swap(tab[i], tab[i * 2 + 1]);
                    i = i * 2 + 1;
                    continue;
                }
            }
                // lewy brat wiekszy od ojca prawy brat wiekszy od ojca
            if ((i * 2 < sizeZmienny && lbratPozakt > oPozakt) && (i * 2 + 1 < sizeZmienny && pbratPozakt > oPozakt)) {
                // lewy brat wiekszy od prawego lub rowni ale mniejszy indeks
                if (lbratPozakt > pbratPozakt || (lbratPozakt == pbratPozakt && tab[i * 2].index < tab[i * 2 + 1].index)) {
                    swap(tab[i], tab[i * 2]);
                    i = i * 2;
                    continue;
                }
                // prawy brat wiekszy od lewego lub rowni ale prawy mniejszy index
                if (lbratPozakt < pbratPozakt || (lbratPozakt == pbratPozakt && tab[i * 2].index > tab[i * 2 + 1].index)) {
                    swap(tab[i], tab[i * 2 + 1]);
                    i = i * 2 + 1;
                    continue;
                }
            }
            // po prostu lewy brat wiekszy ojciec
            if (i * 2 < sizeZmienny && lbratPozakt > oPozakt) {
                swap(tab[i], tab[i * 2]);
                i = i * 2;
                continue;
            }
            //po prostu lewy brat wiekszy ojceic
            if (i * 2 + 1 < sizeZmienny && pbratPozakt > oPozakt) {
                swap(tab[i], tab[i * 2 + 1]);
                i = i * 2 + 1;
                continue;
            }
            //lewy brat rowny ojciec ale mniejszy indeks
            if (i * 2 < sizeZmienny && (lbratPozakt == oPozakt && tab[i * 2].index < tab[i].index)) {
                swap(tab[i], tab[i * 2]);
                i = i * 2;
                continue;
            }
            // prawy brat rowny ojciec ale mniejszy indeks
            if (i * 2 + 1 < sizeZmienny && (pbratPozakt == oPozakt && tab[i * 2 + 1].index < tab[i].index)) {
                swap(tab[i], tab[i * 2 + 1]);
                i = i * 2 + 1;
                continue;
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int liczbaMiejsc;
    cin >> liczbaMiejsc;
    Kopiec k1(liczbaMiejsc);
    elem e;

    for (int i = 0; i < liczbaMiejsc; i++) {
        cin >> e.miasto;
        cin >> e.poz_aktywn;
        e.index = i;
        k1.push(e);
    }
    cin >> maxAktywnosc;
    while (maxAktywnosc > 0 && k1.sizeZmienny != 1) {
        k1.pop();
        //po popie koniecznie naprawa
        k1.naprawa();
    }
    return 0;
}
