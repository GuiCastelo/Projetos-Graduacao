# Autoria de Guilherme C B de Brito e Gabriel D Tambelli
from TrapezioImplicito import TrapezioImplicito
from Quadratura import Quadratura
from typing import Callable
from abc import ABC, abstractmethod
import numpy as np
from math import exp, sinh, sqrt, cos, atan, pi

class RLC(ABC):
    """
    Classe base para obtencao de respostas de circuitos RLC, podendo ser corrente(i(t)), no caso do RLC serie, ou tensao(v(t)) no caso do RLC
    paralelo. Tais respostas sao obtidas a partir da equacao difero-integral, utilizando como metodos numericos a quadratura numerico, em especifico
    o metodo do Trapezio, e metodo de Trapezio Implicito em conjunto com MAS.
    Recebe os parametros de um circuito RLC como entrada, alem do tempo T ate o qual se deseja observar a resposta, considera-se o tempo
    inicial do circuito t0 = 0. 
    """
    def __init__(self, i0: float, v0: float, T: float, R: float, C: float, L: float) -> None:
        self.i0 = i0
        self.v0 = v0
        self.T = T
        self.R = R
        self.C = C
        self.L = L

    @abstractmethod
    def tabelaConvergenciaRLC(self, n0: int = 16, r: int = 2, fileName: str = "tabelaConvergenciaRLC.txt", m: int = 10, normaErro: str = "Maximo", *solucoesExatas) -> None:
        pass
    
    @abstractmethod
    def plotSolucaoAproximada(self, ls, numeroPlots: int = 4, passoIntegracaoInicial: int = 16, multiplicadorPassoIntegracao: int = 2):
        pass

class RLC_Serie(RLC):
    def __init__(self, i0: float, v0: float, T: float, R: float, C: float, L: float, Vg: Callable[[float], float]) -> None:
        super().__init__(i0, v0, T, R, C, L)
        self.Vg = Vg

    def f(self, t: float, h: float, yn: np.array):
        # Onde tem y(t), considera-se o t atual como sendo o ultimo numero no np array i passado como parametro
        return self.Vg(t)/self.L - ((self.R/self.L)*yn[-1][0] + (1/(self.L*self.C))*Quadratura(yn, h) + self.v0/self.L) 
    
    def tabelaConvergenciaRLC(self, n0: int = 16, r: int = 2, fileName: str = "tabelaConvergenciaRLC_Serie.txt", m: int = 10, normaErro: str = "Maximo", *solucoesExatas) -> None:
        TrapezioImplicito(self.f, self.i0, 0, self.T, 3).tabelaDeConvergencia(n0, r, fileName, m, normaErro, *solucoesExatas)
    
    def plotSolucaoAproximada(self, ls, numeroPlots: int = 4, passoIntegracaoInicial: int = 16, multiplicadorPassoIntegracao: int = 2):
        TrapezioImplicito(self.f, self.i0, 0, self.T, 3).plotSolucaoAproximada(ls, numeroPlots, passoIntegracaoInicial, multiplicadorPassoIntegracao,\
                                                                               's', 'A', 'i')

class RLC_Paralelo(RLC):
    def __init__(self, i0: float, v0: float, T: float, R: float, C: float, L: float, Ig: Callable[[float], float]) -> None:
        super().__init__(i0, v0, T, R, C, L)
        self.Ig = Ig

    def f(self, t: float, h: float, yn: np.array):
        # Onde tem y(t), considera-se o t atual como sendo o ultimo numero no np array i passado como parametro
        return self.Ig(t)/self.C - (1/(self.R * self.C)*yn[-1][0] + (1/(self.L*self.C))*Quadratura(yn, h) + self.i0/self.C)
    
    def tabelaConvergenciaRLC(self, n0: int = 16, r: int = 2, fileName: str = "tabelaConvergenciaRLC_Paralelo.txt", m: int = 10, normaErro: str = "Maximo", *solucoesExatas) -> None:
        TrapezioImplicito(self.f, self.v0, 0, self.T, 3).tabelaDeConvergencia(n0, r, fileName, m, normaErro, *solucoesExatas)
    
    def plotSolucaoAproximada(self, ls, numeroPlots: int = 4, passoIntegracaoInicial: int = 16, multiplicadorPassoIntegracao: int = 2):
        TrapezioImplicito(self.f, self.v0, 0, self.T, 3).plotSolucaoAproximada(ls, numeroPlots, passoIntegracaoInicial, multiplicadorPassoIntegracao,\
                                                                               's', 'V', 'v')
        
if __name__ == '__main__':
    """
    Analise do circuito RLC série livre com resposta criticamente amortecida
    R = 10 ohms, L = 1H, C = 0.04F, i0 = 10A, v0 = 0V, T = 2s
    """
    def Vg_livre(t):
        return 0
    def ye_crit_amortecido(t):
        return 10*exp(-5*t)*(1 - 5*t)
    lineStyles = [(0, (1, 10)), (0, (1, 1)), (0, (5, 10)), (0, (5, 1)), (0, (3, 10, 1, 10)), (0, (3, 1, 1, 1))]
    RLC_Serie(10, 0, 2, 10, 4e-2, 1, Vg_livre).tabelaConvergenciaRLC(16, 2, "./tabelasConvergencia/tabelaConvergenciaRLC_SerieCrit.txt", 10, "Maximo", ye_crit_amortecido)
    RLC_Serie(10, 0, 2, 10, 4e-2, 1, Vg_livre).plotSolucaoAproximada(lineStyles, 4, 16, 4)

    """
    Analise do circuito RLC série livre com resposta superamortecida
    R = 4 ohms, L = 1H, C = 4/9F, i0 = 0A, v0 = 10V, T = 2s
    """
    def ye_super_amortecido(t):
        return -5*exp(-2.5*t)*sinh(2*t)
    RLC_Serie(0, 10, 5, 5, 4/9, 1, Vg_livre).tabelaConvergenciaRLC(16, 2, "./tabelasConvergencia/tabelaConvergenciaRLC_SerieSuper.txt", 10, "Maximo", ye_super_amortecido)
    RLC_Serie(0, 10, 5, 5, 4/9, 1, Vg_livre).plotSolucaoAproximada(lineStyles, 4, 16, 4)

    """
    Analise do circuito RLC paralelo livre com resposta subamortecida
    R = 4 ohms, L = 8/82H, C = 1/8F, i0 = 1A, v0 = 3V, T = 6s
    """
    def Ig_livre(t):
        return 0
    def ye_sub_amortecido(t):
        psi = atan(11/27) # 8/27 + 1/9
        vm = sqrt(850/81) # sqrt(9 + (1/3 + 8/9)^2)
        return vm*exp(-t)*cos(9*t + psi)
    RLC_Paralelo(1, 3, 6, 4, 1/8, 8/82, Ig_livre).tabelaConvergenciaRLC(16, 2, "./tabelasConvergencia/tabelaConvergenciaRLC_ParaleloSub.txt", 10, "Maximo", ye_sub_amortecido)
    RLC_Paralelo(1, 3, 6, 4, 1/8, 8/82, Ig_livre).plotSolucaoAproximada(lineStyles, 4, 32, 4)

    """
    Analise do circuito RLC paralelo para uma fonte de corrente exponencial decrescente
    R = 4 ohms, L = 8/82H, C = 1/8F, i0 = 0A, v0 = 0V, T = 8s
    """
    def Ig_exponencial(t):
        return 5*exp(-0.5*t)
    RLC_Paralelo(0, 0, 8, 4, 1/8, 8/82, Ig_exponencial).tabelaConvergenciaRLC(16, 2, "./tabelasConvergencia/tabelaConvergenciaRLC_Paraleloexponencial.txt", 10, "Maximo")
    RLC_Paralelo(0, 0, 8, 4, 1/8, 8/82, Ig_exponencial).plotSolucaoAproximada(lineStyles, 4, 64, 4)

    """
    Analise do circuito RLC serie para uma fonte dente de sabre de periodo 4s, variando entre -1 e 1 e começando em -1
    R = 5 ohms, L = 1H, C = 4/9F, i0 = 0A, v0 = 0V, T = 12s
    """
    def Vg_senoidal(t):
        return 2*cos(3*t - (2*pi)/9)
    RLC_Serie(0, 0, 8, 5, 4/9, 1, Vg_senoidal).tabelaConvergenciaRLC(32, 2, "./tabelasConvergencia/tabelaConvergenciaRLC_Seriesenoidal.txt", 10, "Maximo")
    RLC_Serie(0, 0, 8, 5, 4/9, 1, Vg_senoidal).plotSolucaoAproximada(lineStyles, 4, 32, 4)