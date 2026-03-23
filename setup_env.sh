#!/bin/bash

# Dossier de test cible (comme demandé dans le TP)
DEST_DIR="TP_User"
mkdir -p "$DEST_DIR"

# Nettoyage de l'environnement précédent (fichiers résiduels)
echo "[+] Nettoyage de l'environnement précédent..."
rm -f "$DEST_DIR"/*.old
rm -f "$DEST_DIR"/MonPG*.c
rm -f "$DEST_DIR"/MediaPlayer.c
rm -f "$DEST_DIR"/MediaPlayer.exe
rm -f "$DEST_DIR"/MonPG1 "$DEST_DIR"/MonPG2 "$DEST_DIR"/MonPG3 "$DEST_DIR"/MonPG4 "$DEST_DIR"/MonPG5

echo "[+] Copie des images..."
cp -r images/* "$DEST_DIR/"

echo "[+] Création et compilation des programmes cibles (MonPG1 à MonPG5)..."
for i in {1..5}; do
    SRC_FILE="$DEST_DIR/MonPG$i.c"
    BIN_FILE="$DEST_DIR/MonPG$i"

    # Création du code source C pour le programme cible
    cat <<EOF > "$SRC_FILE"
#include <stdio.h>
int main() {
    printf("Je suis le programme légitime MonPG$i\n");
    return 0;
}
EOF

    # Compilation
    gcc -Wall "$SRC_FILE" -o "$BIN_FILE"

    # Ajustement des permissions (Lecture/Ecriture/Execution pour le propriétaire et le groupe)
    chmod 775 "$BIN_FILE"

    # On peut supprimer les .c des cibles pour que le dossier soit propre
    rm "$SRC_FILE"
done

# Copie et compilation du virus
echo "[+] Copie et compilation de MediaPlayer.c..."
cp MediaPlayer.c "$DEST_DIR/"
gcc -Wall "$DEST_DIR/MediaPlayer.c" -o "$DEST_DIR/MediaPlayer.exe"

# Permissions pour le virus (exécution)
chmod 775 "$DEST_DIR/MediaPlayer.exe"

echo "[+] Environnement TP_User mis en place avec succès !"
ls -la "$DEST_DIR"
