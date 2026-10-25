#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <numeric>
#include <algorithm>

ProblemaManutencao carregarInstancia(const string& caminhoArquivo) {
    ProblemaManutencao prob;
    ifstream arquivo(caminhoArquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << caminhoArquivo << endl;
        exit(1);
    }

    arquivo >> prob.n;
    int n = prob.n;

    // Redimensiona os vetores para n + 1 (índice 0 é a base, 1 a n são os ativos)
    vector<double> x(n + 1), y(n + 1);
    prob.tempoServico.resize(n + 1, 0.0);
    prob.prazo.resize(n + 1, 0.0);
    prob.peso.resize(n + 1, 0.0);

    // 1. Lê as coordenadas da base (índice 0)
    arquivo >> x[0] >> y[0];
    prob.tempoServico[0] = 0.0; // A base não tem tempo de serviço

    // 2. Lê os n ativos (índices 1 até n)
    for (int i = 1; i <= n; i++) {
        arquivo >> x[i] >> y[i] >> prob.tempoServico[i] >> prob.prazo[i] >> prob.peso[i];
    }

    arquivo.close();

    // 3. Pré-calcula a matriz de distâncias (tamanho n+1 x n+1)
    prob.dist.assign(n + 1, vector<double>(n + 1, 0.0));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            // Aplica a fórmula com arredondamento exigida pelo problema
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            prob.dist[i][j] = round(sqrt(dx * dx + dy * dy));
        }
    }

    return prob;
}

vector<int> gerarRotaAleatoria(int n, mt19937& rng) {
    vector<int> rota(n);
    // Preenche a rota com os índices dos ativos de 1 até n (ignora o 0, que é a base)
    iota(rota.begin(), rota.end(), 1); 
    shuffle(rota.begin(), rota.end(), rng);
    return rota;
}