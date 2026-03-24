/*
 * Fichier : MonPG1.c (Programme Cible 1)
 * Rôle : Calculatrice basique en ligne de commande.
 * Utilité dans le projet : Sert de programme légitime cible pour l'infection
 * par le virus compagnon. Démontre que les entrées/sorties utilisateur 
 * (scanf/printf) fonctionnent parfaitement même après un transfert furtif.
 */
#include <stdio.h>
#include <stdlib.h>

int main() {
  int choix;
  double num1, num2, resultat;
  do {
    printf("\n------ Calculatrice simple -----\n");
    printf("1.Addition\n");
    printf("2.Soustraction\n");
    printf("3.Multiplication\n");
    printf("4.Division\n");
    printf("5.Quitter\n");
    printf("Votre choix\n");
    if (scanf("%d", &choix) != 1) {
      int c;
      while ((c = getchar()) != '\n' && c != EOF)
        ;
      choix = 0;
    }

    if (choix >= 1 && choix <= 4) {
      printf("Entrez le premier nombre: ");
      scanf("%lf", &num1);

      printf("Entrez le deuxième nombre: ");
      scanf("%lf", &num2);

      switch (choix) {
      case 1:
        resultat = num1 + num2;
        printf("resultat : %2lf\n", resultat);
        break;
      case 2:
        resultat = num1 - num2;
        printf("resultat : %2lf\n", resultat);
        break;
      case 3:
        resultat = num1 * num2;
        printf("resultat : %2lf\n", resultat);
        break;
      case 4:
        if (num2 != 0) {
          resultat = num1 / num2;
        } else {
          printf("erreur\n");
          continue;
        }
        printf("resultat : %2lf\n", resultat);
        break;
      }
    } else if (choix != 5) {
      printf("choix invalide\n");
    }
  } while (choix != 5);

  printf("Au revoir\n");
  return 0;
}
