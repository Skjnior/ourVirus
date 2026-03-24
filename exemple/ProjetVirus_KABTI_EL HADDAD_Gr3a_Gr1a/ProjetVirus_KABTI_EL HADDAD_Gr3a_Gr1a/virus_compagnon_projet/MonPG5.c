#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXL 20
#define DATA_FILE "gnuplot.dat"
#define PLOT_FILE "gnuplot.plt"

float fx1(int x) { return 2 * x + 1; }        // f(x) = 2x + 1
float fx2(int x) { return x * x * x; }        // f(x) = x^3
float fx3(int x) { return sqrt(x); }          // f(x) = sqrt(x)
float fx4(int x) { return exp(x); }           // f(x) = e^x
float fx5(int x) { return log(x + 1); }       // f(x) = ln(x+1)

float (*functions[])(int) = {fx1, fx2, fx3, fx4, fx5};
const char *labels[] = {"2x+1", "x^3", "sqrt(x)", "e^x", "ln(x+1)"};

void generate_data(int choice) {
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAXL; i++) {
        fprintf(fp, "%d %f\n", i, functions[choice - 1](i));
    }
    fclose(fp);
}

void generate_plot_script(int choice) {
    FILE *fp = fopen(PLOT_FILE, "w");
    if (!fp) {
        perror("Erreur lors de l'ouverture du script gnuplot");
        exit(EXIT_FAILURE);
    }
    fprintf(fp,
            "set xlabel 'x'\n"
            "set ylabel 'f(x) = %s'\n"
            "set title 'Graphique de f(x) = %s'\n"
            "set grid\n"
            "set style data lines\n"
            "plot '%s' using 1:2 lw 2 linecolor rgb 'blue'\n"
            "pause mouse close\n",
            labels[choice - 1], labels[choice - 1], DATA_FILE);
    fclose(fp);
}

void plot_graph() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Erreur fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execlp("gnuplot", "gnuplot", "-p", PLOT_FILE, (char *)NULL);
        perror("Erreur exec gnuplot");
        _exit(EXIT_FAILURE);
    }
    wait(NULL);
}

int main(int argc, char **argv) {
    int choice;
    do {
        printf("\nChoisissez une fonction à tracer :\n");
        printf("1 - f(x) = 2x+1\n");
        printf("2 - f(x) = x^3\n");
        printf("3 - f(x) = sqrt(x)\n");
        printf("4 - f(x) = e^x\n");
        printf("5 - f(x) = ln(x+1)\n");
        printf("0 - Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 5) {
            generate_data(choice);
            generate_plot_script(choice);
            plot_graph();
        }
    } while (choice != 0);
    return 0;
}