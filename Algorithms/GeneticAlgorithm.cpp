#include "GeneticAlgorithm.hpp"
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <fstream>

// Order Crossover (OX) para permutações[cite: 5]
vector<int> cruzamentoOX(const vector<int>& pai1, const vector<int>& pai2, mt19937& rng) {
    int n = pai1.size();
    vector<int> filho(n, -1);
    
    uniform_int_distribution<int> dist(0, n - 1);
    int corte1 = dist(rng);
    int corte2 = dist(rng);
    if (corte1 > corte2) swap(corte1, corte2);

    unordered_set<int> no_filho;
    
    // Copia o trecho central do pai 1
    for (int i = corte1; i <= corte2; i++) {
        filho[i] = pai1[i];
        no_filho.insert(pai1[i]);
    }

    // Preenche o resto com o pai 2, na ordem circular
    int pos_filho = (corte2 + 1) % n;
    int pos_pai2 = (corte2 + 1) % n;
    
    while (filho[pos_filho] == -1) {
        if (no_filho.find(pai2[pos_pai2]) == no_filho.end()) {
            filho[pos_filho] = pai2[pos_pai2];
            pos_filho = (pos_filho + 1) % n;
        }
        pos_pai2 = (pos_pai2 + 1) % n;
    }
    
    return filho;
}

vector<int> executarGA(const ProblemaManutencao& prob, int limite_avaliacoes, int tamanho_populacao, double taxa_mutacao, mt19937& rng, ofstream& log_conv, int execucao) {
    int avaliacoes_gastas = 0;
    vector<vector<int>> populacao(tamanho_populacao, vector<int>(prob.n));
    vector<double> fitness_pop(tamanho_populacao);

    // Inicialização aleatória[cite: 5]
    for (int i = 0; i < tamanho_populacao; i++) {
        iota(populacao[i].begin(), populacao[i].end(), 1);
        shuffle(populacao[i].begin(), populacao[i].end(), rng);
        fitness_pop[i] = prob.calculaFitness(populacao[i]);
        avaliacoes_gastas++;
    }

    vector<int> melhor_rota_global = populacao[0];
    double melhor_custo_global = fitness_pop[0];

    uniform_real_distribution<double> dist_mutacao(0.0, 1.0);
    uniform_int_distribution<int> torneio(0, tamanho_populacao - 1);

    while (avaliacoes_gastas < limite_avaliacoes) {
        vector<vector<int>> nova_populacao;

        for (int i = 0; i < tamanho_populacao / 2; i++) {
            if (avaliacoes_gastas >= limite_avaliacoes) break;

            // Seleção por Torneio (minimizar fitness)[cite: 5]
            int p1 = torneio(rng); int p2 = torneio(rng);
            int pai1 = (fitness_pop[p1] < fitness_pop[p2]) ? p1 : p2;

            int p3 = torneio(rng); int p4 = torneio(rng);
            int pai2 = (fitness_pop[p3] < fitness_pop[p4]) ? p3 : p4;

            // Cruzamento[cite: 5]
            vector<int> filho1 = cruzamentoOX(populacao[pai1], populacao[pai2], rng);
            vector<int> filho2 = cruzamentoOX(populacao[pai2], populacao[pai1], rng);

            // Mutação (Swap simples)[cite: 5]
            if (dist_mutacao(rng) < taxa_mutacao) swap(filho1[torneio(rng) % prob.n], filho1[torneio(rng) % prob.n]);
            if (dist_mutacao(rng) < taxa_mutacao) swap(filho2[torneio(rng) % prob.n], filho2[torneio(rng) % prob.n]);

            nova_populacao.push_back(filho1);
            nova_populacao.push_back(filho2);
        }

        populacao = nova_populacao;
        double soma_fitness = 0.0;

        for (int i = 0; i < tamanho_populacao; i++) {
            if (avaliacoes_gastas >= limite_avaliacoes) break;
            fitness_pop[i] = prob.calculaFitness(populacao[i]);
            avaliacoes_gastas++;

            soma_fitness += fitness_pop[i];

            if (fitness_pop[i] < melhor_custo_global) {
                melhor_custo_global = fitness_pop[i];
                melhor_rota_global = populacao[i];
            }
        }
        
        log_conv << execucao << "," << avaliacoes_gastas << "," << melhor_custo_global << "," << (soma_fitness / tamanho_populacao) << ",GeneticAlgorithm\n";    }

    return melhor_rota_global;
}