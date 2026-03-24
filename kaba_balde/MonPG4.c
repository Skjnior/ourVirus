/*
 * Fichier : MonPG4.c (Programme Cible 4)
 * Rôle : Traceur statique de la courbe f(x) = x^2 via Gnuplot.
 * Utilité dans le projet : Démontre la fiabilité de la furtivité du virus. 
 * Prouve qu'un programme infecté peut toujours générer des sous-fichiers 
 * (.dat, .plt) et instancier des processus lourds fils (pipe avec Gnuplot).
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXL 10
#define DATA_FILE "gnuplot.dat"
#define PLOT_FILE "gnuplot.plt"

int main() {
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        perror("Erreur d'ouverture du fichier de données");
        return 1;
    }

    for (int i = 0; i < MAXL; i++) {
        fprintf(fp, "%d %d\n", i, i * i); 
    }
    fclose(fp);
    FILE *plot = fopen(PLOT_FILE, "w");
    if (plot == NULL) {
        perror("Erreur d'ouverture du fichier de script Gnuplot");
        return 1;
    }

    fprintf(plot, "set title 'Courbe de f(x) = x^2'\n");
    fprintf(plot, "set xlabel 'x'\n");
    fprintf(plot, "set ylabel 'f(x)'\n");
    fprintf(plot, "plot '%s' using 1:2 with lines title 'f(x) = x^2'\n", DATA_FILE);
    fclose(plot);
    char command[50];
    snprintf(command, sizeof(command), "gnuplot -persist %s", PLOT_FILE);
    if (system(command) != 0) {
        perror("Erreur lors du lancement de Gnuplot");
        return 1;
    }

    return 0;
}