#include "ProblemaManutencao.hpp"
#include <algorithm>

double ProblemaManutencao::calculaFitness(const vector<int>& rota) const {
    double tempoAtual = 0.0;
    double custoTotal = 0.0;
    int localAnterior = 0;

    for (int ativo : rota) {
        tempoAtual += dist[localAnterior][ativo];
        tempoAtual += tempoServico[ativo];
        
        double atraso = max(0.0, tempoAtual - prazo[ativo]);
        custoTotal += atraso * peso[ativo];
        
        localAnterior = ativo;
    }
    return custoTotal;
}