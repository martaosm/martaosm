#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

class miejsce
{
public:
	char* nazwa;
	int id;
	miejsce() :nazwa(new char[10]), id(0)
	{
		strcpy(nazwa, "...");
	}
	virtual char* wczytaj(int r) = 0;
	virtual ~miejsce() {};
};
class kraj :public miejsce
{
public:
	char* nazwa;
	int id;
	kraj() :nazwa(new char[10]), id(0)
	{
		strcpy(nazwa, "...");
	}
	kraj(const char* _nazwa, int _id) :nazwa(new char[strlen(_nazwa) + 1]), id(_id)
	{
		strcpy(nazwa, _nazwa);
	}
	char* wczytaj(int r);
	~kraj()
	{
		//cout << "Destruktor kraj" << endl;
		delete[] nazwa;
	}
};
class hotel
{
public:
	char* kraj1;
	string nazwa;
	int koszt_za_noc;
	int ilosc_gwiazdek;
	hotel()
	{
		kraj1 = new char[10];
		strcpy(kraj1, "...");
		nazwa = "...";
		koszt_za_noc = 0;
		ilosc_gwiazdek = 0;
	}
	hotel(const char* _kraj, string _nazwa, int _koszt, int _ilosc) :kraj1(new char[strlen(_kraj) + 1]), nazwa(_nazwa), koszt_za_noc(_koszt), ilosc_gwiazdek(_ilosc)
	{
		strcpy(kraj1, _kraj);
	}
	int wczytaj(int r, char* _kraj, int budget, int x);
	~hotel()
	{
		//cout << "Destruktor hotel" << endl;
		delete[] kraj1;
	}
};
class pokoj
{
public:
	string nazwa;
	int ilu_osobowy;
	int doplata;
	pokoj()
	{
		nazwa = "...";
		ilu_osobowy = 0;
		doplata = 0;
	}
	pokoj(string _nazwa, int _ilu, int _dopl) :nazwa(_nazwa), ilu_osobowy(_ilu), doplata(_dopl)
	{
	}
	void wypisz_p(int nr);
	~pokoj()
	{
		//cout << "Destruktor pokoj" << endl;
	}
};
void pobierz_dane();
int pobierz_ilosc();
void zwieksz_ilosc(int num);
void zwieksz_iloscp(int num);
int ile_hoteli();
int ile_pokoi();
void opcja1();
void opcja3();