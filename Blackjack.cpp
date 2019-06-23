#include <iostream>
#include <string>
#include <time.h>

using namespace std;

const int rozmiarTalii = 104;

class Karta
{
public:
    string kolor;
    string figura;
	int talia;
	int wagaFigura;
	int wagaKolor;

	Karta()
	{}

    Karta(string k, string f, int t)
    {
		talia = t;
        kolor = k;
        figura = f;

		if (f == "2")
			wagaFigura = 1;
		else if (f == "3")
			wagaFigura = 2;
		else if (f == "4")
			wagaFigura = 3;
		else if (f == "5")
			wagaFigura = 4;
		else if (f == "6")
			wagaFigura = 5;
		else if (f == "7")
			wagaFigura = 6;
		else if (f == "8")
			wagaFigura = 7;
		else if (f == "9")
			wagaFigura = 8;
		else if (f == "10")
			wagaFigura = 9;
		else if (f == "J")
			wagaFigura = 10;
		else if (f == "D")
			wagaFigura += 11;
		else if (f == "K")
			wagaFigura += 12;
		else if (f == "A")
			wagaFigura += 13;

		if (k == "Pik")
			wagaKolor = 1;
		else if (k == "Trefl")
			wagaKolor = 2;
		else if (k == "Karo")
			wagaKolor = 3;
		else if (k == "Kier")
			wagaKolor = 4;
    }
};

class Talia
{
public:
    int aktualnaKarta;
    Karta karty[rozmiarTalii];

    Talia()
    {
		aktualnaKarta = 0;
        string kolory[] = {"Pik", "Trefl", "Karo", "Kier"};
        string figury[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "D", "K", "A"};

		for (int i=0; i<52; i++)
		{
			for (int j=0; j<2; j++)
			karty[2 * i + j] = Karta(kolory[i / 13], figury[i % 13], j + 1);
		}
    }

    void pokaz()
    {
        for(int i=0; i<rozmiarTalii; i++)
        {
            cout << i << ". " << karty[i].figura << " " << karty[i].kolor << endl;
        }
    }

	void tasuj()
	{
		aktualnaKarta = 0;
		for (int i = 0; i < rozmiarTalii; i++)
		{
			int tempNr = rand() % rozmiarTalii;
			Karta tempCard = karty[tempNr];
			karty[tempNr] = karty[i];
			karty[i] = tempCard;
		}
	}

	Karta podajKarte()
	{
		if (aktualnaKarta < rozmiarTalii)
		{
			Karta temp = karty[aktualnaKarta];
			aktualnaKarta++;
			return temp;
		}
		else
		{
			aktualnaKarta = 0;
			tasuj();
			Karta temp = karty[aktualnaKarta];
			aktualnaKarta++;
			return temp;
		}
	}

};

class Blackjack
{
public:
	Talia karty;
	Karta rekaKrupiera[5];
	Karta rekaGracza[5];
	int iloscKartKrupiera;
	int iloscKartGracza;

	Blackjack()
	{
		iloscKartGracza = 0;
		iloscKartKrupiera = 0;
	}

	void wyczysc()
	{
		iloscKartGracza = 0;
		iloscKartKrupiera = 0;
	}

	void rozdaj()
	{
		karty.tasuj();
		for (int i = 0; i < 2; i++)
		{
			rekaGracza[i] = karty.podajKarte();
			iloscKartGracza++;
			rekaKrupiera[i] = karty.podajKarte();
			iloscKartKrupiera++;
		}

	}

	void pokazKartyStartowe()
	{
		cout << "Karty krupiera:" << endl;
		cout << rekaKrupiera[0].kolor << " " << rekaKrupiera[0].figura << "   " << "X" <<" X" << "   ";
		cout << "Punkty: " << policzPunktyKrupiera(0) << endl;
		cout << "Karty gracza:" << endl;
		sortujKarty(0);
		cout << "Punkty: " << policzPunktyGracza() << endl;
	}

	void pokazKarty()
	{
		cout << "Karty krupiera:" << endl;
		sortujKarty(1);
		cout << "Punkty: " << policzPunktyKrupiera(1) << endl;
		cout << "Karty gracza:" << endl;
		sortujKarty(0);
		cout << "Punkty: " << policzPunktyGracza() << endl;
	}

	void sortujKarty(int i)
	{
		if (i == 0) // Gracz
		{
			Karta temp[5];
			for (int i = 0; i < iloscKartGracza; i++)
				temp[i] = rekaGracza[i];

			for (int i = 0; i < iloscKartGracza; i++)
			{
				for (int j = i + 1; j < iloscKartGracza; j++)
				{
					if (temp[j].wagaFigura > temp[i].wagaFigura)
						swap(temp[j], temp[i]);
					if (temp[j].wagaFigura == temp[i].wagaFigura)
						if (temp[j].wagaKolor > temp[i].wagaKolor)
							swap(temp[j], temp[i]);
				}
			}

			for (int i = 0; i < iloscKartGracza; i++)
			{
				cout << temp[i].kolor << " " << temp[i].figura << "   ";
			}

		}
		else // Krupier
		{
			Karta temp[5];
			for (int i = 0; i < iloscKartKrupiera; i++)
				temp[i] = rekaKrupiera[i];

			for (int i = 0; i < iloscKartKrupiera; i++)
			{
				for (int j = i + 1; j < iloscKartKrupiera; j++)
				{
					if (temp[j].wagaFigura > temp[i].wagaFigura)
						swap(temp[j], temp[i]);
					if (temp[j].wagaFigura == temp[i].wagaFigura)
						if (temp[j].wagaKolor > temp[i].wagaKolor)
							swap(temp[j], temp[i]);
				}
			}

			for (int i = 0; i < iloscKartKrupiera; i++)
			{
				cout << temp[i].talia << " " << temp[i].kolor << " " << temp[i].figura << "   ";
			}
		}
	}

	int policzPunktyGracza()
	{
		int punkty = 0;
		int punktyTemp = 0;
		for (int i = 0; i < iloscKartGracza; i++)
		{
			if (rekaGracza[i].figura == "2")
				punkty += 2;
			else if (rekaGracza[i].figura == "3")
				punkty += 3;
			else if (rekaGracza[i].figura == "4")
				punkty += 4;
			else if (rekaGracza[i].figura == "5")
				punkty += 5;
			else if (rekaGracza[i].figura == "6")
				punkty += 6;
			else if (rekaGracza[i].figura == "7")
				punkty += 7;
			else if (rekaGracza[i].figura == "8")
				punkty += 8;
			else if (rekaGracza[i].figura == "9")
				punkty += 9;
			else if (rekaGracza[i].figura == "10")
				punkty += 10;
			else if (rekaGracza[i].figura == "J")
				punkty += 10;
			else if (rekaGracza[i].figura == "D")
				punkty += 10;
			else if (rekaGracza[i].figura == "K")
				punkty += 10;
			else if (rekaGracza[i].figura == "A")
			{
				punktyTemp = punkty + 11;
				if (punktyTemp <= 21)
					punkty += 11;
				else
					punkty += 1;
			}
		}
		return punkty;
	}

	int policzPunktyKrupiera(int flag)
	{
		int punkty = 0;
		int punktyTemp = 0;
		if (flag == 1)
		{
			for (int i = 0; i < iloscKartKrupiera; i++)
			{
				if (rekaKrupiera[i].figura == "2")
					punkty += 2;
				else if (rekaKrupiera[i].figura == "3")
					punkty += 3;
				else if (rekaKrupiera[i].figura == "4")
					punkty += 4;
				else if (rekaKrupiera[i].figura == "5")
					punkty += 5;
				else if (rekaKrupiera[i].figura == "6")
					punkty += 6;
				else if (rekaKrupiera[i].figura == "7")
					punkty += 7;
				else if (rekaKrupiera[i].figura == "8")
					punkty += 8;
				else if (rekaKrupiera[i].figura == "9")
					punkty += 9;
				else if (rekaKrupiera[i].figura == "10")
					punkty += 10;
				else if (rekaKrupiera[i].figura == "J")
					punkty += 10;
				else if (rekaKrupiera[i].figura == "D")
					punkty += 10;
				else if (rekaKrupiera[i].figura == "K")
					punkty += 10;
				else if (rekaKrupiera[i].figura == "A")
				{
					punktyTemp = punkty + 11;
					if (punktyTemp <= 21)
						punkty += 11;
					else
						punkty += 1;
				}
			}
			return punkty;
		}
		else
		{
			if (rekaKrupiera[0].figura == "2")
				punkty += 2;
			else if (rekaKrupiera[0].figura == "3")
				punkty += 3;
			else if (rekaKrupiera[0].figura == "4")
				punkty += 4;
			else if (rekaKrupiera[0].figura == "5")
				punkty += 5;
			else if (rekaKrupiera[0].figura == "6")
				punkty += 6;
			else if (rekaKrupiera[0].figura == "7")
				punkty += 7;
			else if (rekaKrupiera[0].figura == "8")
				punkty += 8;
			else if (rekaKrupiera[0].figura == "9")
				punkty += 9;
			else if (rekaKrupiera[0].figura == "10")
				punkty += 10;
			else if (rekaKrupiera[0].figura == "J")
				punkty += 10;
			else if (rekaKrupiera[0].figura == "D")
				punkty += 10;
			else if (rekaKrupiera[0].figura == "K")
				punkty += 10;
			else if (rekaKrupiera[0].figura == "A")
			{
				punktyTemp = punkty + 11;
				if (punktyTemp <= 21)
					punkty += 11;
				else
					punkty += 1;
			}
			return punkty;
		}
	}

	void hitGracz()
	{
		rekaGracza[iloscKartGracza] = karty.podajKarte();
		iloscKartGracza++;
	}

	void hitKrupier()
	{
		rekaKrupiera[iloscKartKrupiera] = karty.podajKarte();
		iloscKartKrupiera++;
	}

	void sprawdzPunkty()
	{
		if (policzPunktyGracza() > 21)
		{
			system("cls");
			pokazKarty();
			cout << "Przegrana! Wygrywa Krupier." << endl;
		}
		else if (policzPunktyGracza() == 21)
		{
			system("cls");
			pokazKarty();
			cout << "BLACKJACK! Wygrales!" << endl;
		}
		else
		{
			system("cls");
			pokazKarty();
			system("pause");
			while (policzPunktyKrupiera(1) <= 16)
			{
				cout << endl;
				hitKrupier();
				pokazKarty();
				system("pause");
			}

			if (policzPunktyKrupiera(1) <= policzPunktyGracza()) // Krupier dobiera jeszcze raz
			{
				cout << endl << "Krupier ryzyskuje!" << endl;
				hitKrupier();
				pokazKarty();
				cout << endl;
			}

			if (policzPunktyKrupiera(1) > 21)
				cout << "Wygrales!" << endl;
			else
			{
				if (policzPunktyGracza() == policzPunktyKrupiera(1))
					cout << "Remis!" << endl;
				else if (policzPunktyGracza() > policzPunktyKrupiera(1))
					cout << "Wygrales!" << endl;
				else
					cout << "Przegrana! Wygrywa Krupier." << endl;
			}
		}
	}

};

int main()
{
	time_t qTime;
	time(&qTime);
	srand(qTime);
	Blackjack gra;
	char wybor;
	int sprawdz;


	while (1)
	{
		system("CLS");
		gra.wyczysc();
		gra.rozdaj();
		sprawdz = 0;

		do
		{
			if (gra.policzPunktyGracza() == 21)
				break;
			system("CLS");
			gra.pokazKartyStartowe();
			cout << "Co teraz? Hit(H) or Stand(S)?" << endl;
			cin >> wybor;
			if ((wybor == 'h') || (wybor == 'H'))
				gra.hitGracz();
			else if ((wybor == 's') || (wybor == 'S'))
				sprawdz = 1;
		} while ((sprawdz == 0) && (gra.policzPunktyGracza() < 22) && (gra.iloscKartGracza < 5));
		gra.sprawdzPunkty();

		system("Pause");
	}
    return 0;
}
