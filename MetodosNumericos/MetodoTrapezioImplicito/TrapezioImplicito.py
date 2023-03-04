# Autoria de Guilherme C B de Brito e Gabriel D Tambelli - Última edição em 18/02/2023

import numpy as np
from math import exp, cos, sin, log, sqrt
import matplotlib.pyplot as plt
from typing import Callable, List

class TrapezioImplicito:
    """
    Classe simples para implementacao da tabela de convergencia para ordem qualquer, usando solucoes exatas ou nao.
    Ainda plota graficos referentes as solucoes aproximadas encontradas
    """
    def __init__(self, f: Callable, y0: int | float | List[float | int] | np.array, t0: int | float, T: int | float, numIter: int) -> None:
        self.__f = f
        self.__y0 =     [y0] if (type(y0) == int or type(y0) == float) else y0
        self.__t0 = t0
        self.__T = T
        self.__numIter = numIter

    # Funcao de discretizacao
    def __phi(self, t, f, yk, yk1, h) -> np.array:
        return (f(t, yk) + f(t+h, yk1))

    def __metodoDeUmPasso(self, n) -> float and np.array:
        yn = [np.array(self.__y0)] # Solucao aproximada
        tn = self.__t0 # Tempo 
        h = (self.__T - self.__t0)/n # Passo de integracao

        # Atualiza a solucao e o tempo ate chegarmos no fim do intervalo de tempo, T
        while(tn < self.__T):
            yk1Inicial = yn[-1]
            yn.append(self.__metodoPontoFixoTrapezio(yn[-1], tn, h, yk1Inicial))
            tn += h
        
        return h, np.array(yn) # Retorna o tamanho do passo de integracao considerado e a solucao aproximada em [t0, T]

    def __metodoPontoFixoTrapezio(self, yk: np.array, tk: float, h: float, chuteInicial: np.array = 0) -> np.array:
        yk1 = chuteInicial
        for _ in range(self.__numIter):
            yk1 = yk + 0.5*h*(self.__phi(tk, self.__f, yk, yk1, h))
        return yk1
    
    def tabelaDeConvergencia(self, n0: int = 16, r: int = 2, fileName : str = "tabelaDeConvergencia.txt", m: int = 10, normaErro: str = "Maximo", *solucoesExatas) -> None:
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
                n = n0 * r**(casoAtual)
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
    
    def plotSolucaoAproximada(self, ls, numeroPlots: int = 4, passoIntegracaoInicial: int = 16, multiplicadorPassoIntegracao: int = 2, unidadeX: str = "adimensional", unidadeY: str = "adimensional") -> None:
        for variavelEstadoAtual in range(len(self.__y0)):
            plt.figure(figsize=[8,6])
            plt.grid(visible=True)
            plt.title(f"Solucoes aproximadas para diferentes passos de integracao\n(Variavel de estado y{variavelEstadoAtual+1}(t))")
            plt.xlabel(f"t [{unidadeX}]")
            plt.ylabel(f"y{variavelEstadoAtual+1}(t) [{unidadeY}]")

            for plotAtual in range(numeroPlots):
                n = (passoIntegracaoInicial) * (multiplicadorPassoIntegracao)**(plotAtual)
                h, yn = self.__metodoDeUmPasso(n)
                dominio = np.arange(self.__t0, self.__T + h, h)
                plt.plot(dominio, yn[:,variavelEstadoAtual], ls = ls[plotAtual], c='k', label=f"y{variavelEstadoAtual+1}(t), n = {n}")

            plt.legend(loc= "best")
            plt.show()

if __name__ == "__main__":
    """
    Problema de Cauchy manufaturado(bidimensional) para implementar atividades verificar implementacao do algoritmo:        
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
    def f1(t, y):
        f0 = 2 * y[0] - y[1]
        f1 = y[0] + 2 * y[1]
        return np.array([f0, f1])

    # Tabela de convergencia para o caso bidimensional, usando solucoes exatas
    TrapezioImplicito(f1, [1, 0], 0, 2, 3).tabelaDeConvergencia(16, 2, "tabelaDeConvergencia2dSolucaoConhecida.txt", 10, "Maximo", y1e, y2e)

    """
    Problema de Cauchy de Lotka-Volterra(alpha = 1, beta = 1, gama = 1, delta = 1) para a ser resolvido pelo algoritmo implementado:        
    t no intervalo de [0, 40]
    {
        d/dt y1(t) = y1(t) - y1(t) * y2(t)
        d/dt y2(t) = -y2(t) + y2(t) * y1(t)
        y1(0) = 10; y2(0) = 10
    """
    # f(t, y) = (f0, f1) 2 dimensoes
    def f2(t, y):
        f0 = y[0] - y[0] * y[1]
        f1 = -y[1] + y[0] * y[1]
        return np.array([f0, f1])

    # Tabela de convergencia para o caso bidimensional, usando solucoes exatas
    TrapezioImplicito(f2, [10, 10], 0, 40, 3).tabelaDeConvergencia(1024, 2, "tabelaDeConvergencia2dSolucaoNaoConhecida.txt", 10, "Maximo")
    lineStyles = [(0, (1, 10)), (0, (1, 1)), (0, (5, 10)), (0, (5, 1)), (0, (3, 10, 1, 10)), (0, (3, 1, 1, 1))]
    TrapezioImplicito(f2, [10, 10], 0, 40, 3).plotSolucaoAproximada(lineStyles, 4, 1024, 2, "anos", "nº de individuos")
    