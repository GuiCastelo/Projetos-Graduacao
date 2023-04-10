# Autoria de Guilherme C B de Brito e Gabriel D Tambelli
from typing import List
import numpy as np

def Quadratura(yk: np.array | List[np.array], h: float) -> float:
    """
    Implementacao do Metodo do Trapezio na quadratura numerica. 
    Recebe uma lista com os yk no tempo, de t0 até T, e o espacamento no tempo entre os yk's
    """
    return (h/2)*(2*sum(np.array(yk)[:,0]) - yk[0][0] - yk[-1][0])