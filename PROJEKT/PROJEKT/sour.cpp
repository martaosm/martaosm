#include "Nag.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

void pobierz_dane()//funkcja pyta sie o dane klienta i zapisuje je do pliku
{
	string imie, nazwisko,linia;
	int lin = 2;
	int a = 1;
	cout << "Prosze podac swoje imie i nazwisko: ";
	cin >> imie >> nazwisko;
	fstream dec;
	dec.open("decyzja.txt", ios::out);
	if (dec.good() == false)
	{
		cout << "Nie udalo sie otworzyc pliku!";
		exit(0);
	}
	dec << imie << " " << nazwisko << endl;
	dec.close();
}
int pobierz_ilosc()//pobieranie z pliku ilosci ofert w bazie danych
{
	string linia;
	fstream plik;
	plik.open("ilosc_ofert.txt", ios::in);
	if (plik.good() == false)
	{
		cout << "Nie udalo sie otworzyc pliku!";
		exit(0);
	}
	getline(plik, linia);
	int ilosc = stoi(linia);
	plik.close();
	return ilosc;
}
void zwieksz_ilosc(int num)//jesli jest taka potrzeba funkcja zwieksza ilosc ofert i zapisuje do pliku nowa liczbe
{
	num = num + 1;
	fstream plik;
	plik.open("ilosc_ofert.txt", ios::out);
	if (plik.good() == false)
	{
		cout << "Nie udalo sie otworzyc pliku!";
		exit(0);
	}
	plik << num;
	plik.close();
}
int ile_hoteli()//funkcja oblicza ile obecnie jest hoteli w bazie danych
{
	string linia;
	fstream plik;
	plik.open("hotele.txt", ios::in);
	if (plik.good() == false)
	{
		cout << "Nie udalo sie otworzyc pliku!";
		exit(0);
	}
	int nr = 0;
	while (getline(plik, linia))
	{
		nr++;
	}
	nr = nr / 4;
	return nr;
}
char* kraj::wczytaj(int r)//funkcja odczytuje z pliku potrzebne informacje i zwraca je 
{
	string ilosc, linia, nazwaa;
	fstream plik;
	plik.open("oferty.txt", ios::in);
	if (plik.good() == false)
	{
		cout << "Nie udalo sie otworzyc pliku!";
		exit(0);
	}
	int nr_linii = 1 + r;
	int akt_nr = 1;
	while (getline(plik, linia))
	{
		if (akt_nr == nr_linii)nazwaa = linia;
		akt_nr++;
	}
	nazwa = new char[nazwaa.length() + 1];
	strcpy(nazwa, nazwaa.c_str());
	plik.close();
	return nazwa;
}
int hotel::wczytaj(int nr_linii,char* _kraj,  int budget,int x)//wypisywanie informacji na temat hoteli
{
	int suma = 0;
	string koszt, krajj,gwiazdki,linia;
	fstream plik;
	plik.open("hotele.txt", ios::in);
	if (plik.good() == false)
	{
		cout << "Nie udalo sie otworzyc pliku!";
		exit(0);
	}
	int akt_nr = 1;
	while (getline(plik, linia))
	{
		if (akt_nr == nr_linii)krajj = linia;
		if (akt_nr == nr_linii + 1)nazwa = linia;
		if (akt_nr == nr_linii + 2)koszt = linia;
		if (akt_nr == nr_linii + 3)gwiazdki = linia;
		akt_nr++;
	}
	kraj1 = new char[krajj.length() + 1];
	strcpy(kraj1, krajj.c_str());
	koszt_za_noc = stoi(koszt);
	ilosc_gwiazdek = stoi(gwiazdki);
	if (strncmp(kraj1,_kraj,5)==0)
	{
		if (koszt_za_noc <= budget)
		{
			cout << x << "." <<  nazwa << "    koszt za noc: " << koszt_za_noc << "    ilosc gwiazdek: " << ilosc_gwiazdek << endl;
			suma++;
		}
		else
		{
			cout << "Niestety " << nazwa << " nie miesci sie w twoim budzecie." << endl;
		}
	}
	plik.close();
	return suma;
}
int ile_pokoi()//pobieranie z pliku informacji o ilosci pokoi
{
	string linia;
	fstream pok;
	pok.open("ilosc_r_pokoi.txt", ios::in);
	if (pok.good() == false)
	{
		cout << "Nie udalo sie otworzyc pliku!";
		exit(0);
	}
	getline(pok, linia);
	const int ilosc = stoi(linia);
	return ilosc;
}
void zwieksz_iloscp(int num)//funkcja zwieksza ilosc pokoi i zapisuje liczbe do pliku
{
	num = num + 1;
	fstream plik;
	plik.open("ilosc_r_pokoi.txt", ios::out);
	if (plik.good() == false)
	{
		cout << "Nie udalo sie otworzyc pliku!";
		exit(0);
	}
	plik << num;
	plik.close();
}
void pokoj::wypisz_p(int nr)//funkcja odczytuje z pliku informacje o pokojach
{
	string linia;
	fstream pokoje;
	pokoje.open("pokoje.txt", ios::in);
	if (pokoje.good() == false)
	{
		cout << "Nie udalo sie otworzyc pliku!";
		exit(0);
	}
	string osoby, dopl;
	int akt = 1;
	while (getline(pokoje, linia))
	{
		if (akt == nr)nazwa = linia;
		if (akt == nr + 1)osoby = linia;
		if (akt == nr + 2)dopl = linia;
		akt++;
	}
	ilu_osobowy = stoi(osoby);
	doplata = stoi(dopl);
	pokoje.close();
}
void opcja1()//funkcja dodaje nowy hotel do pliku, je¿eli znajduje siê on w kraju, którego nie ma w bazie to dopisuje go i zwieksza liczbe ofert
{
	int num=pobierz_ilosc();
	int r = 1;
	int wybor;
	kraj** tab = new kraj * [num];
	for (int i = 0; i < num; i++)
	{
		tab[i] = new kraj;
		tab[i]->nazwa = tab[i]->wczytaj(r);
		r++;
	}
	cout << "W ktorym kraju znajduje sie nowy hotel?" << endl;
	for (int i = 0; i < num; i++)
	{
		cout << i + 1 << "." << tab[i]->nazwa << endl;
	}
	cout << num + 1 << ".Inny kraj" << endl;
	cout << "Wybor: ";
	cin >> wybor;
	if (wybor <= num)
	{
		fstream newhot;
		newhot.open("hotele.txt", ios::app);
		if (newhot.good() == false)
		{
			cout << "Nie udalo sie otworzyc pliku!";
			exit(0);
		}
		newhot << tab[wybor - 1]->nazwa << endl;
		string nazwa;
		int koszt, iloscg;
		cout << "Nazwa: ";
		cin.ignore();
		getline(cin, nazwa);
		cout << "Koszt za noc: ";
		cin >> koszt;
		cout << "Ilosc gwiazdek: ";
		cin >> iloscg;
		newhot << nazwa << endl << koszt << endl << iloscg << endl;
		newhot.close();
	}
	if (wybor == num + 1)
	{
		string nowy;
		cout << "Kraj: ";
		cin.ignore();
		getline(cin, nowy);
		fstream plik;
		plik.open("oferty.txt", ios::app);
		plik << nowy << endl;
		fstream newhot;
		newhot.open("hotele.txt", ios::app);
		if (newhot.good() == false)
		{
			cout << "Nie udalo sie otworzyc pliku!";
			exit(0);
		}
		newhot << nowy << endl;
		string nazwa;
		int koszt, iloscg;
		cout << "Nazwa: ";
		cin.ignore();
		getline(cin, nazwa);
		cout << "Koszt za noc: ";
		cin >> koszt;
		cout << "Ilosc gwiazdek: ";
		cin >> iloscg;
		newhot << nazwa << endl << koszt << endl << iloscg << endl;
		newhot.close();
		zwieksz_ilosc(num);
	}
	delete[] tab;
}
void opcja3()//funkcja dodaje nowy pokoj i zwieksza liczbe w pliku 
{
	string nazwa;
	int osoby, doplata;
	cout << "Nazwa: ";
	cin.ignore();
	getline(cin, nazwa);
	cout << "Ilosc osob w pokoju: ";
	cin >> osoby;
	cout << "Doplata: ";
	cin >> doplata;
	fstream plik;
	plik.open("pokoje.txt", ios::app);
	if (plik.good() == false)
	{
		cout << "Nie udalo sie otworzyc pliku!";
		exit(0);
	}
	plik << nazwa << endl << osoby << endl << doplata << endl;
	plik.close();
	int num = ile_pokoi();
	zwieksz_iloscp(num);
}