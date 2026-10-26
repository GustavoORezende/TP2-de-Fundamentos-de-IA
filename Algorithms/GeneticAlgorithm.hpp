#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include "../Entities/ProblemaManutencao.hpp"
#include <vector>
#include <random>

using namespace std;

vector<int> executarGA(const ProblemaManutencao& prob, int limite_avaliacoes, int tamanho_populacao, double taxa_mutacao, mt19937& rng, ofstream& log_conv, int execucao);

#endif