/** Arquivo main.cpp para o programa do catalogo de filmes.
*   Terceiro trabalho avaliado EEL670 2022.2
*   Aluno: Luis Guilherme Neri Ferreira */

#include <fstream>
#include <sstream>
#include "Catalogo.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<vector<string>> conteudo;
    vector<string> linhas;
    string linha, dado;

    fstream file (argv[1], ios::in);
    if (file.is_open())
    {
        while(getline(file, linha))
        {
            linhas.clear();
            stringstream str(linha);

            while(getline(str, dado, ','))
            {
                linhas.push_back(dado);
            }

            conteudo.push_back(linhas);
        }
    }
    else {
        cout << "Nao foi possivel abrir o arquivo.\n";
	}
	file.close();

	Catalogo Catalogo(25);

	for (unsigned i = 0; i < conteudo.size(); i++) {
        string nome = conteudo[i][0];
        string prod = conteudo[i][1];
      	double nota = stod(conteudo[i][2]);

		Filme* f = new Filme;
		f->nome = nome;
		f->produtora = prod;
		f->nota = nota;
		Catalogo+= f;
	}

	while (true) {
        cout << "\nEntre com o numero correspondente a acao que deseja realizar:"
			 << "\n1: Ver o catalogo inteiro de filmes."
			 << "\n2: Ver os dados de um filme especifico."
			 << "\n3: Inserir um filme no catalogo."
			 << "\n4: Inserir um vector de filmes no catalogo."
			 << "\n5: Remover um filme do catalogo."
			 << "\n6: Editar um filme do catalogo."
			 << "\n7: Buscar o filme mais bem avaliado."
			 << endl;
        int escolha;
        cin >> escolha;

        if (escolha == 1) {
            cout << "\nCatalogo inteiro de filmes:\n";
            cout << &Catalogo;
        }

		else if (escolha == 2) {
            cout << "\nInsira o nome do filme: ";
			string nomeFilme;
            cin >> nomeFilme;
			if (Catalogo(nomeFilme) != -1)
				cout << Catalogo.getFilmes().at(Catalogo(nomeFilme));
			else
				cout << "Esse filme nao esta no catalogo.\n";
        }

        else if (escolha == 3) {
			Filme* f = new Filme;
			cout << "Insira o nome do filme [ENTER], seguido da produtora [ENTER], seguido da nota [ENTER]:\n";
			cin >> f;

            Catalogo+= f;
        }

		else if (escolha == 4) {
            unsigned n;
            vector<Filme*> vectorFilmes;
            cout << "Quantos filmes deseja inserir: ";
            cin >> n;
            for (unsigned i = 0; i < n; i++) {
                Filme* f = new Filme;
                cout << "Insira o nome do filme [ENTER], seguido da produtora [ENTER], seguido da nota [ENTER]:\n";
                cin >> f;
                vectorFilmes.push_back(f);
            }

            Catalogo+= vectorFilmes;
        }

        else if (escolha == 5) {
			cout << "\nInsira o nome do filme que deseja remover: ";
			string nomeFilme;
            cin >> nomeFilme;

			if (Catalogo(nomeFilme) != -1) {
                Catalogo-= Catalogo.getFilmes().at(Catalogo(nomeFilme));
				cout << "Filme removido.\n";
            }
			else
				cout << "Esse filme nao esta no catalogo.\n";
        }

        else if (escolha == 6) {
			cout << "\nInsira o nome do filme que deseja editar: ";
			string nomeFilme;
            cin >> nomeFilme;

            if (Catalogo(nomeFilme) != -1){
                cout << "\nQual atributo deseja editar (nome, produtora ou nota): ";
                string att;
                cin >> att;

                if (att == "nome" || att == "produtora") {
                    cout << "\nInsira nova(o) " << att << ": ";
                    string novo;
                    cin >> novo;
                    Catalogo(nomeFilme, att, novo);
                }
                else if (att == "nota") {
                    cout << "\nInsira nova nota: ";
                    double novo;
                    cin >> novo;
                    Catalogo(nomeFilme, att, novo);
                }
            }
            else
                cout << "Esse filme nao esta no catalogo.\n";
        }

        else if (escolha == 7) {
            cout << "\nMelhor filme: \n";
            cout << Catalogo.getFilmes().at(Catalogo.melhorFilme());
        }

        int escolha2;
        cout << "\nDigite 0 para voltar ao menu ou qualquer coisa para sair: ";
        cin >> escolha2;
        if (escolha2 != 0)
            break;
	}

    int i = 0;
    ofstream myfile;
    myfile.open (argv[1], ios::out);

    for (Filme* f: Catalogo.getFilmes()) {
        if (i != 0)
            myfile << "\n" << f->nome << "," << f->produtora << "," << f->nota;
        else
            myfile << f->nome << "," << f->produtora << "," << f->nota;
        i++;
    }

	myfile.close();

	return 0;
}
