#include <iostream>
#include <cmath>

#define LEWA true
#define PRAWA false

using namespace std;

struct Element { //struktura reprezentuje jeden element, ma dwa wskazniki na poprzedni i na kolejny element oraz wartosc
  int value;
   Element* next;
   Element* prev;

   Element(int v, Element* n, Element* p) {//konstruktor
    value = v;
    next = n;
    prev = p;
  }
};

class List {//lista jest zbiorem elementow, przechowuje wskaznik na poczatek i na koniec listy
  private:
     Element* front = NULL;
     Element* back = NULL;

  public:
    void print();    //metoda wypisujaca
    void push_front(Element*);
    void push_back(Element*);
    
 	Element* pop_front();
 	Element* pop_back();
};

void List::push_front(Element* elem) {

if (front != NULL) { // jak lista nie jest pusta
    front->prev = elem; // nowy elemnt ustawiamy jako wsakznik na poczatek listy

  } else {
    back = elem;// jak nie jest to dajemy na koniec listy
  }
		
	elem->prev=NULL; //wskaznik na poprzedni null-poczatek listy
	elem->next=front; // nastepny element to elemnet ktory byl glowa przed dodatniem nowego elementu
	
  front = elem; //pierwszy to nowy element
}

void List::push_back(Element* elem) {

if (back == NULL) { //jesli wskaznik na ostatni element jest nullem to lista jest pusta i mozna dodac element do  listy
    push_front(elem);
    return;
  }

	elem->prev=back; // dodajemy element ustawiajac wskaznik na porpzedni elelemn na wskaznik na ostatni element
	elem->next=NULL; // a wskaznik na nasteopny element dajemy jako null co jest rownowazne ze lista sie skonczyla

	back->next = elem;
	back = elem; // ostatni element jest koncem listy
}

Element* List::pop_back() {
	Element* elem=back;
	Element* prev = back->prev;
  if (prev != NULL) { // jesli przedostatni element nie jest nullem to ustawiam jego wskaznik na nulla co oznacza ze element ktory nastepowal po nim jest wypiety z listy
  // bo next na  null zamyka liste
    prev->next = NULL;
  } else {  // pojedynczy element w liscie to wskaznik na pierweszy na null
    front = NULL;
  }
  
  back = prev; //przedostatni teraz jest ostatnim
  return elem;
}

Element* List::pop_front() {
	Element* elem=front;
 	Element* next = front->next;
 		
  if (next != NULL) {
    next->prev = NULL;//analogicznie jak w backu jesli drugi nie jest nullem to jego wskaznik na poprzedni na nulla co wypina pierwszy z listy
  } else {  // jesli jest tylko jeden element to wskaznik na ostatni na null
    back = NULL;
  }
  front = next; //drugi jest pierwszym

  return elem;
}

void List::print() {
  Element* iter = front;

  while (iter != NULL) {
    cout << iter->value << " ";  
    iter = iter->next;//iteracja
  }
}

 List lewa;
 List prawa;
 int Z = 0;
 int U = 0;
int* zamiany = NULL;
int* upuszczone = NULL;

Element* wyrzucenie(bool reka) { // funckja zwraca wskaznik na wyrzucony element
  if (reka == LEWA) {
    return lewa.pop_back();
  } else {
    return prawa.pop_front();
  }
}

void zlap(bool reka, Element *elem) { 
  if (reka == LEWA) {
    lewa.push_front(elem);
  } else {
    prawa.push_back(elem);
  }
}

bool zamiana(int index) { //funckja sprawdza czy nastepuje zamiana i zwraca prawde lub falsz
  for (int i = 0; i < Z && index >= zamiany[i]; i++) { 	
    if (index == zamiany[i]) return true;
  }

  return false;
}

bool upuszczenie(int index) { // analogicznie jak zamiana tyle zeupuszczenie
  for (int i = 0; i < U && index >= upuszczone[i]; i++) {
    if (index == upuszczone[i]) return true;
  }

  return false;
}

int main() {

	 
// wczytywanie

  int N, K;
  cin >> N >> K;  
  cin >> U;
  
  upuszczone = new int[U]; //tablica z upuszcoznymi elementami
  for (int i = 0; i < U; i++) {
    cin >> upuszczone[i];
  }

  cin >> Z;
  zamiany = new int[Z];//tablica ze zmianami
  for (int i = 0; i < Z; i++) {
    cin >> zamiany[i];
  }

// zapelnienie listy, liczba elementow determinuje ile w ktorej rece jest elementow

   Element *elem;
  	if (N % 2 == 0) {
    int liczba_w_rece = N / 2;
    
    for (int i = 1; i <= liczba_w_rece; i++) {
    	lewa.push_back(new Element(i, NULL, NULL));
    }

    for (int i = liczba_w_rece + 1; i <= N; i++) {
   		prawa.push_back(new Element(i, NULL, NULL));
    }

  } 
  else {
    int liczba_w_rece = N / 2;
    
    for (int i = 1; i <= liczba_w_rece + 1; i++) {
    	lewa.push_back(new Element(i, NULL, NULL));
    }

    for (int i = ceil(N / 2.0) + 1; i <= N; i++) { //ceil zaokragla liczbe do gory
   		prawa.push_back(new Element(i, NULL, NULL));
    }
  }


// program

  bool reka = LEWA; //zaczynamy od lewej
  Element* pom;

  for (int i = 1; i <= K; i++) { 	
    if (i % 2 == 1) { // nieparzysty ruch wyrzucamy pileczke
      if (zamiana(i)) {
        reka = !reka; //jest zamiana-  to np lewa = !lewa wiec prawa
      }
  
      pom = wyrzucenie(reka); // wyrzucony element przechowujemy w zmiennej pomocniczej
  
      reka = !reka; //zmieniamy reke
  
    } 
    
	else {
      if (upuszczenie(i)) {
        delete pom;
  
      } else {
        zlap(reka, pom); //jesli nie upuscil to dodaje zlapana pileczke
      }
    }

}
  
  lewa.print(); //wypisujemy wynik
  prawa.print();

  return 0;
}
