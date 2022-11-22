/** Arquivo Catalogo.h para o programa do catalogo de filmes.
*   Terceiro trabalho avaliado EEL670 2022.2
*   Aluno: Luis Guilherme Neri Ferreira */

#include <iostream>
#include <ostream>
#include <vector>
#include <string>

using namespace std;

#ifndef CATALOGO_H
#define CATALOGO_H

struct Filme
{
	string nome;
	string produtora;
	double nota;
    bool operator< (Filme*);
    bool operator> (Filme*);
    bool operator== (Filme*);
	bool operator< (double);
    bool operator> (double);
};

class Catalogo
{
	public:
		vector<Filme*> getFilmes();
        unsigned getMaxFilmes();
		Catalogo(int);
		int operator+= (Filme*);
       	void operator+= (vector<Filme*>);
		int operator-= (Filme*);
		int operator() (string);
		int operator() (string, string, double);
		int operator() (string, string, string);
		int melhorFilme();
	private:
		vector<Filme*> filmes;
		unsigned maxFilmes;
};

ostream& operator<< (ostream&, Catalogo*);
ostream& operator<< (ostream&, Filme*);
istream& operator>> (istream&, Filme*);

#endif
