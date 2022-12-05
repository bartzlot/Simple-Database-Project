#include "b.h"
#include "f.h"
// #include "fUzytkowe.h"
using namespace std;
int main()
{

    map <int, produkt> baza;
    produkt a;
    odczytbazy(baza,a);
    gMenu(baza,a);
}
