#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include "Entities/ProblemaManutencao.hpp"
#include "Functions/Utils.hpp"
#include "Algorithms/GreedyDescent.hpp"
#include "Algorithms/SimulatedAnnealing.hpp"
#include "Algorithms/GeneticAlgorithm.hpp"

using namespace std;

// Cada execução recolhe o melhor custo de cada algoritmo para comparar desempenho.
void executarExperimento(const string& nome_instancia, const string& caminho_arquivo, int limite_avaliacoes, int repeticoes) {
    ProblemaManutencao prob = carregarInstancia(caminho_arquivo);
    random_device rd;
    mt19937 rng(rd());

    string nome_csv = "Results/resultados_" + nome_instancia + ".csv";
    ofstream arquivo_csv(nome_csv);
    arquivo_csv << "Execucao,Algoritmo,MelhorCusto\n";

    string nome_conv = "Results/convergencia_" + nome_instancia + ".csv";
    ofstream arquivo_conv(nome_conv);
    arquivo_conv << "Execucao,Avaliacoes,MelhorCustoGlobal,MediaPopulacao,Algoritmo\n";

    cout << "A iniciar experimento para: " << nome_instancia << " (" << repeticoes << " repeticoes)" << endl;

    for (int i = 1; i <= repeticoes; i++) {
        // O Greedy Descent faz vários restarts para aumentar a chance de sair de mínimos locais.
        int avaliacoes_gd = 0;
        double melhor_gd = -1.0;
        while (avaliacoes_gd < limite_avaliacoes) {
            vector<int> rota_ini = gerarRotaAleatoria(prob.n, rng);
            vector<int> otimo = executarGreedyDescent(rota_ini, prob, avaliacoes_gd, limite_avaliacoes);
            double custo = prob.calculaFitness(otimo);
            if (melhor_gd < 0 || custo < melhor_gd) melhor_gd = custo;
        }
        arquivo_csv << i << ",GreedyDescent," << melhor_gd << "\n";

        // Simulated Annealing e GA usam uma rota inicial aleatória para explorar diferentes regiões do espaço.
        vector<int> rota_ini_sa = gerarRotaAleatoria(prob.n, rng);
        vector<int> otimo_sa = executarSimulatedAnnealing(rota_ini_sa, prob, limite_avaliacoes, 1000.0, 0.99, rng, arquivo_conv, i);
        arquivo_csv << i << ",SimulatedAnnealing," << prob.calculaFitness(otimo_sa) << "\n";

        vector<int> otimo_ga = executarGA(prob, limite_avaliacoes, 50, 0.1, rng, arquivo_conv, i);
        arquivo_csv << i << ",GeneticAlgorithm," << prob.calculaFitness(otimo_ga) << "\n";

        cout << "Execucao " << i << " concluida." << endl;
    }

    arquivo_csv.close();
    cout << "Resultados guardados em: " << nome_csv << endl;
}

// As instâncias variam em tamanho e orçamento para comparar escalabilidade e qualidade.
int main() {
    executarExperimento("pequena", "instancias/manutencao_pequena.txt", 50000, 30);
    executarExperimento("media", "instancias/manutencao_media.txt", 150000, 30);
    executarExperimento("grande", "instancias/manutencao_grande.txt", 300000, 10);

    return 0;
}