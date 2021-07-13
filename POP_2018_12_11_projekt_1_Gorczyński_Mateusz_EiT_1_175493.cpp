//POP_2018_12_11_projekt_1_Gorczyñski_Mateusz_EiT_1_175493 Visual C++ 2017

#include<iostream>
#include<ctime>
#include<cmath>
#include<cstdlib>


using namespace std;


#define M_PI       3.14159265358979323846 //potrzebujemy wartoœci liczby pi, aby obliczyæ sinus podwojonego k¹ta


void tura_gracz1(char *plansza, char *oznaczeniapol, int gracz1, int gracz2); //tury trzeba zdefiniowaæ na pocz¹tku kodu, gdy¿ inaczej, by³by problem z ich dzia³aniem


void tura_gracz2(char *plansza, char *oznaczeniapol, int gracz1, int gracz2);


void tura_komputer(char *plansza, char *oznaczeniapol, int gracz1, int gracz2);


void pauza(int sekundy)
{
	clock_t czekanie;
	czekanie = clock() + sekundy * CLOCKS_PER_SEC; //jako¿, ¿e nie mo¿emy uzywaæ bibloiteki windows.h, w której jest funkcja sleep, trzeba utworzyæ w³asn¹ wersje dzia³aj¹c¹ podobnie
	while( clock() < czekanie) {}
}


void wyswietlanie_planszy(char *plansza, char *oznaczeniapol)
{
	for (int i = 0; i < 10; i++)
		cout << " " << plansza[i]; //setw(2) powoduje ,¿e plansza wygl¹da czytelnie, dziêki odstêpom
	cout << " "  << "|"; //podzielenie planszy na pó³ 

	for (int i = 10; i < 20; i++)
		cout << " "  << plansza[i];
	cout << endl;

	for (int i = 0; i < 10; i++)
		cout << " "  << oznaczeniapol[i];
	cout << " "  << "|"; //analogicznie, dla oznaczeñ pól planszy

	for (int i = 10; i < 20; i++)
		cout << " "  << oznaczeniapol[i];
	cout << endl;
}


void koniec_gry(int zwyciezca)
{
	cout << "KONIEC GRY" << endl;
	cout << "Wygrywa gracz" << zwyciezca << endl;
	pauza(5);
}


void koniec_gry_komputer()
{
	cout << "KONIEC GRY" << endl;
	cout << "Wygrywa komputer" << endl;
	pauza(5);
}


double obliczanie_strzalu(double predkosc, double kat)
{
	double strzal;
	double predkosc2;
	double sinuspodwojonegokata;
	double g = 10;

	kat = kat * (M_PI / 180); //zamiana katow na radiany

	predkosc2 = predkosc * predkosc;
	sinuspodwojonegokata = sin(kat * 2);
	strzal = (predkosc2*sinuspodwojonegokata) / g; //wzor na dlugosc rzutu ukosnego, przyjalem ze jedno pole to jeden metr, a jedna tura to jedna sekunda

	return strzal;
}


int losowanie_ktozaczyna()
{
	int gracz;

	srand(time(NULL));
	gracz = rand() % 2 + 1; //losowanie liczby 1 lub 2, w zaleznosci od wartosci bedzie gral gracz 1 lub 2

	return gracz;
}


int generowanie_wiatru()
{
	int wiatr;


	srand(time(NULL));
	wiatr = rand() % 4 - 2; //losowanie liczby z zakresu od -2 do 2

	return wiatr;
}


void wyswietlanie_wiatru(int wiatr)
{
	int wiatrzkierunkiem;

	if (generowanie_wiatru() < 0)
	{
		wiatrzkierunkiem = (-1)*generowanie_wiatru();
		cout << "Wiatr: " << wiatrzkierunkiem << "L" << endl;
	}

	else if (generowanie_wiatru() > 0)
	{
		wiatrzkierunkiem = generowanie_wiatru();
		cout << "Wiatr: " << wiatrzkierunkiem << "P" << endl;
	}

	else cout << "Brak wiatru w tej turze!" << endl;

}


void tura_gracz2(char *plansza, char *oznaczeniapol, int gracz1, int gracz2)
{
	wyswietlanie_planszy(plansza, oznaczeniapol);

	int wiatr = generowanie_wiatru();
	wyswietlanie_wiatru(wiatr);

	double predkosc,strzal,kat;
	cout << "Kolej gracza 2" << endl;
	cout << "Podaj parametry strzalu: " << endl;
	cout << "Predkosc pocisku: ";
	cin >> predkosc;
	cout << "Kat strzalu (w stopniach): ";
	cin >> kat;

	strzal = obliczanie_strzalu(predkosc, kat);

	double cel = (strzal*(-1)) + gracz2;
	int zaokraglenie = round(cel) + wiatr;

	if (zaokraglenie == gracz1) koniec_gry(2);
	else
	{
		if (zaokraglenie < 20 && zaokraglenie >= 0) cout << "Trafiles w pole: " << oznaczeniapol[zaokraglenie] << endl; //program podaje pole, w ktore trafil gracz
		else if (zaokraglenie < 0 || zaokraglenie >=20) cout << "Trafiles poza plansze!" << endl; //jezeli 

		pauza(3);
		system("CLS");

		tura_gracz1(plansza, oznaczeniapol, gracz1, gracz2);
	}
}


void tura_gracz1(char *plansza, char *oznaczeniapol, int gracz1, int gracz2)
{
	wyswietlanie_planszy(plansza, oznaczeniapol);
	int wiatr = generowanie_wiatru();
	wyswietlanie_wiatru(wiatr);

	double predkosc, strzal, kat;
	cout << "Kolej gracza 1" << endl;
	cout << "Podaj parametry strzalu: " << endl;
	cout << "Predkosc pocisku: ";
	cin >> predkosc;
	cout << "Kat strzalu (w stopniach): ";
	cin >> kat;

	strzal = obliczanie_strzalu(predkosc, kat);

	double cel = gracz1 + strzal;
	int zaokraglenie = round(cel) + wiatr;

	if (zaokraglenie == gracz2) koniec_gry(1);
	else
	{
		if (zaokraglenie < 20 && zaokraglenie >= 0) cout << "Trafiles w pole: " << oznaczeniapol[zaokraglenie] << endl; //wypisujemy pole, w które trafiliœmy
		else if (zaokraglenie >= 21) cout << "Trafiles poza plansze!" << endl;

		pauza(3);
		system("CLS");

		tura_gracz2(plansza, oznaczeniapol, gracz1, gracz2);
	}
}


void tura_gracz(char *plansza, char *oznaczeniapol, int gracz1, int gracz2)
{
	wyswietlanie_planszy(plansza, oznaczeniapol);
	int wiatr = generowanie_wiatru();
	wyswietlanie_wiatru(wiatr);

	double predkosc, strzal, kat;
	cout << "Kolej gracza 1" << endl;
	cout << "Podaj parametry strzalu: " << endl;
	cout << "Predkosc pocisku: ";
	cin >> predkosc;
	cout << "Kat strzalu (w stopniach): ";
	cin >> kat;

	strzal = obliczanie_strzalu(predkosc, kat);

	double cel = gracz1 + strzal;
	int zaokraglenie = round(cel) + wiatr;

	if (zaokraglenie == gracz2) koniec_gry(1);
	else
	{
		if (zaokraglenie < 20 && zaokraglenie >= 0) cout << "Trafiles w pole: " << oznaczeniapol[zaokraglenie] << endl;
		else if (zaokraglenie >= 21) cout << "Trafiles poza plansze!" << endl;

		pauza(3);
		system("CLS");

		tura_komputer(plansza, oznaczeniapol, gracz1, gracz2);
	}
}


void tura_komputer(char *plansza, char *oznaczeniapol, int gracz1, int gracz2)
{
	wyswietlanie_planszy(plansza, oznaczeniapol);
	int wiatr = generowanie_wiatru();
	wyswietlanie_wiatru(wiatr);

	cout << "Kolej komputera" << endl;
	cout << "komputer mysli....." << endl;

	srand(time(NULL));
	pauza(3);

	cout << "Podaj parametry strzalu: " << endl;
	cout << "Predkosc pocisku: ";
	double predkosc = rand() % 20;
	cout << predkosc << endl;
	cout << "Kat strzalu (w stopniach): ";
	double kat = rand() % 60;
	cout << kat << endl;

	double strzal = obliczanie_strzalu(predkosc, kat);
	double cel = (strzal*(-1)) + gracz2;
	int zaokraglenie = round(cel) + wiatr;

	if (zaokraglenie == gracz1) koniec_gry_komputer();
	else
	{
		if (zaokraglenie < 20 && zaokraglenie >= 0) cout << "Komputer trafia w pole: " << oznaczeniapol[zaokraglenie] << endl;
		else if (zaokraglenie < 0) cout << "Komputer trafia poza plansze!" << endl;

		pauza(3);
		system("CLS");

		tura_gracz(plansza, oznaczeniapol, gracz1, gracz2);
	}
}


int generowanie_gracz1()
{
	int gracz1;
	gracz1 = rand() % 9;  //generowanie pozycji  gracza nr 1

	return gracz1;
}


int generowanie_gracz2()
{
	int gracz2;
	gracz2 = rand() % 9 + 10; // generowanie pozycji gracza nr 2

	return gracz2;
}


void gra_wielugraczy()
{
	char plansza[20] = { '-','-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' }; //generujemy tablice, ktora bedzie nasza plansza
	char oznaczeniapol[20] = { 'A', 'B' ,'C' , 'D', 'E', 'F','G','H','I', 'J', 'K', 'L' , 'M' , 'N', 'O', 'P', 'Q', 'R', 'S', 'T' }; // oraz oznaczenia pol tej planszy
	cout << "wybrano gre dla dwoch graczy." << endl;

	int gracz1 = generowanie_gracz1(); //podobnie jak w grze dla jednego gracza ustawiamy poczatkowe pozycje
	int gracz2 = generowanie_gracz2();

	plansza[gracz1] = '#'; //na pozycji gracza zamiast znaku '-' bedzie '#'
	plansza[gracz2] = '#';

	if (losowanie_ktozaczyna() == 1) //losowanie zaczynajacego gracza
	{
		cout << "gre rozpocznie gracz1! " << endl;
		tura_gracz1(plansza, oznaczeniapol, gracz1, gracz2);
	}
	else
	{
		cout << "gre rozpocznie gracz2! " << endl;
		tura_gracz2(plansza, oznaczeniapol, gracz1, gracz2);
	}

}


void gra_jedengracz() //konfiguracja gry dla jednego gracza
{
	char plansza[20] = { '-','-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' }; //generujemy tablice, ktora bedzie nasza plansza
	char oznaczeniapol[20] = { 'A', 'B' ,'C' , 'D', 'E', 'F','G','H','I', 'J', 'K', 'L' , 'M' , 'N', 'O', 'P', 'Q', 'R', 'S', 'T' }; // oraz oznaczenia pol tej planszy
	cout << "wybrano gre dla jednego gracza." << endl;

	int gracz1 = generowanie_gracz1(); //gracz1 to adres elementu tablicy, na ktorym spawnujemy gracza 1
	int gracz2 = generowanie_gracz2(); //analogicznie do gracza 1

	plansza[gracz1] = '#'; //na pozycji gracza zamiast znaku '-' bedzie '#'
	plansza[gracz2] = '#';

	if (losowanie_ktozaczyna() == 1) //losowanie zaczynajacego gracza
	{
		cout << "gre rozpocznie gracz1! " << endl;
		tura_gracz(plansza, oznaczeniapol, gracz1, gracz2);
	}
	else
	{
		cout << "gre rozpocznie komputer! " << endl;
		tura_komputer(plansza, oznaczeniapol, gracz1, gracz2);
	}

}


int wybor_menu() //wybieramy jedna z kilku opcji, ktore sie wykonaja
{
	int wybor;
	cin >> wybor;
	switch (wybor)
	{
	case 1:
	{
		system("CLS");
		gra_jedengracz();
		break; //odpala gre dla jednego gracza
	}
	case 2:
	{
		system("CLS");
		gra_wielugraczy();
		break; //odpala gre dla wielugraczy
	}
	case 3:
	{
		return 0; //konczy program
	}
	default:
	{
		cout << "podales nieprawidlowe dane!" << endl; //jezeli uzytkownik poda nieprawidlowe dane, wyswietla komunikat
		break;
	}
	}
}


void menu_glowne()
{
	srand(time(NULL));
	cout << "############################################################" << endl; //interfejs menu glownego
	cout << "#                                                          #" << endl;
	cout << "#                   Witaj w grze Scorch!                   #" << endl;
	cout << "#                                                          #" << endl;
	cout << "############################################################" << endl;
	cout << "#                                                          #" << endl;
	cout << "#                                                          #" << endl;
	cout << "#                       Menu Glowne:                       #" << endl;
	cout << "#                                                          #" << endl;
	cout << "#                 1 - gra z komputerem                     #" << endl;
	cout << "#                                                          #" << endl;
	cout << "#                 2 - gra na dwoch graczy                  #" << endl;
	cout << "#                                                          #" << endl;
	cout << "#                 3 - wyjscie                              #" << endl;
	cout << "#                                                          #" << endl;
	cout << "#                                                          #" << endl;
	cout << "############################################################" << endl;
	wybor_menu(); //przechodzimy do wyboru opcji
}


int main()
{
	menu_glowne(); //wywolujemy menu glowne

	return 0;
}