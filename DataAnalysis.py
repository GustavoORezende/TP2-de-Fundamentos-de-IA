import os

import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
from scipy.stats import mannwhitneyu

# Configuração de estilo visual para manter os gráficos consistentes.
sns.set_theme(style="whitegrid")


def gerar_boxplot(ficheiro_csv, nome_instancia):
    if not os.path.exists(ficheiro_csv):
        print(f"Ficheiro {ficheiro_csv} não encontrado.")
        return

    df = pd.read_csv(ficheiro_csv)

    # O boxplot resume a dispersão do custo por algoritmo e facilita a comparação visual.
    plt.figure(figsize=(10, 6))
    sns.boxplot(data=df, x="Algoritmo", y="MelhorCusto", palette="Set2")
    sns.stripplot(data=df, x="Algoritmo", y="MelhorCusto", color="black", alpha=0.5, jitter=True)

    plt.title(f"Distribuição do Melhor Custo - Instância {nome_instancia.capitalize()}", fontsize=14)
    plt.ylabel("Custo (Atraso Ponderado Total h)", fontsize=12)
    plt.xlabel("Algoritmo", fontsize=12)

    nome_saida = f"Graphs/boxplot_{nome_instancia}.png"
    plt.savefig(nome_saida, dpi=300, bbox_inches="tight")
    plt.close()
    print(f"Boxplot guardado como: {nome_saida}")


def gerar_curva_convergencia(ficheiro_csv, nome_instancia):
    if not os.path.exists(ficheiro_csv):
        print(f"Ficheiro {ficheiro_csv} não encontrado. Salte esta etapa se ainda não exportou os logs de convergência.")
        return

    df = pd.read_csv(ficheiro_csv)

    # A curva mostra como a melhor solução melhora ao longo do número de avaliações.
    plt.figure(figsize=(10, 6))
    sns.lineplot(data=df, x="Avaliacoes", y="MelhorCustoGlobal", hue="Algoritmo", linewidth=2)

    plt.title(f"Curva de Convergência - Instância {nome_instancia.capitalize()}", fontsize=14)
    plt.ylabel("Melhor Custo Encontrado", fontsize=12)
    plt.xlabel("Número de Avaliações", fontsize=12)

    nome_saida = f"Graphs/convergencia_{nome_instancia}.png"
    plt.savefig(nome_saida, dpi=300, bbox_inches="tight")
    plt.close()
    print(f"Curva de convergência guardada como: {nome_saida}")


def aplicar_teste_estatistico(ficheiro_csv):
    df = pd.read_csv(ficheiro_csv)

    custos_sa = df[df["Algoritmo"] == "SimulatedAnnealing"]["MelhorCusto"]
    custos_gd = df[df["Algoritmo"] == "GreedyDescent"]["MelhorCusto"]

    # Teste não paramétrico para verificar se o SA tende a produzir custos menores.
    estatistica, p_valor = mannwhitneyu(custos_sa, custos_gd, alternative='less')

    print("--- Teste de Mann-Whitney (SA vs GD) ---")
    print(f"Estatística U: {estatistica}")
    print(f"Valor-p: {p_valor:.2e}")

    if p_valor < 0.05:
        print("Conclusão: O Simulated Annealing é estatisticamente superior (p < 0.05).")
    else:
        print("Conclusão: Não há evidências suficientes para declarar um vencedor (p >= 0.05).")


if __name__ == "__main__":
    # Gera os gráficos e o teste estatístico para cada instância do estudo.
    gerar_boxplot("Results/resultados_pequena.csv", "pequena")
    gerar_boxplot("Results/resultados_media.csv", "media")
    gerar_boxplot("Results/resultados_grande.csv", "grande")
    gerar_curva_convergencia("Results/convergencia_pequena.csv", "pequena")
    gerar_curva_convergencia("Results/convergencia_media.csv", "media")
    gerar_curva_convergencia("Results/convergencia_grande.csv", "grande")
    aplicar_teste_estatistico("Results/resultados_grande.csv")