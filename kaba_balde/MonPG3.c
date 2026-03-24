/*
 * Fichier : MonPG3.c (Programme Cible 3)
 * Rôle : Vérificateur de nombres parfaits (somme des diviseurs).
 * Utilité dans le projet : Fournit un exécutable légitime supplémentaire
 * pour la validation de couverture de l'algorithme d'infection du virus.
 */
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Calcule la somme des diviseurs propres d'un nombre et vérifie s'il est parfait
bool estParfait(int n, int *sommeDiviseurs) {
    if (n < 1) return false;
    *sommeDiviseurs = 0;
    for (int i = 1; i <= n / 2; i++) { 
        if (n % i == 0) {
            *sommeDiviseurs += i;
        }
    }
    return (*sommeDiviseurs == n);
}

int main() {
    int nombre, sommeDiviseurs;
    printf("Entrez un nombre pour analyser ses diviseurs et vérifier s'il est parfait : ");
    scanf("%d", &nombre);

    if (nombre < 1) {
        printf("Veuillez entrer un nombre positif.\n");
        return 1;
    }

    printf("Diviseurs propres de %d : ", nombre);
    for (int i = 1; i <= nombre / 2; i++) {
        if (nombre % i == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");

    if (estParfait(nombre, &sommeDiviseurs)) {
        printf("%d est un nombre parfait ! (Somme des diviseurs = %d)\n", nombre, sommeDiviseurs);
    } else {
        printf("%d n'est pas un nombre parfait. (Somme des diviseurs = %d)\n", nombre, sommeDiviseurs);
    }

    return 0;
}