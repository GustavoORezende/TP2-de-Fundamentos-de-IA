#ifndef GREEDY_DESCENT_HPP
#define GREEDY_DESCENT_HPP

#include "../Entities/ProblemaManutencao.hpp"
#include <vector>

using namespace std;

vector<int> aplica2Opt(const vector<int>& rota, int i, int j);

vector<int> executarGreedyDescent(const vector<int>& rota_inicial, const ProblemaManutencao& prob, int& avaliacoes_gastas, int limite_avaliacoes);

#endif