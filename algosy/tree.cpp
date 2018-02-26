#include<iostream>
using namespace std;
 
 // struktura elemnet reprezentuje poszczegolny element czyli liter liczbe jej dopiec i liczbe dzieci
struct Element{
    char litera;
    int ile_dopiec;
    Element **children;
    int ile_dzieci = 0;

    // jesli  liczba dzieci jest mniejsza od liczby dopiec to dodajemy ten element do tablicy i zwiekszamy liczbe dzieci
    bool addChild( Element * elem){
        if( ile_dzieci < ile_dopiec){

            children[ile_dzieci] = elem;
            ile_dzieci++;
            return true;
        }
        return false;

    }
// drukowanie rekurencyjne
    void print(){
        cout<< litera;
        for(int i=0; i< ile_dzieci; i++)
            children[i]->print();

    }
//konsturktor
    Element ( char  l, int i){
        litera =l;
        ile_dopiec=i;
        children = new Element * [ile_dopiec];
    }
};


int main(){

    int k,n;
    char l;
    cin>>k;
    int liczba;
    char znak;
    

    for ( int i =0; i< k; i++){

        cin >> n;
//n jesli mam zero elementow to przechodze do kolejnego obrotu petli      -  puste drzewo
        if ( n == 0) continue;
        
        Element **tab = new Element *[n];
        for ( int j=0 ; j < n; j++){
            cin>> znak;
            //wczytuj znak
            if ( znak == ' ')
                cin >>znak;
            cin >>liczba;
            tab[j] = new Element (znak, liczba);

        }

        int pozycja = 1;
        for ( int j =0; j < n ; j++ ){
                //// dopoki pozycja jest mniejsza od konca  i mozna dodac dziecko  zwiekszaj pozycje pozycja wskazuje na ostatni niedodany element
            while (pozycja < n && tab[j]->addChild(tab[pozycja]) ){
                pozycja++;
            }
        }
        tab[0]->print();
        cout  << endl;
    }





    return 0;
}
