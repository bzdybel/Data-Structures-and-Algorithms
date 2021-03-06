#include <iostream>
#include <cmath>


using namespace std;

int NajwDziel(int liczba) {
  int wynik = 1;
  for (int i = 2; i <= sqrt(liczba); i++) {// jak mam 100 znajduje 2 , ktore jest odpowiednikiem dzielnika 50 , 90 znajduje 2 zwracam 45
    if (liczba % i == 0) {
      wynik = liczba / i;
      break;
    }
  }
  return wynik;
}

void SortWstaw(pair<int, int> tab[], int n) {
  pair<int, int> pom;
  for (int i = 1; i < n / 2; i++) {// zaczynam od drugiego elementu  i
    pom = tab[i];
    for (int j = i - 1; j >= 0 && (tab[j].first >= pom.first); j--) {//porownuje z poprzednimi, az element nie bedzie na odpowiednim miejscu
      if (tab[j].first > pom.first) {//zwykle sortowanie
        tab[j + 1] = tab[j];//zamieniam miejscami z
        tab[j] = pom;
      }
      else if (tab[j].first == pom.first) {
        if (NajwDziel(tab[j].second) < NajwDziel(pom.second)) {
          tab[j + 1] = tab[j];
          tab[j] = pom;
        }
      }
    }
  }
}
int main() {
  int N;//liczba ciagow
  int D;//liczba elemntow w ciagu
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> D;
    pair<int, int> tab[D / 2];
    for (int j = 0; j < D / 2; j++) {
      cin >> tab[j].first >> tab[j].second;
    }

    SortWstaw(tab, D);
    for (int j = 0; j < D / 2; j++)
      cout << tab[j].first << " " << tab[j].second << " ";

  }

  return 0;
}
