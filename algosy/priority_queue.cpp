#include <iostream>
#include <queue>
#include <math.h>

using namespace std;

struct Kwiaty {
    int value;
    int index;

    Kwiaty(int value, int index) {
        this->value = value;
        this->index = index;
    }
    bool operator<(const Kwiaty& k1) const {
        if (value == k1.value) {
            return index > k1.index;
        }
        return value < k1.value;
    }
    bool empty(){
        if ( value == 0)
            return true;
        else
            return false;

    }
};

int main() {
    int liczbaRzedow;
    cin >> liczbaRzedow;

    for (int licznikRzedow = 0; licznikRzedow < liczbaRzedow; licznikRzedow++) {
        bool wypisz= true;
        int liczbaWazonow;
        cin >> liczbaWazonow;

//kolejka odrazu sortuje wartosci
        priority_queue<Kwiaty, vector<Kwiaty>, less<Kwiaty> > kolejka; //rosn¹co chuj wie czy vector i less ma przyjac kwaiaty ale chyba tak

        int x;
        int suma = 0;
        for (int licznikWazonow = 0; licznikWazonow < liczbaWazonow; licznikWazonow++) {
            cin >> x;
            suma+=x; //
            Kwiaty k(x, licznikWazonow);
            kolejka.push(k);
        }

        Kwiaty pomocnicza(0, 0);
        Kwiaty pomocnicza2(0,0);

        if (kolejka.top().value > ceil(suma / 2.0)) { //liczba kwiatkow w jednym wazonie jest wieksza niz liczba pozostalych kwiatkow
            cout << "NIE" << endl;
        }else{
            for (int i = 0; i < suma; i++) {
//dwie zmienne pomocnicze zeby nie nadpisywac aktualnei zdjetej wartosci
                cout << kolejka.top().index << " ";
                if (!pomocnicza.empty()) {
                    pomocnicza2 = kolejka.top();
                    kolejka.pop();
                    pomocnicza2.value--;
                    kolejka.push(pomocnicza);
                    pomocnicza = pomocnicza2;


                } else {
                    pomocnicza = kolejka.top();
                    kolejka.pop();
                    pomocnicza.value--;
                }
            }
            }

    }

    return 0;
}
