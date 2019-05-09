#if 1
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
//#include "vld.h"

using namespace std;


int main()
{
	fstream f("date3.in");
	int prod;
	char x, y[4];
	vector<pair<string, vector<string>>> NTerm, Term;
	pair<string, vector<string>> p;
	string convert;


	f >> prod;
	for (int i = 0; i < prod; i++)
	{
		f >> x;
		f.ignore(20, '>');
		f >> y;
		//cout << x << "->" << y << endl;
		if (y[1] == NULL) // TERMINALE
		{

			int ok = 0;

			for (int i = 0; i < Term.size(); i++)
				if (Term[i].first == y)
				{
					convert = x;
					Term[i].second.push_back(convert); ok = 1;
				}
			if (ok == 0) {
				p.first = y;
				convert = x;
				p.second.push_back(convert);
				Term.push_back(p);
				p.second.clear();
			}


		}
		else //NONTERMINALE
		{
			int ok = 0;
			for (int i = 0; i < NTerm.size(); i++)
				if (NTerm[i].first == y)
				{
					convert = x;
					NTerm[i].second.push_back(convert); ok = 1;
				}
			if (ok == 0) {
				p.first = y;
				convert = x;
				p.second.push_back(convert);
				NTerm.push_back(p);
				p.second.clear();
			}

		}
	}

	///PRINTARE TERM
	//cout << Term[0].first << " ";
	//for (int i = 0; i < Term[0].second.size(); i++)
	//	cout << Term[0].second[i] << " ";
	//cout << endl;
	//cout << Term[1].first << " ";
	//for (int i = 0; i < Term[1].second.size(); i++)
	//	cout << Term[1].second[i] << " ";
	//cout << endl;


	///PRINTARE NTERM
	/*cout << NTerm[0].first << " ";
	for (int i = 0; i < NTerm[0].second.size(); i++)
		cout << NTerm[0].second[i] << " ";
	cout << endl;
	cout << NTerm[1].first << " ";
	for (int i = 0; i < NTerm[1].second.size(); i++)
		cout << NTerm[1].second[i] << " ";
	cout << endl;
	cout << NTerm[2].first << " ";
	for (int i = 0; i < NTerm[2].second.size(); i++)
		cout << NTerm[2].second[i] << " ";
	cout << endl;
	cout << NTerm[3].first << " ";
	for (int i = 0; i < NTerm[3].second.size(); i++)
		cout << NTerm[3].second[i] << " ";
	cout << endl;
	*/

	string word;

	while (f >> word)
	{

		int n = word.size();
		vector<string> **tabel = new vector<string>*[n];
		for (int i = 0; i < n; i++)
			tabel[i] = new vector<string>[n - i];
		for (int i = 0; i < n; i++)
		{
			char key = word[i];
			convert = key;
			for (int j = 0; j < Term.size(); j++)
			{
				if (!Term[j].first.compare(convert)) {
					for (int k = 0; k < Term[j].second.size(); k++)
					{
						tabel[0][i].push_back(Term[j].second[k]);
						///PRINTARE PRIMUL RAND TABEL
						//cout << Term[j].second[k] << " ";
					}

				}
			}
			//cout << endl;
		}
		//cout << "////" << endl;
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < n - i; j++)
			{
				for (int k = 1; k <= i; k++)
				{
					///PRINTARE COMBINATII
					//cout << "V" << i << j << "=V" << i - k << j << "+V" << k - 1 << i + j + 1 - k << endl;
					string cuplu;
					if (!tabel[i - k][j].size() || !tabel[k - 1][i + j + 1 - k].size())
						continue;
					for (int w = 0; w < tabel[i - k][j].size(); w++)
						for (int q = 0; q < tabel[k - 1][i + j + 1 - k].size(); q++)
						{
							cuplu.erase();
							cuplu = tabel[i - k][j][w] + tabel[k - 1][i + j + 1 - k][q];
							//cout << cuplu << " "<<endl;
							for (int s = 0; s < NTerm.size(); s++)
							{
								if (!NTerm[s].first.compare(cuplu)) {
									for (int a = 0; a < NTerm[s].second.size(); a++)
									{
										tabel[i][j].push_back(NTerm[s].second[a]);

									}

								}
							}

						}

				}
				//sort & unique
				sort(tabel[i][j].begin(), tabel[i][j].end());
				tabel[i][j].erase(unique(tabel[i][j].begin(), tabel[i][j].end()), tabel[i][j].end());
				///PRINTARE TABEL
				/*for (int k = 0; k < tabel[i][j].size(); k++)
					cout << tabel[i][j][k] << " ";
				cout << endl;*/

			}
			//cout << "////" << endl;
		}

		int ok = 0;
		for (int k = 0; k < tabel[n - 1][0].size(); k++)
			if (tabel[n - 1][0][k] == "S")ok = 1;
		if (ok == 1)cout << word << " este un cuvant acceptat de gramatica" << endl;
		else cout << word << " NU este un cuvant acceptat de gramatica" << endl;


		for (int i = 0; i < n; i++)
			delete[] tabel[i];
		delete[] tabel;
	}



	return 0;
}
#endif