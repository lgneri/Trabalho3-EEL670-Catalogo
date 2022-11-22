# Arquivo makefile para o programa do catalogo de filmes.
# Terceiro trabalho avaliado EEL670 2022.2
# Aluno: Luis Guilherme Neri Ferreira

CPP = g++
CPPFLAGS = -Wall -std=c++11

all:
	$(CPP) $(CPPFLAGS) -o catalogo main.cpp Catalogo.cpp

clean:
	rm catalogo