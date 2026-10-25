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

// Função auxiliar para correr as 30 repetições e guardar em CSV
void executarExperimento(const string& nome_instancia, const string& caminho_arquivo, int limite_avaliacoes, int repeticoes) {
    ProblemaManutencao prob = carregarInstancia(caminho_arquivo);
    random_device rd;
    mt19937 rng(rd());

    // Abre o ficheiro CSV para escrita
    string nome_csv = "Results/resultados_" + nome_instancia + ".csv";
    ofstream arquivo_csv(nome_csv);
    
    // Cabeçalho do CSV
    arquivo_csv << "Execucao,Algoritmo,MelhorCusto\n";

    cout << "A iniciar experimento para: " << nome_instancia << " (" << repeticoes << " repeticoes)" << endl;

    for (int i = 1; i <= repeticoes; i++) {
        // 1. Greedy Descent (com Random Restart simulado para um orçamento fixo)
        int avaliacoes_gd = 0;
        double melhor_gd = -1.0;
        while (avaliacoes_gd < limite_avaliacoes) {
            vector<int> rota_ini = gerarRotaAleatoria(prob.n, rng);
            vector<int> otimo = executarGreedyDescent(rota_ini, prob, avaliacoes_gd, limite_avaliacoes);
            double custo = prob.calculaFitness(otimo);
            if (melhor_gd < 0 || custo < melhor_gd) melhor_gd = custo;
        }
        arquivo_csv << i << ",GreedyDescent," << melhor_gd << "\n";

        // 2. Simulated Annealing
        vector<int> rota_ini_sa = gerarRotaAleatoria(prob.n, rng);
        // Exemplo de parâmetros: T_inicial = 1000, alpha = 0.99 (ajustar conforme a instância)
        vector<int> otimo_sa = executarSimulatedAnnealing(rota_ini_sa, prob, limite_avaliacoes, 1000.0, 0.99, rng);
        arquivo_csv << i << ",SimulatedAnnealing," << prob.calculaFitness(otimo_sa) << "\n";

        // 3. Genetic Algorithm
        // Exemplo: População = 50, Taxa de mutação = 0.1
        vector<int> otimo_ga = executarGA(prob, limite_avaliacoes, 50, 0.1, rng);
        arquivo_csv << i << ",GeneticAlgorithm," << prob.calculaFitness(otimo_ga) << "\n";

        cout << "Execucao " << i << " concluida." << endl;
    }

    arquivo_csv.close();
    cout << "Resultados guardados em: " << nome_csv << endl;
}

int main() {
    // Orçamentos definidos na Secção 3 do guião
    // Instância Pequena: 50.000 avaliações, 30 execuções
    //executarExperimento("pequena", "instancias/manutencao_pequena.txt", 50000, 30);
    
    // Instância Intermédia: 150.000 avaliações, 30 execuções
     //executarExperimento("media", "instancias/manutencao_media.txt", 150000, 30);
    
    // Instância Grande: 300.000 avaliações, 10 execuções[cite: 6]
     executarExperimento("grande", "instancias/manutencao_grande.txt", 300000, 10);

    return 0;
}
	//Para rodar, usar mingw32-make no terminal