#ifndef UTILS_HPP
#define UTILS_HPP

#include "../Entities/ProblemaManutencao.hpp"
#include <string>
#include <vector>
#include <random>

using namespace std;

// Lê o TXT, calcula as raízes quadradas e preenche a matriz de distâncias
ProblemaManutencao carregarInstancia(const string& caminhoArquivo);

// Gera uma rota válida (permutação de 1 a n) embaralhada
vector<int> gerarRotaAleatoria(int n, mt19937& rng);

#endif