import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pickle

from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix, accuracy_score, recall_score
from xgboost import XGBClassifier

# 📥 Carregar os dados
df = pd.read_csv("descritores_nucleos.csv")

# 🎯 Variável alvo (label)
df["label"] = df["ALN status"].map({
    "N0": 0,        # Negativo
    "N+(1-2)": 1,   # Positivo
    "N+(>2)": 1     # Positivo
})

# Remover linhas com NaN (caso alguma imagem sem núcleo tenha sido preenchida com NaN)
df = df.dropna()
# Garantir que as features sejam numéricas
for coluna in ["media_area", "dp_area", "media_circularidade", "dp_circularidade",
                "media_excentricidade", "dp_excentricidade", "media_dist_relativa", "dp_dist_relativa"]:
    df[coluna] = pd.to_numeric(df[coluna], errors='coerce')

# 📦 Agrupar pelos pacientes (Patient ID) e obter uma label por paciente
paciente_labels = df.groupby("Patient ID")["label"].first()

# Lista de pacientes
pacientes = paciente_labels.index.to_numpy()

# 🔄 Separação treino/teste (80/20) garantindo que patches de um paciente estejam no mesmo grupo
pacientes_treino, pacientes_teste = train_test_split(
    pacientes,
    test_size=0.2,
    random_state=42,
    stratify=paciente_labels
)

# Dados de treino e teste
treino_df = df[df["Patient ID"].isin(pacientes_treino)]
teste_df = df[df["Patient ID"].isin(pacientes_teste)]

# 🔍 Separar 25% do treino para validação, também estratificado
treino_labels = treino_df.groupby("Patient ID")["label"].first()

pacientes_treino_sub, pacientes_val = train_test_split(
    pacientes_treino,
    test_size=0.25,
    random_state=42,
    stratify=treino_labels.loc[pacientes_treino]
)

treino_df_final = treino_df[treino_df["Patient ID"].isin(pacientes_treino_sub)]
val_df = treino_df[treino_df["Patient ID"].isin(pacientes_val)]

# 🎯 Features e Labels
features = [
    "media_area", "dp_area", "media_circularidade", "dp_circularidade",
    "media_excentricidade", "dp_excentricidade", "media_dist_relativa", "dp_dist_relativa"
]

X_train = treino_df_final[features]
y_train = treino_df_final["label"]

X_val = val_df[features]
y_val = val_df["label"]

X_test = teste_df[features]
y_test = teste_df["label"]

# ✅ Modelagem XGBoost
model = XGBClassifier(
    n_estimators=100,
    learning_rate=0.1,
    max_depth=3,
    random_state=42,
    use_label_encoder=False,
    eval_metric='logloss'
)

model.fit(
    X_train, y_train,
    eval_set=[(X_train, y_train), (X_val, y_val)],
    verbose=False
)

# 🚀 Avaliação no conjunto de teste
y_pred = model.predict(X_test)

# 📊 Métricas
accuracy = accuracy_score(y_test, y_pred)
sensitivity = recall_score(y_test, y_pred, pos_label=1)  # Sensibilidade
specificity = recall_score(y_test, y_pred, pos_label=0)  # Especificidade

print("\n🎯 Resultados no conjunto de Teste:")
print(f"Acurácia: {accuracy:.4f}")
print(f"Sensibilidade (Recall para positivo): {sensitivity:.4f}")
print(f"Especificidade (Recall para negativo): {specificity:.4f}")

# 🔥 Matriz de Confusão
cm = confusion_matrix(y_test, y_pred)
plt.figure(figsize=(5,4))
sns.heatmap(cm, annot=True, fmt="d", cmap="Blues", cbar=False)
plt.xlabel("Predito")
plt.ylabel("Real")
plt.title("Matriz de Confusão - Teste")
plt.show()

# 💾 Salvar modelo
with open("modelo_xgboost.pkl", "wb") as f:
    pickle.dump(model, f)

print("\n✅ Modelo salvo como 'modelo_xgboost.pkl'")
