#include<iostream>
#include<utility>
#include<map>
#include<list>
#include<set>
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

void afisare_multime(set<int> mult)
{
	set<int>::iterator i_mult;
	for (i_mult = mult.begin(); i_mult != mult.end(); i_mult++)
		cout << *i_mult << " ";
	cout << endl;
}

set<int> verificare(set<int> stari, char litera, map<pair<int, char>, set<int>> tranz)
{
	set<int>::iterator i_multime;
	set<int> multime_rezultata;
	for (i_multime = stari.begin(); i_multime != stari.end(); i_multime++)
	{
		pair<int, char> pereche;
		pereche.first = *i_multime;
		pereche.second = litera;
		multime_rezultata = reuniune(multime_rezultata, tranz[pereche]);
		//afisare_multime(multime_rezultata);
	}
	return multime_rezultata;
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


	map< pair<int, char>, set<int>> tranzitie;
	set<int> mult_stari,mult_stari_finale;


	int  S, nr_stari, nr_stari_finale,nr_tranz;

	cout << "Citire nr de stari "<<endl;
	cin >> nr_stari;
	cout << "Citire stari" << endl;

	for (int i = 0; i < nr_stari; i++)
	{
		int x;
		cin >> x;
		mult_stari.insert(x);

	}
	cout << "Citire stare de start " << endl;
	cin >> S;
	cout << "Nr stari finale " << endl;
	cin >> nr_stari_finale;
	cout << "Citire stari finala " << endl;

	for(int i=0; i < nr_stari_finale; i++)
	{
		int x;
		cin >> x;
		mult_stari_finale.insert(x);
	}

	cout << "Citire nr tranzitii " << endl;
	cin >> nr_tranz;
	cout << "Citire tranzitii " << endl;


	for (int i = 0; i < nr_tranz; i++)
	{
		int f, s;
		char leg;
		cin >> s >> leg >> f;
		pair<int, char> pereche;
		pereche.first = s;
		pereche.second = leg;
		tranzitie[pereche].insert(f); 
	}

	// Afisare tranzitii

	map< pair<int, char>, set<int> >::iterator iterator_map;
	for (iterator_map = tranzitie.begin(); iterator_map != tranzitie.end(); iterator_map++)
	{
		cout << iterator_map->first.first << " " << iterator_map->first.second << " -> ";
		afisare_multime(iterator_map->second);
	}


	string cuvant;
	cout << "Citire cuvant de verificat: " << endl;
	cin >> cuvant;

	if (cuvant == "~" && mult_stari_finale.find(S) != mult_stari_finale.end())
	{
		cout << "Cuvantul este acceptat !";
		return 0;
	}

	set<int> stari_curente;
	stari_curente.insert(S);
	//cout << "stare curente: " << endl;  afisare_multime(stari_curente)
		
	for (int i = 0; i < cuvant.length(); i++)
	{
		//cout << "cuvant    :" << cuvant[i] << endl;
		stari_curente=verificare(stari_curente, cuvant[i], tranzitie);
		if (stari_curente.empty())
		{
			cout << "Cuvantul nu este acceptat!";
			return 0;
		}
		//cout << "multimi curente!" << endl;  afisare_multime(stari_curente);
	}
	//afisare_multime(stari_curente);
	set<int> corect;
	corect = intersectie(stari_curente, mult_stari_finale);
	//cout << "afisare mult corecta" << endl;  afisare_multime(corect);
	if (!corect.empty() )
		cout << "Cuvantul este acceptat!";
	else
		cout << "Cuvantul nu este acceptat!";
	}



	

