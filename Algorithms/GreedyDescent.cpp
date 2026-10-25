#include "GreedyDescent.hpp"
#include <algorithm>

vector<int> aplica2Opt(const vector<int>& rota, int i, int j) {
    vector<int> vizinho = rota;
    reverse(vizinho.begin() + i, vizinho.begin() + j + 1);
    return vizinho;
}

vector<int> executarGreedyDescent(const vector<int>& rota_inicial, const ProblemaManutencao& prob, int& avaliacoes_gastas, int limite_avaliacoes) {
    vector<int> melhor_rota_local = rota_inicial;
    double menor_custo_local = prob.calculaFitness(melhor_rota_local);
    avaliacoes_gastas++;

    bool houve_melhoria = true;

    while (houve_melhoria && avaliacoes_gastas < limite_avaliacoes) {
        houve_melhoria = false;
        vector<int> melhor_vizinho = melhor_rota_local;
        double menor_custo_vizinhanca = menor_custo_local;

        for (int i = 0; i < prob.n - 1; i++) {
            for (int j = i + 1; j < prob.n; j++) {
                if (avaliacoes_gastas >= limite_avaliacoes) break;

                vector<int> vizinho = aplica2Opt(melhor_rota_local, i, j);
                double custo_vizinho = prob.calculaFitness(vizinho);
                avaliacoes_gastas++;

                if (custo_vizinho < menor_custo_vizinhanca) {
                    menor_custo_vizinhanca = custo_vizinho;
                    melhor_vizinho = vizinho;
                    houve_melhoria = true;
                }
            }
            if (avaliacoes_gastas >= limite_avaliacoes) break;
        }

        if (houve_melhoria) {
            melhor_rota_local = melhor_vizinho;
            menor_custo_local = menor_custo_vizinhanca;
        }
    }
    return melhor_rota_local;
}