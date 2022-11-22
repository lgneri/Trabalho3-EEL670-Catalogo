/** Arquivo Catalogo.cpp para o programa do catalogo de filmes.
*   Terceiro trabalho avaliado EEL670 2022.2
*   Aluno: Luis Guilherme Neri Ferreira */

#include <iomanip>
#include "Catalogo.h"

using namespace std;

Catalogo::Catalogo(int max) {
	maxFilmes = max;
}

vector<Filme*> Catalogo::getFilmes() {
	return filmes;
}

unsigned Catalogo::getMaxFilmes() {
	return maxFilmes;
}

ostream& operator<< (ostream& out, Catalogo* cat) {
	for (Filme* f: cat->getFilmes())
		out << f->nome << ", Produtora: "
			<< f->produtora << ", Nota: "
			<< f->nota << endl;

	return out;
}

ostream& operator<< (ostream& out, Filme* f) {
	out << f->nome << ", Produtora: "
		<< f->produtora << ", Nota: "
		<< f->nota << endl;

	return out;
}

istream &operator>> (istream& in, Filme* f) {
	in >> f->nome;
	in >> f->produtora;
	in >> f->nota;

	return in;
}

bool Filme::operator< (Filme* filme) {
	return nome < filme->nome;
}

bool Filme::operator> (Filme* filme) {
	return nome > filme->nome;
}

bool Filme::operator== (Filme* filme) {
	return nome == filme->nome;
}

int Catalogo::operator+= (Filme* filme) {
	if (filmes.size() < maxFilmes) {
		if (filmes.size() > 0) {
			vector<Filme*>::iterator it = filmes.begin();
			int i = 0;

			for (Filme *f: filmes) {
				if (*filme == f) {
					cout << "\nFilme " << filme->nome << " ja esta no catalogo.\n";
					return -1;
				}

				else if (*filme < f) {
					filmes.insert(it, filme);
					return i;
				}

				it++;
				i++;
			}

			filmes.push_back(filme);
			return filmes.size() - 1;
		}

		else {
			filmes.push_back(filme);
			return filmes.size() - 1;
		}
	}

	else {
		cout << "Maximo de filmes no catalogo atingido" << endl;
		return -1;
	}
}

void Catalogo::operator+= (vector<Filme*> vecFilmes) {
	for (Filme* f: vecFilmes)
		this->operator+=(f);
}

int Catalogo::operator-= (Filme* filme) {
	vector<Filme*>::iterator it = filmes.begin();
	int i = 0;
	for (Filme* f: filmes) {
		if (*filme == f) {
			filmes.erase(it);
			return i;
		}
		it++;
		i++;
	}

	return -1;
}

int Catalogo::operator() (string nome) {
	vector<Filme*>::iterator it = filmes.begin();
	int i = 0;
	for (Filme* f: filmes) {
		if (nome == f->nome) {
			return i;
		}
		it++;
		i++;
	}

	return -1;
}

int Catalogo::operator() (string nome, string atributo, string novo) {
	int posicao = this->operator()(nome);
	if (posicao > -1) {
		if (atributo == "nome") {
			filmes.at(posicao)->nome = novo;
			return posicao;
		}

		else if (atributo == "produtora") {
			filmes.at(posicao)->produtora = novo;
			return posicao;
		}

		else if (atributo == "nota") {
			cout << "Se deseja modificar nota o ultimo argumento deve ser double.\n";
			return -1;
		}

		else {
			cout << "Atributo deve ser nome ou produtora.\n";
			return -1;
		}
	}

	else {
		cout << "Filme nao encontrado\n";
		return -1;
	}
}

int Catalogo::operator() (string nome, string atributo, double novo) {
	int posicao = this->operator()(nome);
	if (posicao > -1) {
		if (atributo == "nota") {
			filmes.at(posicao)->nota = novo;
			return posicao;
		}

		else if (atributo == "nome" || atributo == "produtora") {
			cout << "Se deseja modificar nome ou produtora o ultimo argumento deve ser string.\n";
			return -1;
		}

		else {
			cout << "Atributo deve ser nota.\n";
			return -1;
		}
	}

	else {
		cout << "Filme nao encontrado\n";
		return -1;
	}
}

bool Filme::operator< (double n) {
	return nota < n;
}

bool Filme::operator> (double n) {
	return nota > n;
}

int Catalogo::melhorFilme() {
	double max = 0;
	int i = 0;
	int indice;

	for (Filme* f: filmes) {
		if (*f > max) {
			max = f->nota;
			indice = i;
		}

		i++;
	}

	return indice;
}
