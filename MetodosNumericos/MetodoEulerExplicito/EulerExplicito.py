import numpy as np
from math import exp, cos, sin, log, sqrt
import matplotlib.pyplot as plt

class EulerExplicito:
    """
    Classe simples para implementacao da tabela de convergencia para ordem qualquer, usando solucoes exatas ou nao.
    Ainda plota graficos referentes as solucoes aproximadas encontradas
    """
    def __init__(self, f, y0: int | list, t0: int | float, T: int | float) -> None:
        self.__f = f
        self.__y0 = [y0] if type(y0) == int else y0
        self.__t0 = t0
        self.__T = T

    # Funcao de discretizacao
    def __phi(self, t, f, y, h):
        return f(t, y)

    def __metodoDeUmPasso(self, n):
        yn = [np.array(self.__y0)] # Solucao aproximada
        tn = self.__t0 # Tempo 
        h = (self.__T - self.__t0)/n # Passo de integracao

        # Atualiza a solucao e o tempo ate chegarmos no fim do intervalo de tempo, T
        while(tn < self.__T):
            yn.append(yn[-1] + h * self.__phi(tn, self.__f, yn[-1], h))
            tn += h
        
        return h, np.array(yn) # Retorna o tamanho do passo de integracao considerado e a solucao aproximada em [t0, T]
    
    def tabelaDeConvergencia(self,r: int = 2, fileName : str = "tabelaDeConvergencia.txt", m: int = 10, normaErro: str = "Maximo", *solucoesExatas) -> None:
        # Verifica se foram passadas solucoes exatas para a construcao da tabela
        solucoesExatasEmpty = True if len(solucoesExatas) == 0 else False
        # Inicializacao de listas para armazenar diferenca entre solucoes, erros, tamanhos dos passos de integracao e as solucoes aproximadas
        d = m * [0]
        e = m * [0]
        h = m * [0]
        yn = m * [self.__y0]

        # Nome do arquivo de destino da saida
        path = f"./{fileName}"
        with open(path, 'w') as file:
            print("\tTabela de Convergencia")  
            for casoAtual in range(m):
                # Calculo do passo de integracao e solucao aproximada do caso atual
                n = 16 * r**(casoAtual)
                h[casoAtual], yn[casoAtual] = self.__metodoDeUmPasso(n)
                # Se nao foi passada a solucao exata, o erro sera a diferenca das solucoes aproximadas para
                # tamanhos de passos de integracao vizinhos, nesse caso, para h e h/2, dividido por 2^(p-barra) - 1,
                # onde p-barra eh a ordem de convergencia estimada do metodo
                if solucoesExatasEmpty:
                    d[casoAtual] = self.__diferencaSolucoes(yn[casoAtual-1][-1], yn[casoAtual][-1], normaErro) if casoAtual > 0 else 0
                # Caso tenhamos a solucao exata, erro eh a diferenca da solucao aproximada e a exata
                else:
                    solucoesExatasFinal = [yie(self.__T) for yie in solucoesExatas]
                    d[casoAtual] = e[casoAtual] = self.__diferencaSolucoes(solucoesExatasFinal, yn[casoAtual][-1], normaErro)
                
                # Calculo da ordem de convergencia estimada e ajuste do erro caso nao se tenha solucao exata
                q = d[casoAtual-1] / d[casoAtual] if casoAtual > 0 else 0
                inicioCalculoOrdemDeConnvergencia = 1 if solucoesExatasEmpty else 0
                p = abs(log(q) / log(r)) if casoAtual > inicioCalculoOrdemDeConnvergencia else 0
                e[casoAtual] = abs((d[casoAtual])/((r**p) - 1)) if (casoAtual > 1 and solucoesExatasEmpty) else e[casoAtual]
                # Saida das informacoes para txt e console
                file.write("%5d & %9.3e & %9.3e & %9.3e \\\\\n" % (n, h[casoAtual], e[casoAtual], p))
                print("%5d & %9.3e & %9.3e & %9.3e \\\\" % (n, h[casoAtual], e[casoAtual], p))

    def __diferencaSolucoes(self, ye, yn, normaErro: str = "Maximo") -> float:
        # Calculo da diferenca entre dois vetores para diferentes normas passadas como argumentos
        dif = 0
        match normaErro:
            case "Maximo":
                for num in range(len(ye)):
                    difAtual = abs(ye[num] - yn[num])
                    dif = difAtual if difAtual > dif else dif
            case "Euclidiana":
                somaQuadrados = 0
                for num in range(len(ye)):
                    somaQuadrados += (ye[num] - yn[num])**(2)
                dif = sqrt(somaQuadrados)
        return dif
    
    def plotSolucaoAproximada(self, ls, numeroPlots: int = 4, passoIntegracaoInicial: int = 16, multiplicadorPassoIntegracao: int = 2) -> None:
        for variavelEstadoAtual in range(len(self.__y0)):
            plt.figure(figsize=[8,6])
            plt.grid(visible=True)
            plt.title(f"Solucoes aproximadas para diferentes passos de integracao\n(Variavel de estado y{variavelEstadoAtual+1}(t))")
            plt.xlabel("t [adimensional]")
            plt.ylabel(f"y{variavelEstadoAtual+1}(t) [adimensional]")

            for plotAtual in range(numeroPlots):
                n = (passoIntegracaoInicial) * (multiplicadorPassoIntegracao)**(plotAtual)
                h, yn = self.__metodoDeUmPasso(n)
                dominio = np.arange(self.__t0, self.__T + h, h)
                plt.plot(dominio, yn[:,variavelEstadoAtual], ls = ls[plotAtual], c='k', label=f"y{variavelEstadoAtual+1}(t), n = {n}")

            plt.legend(loc= "best")
            plt.show()

# Executa as atividades da tarefa 01, apenas, se esse arquivo, necessariamente esse, for "rodado"
if __name__ == "__main__":
    """
    Problema de Cauchy manufaturado escalar usado para implementar atividade 2.1 da tarefa 1:
    (Crescimento populacional, modelagem simples)
    t no intervalo [0, 2]
    {
        d/dt y(t) = 3 * y(t)
        y(0) = 5
    }
    Solucao exata: ye(t) = 5e^(3t)
    """
    # Solucao exata
    def ye(t):
        return 5 * exp(3*t)
    # f = d/dt y(t)
    def f1(t, y):
        return 3 * y

    # Tabela de convergencia para o caso escalar
    EulerExplicito(f1, 5, 0, 2).tabelaDeConvergencia(2, "tabelaDeConvergenciaEscalar.txt", 12, "Maximo", ye)

    """
    Problema de Cauchy manufaturado(bidimensional) para implementar atividades 2.2 e 2.3 da tarefa 1:
    (OBS): Na atividade 2.2, sera usado juntamente com sua solucao exata; ja na 2.3, usaremos apenas
        o problema de Cauchy, sem solucao exata 
        
    t no intervalo de [0, 2]
    {
        d/dt y1(t) = 2y1(t) - y2(t)
        d/dt y2(t) = y1(t) + 2y2(t)
        y1(0) = 1; y2(0) = 0
    }
    Solucao exata: {
                    y1(t) = cos(t) * e^(2t)
                    y2(t) = sen(t) * e^(2t)
                }
    """
    # Solucoes exatas
    def y1e(t):
        return cos(t) * exp(2*t)
    def y2e(t):
        return sin(t) * exp(2*t)
    # f(t, y) = (f0, f1) 2 dimensoes
    def f2(t, y):
        f0 = 2 * y[0] - y[1]
        f1 = y[0] + 2 * y[1]
        return np.array([f0, f1])

    # Tabela de convergencia para o caso bidimensional, usando solucoes exatas
    EulerExplicito(f2, [1, 0], 0, 2).tabelaDeConvergencia(2, "tabelaDeConvergencia2dSolucaoConhecida.txt", 12, "Maximo", y1e, y2e)

    # Tabela de convergencia para o caso bidimensional, sem usar solucoes exatas do problema
    EulerExplicito(f2, [1, 0], 0, 2).tabelaDeConvergencia(2, "tabelaDeConvergencia2dSolucaoNaoConhecida.txt", 12, "Euclidiana")

    # Plot dos graficos das solucoes aproximadas para diferentes valores de n, para o caso da atividade 2.3
    # Estilos sao os estilos da linha usados para os graficos
    estilos = [(0, (1, 10)), (0, (1, 1)), (0, (5, 10)), (0, (5, 1)), (0, (3, 10, 1, 10)), (0, (3, 1, 1, 1))]
    EulerExplicito(f2, [1, 0], 0, 2).plotSolucaoAproximada(estilos, 6, 16, 4)