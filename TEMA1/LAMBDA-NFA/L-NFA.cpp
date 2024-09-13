#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <map>
//3.automat finit nedeterminist cu lambda
using namespace std;
ifstream f("input.txt");
ofstream g("output.txt");
int stare, n, m, i, j, stare_finala, nrcuv, nod1, nod2, stare_init, nrf, stare_curenta, ui, vecin;
char caracter;
vector<int> stari;
string s;
unordered_map<int, bool> fin; //true = e stare finala, false = nu e stare finala
map<pair<int, char>, vector<int>> muta; //(stare_curenta, litera) : vector cu toate stare_urmatoare posibile
set<pair<int, int>> deja;

bool verifica_cuv(int stare_curenta, string s, int pos)
{
    if (deja.count({stare_curenta, pos})) return 0;
    deja.insert({stare_curenta, pos});

    bool rezultat = false;
    unsigned int ui;


    if(muta.find(make_pair(stare_curenta,'L')) != muta.end())
        for(ui=0; ui<muta[make_pair(stare_curenta,'L')].size(); ui++) //vecinii lui stare_curenta cu litera s[0]
        {
            vecin = muta[make_pair(stare_curenta,'L')][ui];
            rezultat = (verifica_cuv(vecin, s, pos) | rezultat);
        }


    if(pos==s.size() && rezultat==0)
    {

        if(fin[stare_curenta]==true)
            return 1;
        else
            return 0;
    }


    if(muta.find(make_pair(stare_curenta,s[pos])) != muta.end()) //exista pair-ul
        for(ui=0; ui<muta[make_pair(stare_curenta,s[pos])].size(); ui++) //vecinii lui stare_curenta cu litera s[0]
        {
            vecin = muta[make_pair(stare_curenta,s[pos])][ui];
            rezultat = (verifica_cuv(vecin, s, pos + 1) | rezultat);
        }


    return rezultat;
}

int main()
{
    f >> n; //nr de stari
    for(i=1; i<=n; i++)
    {
        f>>stare; //numărul stării
        stari.push_back(stare);
    }
    f >> m; //nr tranzitii
    for(i=1; i<=m; i++)
    {
        f>>nod1>>nod2;
        f>>caracter;
        muta[make_pair(nod1,caracter)].push_back(nod2);
    }
    f>>stare_init;
    f>>nrf; //numarul de stari finale
    for(i=1; i<=nrf; i++)
    {
        f>>stare_finala; //numarul fiecărei stări finale
        fin[stare_finala] = true;
    }

    f>>nrcuv; //numărul de cuvinte de verificat
    for(i=1; i<=nrcuv; i++)
    {
        f>>s;//cuvantul de verificat
        deja.clear();
        if(verifica_cuv(stare_init,s,0)==1)
        {
            g<<"DA\n";
        }
        else
            g<<"NU\n";

    }
    f.close();
    g.close();
    return 0;
}