#include<iostream>
#include<sstream>


using namespace std;

typedef long long num;

// stos uzywany tylko do obliczania wartosci ONP, zawiera jedynie liczby
class NumberStack {
private:
    num* arr = NULL;
    int pos; // wskazuje na ostatnio zapisany element

public:
    NumberStack(int size) {
        arr = new num[size];
        pos = -1;
    }

    ~NumberStack() {
        delete[] arr;
    }

    void push(num value) {
        pos++;
        arr[pos] = value;
    }

    num pop() {
        return arr[pos--];
    }
};

// liczba albo operator jako znak
struct PostfixToken {
    num value = 0;
    bool is_operator = false; // sprawdzxa czy liczba czy znak
    PostfixToken(num v, bool op) {
        value = v;
        is_operator = op;
    }

    PostfixToken() {}
};

// zawiera wejscie zamienione na tokeny
// tablica ktora przechowuje postfix tokeny -znaki i wartosci
class PostfixTokenArray {
private:
    int position;
public:
    PostfixToken* arr = NULL;
    int size;
    PostfixTokenArray() {}
    PostfixTokenArray(int s) {
        position = 0;
        size = s;
        arr = new PostfixToken[s];
    }

    ~PostfixTokenArray() {
        delete[] arr;
    }
    void add(PostfixToken pt) {
        arr[position] = pt;
        position++;
    }

    void print() {
        for (int i = 0; i < position; i++) {
            if (arr[i].is_operator)
                cout << arr[i].is_operator << "  " << char(arr[i].value) << endl;
            else
                cout << arr[i].is_operator << "  " << arr[i].value << endl;
        }
    }
};

// oper uzywamy przy zamianie do wstawiania nawiasow
struct InfixToken {
    string expr;
    char oper;

    InfixToken(const string& expr, char oper) : expr(expr), oper(oper) {}
    InfixToken() {}
};

// stos do zamiany na postac infixowa
class InfixStack {
private:
    InfixToken* arr = NULL;
    int pos;
    int size;

public:
    InfixStack(int s) {
        this->size = s;
        arr = new InfixToken[size];
        pos = -1;
    }
    int get_size() {
        return size;
    }
    ~InfixStack() {
        delete[] arr;
    }

    void push(InfixToken token) {
        pos++;
        arr[pos] = token;
    }

    InfixToken pop() {
        return arr[pos--];
    }

    bool isEmpty() {
        return pos < 0;
    }
};

// wszystkie wartosci w jednym miejscu
class Expression {
public:
    PostfixTokenArray* postfix = NULL; //postfix zamieniony na tokeny
    num value = 0; //wartosc
    string infix; // gotoy infix
    int liczba_nawiasow = -1;
    bool printed = false;

    ~Expression() {
        delete postfix;
    }

    void policzNawiasy() {
        // wyzeruj
        liczba_nawiasow = 0;

         long infix_length = infix.length();
        for (long i = 0; i < infix_length; i++) {
            if (infix[i] == '(' || infix[i] == ')') {
                liczba_nawiasow++;
            }
        }
    }
};
//ZACZYNAM OD LEWEJ DO PRAWEJ PO TOKENACH jesli
string postfixToInfix(PostfixTokenArray* arr) {
    InfixStack stos(arr->size);

    stringstream ss;
    for (int i = 0; i < arr->size; i++) {
         PostfixToken token = arr->arr[i];

        if (token.is_operator) {// jak wcyzta + lub - to  wrzucam pomiedyz dwie wczytane liczby znak i wrzucam tto dzialanie na stos z operatorem
            if (token.value == '+' || token.value == '-') {
                InfixToken element;

                InfixToken right = stos.pop();
                InfixToken left = stos.pop();

                string right_expr = right.expr;
                string left_expr = left.expr;
// jak mam odejmowanie po srodku to sprawdzam cyz po prawej stornie dzialania jest + lub - jesli tak to daje wyrazniee po prawej w nawiasy
                if (token.value == '-' && (right.oper == '+' || right.oper == '-')) {
                    right_expr = "(" + right.expr + ")";
                }

                left_expr += (char) token.value;
                element.expr = left_expr + right_expr;
                element.oper = (char) token.value;
                stos.push(element);

            } else {

                InfixToken right = stos.pop();
                InfixToken left = stos.pop();

                string left_expr, right_expr;

                if (left.oper == '+' || left.oper == '-') { // jesli po lewej + - to w nawaisy
                    left_expr = "(" + left.expr + ")";
                } else {
                    left_expr = left.expr;
                }
                left_expr += (char) token.value;

                if (token.value == '*') {// jesli  wczytalem gwiazdke  sprawdzam czy po prawej stronie dzialania mam dodawanie lub obejmowanie jesli tak obejmuje to w nawiasy
                    if (right.oper == '+' || right.oper == '-') {
                        right_expr = "(" + right.expr + ")";
                    } else {
                        right_expr = right.expr;
                    }
                } else {
                    if (right.oper == '\0') { // jesli mam dzielenie to sprawdzam czy po lewej mam liczbe jesli tak to na zywca jesli nei to zawsze nawiasy
                        right_expr = right.expr;
                    } else {
                        right_expr = "(" + right.expr + ")";
                    }
                }

                stos.push(InfixToken(left_expr + right_expr, (char) token.value)); // i wrzucam to na stos
            }
    }         else { // jesli liczba to czyscze stringstreama i wrzucam wczytana liczbe jako napis na infix stos
            ss.str("");
            ss << token.value;

            stos.push(InfixToken(ss.str(), '\0'));
        }
    }

    return stos.pop().expr; // na koneic zwracam mojego stringa
}

int main() {
    int liczba_wejsc;
    cin >> liczba_wejsc;
    Expression wyrazenia[liczba_wejsc]; // troche za duzo, bo mamy mniej wyrazen
    int liczba_wyrazen = 0;

    for (int ktore_wejscie = 0; ktore_wejscie < liczba_wejsc; ktore_wejscie++) { //D czy S
        char znak;
        cin >> znak;
        if (znak == 'D') {

            string line = "";
            while (line.length() == 0) {
                getline(cin, line); //  jesli wczytuje pusta linie wczytuje puste linie
//      getline(cin, line);
            }

            const long n = line.size();
            int licz_tokenow = 1; // wiecej tokenow niz spacji

            for (int j = 0; j < n; j++) // sprawdzam czy spacja licze je
                if (line[j] == ' ')
                    licz_tokenow++;

            if (line[n - 1] == ' ') licz_tokenow--; // jak na koncu jest spacja TEST 5

            PostfixTokenArray* ta = new PostfixTokenArray(licz_tokenow); // tworze tablice wielkosci lioczby tokenow (spacje+1)
            wyrazenia[liczba_wyrazen].postfix = ta;

            stringstream ss(line); // zamiana wejscia na strumien wczytanie

            for (int j = 0; j < n; j++) { // lece po znakach napisu
                if (j == 0) { // pierwszy token wczytujemy zawsze
                    if (line[j] >= '0' && line[j] <= '9') { //sprawdzxam czy wczytuje cyfre czy znak
                        num tmp;
                        ss >> tmp;
                        ta->add(PostfixToken(tmp, false));

                    } else if (line[j] == '+' || line[j] == '-' || line[j] == '/'
                               || line[j] == '*') {
                        char tmp;
                        ss >> tmp;
                        ta->add(PostfixToken(tmp, true));
                    } else {
                        return 1;
                    }

                } else if (line[j] == ' ' && j + 1 < n) {
                    if (line[j + 1] >= '0' && line[j + 1] <= '9') { // jak trafilem spacje to sprawdzam kolejny znak analogicznie jak wyzej
                        num tmp;
                        ss >> tmp;
                        ta->add(PostfixToken(tmp, false));

                    } else if (line[j + 1] == '+' || line[j + 1] == '-'
                               || line[j + 1] == '/'
                               || line[j + 1] == '*') {
                        char tmp;
                        ss >> tmp;
                        ta->add(PostfixToken(tmp, true));
                    } else {
                        return 1;
                    }
                }
            }
            // obliczam wartosc
            NumberStack ns(licz_tokenow);
            for (int j = 0; j < licz_tokenow; j++) {
                if (ta->arr[j].is_operator == false) {
                    ns.push(ta->arr[j].value);
                } else {
                    num a, b;
                    a = ns.pop();
                    b = ns.pop();
// jak mam znak zdejmuje dwie liczby ze stosu wykonuje operacje i wrzucam na stack
                    switch ((char) ta->arr[j].value) {
                        case '+' :ns.push((a + b));
                            break;
                        case '-' :ns.push((b - a));
                            break;
                        case '*' :ns.push((a * b));
                            break;
                        case '/' :ns.push((b / a));
                            break;

                    }
                }
            }
// tablica wyrazenia jest typu expression
            wyrazenia[liczba_wyrazen].value = ns.pop();
//      if (wyrazenia[liczba_wyrazen].value < 0) return 1; DEBUG

//            if (false) {
//                cout << "postfix: " << line << endl;
//                wyrazenia[liczba_wyrazen].infix =
//                        postfixToInfix(wyrazenia[liczba_wyrazen].postfix);
//                cout << "wartosc = " << wyrazenia[liczba_wyrazen].value << ", infix: "
//                     << wyrazenia[liczba_wyrazen].infix << endl;
//                cout << "Postfixowa tablica: (czy operator) (wartosc)" << endl;
//                ta->print();
//                wyrazenia[liczba_wyrazen].policzNawiasy();
//                cout << "nawiasy: " << wyrazenia[liczba_wyrazen].liczba_nawiasow
//                     << endl;
//                cout << "---------------" << endl;
//            }

            liczba_wyrazen++;

        } else if (znak == 'S') {

            num desired_value;
            cin >> desired_value;

            // wyszukujemy wszystkie pasujace wyrazenia
            // wyznaczamy dla nich niezbedne rzeczy jak postac infixowa i liczba nawiasow
            int results = 0;
            for (int i = 0; i < liczba_wyrazen; ++i) {
                if (wyrazenia[i].value == desired_value && !wyrazenia[i].printed) {
                    results++;

                    // nawiasy nie zostaly jeszcze policzone
                    // jesli nic nie robilem z danym elementem liczba nawiasow jest rowwna -1
                    // jesli przerobilem na infix to liczba nawiasow jest rowna 0 lub wieksza
                    if (wyrazenia[i].liczba_nawiasow == -1) {
                        wyrazenia[i].infix = postfixToInfix(wyrazenia[i].postfix);
                        wyrazenia[i].policzNawiasy();
                    }
                }
            }

            // jesli nie znalezlismy nic
            if (results == 0) {
                cout << "NIE" << endl;

                // znalezlismy jeden wynik, od razu go wypisujemy
            } else if (results == 1) {
                for (int i = 0; i < liczba_wyrazen; ++i) {
                    if (wyrazenia[i].value == desired_value && !wyrazenia[i].printed) {
                        cout << "TAK" << endl;
                        cout << wyrazenia[i].infix << endl;
                        wyrazenia[i].printed = true;
                        break;
                    }
                }

                // mamy wiecej wynikow, musimy porownac liczbe nawiasow
            } else {
                // wyszukujemy pierwszy wynik z najmniejsza liczba nawiasow
                int min_index = -1;
                for (int i = 0; i < liczba_wyrazen; ++i) {
                    if (wyrazenia[i].value == desired_value && !wyrazenia[i].printed) {
                        if (min_index == -1 || wyrazenia[i].liczba_nawiasow
                                               < wyrazenia[min_index].liczba_nawiasow) {
                            min_index = i;
                        }
                    }
                }

                // wypisujemy ten wynik
                cout << "TAK" << endl;
                cout << wyrazenia[min_index].infix << endl;
                wyrazenia[min_index].printed = true;
            }
            // znak operacji rozny od S i D
        } //else {DEBUG
          //  return 1;
        //}
    }
}
