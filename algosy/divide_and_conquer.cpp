#include <cmath>
#include <iostream>
using namespace std;
int x,y;
// funkcja sprawdzaj¹ca czy dana wartosc jest szczytem
bool  szczyt(int i, int j, double val){
    if (i != 0 && P(i-1,j) > val ){
        return false;
    }
    if ( i < x-1 && P ( i+1,j) > val ){
        return false;
    }
    if ( j!= 0 && P (i,j-1) > val ){
        return false;

    }
    if ( j < y-1 && P(i,j+1) > val ){
        return false;
    }
    return true;
}
double rek(const int right, int top, int bottom) {
    int half = top + (bottom - top) / 2; //polowa srodkowy wiersz

    int max = 0;
    //znajdywanie indeksu wiersdza z maxymalna waretoscia
    double val= P(max,half);
    for ( int i = 1; i < right; i++){
        if (val <= P(i,half)) {
            max = i;
            val = P(i,half); // wartosc maxymalna w srodkowym wierszu
        }
    }
    if (szczyt(max,half,val) || top == bottom - 1) { // jesli znalazno szczyt lub zeszly sie top z bottom to zwracamy ansz funkcje
        return P(max,half);
    }
    // jesli nie jest szczytem to dziel i zwyciezaj na kolumnie, albo idziemy do gory albo idziemy do dolu 
    double max_top = P(max,top);
    double max_bottom = P(max,bottom-1);

    int  t, b;
    //zawezanie przedzialow dziel i wyciezaj
    if ( max_top > max_bottom) {
        t = top;
        b = half;
    }else {
        t = half;
        b = bottom;
    }
    return rek(right, t, b);
}
int main() {
    ios_base::sync_with_stdio(false);
    int n;
    int m;

    cin >> n >> m;
    x=n;
    y=m;
    cout << (int)rek(n, 0, m);

    return 0;
}
