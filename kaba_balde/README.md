# Projet Virus Compagnon - Sécurité et Virologie

Ce projet met en œuvre un virus informatique de type "Compagnon". Il usurpe l'identité de programmes légitimes (les "cibles" `MonPG1` à `MonPG5`) en se nommant comme eux et en renommant les originaux avec une extension `.old`.

---

## 1. Prérequis (Installation)
Avant toute chose, vous devez installer les paquets nécessaires sur votre système Linux (Debian/Kali/Ubuntu) :

* **GTK+3** (Pour l'interface graphique du virus) :
  ```bash
  sudo apt-get update
  sudo apt install pkg-config pkgconf libgtk-3-dev -y
  ```
* **Gnuplot** (Pour que les programmes cibles 4 et 5 affichent leurs courbes mathématiques) :
  ```bash
  sudo apt install gnuplot -y
  ```

---

## 2. Nettoyer le projet (L'étape la plus importante !)
**TRÈS IMPORTANT :** Avant de procéder à un nouveau test ou de recompiler le virus, vous devez **absolument effacer toutes les traces des infections précédentes** (les fichiers `.old` et les clones artificiels). Si vous ne le faites pas, le virus verra que les fichiers `.old` existent déjà et n'infectera rien en affichant `déjà infecté`.

Exécutez cette commande de nettoyage à la racine du projet :
```bash
rm -f *.old MonPG1 MonPG2 MonPG3 MonPG4 MonPG5 MediaPlayer.exe
```

---

## 3. Compiler le projet
Utilisez le script fourni pour compiler le virus et les 5 programmes cibles d'un seul coup :
```bash
./build.sh
```
Après cela, vérifiez avec un `ls -l` que vos exécutables ont bien tous une petite taille (environ 16 Ko), sauf `MediaPlayer.exe` qui est plus lourd.

---

## 4. Tester l'infection (Étape par étape)

### A. La Primo-Infection
L'utilisateur pense ouvrir un simple gestionnaire de photos :
```bash
./MediaPlayer.exe
```
*L'interface graphique va s'ouvrir. Fermez simplement la fenêtre. Le virus vient d'infecter silencieusement tout le dossier.*

### B. Vérification
Vérifiez que vos exécutables originaux s'appellent désormais `.old` et que de faux exécutables `MonPG*` ont pris leur place (ils auront tous la taille exacte de `MediaPlayer.exe`) :
```bash
ls -l
```

### C. La Furtivité (Le test final)
Lancez l'un des logiciels qui a été infecté, par exemple la calculatrice :
```bash
./MonPG1
```
*Le virus s'exécutera une fraction de seconde, puis passera secrètement le relais à la vraie calculatrice (`MonPG1.old`). L'utilisateur n'y verra que du feu !*
