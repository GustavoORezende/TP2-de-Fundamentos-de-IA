#ifndef SIMULATED_ANNEALING_HPP
#define SIMULATED_ANNEALING_HPP

#include "../Entities/ProblemaManutencao.hpp"
#include <vector>
#include <random>

using namespace std;

vector<int> executarSimulatedAnnealing(const vector<int>& rota_inicial, const ProblemaManutencao& prob, int limite_avaliacoes, double T_inicial, double alpha, mt19937& rng, ofstream& log_conv, int execucao);

#endif