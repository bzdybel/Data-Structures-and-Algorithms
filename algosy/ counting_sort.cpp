#include <iostream>
#include <cstring>

using namespace std;

struct para {
    int kcal;
    string potrawa;
};

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;

    int *dig, *dig2;
    dig = new int[n];
    dig2 = new int[n];

    para* v = new para[n];
    para* v2 = new para[n];

    //zerowanie tablicy
    memset(dig, 0, sizeof(int) * n);
    memset(dig2, 0, sizeof(int) * n);

    para p;
    for (int i = 0; i < n; i++) {
        cin >> p.potrawa >> p.kcal;
        v[i] = p;
        dig[p.kcal % n]++; //zliczanie
    }
    dig[0]--;
    for (int i = 1; i < n; i++) {
        dig[i] = dig[i] + dig[i - 1];
    } // 1 2 3 4 -> 0 2 5 9
    for (int i = n - 1; i >= 0; i--) {
        int kcal = v[i].kcal % n;
        v2[dig[kcal]] = v[i];
        dig[kcal]--;
        // ustawianie pierwszej tablicy
    }

    for (int i = 0; i < n; i++) {
        //zliczanie
        dig2[(v2[i].kcal - (v2[i].kcal % n)) / n]++;
    }
    dig2[0] --;
    for (int i = 1; i < n; i++) {
        dig2[i] = dig2[i] + dig2[i - 1];
    }
    int kcal;
    int digg;
    
    for (int i = n - 1; i >= 0; i--) {
        //ustawianie wyjsciowej tablicy
        kcal = v2[i].kcal;
        digg = (kcal - (kcal % n)) / n;
        v[dig2[digg]] = v2[i];
        dig2[digg]--;
    }
    for (int i = 0; i < n; i++) {
        cout << v[i].potrawa << " ";
    }
    return 0;
}
