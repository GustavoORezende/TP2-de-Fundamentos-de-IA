import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os
from scipy.stats import mannwhitneyu
# Configuração de estilo visual
sns.set_theme(style="whitegrid")

def gerar_boxplot(ficheiro_csv, nome_instancia):
    """Lê os resultados finais e gera o boxplot comparativo."""
    if not os.path.exists(ficheiro_csv):
        print(f"Ficheiro {ficheiro_csv} não encontrado.")
        return

    df = pd.read_csv(ficheiro_csv)
    
    plt.figure(figsize=(10, 6))
    ax = sns.boxplot(data=df, x="Algoritmo", y="MelhorCusto", palette="Set2")
    
    # Adiciona os pontos individuais por cima do boxplot para mostrar a dispersão
    sns.stripplot(data=df, x="Algoritmo", y="MelhorCusto", color="black", alpha=0.5, jitter=True)
    
    plt.title(f"Distribuição do Melhor Custo - Instância {nome_instancia.capitalize()}", fontsize=14)
    plt.ylabel("Custo (Atraso Ponderado Total h)", fontsize=12)
    plt.xlabel("Algoritmo", fontsize=12)
    
    nome_saida = f"boxplot_{nome_instancia}.png"
    plt.savefig(nome_saida, dpi=300, bbox_inches="tight")
    plt.close()
    print(f"Boxplot guardado como: {nome_saida}")

def gerar_curva_convergencia(ficheiro_csv, nome_instancia):
    """Gera o gráfico de convergência (Custo vs Avaliações) se o ficheiro existir."""
    if not os.path.exists(ficheiro_csv):
        print(f"Ficheiro {ficheiro_csv} não encontrado. Salte esta etapa se ainda não exportou os logs de convergência.")
        return

    df = pd.read_csv(ficheiro_csv)
    
    plt.figure(figsize=(10, 6))
    # Assume que o CSV tem as colunas: 'Avaliacoes', 'MelhorCustoGlobal', 'Algoritmo'
    sns.lineplot(data=df, x="Avaliacoes", y="MelhorCustoGlobal", hue="Algoritmo", linewidth=2)
    
    plt.title(f"Curva de Convergência - Instância {nome_instancia.capitalize()}", fontsize=14)
    plt.ylabel("Melhor Custo Encontrado", fontsize=12)
    plt.xlabel("Número de Avaliações", fontsize=12)
    
    nome_saida = f"convergencia_{nome_instancia}.png"
    plt.savefig(nome_saida, dpi=300, bbox_inches="tight")
    plt.close()
    print(f"Curva de convergência guardada como: {nome_saida}")

#if __name__ == "__main__":
    # Gera o boxplot para a instância pequena 
    #gerar_boxplot("Results/resultados_pequena.csv", "pequena")
    #gerar_boxplot("Results/resultados_media.csv", "media")
    #gerar_boxplot("Results/resultados_grande.csv", "grande")

def aplicar_teste_estatistico(ficheiro_csv):
    # Lê os dados guardados em disco
    df = pd.read_csv(ficheiro_csv)
    
    # Isola os arrays com os custos de cada algoritmo
    custos_sa = df[df["Algoritmo"] == "SimulatedAnnealing"]["MelhorCusto"]
    custos_gd = df[df["Algoritmo"] == "GreedyDescent"]["MelhorCusto"]
    
    # Aplica o teste de Mann-Whitney
    # alternative='less' testa se a distribuição do SA é estocasticamente menor (melhor custo) que a do GD
    estatistica, p_valor = mannwhitneyu(custos_sa, custos_gd, alternative='less')
    
    print("--- Teste de Mann-Whitney (SA vs GD) ---")
    print(f"Estatística U: {estatistica}")
    print(f"Valor-p: {p_valor:.2e}") # Exibe em notação científica
    
    if p_valor < 0.05:
        print("Conclusão: O Simulated Annealing é estatisticamente SUPERIOR (p < 0.05).")
    else:
        print("Conclusão: Não há evidências suficientes para declarar um vencedor (p >= 0.05).")

# Chama a função para o teu ficheiro da instância grande
aplicar_teste_estatistico("Results/resultados_grande.csv")