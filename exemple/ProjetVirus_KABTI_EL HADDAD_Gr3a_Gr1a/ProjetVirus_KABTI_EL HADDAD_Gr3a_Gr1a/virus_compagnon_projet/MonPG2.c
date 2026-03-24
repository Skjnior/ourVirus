#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Vérifie si un nombre est un carré parfait
bool estCarreParfait(int n) {
    if (n < 0) return false;
    int racine = (int)sqrt(n);
    return (racine * racine == n);
}

int main() {
    int nombre;
    printf("Entrez un nombre pour vérifier s'il est un carré parfait : ");
    scanf("%d", &nombre);

    if (nombre < 0) {
        printf("Veuillez entrer un nombre positif ou zéro.\n");
        return 1;
    }
    if (estCarreParfait(nombre)) {
        int racine = (int)sqrt(nombre);
        printf("%d est un carré parfait ! Sa racine carrée est %d.\n", nombre, racine);
    } else {
        printf("%d n'est pas un carré parfait.\n", nombre);
    }

    return 0;
}
