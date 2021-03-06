#include <iostream>
#include <cstdio>


using namespace std;

class Stack {
    int rozmiar;
public:
    int* arr;
    int pos; // wskazuje na ostatnio zapisany element

    Stack(int size) {
        arr = new int[size];
        pos = -1;
        rozmiar = size;
    }

    void push(int value) {
        pos++;
        arr[pos] = value;
    }
    int pop() {
        return arr[pos--];
    }

    int top() {
        return arr[pos];
    }

    ~Stack() {
        delete[] arr;
    }

    void clear() {
        pos = -1;
    }

};

struct Vertex {
    int value;
    int* sasiedzi;
    int ileSasiadow;

    Vertex(int v, int liczba_wierzcholkow) {
        sasiedzi = new int[liczba_wierzcholkow];
        this->value = v;
        ileSasiadow = 0;
    }

    ~Vertex() {
        delete[] sasiedzi;
    }

    void dodajSasiada(int sasiad_value) {
        sasiedzi[ileSasiadow] = sasiad_value;
        ileSasiadow++;
    }

};
//DFS wyklad
bool DFSZnajdzCykl(Vertex** arr, const int& v, int w, Stack& s, bool* visited) {
    visited[w] = true;

    for (int u_index = 0; u_index < arr[w]->ileSasiadow; u_index++) {
        int u = arr[w]->sasiedzi[u_index];
        if (!visited[u]) {
            DFSZnajdzCykl(arr, v, u, s, visited);
        }
    }

    return true;
}

bool policzCykle(Vertex** arr, int liczbaWierzcholkow) {
    bool jestKartoflem = true;
    Stack cykl(0);
//funkcja ktora dla poszczegolnych wierzcholkow znajduje cykl i wpisuje go na stos
// nastepnie sortujemy zawartosc stosu u porownujemy ze soba posortowane elementy, jesli
// wszystkie sa takie same to znaczy ze znalezlismy 1 cykl jest kartoflem, jak znalezlismy dwa cykle to nei jets jaknie ma cyklu yto nie jest
    Stack s(liczbaWierzcholkow);
    bool* visited = new bool[liczbaWierzcholkow];
    for (int licznikCykli = liczbaWierzcholkow - 1; licznikCykli >= 0 && jestKartoflem; licznikCykli--) {
        s.clear();
        s.push(-1); //sztuczne ustawienie warotsci

        for (int i = 0; i < liczbaWierzcholkow; i++) visited[i] = false;

        if (DFSZnajdzCykl(arr, licznikCykli, licznikCykli, s, visited) == false) {
            continue;
        }

        for (int i = 0; i < liczbaWierzcholkow; i++) {
            if (!visited[i]) return false;
        }
        return true;
        

        for (int i = 0; i < s.pos; i++) { //sortowanie
            for (int j = 0; j < s.pos; j++) {
                if (s.arr[j] < s.arr[j + 1]) {
                    swap(s.arr[j], s.arr[j + 1]);
                }
            }
        }

        if (cykl.pos == -1) {
            cykl = s;

        } else {//inna dlugosc
            if (cykl.pos != s.pos) {
                jestKartoflem = false;
            }
    //wiecej niz jeden cykl
            for (int i = 0; i < cykl.pos + 1; i++) {
                if (cykl.arr[i] != s.arr[i]) {
                    jestKartoflem = false;
                    break;
                }
            }
        }
    }
    //nie znaleziono cyklu
    if (cykl.pos == -1) {
        jestKartoflem = false;
    }

    delete[] visited;
    return jestKartoflem;
}

bool policzSasiadow(Vertex** arr, int liczbaWierzcholkow) {
    for (int i = 0; i < liczbaWierzcholkow; i++) {
        if (arr[i]->ileSasiadow == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
 // printf i scanf dzialaja szybciej od cout i cin wiec uzywamy ich zeby przyspieszyc czas

    int liczbaZdjec;// liczba wczytanych zdjec
    scanf("%d", &liczbaZdjec);
    for (int numerZdjecia = 0; numerZdjecia < liczbaZdjec; numerZdjecia++) {

        int liczbaWierzcholkow, liczbaKrawedzi; //liczba wierzchołkow i krawedzi
        scanf("%d%d", &liczbaWierzcholkow, &liczbaKrawedzi);

        if (liczbaWierzcholkow != liczbaKrawedzi || liczbaWierzcholkow < 3 || liczbaKrawedzi < 3) {
            int temp;
            for (int i = 0; i < liczbaKrawedzi; i++) {
                scanf("%d%d", &temp, &temp);
            }

            printf("%s", "TO NIE KARTOFEL\n");
            continue;
        }

        Vertex** arr = new Vertex* [liczbaWierzcholkow];

        for (int i = 0; i < liczbaWierzcholkow; i++) {
            arr[i] = new Vertex(i, liczbaWierzcholkow);
        }

        for (int j = 0; j < liczbaKrawedzi; j++) {
            int x, y; // numer wierzcholkow polaczonych krawedziš
            scanf("%d%d", &x, &y);

            arr[x]->dodajSasiada(y); //dodawanie sasiadow wzajemne
            arr[y]->dodajSasiada(x);
        }

        if (policzSasiadow(arr, liczbaWierzcholkow) && policzCykle(arr, liczbaWierzcholkow)) {
            printf("%s", "TO KARTOFEL\n");
        } else {
            printf("%s", "TO NIE KARTOFEL\n");
        }


        for (int i = 0; i < liczbaWierzcholkow; i++)
            delete arr[i];
        delete[] arr;
    }

    return 0;
}
