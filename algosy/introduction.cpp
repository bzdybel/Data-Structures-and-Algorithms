#include <iostream>
using namespace std;

int main()
{
    char znak;
    int max, min;
    char mi, ma;
    pair <char,int> tab1[123];
    int i=0, licznik=0;
    znak='a';

       while ( i <123){
        tab1[i].second=0;

        i++;
       }

           while (znak!= '^'){
            cin>>znak;
            if (znak >= 97 && znak <=122){
                    tab1[znak].second++;
                    tab1[znak].first=znak;
                }
            if ( znak <= 90 && znak > 64){
                    znak=znak+32;
                    tab1[znak].second++;
                    tab1[znak].first=znak;
                }

           }

         max=tab1[97].second;
          for( int i=97;i<=122;i++){
                if (tab1[i].second >= 1 && tab1[i].second > max){
                max=tab1[i].second;

                 }
         }
         min=max;
          for( int i=97;i<123;i++){
                if (tab1[i].second > 0 && tab1[i].second < min){

                min=tab1[i].second;
                 }
         }
         for( int i=97;i<123;i++){
                if (tab1[i].second==min){

               mi=tab1[i].first;
               break;
                 }
         }
             for( int i=97;i<123;i++){
                if (tab1[i].second==max){

               ma=tab1[i].first;
               break;
                 }
         }


            cout<<ma<<" "<<mi;
      return 0;
}
