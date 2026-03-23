# TP Virologie - Rendu et demonstration

Ce dossier contient un projet de TP en C autour du concept de "compagnon", avec une demonstration en environnement local de test.

## Contenu du dossier

- `MediaPlayer.c` : programme principal en C.
- `setup_env.sh` : script de preparation de l'environnement `TP_User`.
- `images/` : ressources copiees dans l'environnement de test.
- `TP_User/` : dossier de test genere avec les executables cibles.
- `docs/` : scans du sujet.

## Prerequis

- Linux
- `gcc`
- droits d'execution sur les scripts

## Mise en place rapide

Depuis `virologie/` :

```bash
chmod +x setup_env.sh
./setup_env.sh
```

Le script :
- cree `TP_User/` si necessaire,
- copie les images,
- cree et compile `MonPG1` a `MonPG5`,
- compile `MediaPlayer.c` en `TP_User/MediaPlayer.exe`.

## Verification minimale

```bash
ls -la TP_User
```

Verifier la presence de :
- `MediaPlayer.exe`
- `MonPG1` ... `MonPG5`
- leurs versions `MonPG1.old` ... `MonPG5.old` si deja produites pendant un test precedent

## Ce qui est montre dans la demo

- affichage du service utilisateur (sortie console),
- traitement des cibles executables dans le repertoire courant,
- prevention de la re-infection (fichiers deja marques),
- continuation d'execution du programme d'origine quand applicable.

## Limites et remarques de rendu

- Le "service" est actuellement une simulation texte (pas de visualisation graphique native).
- Le projet est prevu pour un environnement de TP local.
- Pour un rendu propre, utiliser aussi :
  - `docs/tableau_conformite.md`
  - `docs/checklist_demo_orale.md`

# ourVirus
