#if 1
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
//#include "vld.h"

using namespace std;

int main()
{

	fstream f("date2.in");

	char alfabet[100], noduri[100];

	int *ascii = new int[300];
	int *asciinoduri = new int[300];
	memset(ascii, -1, 300 * sizeof(int));
	memset(asciinoduri, -1, 300 * sizeof(int));

	int inverse = 0, prod;


	f >> noduri >> alfabet;


	int nr_nod = strlen(noduri);
	int index_noduri = 0;
	for (int i = 0; i < nr_nod; i++)
	{
		asciinoduri[noduri[i]] = index_noduri;
		index_noduri++;

	}

	int* fin = new int[index_noduri]();

	int nr_alf = strlen(alfabet);
	int index_alfabet = 0;
	for (int i = 0; i < nr_alf; i++)
	{
		ascii[alfabet[i]] = index_alfabet;
		index_alfabet++;

	}
	vector<int> **functie = new vector<int>*[nr_nod + 1];
	for (int i = 0; i < nr_nod + 1; i++)
		functie[i] = new vector<int>[nr_alf];


	f >> prod;
	char x, y[5];

	for (int i = 0; i < prod; i++)
	{
		f >> x;
		f.ignore(20, '>');
		f >> y;
		if (y[0] == '*')
		{
			fin[asciinoduri[x]] = 1;
			continue;
		}
		if (y[1] == '\0')
		{
			functie[asciinoduri[x]][ascii[y[0]]].push_back(index_noduri);
			fin[index_noduri] = 1;
			continue;
		}
		if (ascii[y[0]] == -1)
			inverse = 1;
		if (inverse)
			functie[asciinoduri[x]][ascii[y[1]]].push_back(asciinoduri[y[0]]);
		else	functie[asciinoduri[x]][ascii[y[0]]].push_back(asciinoduri[y[1]]);


	}

	int curr[100], inter[100];
	char word[100];
	int index_curr/*ind*/, index_inter/*ind1*/, lit;
	while (f >> word)
	{
		if (inverse)_strrev(word);
		curr[0] = 0;
		index_curr = 1;
		for (int i = 0; i < strlen(word); i++)
		{
			lit = ascii[word[i]];
			if (lit == -1)break;
			index_inter = 0;

			for (int j = 0; j < index_curr; j++)
				for (int k = 0; k < functie[curr[j]][lit].size(); k++)
					inter[index_inter++] = functie[curr[j]][lit][k];

			for (int j = 0; j < index_inter; j++)
				curr[j] = inter[j];

			index_curr = index_inter;

		}
		int ok = 0;
		for (int i = 0; i < index_curr; i++)
			if (fin[curr[i]] == 1)
			{
				ok = 1;
				break;
			}
		if (inverse)_strrev(word);
		cout << word << " este ";

		if (ok == 0)cout << "respins\n";
		else cout << "ok\n";
	}

	for (int i = 0; i < nr_nod; i++)
		delete[] functie[i];
	delete[] functie;
	delete[] ascii;
	delete[] asciinoduri;
	delete[] fin;
	f.close();

	return 0;
}

#endif
