import os
import cv2
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.spatial import distance
import itertools

# Caminhos dos arquivos de entrada e saída
image_dir = "images"
output_csv = "descritores_nucleos.csv"
excel_path = "patient-clinical-data.xlsx"
log_path = "erros_log.txt"

# Extrai descritores morfológicos de núcleos celulares a partir de uma imagem colorida.
def extrair_descritores(imagem_bgr):
    try:
        # Converter para escala de cinza
        imagem_gray = cv2.cvtColor(imagem_bgr, cv2.COLOR_BGR2GRAY)

        # Remover fundo claro (valores muito altos)
        fundo = cv2.inRange(imagem_bgr, (200, 200, 200), (255, 255, 255))

        # Binarização
        blur = cv2.GaussianBlur(imagem_gray, (5, 5), 0)
        _, binaria = cv2.threshold(blur, 90, 255, cv2.THRESH_BINARY_INV)

        # Remoção de ruído
        limpa = cv2.morphologyEx(binaria, cv2.MORPH_OPEN, np.ones((3, 3), np.uint8), iterations=1)

        # Remover fundo identificado anteriormente
        limpa[fundo == 255] = 0

        # Encontrar contornos dos núcleos
        contornos, _ = cv2.findContours(limpa, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        descritores = []
        centros = []
        raios = []

        for contorno in contornos:
            area = cv2.contourArea(contorno)
            if area == 0: continue

            perimetro = cv2.arcLength(contorno, True)
            circularidade = 4 * np.pi * area / (perimetro ** 2) if perimetro != 0 else 0

            if len(contorno) >= 5:
                (_, _), (MA, ma), _ = cv2.fitEllipse(contorno)
                excentricidade = np.sqrt(1 - (MA / ma) ** 2) if ma != 0 else 0
            else:
                excentricidade = 0

            M = cv2.moments(contorno)
            if M["m00"] == 0: continue

            cx = int(M["m10"] / M["m00"])
            cy = int(M["m01"] / M["m00"])

            raio_eq = np.sqrt(area / np.pi)

            centros.append((cx, cy))
            raios.append(raio_eq)
            descritores.append([area, circularidade, excentricidade, 0])  # último campo será distância relativa

        # Cálculo da distância relativa
        for i, (cx, cy) in enumerate(centros):
            dists = [distance.euclidean((cx, cy), c2) for j, c2 in enumerate(centros) if j != i]
            dist_rel = min(dists) / raios[i] if dists and raios[i] != 0 else 0
            descritores[i][3] = dist_rel

        return np.array(descritores)

    except Exception as e:
        raise RuntimeError(f"Erro na extração de descritores: {str(e)}")

# Processar imagens
# Processar imagens
dados = []

for nome_arquivo in os.listdir(image_dir):
    caminho = os.path.join(image_dir, nome_arquivo)
    img = cv2.imread(caminho)
    if img is None:
        print(f"Erro ao ler a imagem {nome_arquivo}")
        continue

    descritores = extrair_descritores(img)

    if descritores.shape[0] == 0:
        print(f"Nenhum núcleo encontrado na imagem {nome_arquivo}")

        # Se já existem dados, usar a média dos dados anteriores
        if dados:
            medias_gerais = pd.DataFrame(dados).mean(numeric_only=True)
            dados.append({
                "imagem": nome_arquivo,
                "media_area": medias_gerais["media_area"],
                "dp_area": medias_gerais["dp_area"],
                "media_circularidade": medias_gerais["media_circularidade"],
                "dp_circularidade": medias_gerais["dp_circularidade"],
                "media_excentricidade": medias_gerais["media_excentricidade"],
                "dp_excentricidade": medias_gerais["dp_excentricidade"],
                "media_dist_relativa": medias_gerais["media_dist_relativa"],
                "dp_dist_relativa": medias_gerais["dp_dist_relativa"],
                "num_nucleos": 0  # Zero núcleos detectados
            })
        else:
            # Se for a primeira imagem e não há dados, preenche com zero ou NaN
            dados.append({
                "imagem": nome_arquivo,
                "media_area": np.nan,
                "dp_area": np.nan,
                "media_circularidade": np.nan,
                "dp_circularidade": np.nan,
                "media_excentricidade": np.nan,
                "dp_excentricidade": np.nan,
                "media_dist_relativa": np.nan,
                "dp_dist_relativa": np.nan,
                "num_nucleos": 0
            })
        continue

    medias = np.mean(descritores, axis=0)
    desvios = np.std(descritores, axis=0)

    dados.append({
        "imagem": nome_arquivo,
        "media_area": medias[0],
        "dp_area": desvios[0],
        "media_circularidade": medias[1],
        "dp_circularidade": desvios[1],
        "media_excentricidade": medias[2],
        "dp_excentricidade": desvios[2],
        "media_dist_relativa": medias[3],
        "dp_dist_relativa": desvios[3],
        "num_nucleos": descritores.shape[0]
    })

# Criar DataFrame e salvar CSV
df_descritores = pd.DataFrame(dados)

if not df_descritores.empty:
    df_descritores["Patient ID"] = df_descritores["imagem"].str.extract(r"(\d+)_").astype(int)
    
    # 🔥 ORDENAR POR Patient ID EM ORDEM CRESCENTE
    df_descritores = df_descritores.sort_values(by="Patient ID")
    
    df_descritores.to_csv(output_csv, index=False)

    # Juntar com dados clínicos
    clinical_df = pd.read_excel(excel_path)
    merged_df = pd.merge(df_descritores, clinical_df[["Patient ID", "ALN status"]], on="Patient ID", how="left")

    # Mapear cores
    merged_df["cor"] = merged_df["ALN status"].map({
        "N0": "black",
        "N+(1-2)": "blue",
        "N+(>2)": "red"
    })

    # Gerar gráficos de dispersão aos pares
    descritor_cols = ["media_area", "media_circularidade", "media_excentricidade", "media_dist_relativa"]
    for desc1, desc2 in itertools.combinations(descritor_cols, 2):
        plt.figure(figsize=(6, 6))
        for classe, cor in {"N0": "black", "N+(1-2)": "blue", "N+(>2)": "red"}.items():
            subset = merged_df[merged_df["ALN status"] == classe]
            plt.scatter(subset[desc1], subset[desc2], label=classe, c=cor, alpha=0.6, edgecolors='w', s=40)
        plt.xlabel(desc1)
        plt.ylabel(desc2)
        plt.title(f"{desc1} vs {desc2}")
        plt.legend()
        plt.savefig(f"scatter_{desc1}vs{desc2}.png", bbox_inches='tight')
        plt.close()
else:
    print("Nenhum dado processado. Verifique o log de erros.")
