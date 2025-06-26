import numpy as np

import numpy as np

# Recebe a matriz de entrada e se o usuário pediu para mostrar o passo a passo dos cálculos ou não
def gauss_jordan(matriz, mostrar_passos=False):
    linhas, colunas = matriz.shape  # .shape retorna as dimensões da matriz
    matriz_calculo = matriz.astype(float).copy()  # Cria uma cópia da matriz original em float
    lista_passos = []

    for i in range(min(linhas, colunas)):
        # Verifica se o pivô da linha atual pode ser usado (é diferente de zero)
        if not np.isclose(matriz_calculo[i, i], 0):
            linha_pivo = i
        else:
            # Procura, a partir da linha i, uma linha abaixo com valor diferente de zero na coluna i
            linha_pivo = None
            for k in range(i + 1, linhas):
                if not np.isclose(matriz_calculo[k, i], 0):
                    linha_pivo = k
                    break
            if linha_pivo is None:
                continue  # Nenhum pivô válido nesta coluna

            # Troca as linhas imediatamente, pois foi necessário buscar outro pivô
            matriz_calculo[[i, linha_pivo]] = matriz_calculo[[linha_pivo, i]]
            if mostrar_passos:
                lista_passos.append(f"Trocar Linha {i+1} com Linha {linha_pivo+1}")

        # Tornar o pivô igual a 1 (Normalização)
        pivo = matriz_calculo[i, i]
        # Verifica se o pivô da linha atual é diferente de 1
        if not np.isclose(pivo, 1):
            matriz_calculo[i] = matriz_calculo[i] / pivo
            if mostrar_passos:
                lista_passos.append(f"Dividir Linha {i+1} por {pivo}")

        # Zerar os outros elementos da coluna (acima e abaixo do pivô)
        for j in range(linhas):
            # Verifica se o elemento da coluna é de uma linha diferente e o valor não é zero
            if j != i and not np.isclose(matriz_calculo[j, i], 0):
                fator = matriz_calculo[j, i]
                # Lj = Lj - fator*Li
                matriz_calculo[j] -= fator * matriz_calculo[i]
                if mostrar_passos:
                    lista_passos.append(f"L{j+1} = L{j+1} - ({fator}) × L{i+1}")

    # Mover linhas nulas para o final
    linhas_nao_nulas = [linha for linha in matriz_calculo if not np.allclose(linha, 0)]
    linhas_nulas = [linha for linha in matriz_calculo if np.allclose(linha, 0)]
    matriz_calculo = np.array(linhas_nao_nulas + linhas_nulas)

    return matriz_calculo, lista_passos

def principal():
    print("=== CÁLCULO DA FORMA ESCADA REDUZIDA POR LINHAS (FER) ===")

    total_linhas = int(input("Informe o número de linhas da matriz: "))
    total_colunas = int(input("Informe o número de colunas da matriz: "))
    matriz_entrada = []

    print("\nComo deseja inserir os elementos da matriz?")
    print("1 - Digitar todos os elementos de uma vez só (exemplo: 1 2 3 4 5 6 7 8 9)")
    print("2 - Digitar linha por linha (exemplo: Linha 1: 1 2 3; Linha 2: 4 5 6; ...)")
    modo = input("Escolha (1 ou 2): ")

    if modo.strip() == "1":
        print(f"\nDigite os {total_linhas * total_colunas} elementos da matriz, separados por espaço:")
        # Recebe os valores digitados pelo usuário, converte cada um para número decimal (`float`) e os guarda como lista
        elementos = list(map(float, input().split()))
        if len(elementos) != total_linhas * total_colunas:
            print("Quantidade incorreta de elementos! Reinicie o programa e tente novamente.")
            return
        # Pega a lista de elementos, transforma ela em um array e depois usa .reshape para dividir os elementos nas linhas e colunas certas
        matriz_entrada = np.array(elementos).reshape((total_linhas, total_colunas))

    elif modo.strip() == "2":
        print("\nDigite os elementos linha por linha:")
        for i in range(total_linhas):
            while True:
                entrada = input(f"Elementos da Linha {i+1}: ").strip().split()
                if len(entrada) == total_colunas:
                    try:
                        linha_convertida = [float(num) for num in entrada]
                        matriz_entrada.append(linha_convertida)
                        break
                    except ValueError:
                        print("Por favor, digite apenas números válidos.")
                else:
                    print(f"A linha {i+1} deve ter exatamente {total_colunas} elementos.")
        matriz_entrada = np.array(matriz_entrada)
    else:
        print("Opção inválida! Reinicie o programa e tente novamente.")
        return

    print("\nMatriz Original:")
    print(matriz_entrada)

    print("\nEscolha a opção de saída:")
    print("1 - Mostrar apenas a FER final")
    print("2 - Mostrar o passo a passo completo das operações realizadas")
    escolha = input("Digite a opção (1 ou 2): ").strip()

    if escolha == "1":
        mostrar_passos = False
        matriz_resultado, passos_realizados = gauss_jordan(matriz_entrada, mostrar_passos)
        print("\nMatriz final na Forma Escada Reduzida por Linhas (FER):")
        print(matriz_resultado)

    elif escolha == "2":
        mostrar_passos = True
        matriz_resultado, passos_realizados = gauss_jordan(matriz_entrada, mostrar_passos)
        print("\nPassos executados durante o cálculo:")
        for passo in passos_realizados:
            print(passo)
        print("\nMatriz final na Forma Escada Reduzida por Linhas (FER):")
        print(matriz_resultado)

    else:
        print("Opção inválida! Reinicie o programa e tente novamente.")
        return

if __name__ == "__main__":
    principal()
