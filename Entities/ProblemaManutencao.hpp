#ifndef PROBLEMA_MANUTENCAO_HPP
#define PROBLEMA_MANUTENCAO_HPP

#include <vector>

using namespace std;

struct ProblemaManutencao {
    int n; 
    vector<vector<double>> dist;
    vector<double> tempoServico;
    vector<double> prazo;
    vector<double> peso;

    // Declaração do método de avaliação
    double calculaFitness(const vector<int>& rota) const;
};

#endif