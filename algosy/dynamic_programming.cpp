#include<iostream>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    int liczbaRzedow;
    int liczbaKolumn;
    int wart;
    int a=0;
    int b;
    cin >> liczbaRzedow;
    cin >> liczbaKolumn;

    int **tab = new int *[2];
    for ( int i =0 ;i < 2; i++){
        tab[i] =  new int [liczbaKolumn];
    }
//wczytujemy pierwszy wiersz
    for (int i = 0; i < liczbaKolumn; i++) {
        cin >> tab[0][i];
    }

        for (int i = 1; i < liczbaRzedow; i++) {

            a = i % 2;
            b = (i + 1) % 2;

            for (int j = 0; j < liczbaKolumn; j++) {

                cin >> wart;
                //wczytujemy wartosc i w zaleznosci od pozycji obslugujemy j¹
                if (liczbaKolumn == 1) {
                    tab[a][j] = wart + tab[b][j];
                } else if (j == 0) {
                    int maximum = max(tab[b][j], tab[b][j + 1]);
                    tab[a][j] = wart + maximum;
                } else if (j == liczbaKolumn - 1) {
                    int maximum = max(tab[b][j], tab[b][j - 1]);
                    tab[a][j] = wart + maximum;
                } else {
                    int maximum = max(tab[b][j - 1], tab[b][j]);
                    tab[a][j] = wart + max(maximum, tab[b][j + 1]);

                }
            }
        }

    //szukamy maximu i zapamietujemy jego index
    int max = tab[a][0];
    int index=0;
    for (int i = 0; i < liczbaKolumn; i++) {
        if (tab[a][i] >max) {
            max = tab[a][i];
            index = i;
        }
    }
    cout << index << " " << max;
    return 0;
}
