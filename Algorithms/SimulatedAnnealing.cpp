#include "SimulatedAnnealing.hpp"
#include <cmath>
#include <algorithm>

vector<int> aplicarSwapAleatorio(const vector<int>& rota, mt19937& rng) {
    vector<int> vizinho = rota;
    uniform_int_distribution<int> dist(0, rota.size() - 1);
    int i = dist(rng);
    int j = dist(rng);
    swap(vizinho[i], vizinho[j]);
    return vizinho;
}

vector<int> executarSimulatedAnnealing(const vector<int>& rota_inicial, const ProblemaManutencao& prob, int limite_avaliacoes, double T_inicial, double alpha, mt19937& rng) {
    vector<int> rota_atual = rota_inicial;
    vector<int> melhor_rota = rota_inicial;
    
    double custo_atual = prob.calculaFitness(rota_atual);
    double melhor_custo = custo_atual;
    double T = T_inicial;
    int avaliacoes_gastas = 1;

    uniform_real_distribution<double> probabilidade(0.0, 1.0);

    while (avaliacoes_gastas < limite_avaliacoes) {
        vector<int> vizinho = aplicarSwapAleatorio(rota_atual, rng);
        double custo_vizinho = prob.calculaFitness(vizinho);
        avaliacoes_gastas++;

        double delta = custo_vizinho - custo_atual;

        // Se for melhor, ou se a probabilidade de Gibbs permitir a piora
        if (delta <= 0 || probabilidade(rng) < exp(-delta / T)) {
            rota_atual = vizinho;
            custo_atual = custo_vizinho;

            if (custo_atual < melhor_custo) {
                melhor_custo = custo_atual;
                melhor_rota = rota_atual;
            }
        }

        // Resfriamento geométrico[cite: 5]
        T *= alpha; 
    }

    return melhor_rota;
}