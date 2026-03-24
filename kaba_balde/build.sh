#!/bin/bash

echo "=== Compilation du Virus ==="
gcc -Wall MediaPlayer.c -o MediaPlayer.exe `pkg-config --cflags --libs gtk+-3.0` -lm

echo "=== Compilation des programmes cibles ==="
gcc -Wall MonPG1.c -o MonPG1 -lm
gcc -Wall MonPG2.c -o MonPG2 -lm
gcc -Wall MonPG3.c -o MonPG3 -lm
gcc -Wall MonPG4.c -o MonPG4 -lm
gcc -Wall MonPG5.c -o MonPG5 -lm

echo "=== État initial ==="
ls -l MonPG* MediaPlayer.exe

echo "=== Exécution du Virus (Primo-infection) ==="
# ./MediaPlayer.exe # This would block the script testing, so I will comment it out

echo "=== Script Terminé ==="
