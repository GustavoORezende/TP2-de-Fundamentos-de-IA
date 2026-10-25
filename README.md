TP2: Busca Local e Algoritmo Genético

Este repositório contém a implementação do Trabalho Prático 2 da disciplina de Fundamentos de Inteligência Artificial (UFMG). O objetivo do trabalho é resolver o problema de sequenciamento de manutenção de ativos em uma rede de distribuição, minimizando o atraso ponderado total através de metaheurísticas.

🛠️ Algoritmos Implementados

Greedy Descent (Best Improvement) com Random Restart e vizinhança 2-opt.

Simulated Annealing com resfriamento geométrico.

Algoritmo Genético com Order Crossover (OX) e mutação por Swap.

📂 Estrutura do Projeto

Entities/: Estruturas de dados e modelagem do problema (cálculo de fitness).

Functions/: Funções utilitárias (leitura de instâncias, geradores aleatórios).

Algorithms/: Implementação isolada de cada algoritmo de busca.

instancias/: Arquivos de texto originais fornecidos (pequena, media, grande).

main.cpp: Orquestrador dos experimentos e exportação de dados para .csv.

Makefile: Script de compilação automatizada.

🚀 Como Compilar e Rodar (C++)

O projeto foi desenvolvido em C++17 e utiliza um Makefile para facilitar a compilação com otimização máxima (-O3), garantindo alta performance nas milhões de avaliações.

Abra o terminal na pasta raiz do projeto.

Compile o código executando:

make


Execute o programa:

make run


Limpe os binários (opcional, útil antes de compactar o projeto):

make clean


Nota: Ao rodar o executável, o programa lerá os arquivos da pasta instancias/ e gerará automaticamente arquivos .csv com os resultados de cada execução independente.

📊 Como Gerar os Gráficos e Testes (Python)

Para gerar os boxplots, as curvas de convergência e executar o teste estatístico (Mann-Whitney), utilize o script Python fornecido.

Instale as dependências (caso não tenha):

pip install pandas seaborn matplotlib scipy


Execute o script (certifique-se de que os .csv foram gerados pelo C++ no passo anterior):

python nome_do_script.py


Isso irá gerar os gráficos em formato .png na mesma pasta, prontos para serem inseridos no relatório.
