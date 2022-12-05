using namespace std;
//DEFINICJA STRUKTURY//
struct produkt
{
    char nazwa[256];
    char producent[256];
    double srednica;
    string kategoria;
    int lSztuk;
    double cenajedn;
    double cenazakg;
    string data;
    char uwagi[1000];
//--------------------------//
};
//    --FUNCKJE UZYTKOWE--   //
bool czy_Liczba(const string& s) //SPRAWDZANIE CZY DANY STRING JEST LICZBĄ
{
    try
    {
        std::stod(s);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

bool sprawdzeniedaty(string data)//SPRAWDZANIE CZY DATA JEST ZGODNA ZE STANDARDAMI I DANYM FORMATEM DDMMRRRR
{   

    if (data.length()==0) return true;
    if (data.length()>8) return false;
    if (data.length()<8) return false;
    bool i=all_of(data.begin(),data.end(), ::isdigit);
    if (i==0) return false; 
    int dzien = stoi(data.substr(0, 2));
    int miesiac = stoi(data.substr(2, 2));
    int rok = stoi(data.substr(4, 4));

    const set<int> miesiace31({ 1, 3, 5, 7, 8, 10, 12 });
    const set<int> miesiace30({ 4,6,9,11 });

    bool ret = false;

    if (dzien > 0 && dzien <= 31 && rok < 2023 && rok > 1000)
    {
        // miesiac 31-dniowy
        if (miesiace31.find(miesiac) != miesiace31.end())
        {
            ret = true;
        }
        // miesiac 30-dniowy
        else if (miesiace30.find(miesiac) != miesiace30.end() && dzien < 31)
        {
            ret = true;
        }
        // luty
        else if (miesiac == 2 && dzien <= 29)
        {
            // sprawdzenie czy dzien jest poprawny dla aktualnego typu roku
            if (dzien == 29)
            {
                ret = (rok % 4 == 0);
            }
            else 
            {
                ret = true;
            }
        }
    }
    
    return ret;
}
void dodawanie(produkt& a, map<int, produkt>& baza, int n)//DODAWANIE STRUKTURY DO MAPY
{
    baza.insert(make_pair(n,a));
}
void wypisywanie(map<int, produkt>& baza)//WYPISYWANIE CAŁEJ MAPY
{
        for (size_t index=0; auto& i : baza) {
            cout << index << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).srednica << " " << (i.second).kategoria << " " << (i.second).lSztuk << " " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
            index++;
        }
}
void usuwanie(map<int, produkt>& baza, int index)//USUWANIE DANEGO ID W MAPIE
{
    auto itr=ranges::next(baza.begin(),index);
    if(itr!=baza.end()) baza.erase(itr);
}
void zapisbazy(map<int, produkt> baza)//ZAPIS MAPY(BAZY) DO PLIKU TEKSTOWEGO
{
    fstream bazaplik;
    bazaplik.open("baza.txt", ios::out);
    for(size_t index=0;auto i : baza) {
        bazaplik << index << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).kategoria << " " << (i.second).srednica <<" " << (i.second).lSztuk <<" " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
        index++;
    }
    bazaplik.close();
}
void odczytbazy(map<int, produkt> &baza, produkt &a)//ODCZYTYWANIE BAZY Z PLIKU I ZAPISYWANIE JEJ DO MAPY NA POTRZEBY DZIALANIA PROGRAMU
{
    string line;
    ifstream file("baza.txt",ifstream::in);
   
   
   string zmienne[10]; 
    if(file)
    {
        string i;
        int count = 0;
        while(getline(file, line, '\n'))        
        {
            
            
            
            std::istringstream s(line);
            
            while(s >> i || !s.eof()) {
                if(s.fail())
                {
                    s.clear();
                    std::string temp;
                    s >> temp;
                    continue;
                 }
                else 
                {
                    zmienne[count] = i;
                    ++count;
                    
                    if(count >9)
                    {
                        memcpy(a.nazwa,zmienne[1].data(),zmienne[1].size());
                        memcpy(a.producent,zmienne[2].data(),zmienne[2].size());
                        a.kategoria=zmienne[3];
                        a.srednica=stod(zmienne[4]);
                        a.lSztuk=stoi(zmienne[5]);
                        a.cenajedn=stod(zmienne[6]);
                        a.cenazakg=stod(zmienne[7]);
                        a.data=zmienne[8];
                        memcpy(a.uwagi,zmienne[9].data(),zmienne[9].size());
                        dodawanie(a,baza,stoi(zmienne[0]));
                        count=0;
                    }
                }     
            }
        }
    }
    else 
    {
        cout<<"Plik nie moze zostać odczytany..."<<endl;
    }
    file.close();
}
//----------------------------------------------------------------//

//      --FUNCKJE MENU / DZIAŁANIA PROGRAMU--       //
void Menudodawania(produkt &a)//MENU DODAWANIA DANYCH DO STRUKTURY Z OBSŁUGĄ BŁĘDOW
{
    
    cout<<"Podaj nazwe produktu: ";
    cin.getline(a.nazwa, 256);
    while(strlen(a.nazwa)==0){
        cout<<"Prosze wprowadzic nazwe: ";
        cin.getline(a.nazwa,256);
    }
    cout<<"Podaj nazwe producenta: ";
    cin.getline(a.producent, 256);
    if(strlen(a.producent)==0){
        cout<<"Prosze wprowadzic producenta: ";
        cin.getline(a.producent, 256);
    }
    cout<<"Podaj srednice: ";
    string sr;
    getline(cin, sr);
    //cin.ignore(1000, '\n');
    if (sr.length()!=0){
        while(czy_Liczba(sr)!=true){
            cout<<"Podaj liczbe calkowita lub zmiennoprzecinkowa: ";
            getline(cin, sr);
        }
        a.srednica=stod(sr);
    }
    cout<<"Podaj nazwe kategorii spośrod (sruba / gwozdz / nakretka / zaslepka): ";
    getline(cin, a.kategoria);
    bool kategoria=false;
    while (kategoria==false){
        if (a.kategoria=="sruba" || a.kategoria=="gwozdz" || a.kategoria=="nakretka" || a.kategoria=="zaslepka") kategoria=true;
        else{
            cout<<"Prosze podac spośrod (sruba / gwozdz / nakretka / zaslepka): ";
            getline(cin, a.kategoria);
        }
   
    }
    cout<<"Podaj liczbe sztuk: ";
    while(!(cin>>a.lSztuk)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Zle dane, prosze podaj liczbe sztuk: ";
    }
    cout<<"Podaj cene jednostkowa: ";
    string cJednostkowa;
    cin.ignore(1000, '\n');
    getline(cin, cJednostkowa);
    if (cJednostkowa.length()!=0){
        while(czy_Liczba(cJednostkowa)!=true){
            cout<<"Podaj liczbe calkowita lub zmiennoprzecinkowa: ";
            getline(cin, cJednostkowa);
        }
        a.cenajedn=stod(cJednostkowa);
    }
    else{
        a.cenajedn=0;
    }
    cout<<"Podaj cene za kilogram: ";
    string cKilogram;
    getline(cin, cKilogram);
    if (cKilogram.length()!=0){
        while(czy_Liczba(cKilogram)!=true){
            cout<<"Podaj liczbe calkowita lub zmiennoprzecinkowa: ";
            getline(cin, cKilogram);
        }
        a.cenazakg=stod(cKilogram);
    }
    else{
        a.cenazakg=0;
    }
    cout<<"Podaj date w formacie (ddmmrrrr): ";
    getline(cin, a.data);
    while (sprawdzeniedaty(a.data)==false) //jezeli by nie dzialało to dodać string =0
    {
        cout<<"Podaj date we wlasciwym formacie (ddmmrrr): ";
        getline(cin, a.data);
    }
    if (a.data.length()>0)
    {
        a.data=a.data.insert(2,".").insert(5,".");
    }
    else{
        a.data="brak-daty";
    }
    cout<<"Podaj uwagi dotyczace produktu: ";
    cin.getline(a.uwagi, 1000);
    while (strlen(a.uwagi)==0){
        cout<<"Nie podano uwag, jezeli ich nie masz wpisz 'brak': ";
        cin.getline(a.uwagi, 1000);

    }
    
}

void filtrowanie(map<int, produkt> &baza, string fraza, int wybor)//MENU FILTROWANIA/WYSZUKIWANIA DANYCH W BAZIE
{
    if(wybor == 1)
        {
            cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
            for (size_t index=0;auto& i : baza){
                if((i.second).nazwa==fraza){
                    cout << index << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).srednica << " " << (i.second).kategoria << " " << (i.second).lSztuk << " " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
                }
                index++;
            }
        }  
    if(wybor == 2)
        {
            cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
            for (size_t index=0;auto& i : baza){
                if((i.second).producent==fraza){
                    cout << index << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).srednica << " " << (i.second).kategoria << " " << (i.second).lSztuk << " " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
                }
                index++;
            }
        } 
    if(wybor == 3)
        {
            cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
            if(czy_Liczba(fraza)==false){
                cout<<"Podałes złą daną..."<<endl;
            }
            else{
                for (size_t index=0;auto& i : baza){
                    if((i.second).srednica==stod(fraza)){
                        cout << index << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).srednica << " " << (i.second).kategoria << " " << (i.second).lSztuk << " " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
                    }
                    index++;
                }
            }
        }
    if(wybor == 4)
        {
            cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
            for (size_t index=0;auto& i : baza){
                if((i.second).kategoria==fraza){
                    cout << index << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).srednica << " " << (i.second).kategoria << " " << (i.second).lSztuk << " " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
                }
                index++;
            }
        }
    if(wybor == 5)
        {
            cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
            if(czy_Liczba(fraza)==false){
                cout<<"Podałes złą daną..."<<endl;
            }
            else{
                for (size_t index=0;auto& i : baza){
                    if((i.second).lSztuk==stoi(fraza)){
                        cout << index << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).srednica << " " << (i.second).kategoria << " " << (i.second).lSztuk << " " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
                    }
                    index++;
                }
            }
        }
    if(wybor == 6)
        {
            cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
            if(czy_Liczba(fraza)==false){
                cout<< "Podałes złą daną..."<<endl;
            }
            else{
                for (size_t index=0;auto& i : baza){
                    if((i.second).cenajedn==stod(fraza)){
                        cout << index << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).srednica << " " << (i.second).kategoria << " " << (i.second).lSztuk << " " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
                    }
                    index++;
                }
            }
        }
    if(wybor == 7)
        {
            cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
            if(czy_Liczba(fraza)==false){
                cout<< "Podałes złą daną..."<<endl;
            }
            else{
                for (size_t index=0;auto& i : baza){
                    if((i.second).cenazakg==stod(fraza)){
                        cout << index << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).srednica << " " << (i.second).kategoria << " " << (i.second).lSztuk << " " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
                    }
                    index++;
                }
            }
        }
    if(wybor == 8)
        {
            cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
            for (size_t index=0;auto& i : baza){
                if((i.second).data==fraza){
                    cout << index << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).srednica << " " << (i.second).kategoria << " " << (i.second).lSztuk << " " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
                }
                index++;
            }
        }
    if(wybor == 8)
        {
            cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
            fraza=fraza.insert(2,".").insert(5,".");
            for (size_t index=0;auto& i : baza){
                if((i.second).data==fraza){
                    cout << index << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).srednica << " " << (i.second).kategoria << " " << (i.second).lSztuk << " " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
                }
                index++;
            }
        }
    
}

void gMenu(map<int, produkt> &baza, produkt &a)//MENU GŁOWNE, W KTORE SCALA DZIALANIE CALEGO PROGRAMU
{
bool opened=true;
int mapIterator=baza.size();

while(opened==true){
    system("clear");
    cout<<"1.Wyświetl listę\n2.Dodaj produkt\n3.Edycja danych w bazie\n4.Usuwanie danych\n5.Wyszukaj/filtruj po wartości\n6.Wyszukiwanie po wyrazeniach regularnych\n7.Zakmnij program"<<endl;
    cout<<"Twoj wybor: ";
    string w;
    getline(cin, w);
    while (czy_Liczba(w)==0){
        cout<<"Podaj liczbę, a nie wyraz: ";
        getline(cin,w);
    }
    int wybor;
    wybor=stoi(w);
        switch(wybor){
            case 1:
                system("clear");
                cout<<"BAZA DANYCH"<<endl;
                cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
                wypisywanie(baza);
                cout<<"Jezeli chcesz wyjść z podglądu kliknij enter: ";
                cin.ignore();
                break;
            case 2:
                {   
                    system("clear");
                    cout<<"DODAWANIE PRODUKTU"<<endl;
                    produkt a;
                    bool add=true;
                    string choice;
                    while(add==true){
                        Menudodawania(a);
                        mapIterator++;
                        dodawanie(a, baza, mapIterator);
                        cout<<"Jezeli chcesz prowadzić następną pozycję w bazie wpisz 'T' i zatwierdź enterem: ";
                        getline(cin, choice);
                        if (choice=="T"){
                            continue;
                        }
                        else{
                            add=false;
                        }

                    }
                    zapisbazy(baza);
                }
                
                
                system("clear");
                break;
            case 3:
            {
                baza.clear();
                odczytbazy(baza, a);
                if (baza.size()==0){
                        cout<<endl;
                        cout<<"Najpierw musisz wprowadzić dane do bazy..."<<endl;
                        cin.ignore();
                        break;
                    }
                system("clear");
                cout<<"EDYCJA DANYCH"<<endl;
                cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
                wypisywanie(baza);
                string wannaEdit;
                int id;
                cout<<"Podaj ID produktu, ktory chcesz edytować: ";
                while(!(cin>>id) || id>baza.size()-1){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout<<"Podaj liczbę z zakresu ID w bazie: ";
                }
                    system("clear");
                    cout<<"EDYCJA DANYCH"<<endl;
                    cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
                    cout<<"1. Nazwa\n2. Producent\n3. Średnica\n4. Kategoria\n5. Liczba Sztuk\n6. Cena jednostkowa\n7. Cena za kilogram\n8. Data\n9.Uwagi"<<endl;
                    cout<<endl;
                    cout<<"Wybierz numer danej, ktorą chcesz edytować... "<<endl;
                    cout<<"Jezeli zmieniłeś zdanie kliknij enter: ";
                    cin.ignore(1000, '\n');
                    getline(cin, wannaEdit);
                    if (wannaEdit.length()==0){
                        break;
                    }
                    while (czy_Liczba(wannaEdit)==false || stoi(wannaEdit)<1 ||stoi(wannaEdit)>9)
                    {
                       cout<<"Podaj liczbę z zakresu 1-9: ";
                       getline(cin, wannaEdit);
                    }
                    int wannabenumber = stoi(wannaEdit);
                    if(wannabenumber == 1)
                    {
                        cout << "Podaj nowa wartosc:";
                        cin.getline(baza[id].nazwa, 256);
                        while(strlen(baza[id].nazwa)==0){
                            cout<<"Prosze wprowadzic nazwe: ";
                            cin.getline(baza[id].nazwa, 256);
                        }
                    }
                    if(wannabenumber == 2)
                    {
                        cout << "Podaj nowa wartosc:";
                        cin.getline(baza[id].producent, 256);
                        while(strlen(baza[id].producent)==0){
                            cout<<"Prosze wprowadzic nazwe: ";
                            cin.getline(baza[id].producent, 256);
                        }
                    }
                    if(wannabenumber == 3)
                    {
                        string editSrednica;
                        cout << "Podaj nowa wartosc:";
                        getline(cin, editSrednica);
                        if (editSrednica.length()!=0){
                            while(czy_Liczba(editSrednica)!=true){
                                cout<<"Podaj liczbe calkowita lub zmiennoprzecinkowa: ";
                                getline(cin, editSrednica);
                            }
                            double temp=stod(editSrednica);
                        baza[id].srednica = temp;
                    }
                    }
                    if(wannabenumber == 4)
                    {
                        string editKategoria;
                        cout << "Podaj kategorie:";
                        getline(cin, editKategoria);
                        while (editKategoria.length()==0){
                            cout<<"Prosze podac kategorie: ";
                            cin.ignore(1000, '\n');
                            getline(cin, editKategoria);
                        }
                        baza[id].kategoria = editKategoria;
                    }
                    if(wannabenumber == 5)
                    {
                        int editLSztuk;
                        cout << "Podaj liczbę sztuk:";
                        while(!(cin>>editLSztuk)){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout<<"Zle dane, prosze podaj liczbe sztuk: ";
                    }
                        baza[id].lSztuk = editLSztuk;
                    }
                    if(wannabenumber == 6)
                    {
                        cout<<"Podaj cene jednostkowa: ";
                        string editCJEDNOSTKOWA;
                        getline(cin, editCJEDNOSTKOWA);
                        if (editCJEDNOSTKOWA.length()!=0){
                            while(czy_Liczba(editCJEDNOSTKOWA)!=true){
                                cout<<"Podaj liczbe calkowita lub zmiennoprzecinkowa: ";
                                getline(cin, editCJEDNOSTKOWA);
                            }
                        }
                        double temp=stod(editCJEDNOSTKOWA);
                        baza[id].cenajedn = temp;
                    }
                    if(wannabenumber == 7)
                    {
                        cout<<"Podaj cene za kilogram: ";
                        string editCenaZaKg;
                        getline(cin, editCenaZaKg);
                        if (editCenaZaKg.length()!=0){
                            while(czy_Liczba(editCenaZaKg)!=true){
                                cout<<"Podaj liczbe calkowita lub zmiennoprzecinkowa: ";
                                getline(cin, editCenaZaKg);
                            }
                            double temp=stod(editCenaZaKg);
                            baza[id].cenazakg = temp;
                        }
                    }
                    if(wannabenumber == 8)
                    {
                        string editData;
                        cout<<"Podaj date w formacie (ddmmrrrr): ";
                        getline(cin, editData);
                        while (sprawdzeniedaty(editData)==false) //jezeli by nie dzialało to dodać string =0
                        {
                            cout<<"Podaj date we wlasciwym formacie (ddmmrrr): ";
                            getline(cin, editData);
                        }
                        if (editData.length()>0)
                        {
                            editData=editData.insert(2,".").insert(5,".");
                        }
                        else{
                            editData="-1";
                        }
                        baza[id].data=editData;
                    }
                    if(wannabenumber==9){
                        
                        cout<<"Podaj uwagi: ";
                        cin.getline(baza[id].uwagi, 256);
                        while(strlen(baza[id].uwagi)==0){
                            cout<<"Prosze wprowadzic uwagi: ";
                            cin.getline(baza[id].uwagi, 256);
                        }

                    }
                zapisbazy(baza);
                break;

            }
                break;
            case 4:
            {
                system("clear");
                cout<<"USUWANIE DANYCH"<<endl;
                cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
                wypisywanie(baza);
                int toDeleteID;
                cout<<"Podaj ID produktu, ktory chcesz edytować: ";
                while(!(cin>>toDeleteID)){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout<<"Podaj liczbę z zakresu ID w bazie: ";
                }
                usuwanie(baza, toDeleteID);
                zapisbazy(baza);
                break;
            }
                
            case 5:
            {
                string wyb;
                string f;
                system("clear");
                cout<<"FILTROWANIE/WYSZUKIWANIE"<<endl;
                cout<<"1. Nazwa\n2. Producent\n3. Średnica\n4. Kategoria\n5. Liczba Sztuk\n6. Cena jednostkowa\n7. Cena za kilogram\n8. Data"<<endl;
                cout<<"Podaj numer po ktorym chcesz filtrować: ";
                getline(cin,wyb);
                while (czy_Liczba(wyb)==false || stoi(wyb)<1 ||stoi(wyb)>8)
                    {
                       cout<<"Podaj liczbę z zakresu 1-8: ";
                       getline(cin, wyb);
                    }
                    int w = stoi(wyb);
                cout<<"Podaj frazę po ktorej chcesz filtrować: ";
                getline(cin,f);
                system("clear");
                filtrowanie(baza,f,w);
                cin.ignore();
            break;
            }
                
            case 6:
            {
                string wybor;
                system("clear");
                cout<<"WYSZUKIWANIE PO WYRAZENIACH REGULARNYCH"<<endl;
                cout<<"1.Nazwa\n2.Producent\n3.Data"<<endl;
                cout<<"Podaj numer zmiennej, po ktorej chcesz szukać... "<<endl;
                cout<<"Jezeli sie rozmysliles, kliknij enter: ";
                getline(cin, wybor);
                if (wybor.length()==0){
                        break;
                    }
                    while (czy_Liczba(wybor)==false || stoi(wybor)<1 ||stoi(wybor)>3)
                    {
                        cout<<"Podaj poprawną wartość 1-3: ";
                        getline(cin, wybor);
                    }
                string wyrRegularne;
                if (wybor=="1"){
                    cout<<"Podaj wyrazenie regularne, ktorego chcesz uzyć: ";
                    getline(cin, wyrRegularne);
                    regex wyr (wyrRegularne);
                    system("clear");
                    cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
                    for (int index = 0;auto& i : baza){
                        if (regex_match((i.second).nazwa, wyr)==true){
                            cout << index << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).srednica << " " << (i.second).kategoria << " " << (i.second).lSztuk << " " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
                            index++;
                        }    
                         
                    }
                    cout<<endl;
                    cout<<"Wyrazenie uzyte w nazwie: "<<wyrRegularne<<endl;
                    cout<<"Kliknij enter, aby wyjść z podglądu: ";
                    cin.ignore();
                }
                if (wybor=="2"){
                    cout<<"Podaj wyrazenie regularne, ktorego chcesz uzyć: ";
                    getline(cin, wyrRegularne);
                    regex wyr (wyrRegularne);
                    system("clear");
                    cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
                    for (int index=0;auto& i : baza){
                        if (regex_match((i.second).producent, wyr)==true){
                            cout << i.first << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).srednica << " " << (i.second).kategoria << " " << (i.second).lSztuk << " " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
                            index++;
                        }
                    }
                    cout<<endl;
                    cout<<"Wyrazenie uzyte w producencie: "<<wyrRegularne<<endl;
                    cout<<"Kliknij enter, aby wyjść z podglądu: ";
                    cin.ignore();
                }
                if (wybor=="3"){
                    cout<<"Proszę uwzględnić format daty DD.MM.RRRR..."<<endl;
                    cout<<"Podaj wyrazenie regularne, ktorego chcesz uzyć: ";
                    getline(cin, wyrRegularne);
                    regex wyr (wyrRegularne);
                    system("clear");
                    cout<<"ID | NAZWA | PRODUCENT | ŚREDNICA | KATEGORIA | LICZBA SZTUK | CENA JED. | CENA KG | DATA | UWAGI"<<endl;
                    for (int index=0;auto& i : baza){
                        if (regex_match((i.second).data, wyr)==true){
                            cout << i.first << " " << (i.second).nazwa << " " << (i.second).producent << " " << (i.second).srednica << " " << (i.second).kategoria << " " << (i.second).lSztuk << " " << (i.second).cenajedn << " " << (i.second).cenazakg << " " << (i.second).data << " " <<  (i.second).uwagi << endl;
                            index++;
                        }
                        
                    }
                    cout<<endl;
                        cout<<"Wyrazenie uzyte: "<<wyrRegularne<<endl;
                        cout<<"Kliknij enter, aby wyjść z podglądu: ";
                        cin.ignore();
                }


            break;
            }
            case 7:
                opened=false;
                zapisbazy(baza);
                baza.clear();
                break;

            default:
                system("clear");
                cout<<"Proszę podać liczbe z zakresu 1-7: "<<endl;

                break;

        }
    }


}
//------------------------------------------------------------------------------------//
