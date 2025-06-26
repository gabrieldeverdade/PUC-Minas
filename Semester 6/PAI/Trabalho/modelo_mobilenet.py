# 🚀 Bibliotecas
import pandas as pd
import os
import numpy as np
from sklearn.utils.class_weight import compute_class_weight
import tensorflow as tf
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.applications import MobileNetV2
from tensorflow.keras.models import Model
from tensorflow.keras.layers import Dense, GlobalAveragePooling2D, Dropout
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import EarlyStopping, ModelCheckpoint, ReduceLROnPlateau
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.metrics import classification_report, confusion_matrix

# ✅ Verificar GPU
gpus = tf.config.list_physical_devices('GPU')
if gpus:
    print(f"✅ GPU disponível: {gpus}")
    try:
        # Configurar para alocar memória dinamicamente (opcional, mas bom para evitar erros de OOM)
        for gpu in gpus:
            tf.config.experimental.set_memory_growth(gpu, True)
    except RuntimeError as e:
        print(f"Erro ao configurar memória da GPU: {e}")
else:
    print("🚫 GPU NÃO detectada. Usando CPU.")

# 📄 Ler CSV
try:
    df = pd.read_csv('descritores_nucleos.csv')
except FileNotFoundError:
    print("Erro: Arquivo 'descritores_nucleos.csv' não encontrado. Verifique o caminho.")
    exit()

# 🔖 Mapear as classes
df['label'] = df['ALN status'].map({
    'N0': 'negativo',
    'N+(1-2)': 'positivo',
    'N+(>2)': 'positivo'
})

# 🖼 Pasta com as imagens
image_dir = 'patches'
if not os.path.isdir(image_dir):
    print(f"Erro: Diretório de imagens '{image_dir}' não encontrado.")
    exit()

# 🔗 Carregar listas de IDs
def load_ids(file_path):
    try:
        with open(file_path, 'r') as f:
            ids = [line.strip() for line in f if line.strip().isdigit()]
        return set(ids)
    except FileNotFoundError:
        print(f"Erro: Arquivo de IDs '{file_path}' não encontrado.")
        return set() # Retorna um conjunto vazio para evitar mais erros

train_ids = load_ids('dataset-splitting/train_id.txt')
val_ids = load_ids('dataset-splitting/val_id.txt')
test_ids = load_ids('dataset-splitting/test_id.txt')

if not train_ids or not val_ids or not test_ids:
    print("Um ou mais arquivos de IDs (train_id.txt, val_id.txt, test_id.txt) não foram carregados corretamente ou estão vazios.")
    print("Verifique os caminhos e o conteúdo dos arquivos em 'dataset-splitting/'.")
    # Decida se quer parar ou continuar com dados possivelmente vazios
    # exit() # Descomente se quiser parar a execução

# 📦 Lista para armazenar os dados
data = []

# 🔗 Associar imagem → paciente → rótulo
for patient_folder in os.listdir(image_dir):
    patient_folder_path = os.path.join(image_dir, patient_folder)
    
    if os.path.isdir(patient_folder_path) and patient_folder.isdigit():
        patient_id_str = patient_folder # patient_id é string aqui
        
        try:
            # Ajuste para encontrar o paciente no DataFrame. O CSV parece ser 0-indexed,
            # e os IDs dos pacientes podem não ser sequenciais ou começar em 1.
            # Assumindo que 'patient_id' no CSV é a coluna que corresponde aos nomes das pastas.
            # Se a coluna de ID no CSV tiver outro nome, ajuste 'Patient_ID' abaixo.
            # Se o CSV usa um índice numérico que corresponde a patient_id - 1, mantenha como antes.
            # Vamos assumir que existe uma coluna no CSV que guarda os IDs dos pacientes como strings
            # ou que eles podem ser convertidos para o tipo correto para correspondência.
            # Exemplo: se o CSV tem uma coluna 'ID_Paciente' que são números:
            # patient_row = df[df['ID_Paciente'] == int(patient_id_str)]
            # Se 'Patient_ID' no CSV é a coluna de índice + 1
            patient_row = df.loc[int(patient_id_str) - 1] # Mantendo a lógica original se for essa
            aln_status = patient_row['ALN status']
            label = 'positivo' if aln_status in ['N+(1-2)', 'N+(>2)'] else 'negativo'
        except KeyError:
             print(f"Aviso: Paciente {patient_id_str} não encontrado no CSV ou coluna 'ALN status' ausente para este paciente. Pulando.")
             continue
        except Exception as e:
            print(f"Erro ao processar paciente {patient_id_str} do CSV: {e}")
            continue
            
        for file in os.listdir(patient_folder_path):
            if file.lower().endswith(('.png', '.jpg', '.jpeg')):
                data.append({
                    'filename': os.path.join(patient_folder, file), # Caminho relativo à image_dir
                    'label': label,
                    'patient_id': patient_id_str # Mantém como string para consistência com train_ids etc.
                })
    else:
        print(f"Pasta ignorada (não é diretório ou nome não é numérico): {patient_folder}")

# ✅ DataFrame com imagens e labels
data_df = pd.DataFrame(data)

if data_df.empty:
    print("Nenhum dado de imagem foi carregado. Verifique a estrutura de pastas e o CSV.")
    exit()

print(f"Total de imagens mapeadas: {len(data_df)}")
print("Distribuição inicial das classes no dataset completo:")
print(data_df['label'].value_counts())

# 🔀 Separar os conjuntos usando os arquivos de ids
train_df = data_df[data_df['patient_id'].isin(train_ids)]
val_df = data_df[data_df['patient_id'].isin(val_ids)]
test_df = data_df[data_df['patient_id'].isin(test_ids)]

print(f"Imagens treino: {len(train_df)}")
print(f"Imagens validação: {len(val_df)}")
print(f"Imagens teste: {len(test_df)}")

if train_df.empty or val_df.empty:
    print("Erro: Conjunto de treino ou validação está vazio. Verifique os arquivos de ID e o mapeamento.")
    exit()

# 🚀 Geradores de dados
IMG_WIDTH, IMG_HEIGHT = 224, 224
BATCH_SIZE = 32 # Pode ajustar conforme a memória da GPU

train_datagen = ImageDataGenerator(
    rescale=1./255,
    rotation_range=30,      # Aumentado ligeiramente
    zoom_range=0.2,         # Aumentado ligeiramente
    width_shift_range=0.2,
    height_shift_range=0.2,
    shear_range=0.15,       # Adicionado shear
    horizontal_flip=True,
    fill_mode='nearest'     # Modo de preenchimento para pixels criados
)

val_test_datagen = ImageDataGenerator(rescale=1./255)

train_generator = train_datagen.flow_from_dataframe(
    train_df,
    directory=image_dir,
    x_col='filename',
    y_col='label',
    target_size=(IMG_WIDTH, IMG_HEIGHT),
    batch_size=BATCH_SIZE,
    class_mode='binary',
    shuffle=True
)

val_generator = val_test_datagen.flow_from_dataframe(
    val_df,
    directory=image_dir,
    x_col='filename',
    y_col='label',
    target_size=(IMG_WIDTH, IMG_HEIGHT),
    batch_size=BATCH_SIZE,
    class_mode='binary',
    shuffle=False
)

if not test_df.empty:
    test_generator = val_test_datagen.flow_from_dataframe(
        test_df,
        directory=image_dir,
        x_col='filename',
        y_col='label',
        target_size=(IMG_WIDTH, IMG_HEIGHT),
        batch_size=BATCH_SIZE,
        class_mode='binary',
        shuffle=False
    )
else:
    print("Aviso: Conjunto de teste está vazio. A avaliação final não será realizada.")
    test_generator = None


# ⚖️ Calcular Class Weights (se houver desbalanceamento significativo)
# É importante calcular com base nas classes do conjunto de treino
# Os labels do gerador são 0 e 1, então mapeamos 'negativo' e 'positivo' para isso
# train_generator.class_indices lhe dará o mapeamento: {'negativo': 0, 'positivo': 1} (ou similar)
print(f"Mapeamento de classes do gerador: {train_generator.class_indices}")
labels_train = train_generator.classes # Labels numéricos (0 ou 1)

# Verifica se há mais de uma classe antes de calcular os pesos
if len(np.unique(labels_train)) > 1:
    class_weights_values = compute_class_weight(
        class_weight='balanced',
        classes=np.unique(labels_train),
        y=labels_train
    )
    class_weights = dict(enumerate(class_weights_values))
    print(f"Pesos das classes calculados: {class_weights}")
else:
    print("Apenas uma classe presente no conjunto de treinamento. Não aplicando pesos de classe.")
    class_weights = None


# 🔥 Definir o modelo com MobileNetV2
base_model = MobileNetV2(weights='imagenet', include_top=False, input_shape=(IMG_WIDTH, IMG_HEIGHT, 3))

# Congelar a base do modelo inicialmente
base_model.trainable = False

x = base_model.output
x = GlobalAveragePooling2D()(x)
x = Dropout(0.5)(x) # Dropout para regularização
x = Dense(128, activation='relu')(x)
# x = Dropout(0.3)(x) # Dropout adicional opcional antes da camada final
predictions = Dense(1, activation='sigmoid')(x) # Saída binária

model = Model(inputs=base_model.input, outputs=predictions)

# 🔧 Compilar para a primeira fase de treinamento (treinar a cabeça)
INITIAL_LR = 1e-4 # 0.0001
model.compile(optimizer=Adam(learning_rate=INITIAL_LR),
              loss='binary_crossentropy',
              metrics=['accuracy'])

model.summary()

# 🏁 Callbacks para a primeira fase
early_stop_head = EarlyStopping(monitor='val_loss', patience=10, restore_best_weights=True, verbose=1)
checkpoint_head = ModelCheckpoint('best_model_mobilenet_head.keras', # Usar .keras
                                  monitor='val_accuracy', save_best_only=True, verbose=1)
reduce_lr_head = ReduceLROnPlateau(monitor='val_loss', factor=0.2, patience=5, min_lr=1e-6, verbose=1)

# 🚀 Treinar - Fase 1: Treinar apenas a cabeça adicionada
print("\n--- Iniciando Treinamento da Cabeça do Modelo ---")
EPOCHS_HEAD = 25 # Ajuste conforme necessário

history_head = model.fit(
    train_generator,
    steps_per_epoch=train_generator.samples // BATCH_SIZE if train_generator.samples > 0 else 1,
    validation_data=val_generator,
    validation_steps=val_generator.samples // BATCH_SIZE if val_generator.samples > 0 else 1,
    epochs=EPOCHS_HEAD,
    callbacks=[early_stop_head, checkpoint_head, reduce_lr_head],
    class_weight=class_weights # Aplicar pesos de classe
)

# Carregar o melhor modelo da Fase 1
print("\n--- Carregando melhores pesos do treinamento da cabeça ---")
model.load_weights('best_model_mobilenet_head.keras')

# --- Fase 2: Fine-Tuning ---
print("\n--- Iniciando Fase de Fine-Tuning ---")

# ❄ Descongelar algumas camadas da base_model para fine-tuning
base_model.trainable = True

# Quantas camadas descongelar do final. MobileNetV2 tem ~155 camadas.
# Descongelar os últimos blocos é uma boa estratégia.
# Ex: Descongelar as últimas 40 camadas
fine_tune_at = len(base_model.layers) - 40 # Você pode ajustar este valor

for layer in base_model.layers[:fine_tune_at]:
    layer.trainable = False
for layer in base_model.layers[fine_tune_at:]:
    layer.trainable = True
    print(f"Camada {layer.name} descongelada para fine-tuning.")


# 🔧 Recompilar o modelo com uma taxa de aprendizado MENOR para fine-tuning
FINE_TUNE_LR = 1e-5 # 0.00001
model.compile(optimizer=Adam(learning_rate=FINE_TUNE_LR),
              loss='binary_crossentropy',
              metrics=['accuracy'])

model.summary() # Verifique quais camadas são treináveis

# 🏁 Callbacks para fine-tuning
early_stop_ft = EarlyStopping(monitor='val_loss', patience=15, # Maior paciência para fine-tuning
                              restore_best_weights=True, verbose=1)
checkpoint_ft = ModelCheckpoint('best_model_mobilenet_finetuned.keras', # Usar .keras
                                monitor='val_accuracy', save_best_only=True, verbose=1)
reduce_lr_ft = ReduceLROnPlateau(monitor='val_loss', factor=0.2, patience=5, min_lr=1e-7, verbose=1) # min_lr ainda menor

# 🚀 Continuar o treinamento (Fine-tuning)
EPOCHS_FT = 50 # Mais épocas para fine-tuning, EarlyStopping cuidará disso

history_ft = model.fit(
    train_generator,
    steps_per_epoch=train_generator.samples // BATCH_SIZE if train_generator.samples > 0 else 1,
    validation_data=val_generator,
    validation_steps=val_generator.samples // BATCH_SIZE if val_generator.samples > 0 else 1,
    epochs=EPOCHS_HEAD + EPOCHS_FT, # Continuar a contagem de épocas
    initial_epoch=history_head.epoch[-1] + 1, # Começar da época onde o anterior parou
    callbacks=[early_stop_ft, checkpoint_ft, reduce_lr_ft],
    class_weight=class_weights # Aplicar pesos de classe também no fine-tuning
)

# Carregar o melhor modelo da fase de Fine-Tuning para avaliação final
print("\n--- Carregando melhores pesos do fine-tuning ---")
model.load_weights('best_model_mobilenet_finetuned.keras')


# 🧠 Avaliação no conjunto de teste (se existir)
if test_generator:
    print("\n--- Avaliando no Conjunto de Teste ---")
    loss, acc = model.evaluate(test_generator, steps=test_generator.samples // BATCH_SIZE if test_generator.samples > 0 else 1)
    print(f"🧪 Acurácia no Teste (Fine-tuned): {acc * 100:.2f}%")
    print(f"🧪 Perda no Teste (Fine-tuned): {loss:.4f}")

    # 📊 Matriz de confusão e relatório
    print("\n--- Relatório de Classificação e Matriz de Confusão (Teste) ---")
    Y_pred_probs = model.predict(test_generator, steps=test_generator.samples // BATCH_SIZE +1 if test_generator.samples % BATCH_SIZE != 0 else test_generator.samples // BATCH_SIZE )
    # Precisamos pegar o número exato de predições correspondente ao número de amostras
    Y_pred_probs = Y_pred_probs[:test_generator.samples]
    y_pred_classes = (Y_pred_probs > 0.5).astype(int).ravel()
    y_true = test_generator.classes

    if len(y_true) != len(y_pred_classes):
         print(f"Alerta: Discrepância no número de labels verdadeiros ({len(y_true)}) e predições ({len(y_pred_classes)}). Ajustando...")
         # Isso pode acontecer se o número de amostras não for divisível pelo batch_size
         # e steps não estiverem corretos. O ajuste acima em Y_pred_probs tenta corrigir isso.
         # Se ainda assim der erro, pode ser necessário um ajuste mais fino no predict steps
         # ou garantir que o gerador não repita dados de forma inesperada na predição.
         # Se y_true for maior, pode ser que test_generator.samples seja maior que o número real de batches * batch_size.
         # A forma mais segura é garantir que o test_generator não use shuffle e pegar y_true = test_generator.classes[:len(y_pred_classes)]
         # ou re-gerar o test_generator com shuffle=False e batch_size=1 para ter certeza absoluta.

    target_names = [name for name, index in sorted(train_generator.class_indices.items(), key=lambda item: item[1])]
    print(classification_report(y_true, y_pred_classes, target_names=target_names))

    cm = confusion_matrix(y_true, y_pred_classes)
    plt.figure(figsize=(8, 6))
    sns.heatmap(cm, annot=True, fmt='d', cmap='Blues',
                xticklabels=target_names, yticklabels=target_names)
    plt.xlabel('Predito')
    plt.ylabel('Real')
    plt.title('Matriz de Confusão (Teste)')
    plt.show()
else:
    print("\nNenhum conjunto de teste para avaliar.")

print("\n--- FIM DO SCRIPT ---")
