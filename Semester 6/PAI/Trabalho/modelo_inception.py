# 🚀 Bibliotecas
import pandas as pd
import os
import re
from sklearn.model_selection import train_test_split
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.applications import InceptionV3
from tensorflow.keras.models import Model
from tensorflow.keras.layers import Dense, GlobalAveragePooling2D, Dropout
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import EarlyStopping, ModelCheckpoint

# 📄 Ler CSV
df = pd.read_csv('descritores_nucleos.csv')

# 🔖 Mapear as classes
df['label'] = df['ALN status'].map({
    'N0': 'negativo',
    'N+(1-2)': 'positivo',
    'N+(>2)': 'positivo'
})

# 🖼️ Pasta com as imagens
image_dir = 'images'
image_files = os.listdir(image_dir)

# 📦 Lista para armazenar os dados
data = []

# 🔗 Associar imagem → paciente → rótulo
for file in image_files:
    match = re.match(r'^(\d+)_', file)  # Pega o número antes do primeiro underline
    if match:
        patient_id = int(match.group(1))
        try:
            aln_status = df.loc[patient_id - 1, 'ALN status']
            label = 'positivo' if aln_status in ['N+(1-2)', 'N+(>2)'] else 'negativo'
            data.append({'filename': file, 'label': label})
        except Exception as e:
            print(f"Erro com paciente {patient_id}: {e}")
    else:
        print(f"Formato de nome inesperado: {file}")

# ✅ DataFrame com imagens e labels
data_df = pd.DataFrame(data)

print(f"Total de imagens mapeadas: {len(data_df)}")
print(data_df['label'].value_counts())

# 🔀 Dividir em treino, validação e teste
train_df, test_df = train_test_split(data_df, test_size=0.2, random_state=42, stratify=data_df['label'])
train_df, val_df = train_test_split(train_df, test_size=0.25, random_state=42, stratify=train_df['label'])

# 🚀 Geradores de dados
train_datagen = ImageDataGenerator(
    rescale=1./255,
    rotation_range=20,
    zoom_range=0.15,
    width_shift_range=0.2,
    height_shift_range=0.2,
    horizontal_flip=True
)

val_test_datagen = ImageDataGenerator(rescale=1./255)

train_generator = train_datagen.flow_from_dataframe(
    train_df,
    directory=image_dir,
    x_col='filename',
    y_col='label',
    target_size=(299, 299),
    batch_size=32,
    class_mode='binary'
)

val_generator = val_test_datagen.flow_from_dataframe(
    val_df,
    directory=image_dir,
    x_col='filename',
    y_col='label',
    target_size=(299, 299),
    batch_size=32,
    class_mode='binary'
)

test_generator = val_test_datagen.flow_from_dataframe(
    test_df,
    directory=image_dir,
    x_col='filename',
    y_col='label',
    target_size=(299, 299),
    batch_size=32,
    class_mode='binary',
    shuffle=False
)

# 🔥 Definir o modelo com InceptionV3
base_model = InceptionV3(weights='imagenet', include_top=False, input_shape=(299, 299, 3))

x = base_model.output
x = GlobalAveragePooling2D()(x)
x = Dropout(0.5)(x)  # Regularização
x = Dense(128, activation='relu')(x)
predictions = Dense(1, activation='sigmoid')(x)

model = Model(inputs=base_model.input, outputs=predictions)

# ❄️ Congelar a base do modelo
for layer in base_model.layers:
    layer.trainable = False

# 🔧 Compilar
model.compile(optimizer=Adam(learning_rate=0.0001), loss='binary_crossentropy', metrics=['accuracy'])

# 🏁 Callbacks
early_stop = EarlyStopping(monitor='val_loss', patience=5, restore_best_weights=True)
checkpoint = ModelCheckpoint('best_model.h5', monitor='val_accuracy', save_best_only=True)

# 🚀 Treinar
history = model.fit(
    train_generator,
    steps_per_epoch=train_generator.samples // train_generator.batch_size,
    validation_data=val_generator,
    validation_steps=val_generator.samples // val_generator.batch_size,
    epochs=20,
    callbacks=[early_stop, checkpoint]
)

# 🧠 Avaliação no conjunto de teste
loss, acc = model.evaluate(test_generator)
print(f"🧪 Test Accuracy: {acc * 100:.2f}%")

# 📊 Matriz de confusão e relatório
import numpy as np
from sklearn.metrics import classification_report, confusion_matrix
import seaborn as sns
import matplotlib.pyplot as plt

# Previsões
Y_pred = model.predict(test_generator)
y_pred = (Y_pred > 0.5).astype(int).ravel()

# Labels reais
y_true = test_generator.classes

# Relatório
print(classification_report(y_true, y_pred, target_names=['negativo', 'positivo']))

# Matriz de confusão
cm = confusion_matrix(y_true, y_pred)
sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', xticklabels=['negativo', 'positivo'], yticklabels=['negativo', 'positivo'])
plt.xlabel('Predito')
plt.ylabel('Real')
plt.title('Matriz de Confusão')
plt.show()
