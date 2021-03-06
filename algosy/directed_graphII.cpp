#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <limits>


using namespace std;

int main() {
  ios_base::sync_with_stdio(false);

  vector<vector<int> > sasiedzi; // indeksem jest id, w wewnetrznych przechowujemy listy sasiadow
  map<string, int> nazwyNaId; // do wczytywania danych
  map<int, string> idNaNazwy; // do wypisywania
  int liczbaSokow;
  int liczbaPar;

  cin >> liczbaSokow >> liczbaPar;

  string sok;
  for (int i = 0; i < liczbaSokow; i++) {
    cin >> sok;
    nazwyNaId[sok] = i;
    idNaNazwy[i] = sok;
    sasiedzi.push_back(vector<int>());
  }

  vector<int> liczba_dopiec(liczbaSokow, 0); // id jest indeksem
  pair<string, string> paraSokow;
  for (int licznikPar = 0; licznikPar < liczbaPar; licznikPar++) {
    cin >> paraSokow.first >> paraSokow.second;

    int id_second = nazwyNaId[paraSokow.second];
    liczba_dopiec[id_second]++;
    sasiedzi[nazwyNaId[paraSokow.first]].push_back(id_second);
  }

  priority_queue<int, vector<int>, greater<int> > kolejka;

  for (int i = 0; i < liczbaSokow; i++) {
    if (liczba_dopiec[i] == 0) kolejka.push(i);
  }

  for (int j = 0; j < liczbaSokow; j++) {
    int min_id = kolejka.top();
    kolejka.pop();

    int sas_size = sasiedzi[min_id].size();
    for (int i = 0; i < sas_size; i++) {
      int sas_id = sasiedzi[min_id][i];
      if (--liczba_dopiec[sas_id] == 0) 
        kolejka.push(sas_id);
    }

    liczba_dopiec[min_id] = liczbaSokow;

    cout << idNaNazwy[min_id] << endl;
  }

  return 0;
}
