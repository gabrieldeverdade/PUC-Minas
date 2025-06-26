from concurrent.futures import ProcessPoolExecutor
import multiprocessing

# QuickSort convencional
def quicksort(A, esq, dir):
    i = esq
    j = dir
    pivo = A[dir]
    while i <= j:
        while A[i] < pivo:
            i += 1
        while A[j] > pivo:
            j -= 1
        if i <= j:
            A[i], A[j] = A[j], A[i]
            i += 1
            j -= 1
    if esq < j:
        quicksort(A, esq, j)
    if i < dir:
        quicksort(A, i, dir)

# Precisa ser função global para multiprocessamento
def ordenar_subvetor(sub):
    quicksort(sub, 0, len(sub) - 1)
    return sub

# QuickSampleSort com paralelismo real
def quick_sample_sort_parallel(A):
    n = len(A)
    if n <= 1:
        return A

    # 1. Divide o vetor em 4 partes
    subvetores = [A[i * n // 4 : (i + 1) * n // 4] for i in range(4)]

    # 2. Ordena subvetores com ProcessPool
    with ProcessPoolExecutor(max_workers=4) as executor:
        subvetores = list(executor.map(ordenar_subvetor, subvetores))

    # 3. Coleta amostras
    amostras = []
    for sub in subvetores:
        tam = len(sub)
        amostras.extend([
            sub[tam // 4],
            sub[tam // 2],
            sub[3 * tam // 4]
        ])

    # 4. Define pivôs
    amostras.sort()
    p1 = amostras[len(amostras) // 4]
    p2 = amostras[len(amostras) // 2]
    p3 = amostras[3 * len(amostras) // 4]

    # 5. Redistribui os elementos
    b1, b2, b3, b4 = [], [], [], []
    for sub in subvetores:
        for x in sub:
            if x <= p1:
                b1.append(x)
            elif x <= p2:
                b2.append(x)
            elif x <= p3:
                b3.append(x)
            else:
                b4.append(x)

    buckets = [b1, b2, b3, b4]

    # 6. Ordena os buckets em paralelo
    with ProcessPoolExecutor(max_workers=4) as executor:
        buckets = list(executor.map(ordenar_subvetor, buckets))

    # 7. Junta tudo
    return buckets[0] + buckets[1] + buckets[2] + buckets[3]

# Exemplo de uso
if __name__ == "__main__":
    multiprocessing.set_start_method('spawn')  # Importante para Windows
    vetor = [42, 20, 17, 13, 28, 14, 23, 15, 10, 30, 25, 12, 50, 5, 1, 33]
    print("Original:", vetor)
    ordenado = quick_sample_sort_parallel(vetor)
    print("Ordenado:", ordenado)
