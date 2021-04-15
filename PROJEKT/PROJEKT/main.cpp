#include "Nag.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

int main()
{
	cout << "1.Pracownik" << endl << "2.Klient" << endl;
	int status;
	cin >> status;
	if (status == 1)
	{
		cout << "1.Dodanie do bazy danych nowego hotelu." << endl;
		cout << "2.Dodanie do bazy danych nowego rodzaju pokoju." << endl;
		int wyb;
		cin >> wyb;
		if (wyb == 1)
		{
			opcja1();
		}
		if (wyb == 2)
		{
			opcja3();
		}
	}
	if (status == 2)
	{
		//PYTANIE O DANE KLIENTA
		int num = pobierz_ilosc();
		pobierz_dane();
		cout << "Oferty:" << endl;
		//WYPISANIE WSZYSTKICH OFERT
		int r = 1;
		kraj** tab = new kraj * [num];
		for (int i = 0; i < num; i++)
		{
			tab[i] = new kraj;
			tab[i]->nazwa = tab[i]->wczytaj(r);
			tab[i]->id = i + 1;
			cout << tab[i]->id << "." << tab[i]->nazwa << endl;
			r++;
		}
		int z, budget;
		cout << "Do ktorego kraju chcialbys sie udac?" << endl;
		cin >> z;
		cout << "Jaki jest twoj budzet na osobe na noc?" << endl;
		cin >> budget;
		fstream decyzja;
		decyzja.open("decyzja.txt", ios::app);
		if (decyzja.good() == false)
		{
			cout << "Nie udalo sie otworzyc pliku!";
			exit(0);
		}
		decyzja << "Kraj: " << tab[z - 1]->nazwa << endl << "Budzet na osobe: " << budget << endl;
		decyzja.close();
		//WYPISANIE HOTELI Z KONKRETNEGO KRAJU
		int nr = ile_hoteli();
		int g = 1, p = 1;
		int* stacmnie = new int[nr];
		cout << "Opcje hoteli: " << endl;
		hotel** tab1 = new hotel * [nr];
		int* tab_ = new int[nr];
		for (int i = 0; i < nr; i++)
		{
			tab1[i] = new hotel;
			stacmnie[i] = tab1[i]->wczytaj(g, tab[z - 1]->nazwa, budget, p);
			g = g + 4;
			if (stacmnie[i] > 0)
			{
				tab_[p - 1] = i;
				p++;
			}
		}
		int wynik = 0;
		for (int i = 0; i < nr; i++)
		{
			wynik = wynik + stacmnie[i];
		}
		if (wynik == 0)
		{
			cout << "Niestety nie znalezlismy hoteli w zakresie twojego budzetu. Sprobuj poszukac hoteli w innym kraju." << endl;
			exit(0);
		}
		//WYBOR I ZAPIS HOTELU
		cout << "Ktory hotel?" << endl;
		int hotell;
		cin >> hotell;
		int cena = 0;
		int op = 0;
		fstream decyz;
		decyz.open("decyzja.txt", ios::app);
		if (decyz.good() == false)
		{
			cout << "Nie udalo sie otworzyc pliku!";
			exit(0);
		}
		for (int i = 0; i < p; i++)
		{
			if (i + 1 == hotell)
			{
				decyz << "Hotel: " << tab1[tab_[i]]->nazwa << endl << "Koszt za noc: " << tab1[tab_[i]]->koszt_za_noc << endl << "Ilosc gwiazdek: " << tab1[tab_[i]]->ilosc_gwiazdek << endl;
				cena = tab1[tab_[i]]->koszt_za_noc;
				op = tab_[i];
			}

		}
		decyz.close();
		//WYPISYWANIE I WYBOR POKOI
		int ilosc_pokoi = ile_pokoi();
		int q = 1;
		int w = 1;
		cout << "Wybor pokoi" << endl;
		cout << "Za niektore pokoje trzeba doplacic dodatkowa sume." << endl;
		cout << "Dostepne rodzaje pokoi: " << endl;
		pokoj** tab2 = new pokoj * [ilosc_pokoi];
		for (int i = 0; i < ilosc_pokoi; i++)
		{
			tab2[i] = new pokoj;
			cout << w << ".";
			tab2[i]->wypisz_p(q);
			cout << tab2[i]->nazwa << "     pokoj " << tab2[i]->ilu_osobowy << "-osobowy     doplata: " << tab2[i]->doplata << endl;
			q = q + 3;
			w++;
		}
		int ile;
		fstream decy;
		decy.open("decyzja.txt", ios::app);
		if (decy.good() == false)
		{
			cout << "Nie udalo sie otworzyc pliku!";
			exit(0);
		}
		decy << endl;
		decy << "Zarezerwowane pokoje: " << endl;
		cout << "Ile pokoi chcialbys zarezerwowaæ?" << endl;
		cin >> ile;
		cout << "Ktore?" << endl;
		int ktory;
		int koszty = 0;
		int all = 0;
		int* tab_2 = new int[ile];
		for (int i = 0; i < ile; i++)
		{
			cin >> ktory;
			tab_2[i] = ktory;
			koszty = (cena * tab2[ktory - 1]->ilu_osobowy) + (tab2[ktory - 1]->doplata * tab2[ktory - 1]->ilu_osobowy);
			all = all + koszty;
			fstream decyzja;
			decyzja.open("decyzja.txt", ios::app);
			if (decyzja.good() == false)
			{
				cout << "Nie udalo sie otworzyc pliku!";
				exit(0);
			}
			decyzja << tab2[ktory - 1]->nazwa << endl << "Ilosc osob w pokoju: " << tab2[ktory - 1]->ilu_osobowy << endl << "Doplata: " << tab2[ktory - 1]->doplata << endl;
			decyzja.close();
		}
		int noce;
		cout << "Na ile noc chcesz zarezerwowac pobyt?" << endl;
		cin >> noce;
		decy << endl;
		decy << "Koszt pobytu: " << noce * all << endl;
		decy.close();
		//WYPISYWANIE OSTATECZNEJ DECYZJI
		cout << "Kraj: " << tab[z - 1]->nazwa << endl << "Budzet na osobe: " << budget << endl;
		cout << "Hotel: " << tab1[op]->nazwa << endl << "Koszt za noc: " << tab1[op]->koszt_za_noc << endl << "Ilosc gwiazdek: " << tab1[op]->ilosc_gwiazdek << endl;
		for (int i = 0; i < ile; i++)
		{
			cout << tab2[tab_2[i] - 1]->nazwa << endl << "Ilosc osob w pokoju: " << tab2[tab_2[i] - 1]->ilu_osobowy << endl << "Doplata: " << tab2[tab_2[i] - 1]->doplata << endl;
		}
		cout << "Koszt pobytu: " << noce * all << endl;
		//USUWANIE TABLIC 
		delete[] tab;
		delete[] tab1;
		delete[] tab2;
		delete[] tab_;
		delete[] tab_2;
	}
	else
	{
		exit(0);
	}
}