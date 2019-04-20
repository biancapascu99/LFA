#include<iostream>
#include<utility>
#include<set>
#include<map>
#include<iterator>
#include<string>

using namespace std;

set<int> reuniune(set<int> mult1, set<int> mult2)
{
	set<int>::iterator i_mult;
	for (i_mult = mult2.begin(); i_mult != mult2.end(); i_mult++)
	{
		mult1.insert(*i_mult);
	}
	return mult1;
}

set<int> intersectie(set<int> mult1, set<int> mult2)
{
	set<int> mult3;
	set<int>::iterator i_mult1, i_mult2;
	for (i_mult1 = mult1.begin(); i_mult1 != mult1.end(); i_mult1++)
		for (i_mult2 = mult2.begin(); i_mult2 != mult2.end(); i_mult2++)
			if (*i_mult1 == *i_mult2)
				mult3.insert(*i_mult1);
	return mult3;
}

set<int> minim(set<int> mult1, set<int> mult2)
{
	if (mult1.size() <= mult2.size())
		return mult1;
	else
		return mult2;
}

set<int> diferenta(set<int> mult1, set<int> mult2)
{
	set<int> mult3;
	set<int>::iterator i_mult1, i_mult2;
	for (i_mult1 = mult1.begin(); i_mult1 != mult1.end(); i_mult1++)
	{
		bool adaug = true;
		for (i_mult2 = mult2.begin(); i_mult2 != mult2.end(); i_mult2++)
			if (*i_mult1 == *i_mult2)
				adaug = false;
		if (adaug)
			mult3.insert(*i_mult1);
	}

	return mult3;
}

set<int> tranzitii_inverse(char c, set<int> X, map<pair<int, char>, int> tranz)
{
	set<int>::iterator i_multime;
	set<int> multime_rezultata;
	int stare_noua, stare_curenta;
	for (i_multime = X.begin(); i_multime != X.end(); i_multime++)
	{
		stare_curenta = *i_multime;
		map<pair<int, char>, int>::iterator i_map;
		for (i_map = tranz.begin(); i_map != tranz.end(); i_map++)
		{
			if (i_map->first.second == c && i_map->second == stare_curenta)
			{
				stare_noua = i_map->first.first;
				multime_rezultata.insert(stare_noua);

			}
		}

	}
	return multime_rezultata;

}


pair <set<int>, set<int>> rafinare(set <int> Y, set<int> X)
{
	set<int> Y1, Y2;
	Y1 = intersectie(Y, X);
	Y2 = diferenta(Y, X);
	pair<set<int>, set<int>> pereche;
	pereche.first = Y1;
	pereche.second = Y2;
	return pereche;
}


void afisare_multime(set<int> mult)
{
	set<int>::iterator i_mult;
	for (i_mult = mult.begin(); i_mult != mult.end(); i_mult++)
		cout << *i_mult << " ";
	//cout << endl;
}

int main()
{
	set <char> alfabet;
	for (int i = 'a'; i <= 'z'; i++)
		alfabet.insert(i);
	for (int i = 'A'; i <= 'Z'; i++)
		alfabet.insert(i);
	//cuvant vid
	alfabet.insert('~');


	map< pair<int, char>, int> tranzitie;
	set<int> mult_stari, mult_stari_finale;


	int  S, nr_stari, nr_stari_finale, nr_tranz;

	//cout << "Citire nr de stari " << endl;
	cin >> nr_stari;
	//cout << "Citire stari" << endl;

	for (int i = 0; i < nr_stari; i++)
	{
		int x;
		cin >> x;
		mult_stari.insert(x);

	}
	//cout << "Citire stare de start " << endl;
	cin >> S;
	//cout << "Nr stari finale " << endl;
	cin >> nr_stari_finale;
	//cout << "Citire stari finala " << endl;

	for (int i = 0; i < nr_stari_finale; i++)
	{
		int x;
		cin >> x;
		mult_stari_finale.insert(x);
	}

	//	cout << "Citire nr tranzitii " << endl;
	cin >> nr_tranz;
	//cout << "Citire tranzitii " << endl;

	set<char> mult_litere;
	for (int i = 0; i < nr_tranz; i++)
	{
		int f, s;
		char leg;
		cin >> s >> leg >> f;
		pair<int, char> pereche;
		pereche.first = s;
		pereche.second = leg;
		tranzitie[pereche] = f;
		mult_litere.insert(leg);

	}

	// Afisare tranzitii

	map< pair<int, char>, int >::iterator iterator_map;
	for (iterator_map = tranzitie.begin(); iterator_map != tranzitie.end(); iterator_map++)
	{
		cout << iterator_map->first.first << " " << iterator_map->first.second << " -> ";
		cout << iterator_map->second << endl;


	}

	set <int> X, X_invers;
	set<int> multime_stari_nefinale;
	multime_stari_nefinale = diferenta(mult_stari, mult_stari_finale);
	set<set<int>> P;
	P.insert(multime_stari_nefinale);
	P.insert(mult_stari_finale);
	set<set<int>> W;
	W.insert(minim(mult_stari_finale, multime_stari_nefinale));
	while (!W.empty())
	{
		set<int> A;
		A = *W.begin();
		W.erase(W.begin());
		set<char>::iterator i_mult;
		for (i_mult = mult_litere.begin(); i_mult != mult_litere.end(); i_mult++)
		{
			char caracter_curent = *i_mult;
			set<set<int>> ::iterator i_mult_P;
			for (i_mult_P = P.begin(); i_mult_P != P.end(); i_mult_P++)
			{
				set<int> Y = *i_mult_P;
				set<int> D;
				D = tranzitii_inverse(caracter_curent, A, tranzitie);
				pair<set<int>, set<int>> pereche;
				pereche = rafinare(Y, D);
				if (!(pereche.first.empty()) && !(pereche.second.empty()))
				{
					P.erase(Y);
					P.insert(pereche.first);
					P.insert(pereche.second);
					if (W.find(Y) != W.end())
					{
						W.erase(Y);
						W.insert(pereche.first);
						W.insert(pereche.second);
					}
					else
					{
						W.insert(minim(pereche.first, pereche.second));
					}
				}
			}
		}
	}
	map<int,set<int>> apartine;
	set <set<int>>::iterator iterator_P;
	for (iterator_P = P.begin(); iterator_P != P.end(); iterator_P++)
	{
	    set<int> partitie=*iterator_P;
	    set<int>::iterator iterator_partitie;
	    for(iterator_partitie=partitie.begin(); iterator_partitie != partitie.end(); iterator_partitie++)
        {
            apartine[*iterator_partitie]= partitie;
        }
	}
	set<int> stare_initiala_minimizare;
	set<set<int>> stari_finale_minimizare;
	stare_initiala_minimizare = apartine[S];
	set<int>::iterator iterator_final;
	for(iterator_final = mult_stari_finale.begin();iterator_final != mult_stari_finale.end(); iterator_final++)
    {
        stari_finale_minimizare.insert(apartine[*iterator_final]);
    }
    cout<<"stare initiala "<<endl;
    afisare_multime(stare_initiala_minimizare);
    cout<<endl;
    cout<<"stari finale "<<endl;

    for(iterator_P = stari_finale_minimizare.begin(); iterator_P != stari_finale_minimizare.end(); iterator_P++)
    {
        afisare_multime(*iterator_P);
    }
    cout<<endl;

    map<pair<set<int>,char>,set<int>> tranzitie_minimizare;
	for (iterator_map = tranzitie.begin(); iterator_map != tranzitie.end(); iterator_map++)
    {
         pair<int,char> pereche;
         pereche=iterator_map->first;
         pair<set<int>,char> pereche_minimizare;
         pereche_minimizare.first = apartine[pereche.first];
         pereche_minimizare.second = pereche.second;
         tranzitie_minimizare[pereche_minimizare] = apartine[iterator_map->second];
    }

    //afisare tranzitii minimizare
    cout<<"tranzitii minimizare"<<endl;
    map< pair<set<int>, char>, set<int> >::iterator iterator_map_min;
	for (iterator_map_min = tranzitie_minimizare.begin(); iterator_map_min != tranzitie_minimizare.end(); iterator_map_min++)
	{
	   afisare_multime(iterator_map_min->first.first);
        cout<<iterator_map_min->first.second<<" -> ";
        afisare_multime(iterator_map_min->second);
        cout<<endl;

	}


}

