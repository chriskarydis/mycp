/* Λειτουργικά Συστήματα | Επεισόδιο ΙΙ | Ομάδα Χρηστών ΙΙΙ | Παραλλαγή της cp γνωστή και ως mycp */

/* -------------------------------------------------------------- */

/* Τμήμα εισαγωγής βιβλιοθηκών εισόδου / εξόδου στην C */

#include "file_operations.h"
#include "error_handling.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/statvfs.h>
#include <time.h>

/* Aξιοποιούνται οι: string.h που περιέχει συναρτήσεις για τον
   χειρισμό συμβολοσειρών (πίνακες χαρακτήρων), όπως: strncmp(),
   memset() κα.  η stdlib.h η οποία περιλαμβάνει διάφορες συναρτήσεις
   που σχετίζονται με την λειτουργία του εκάστοτε συστήματος όπως:
   malloc(), atoi(), exit(), system() κα. , η errno.h η οποία ορίζει 
   την ακέραια μεταβλητή errno, η οποία ορίζεται από κλήσεις συστήματος 
   και ορισμένες λειτουργίες βιβλιοθήκης σε περίπτωση σφάλματος για να 
   υποδείξει τι πήγε στραβά, η sys/statvfs η οποία χρησιμοποιείται για να 
   εισάγει τις δηλώσεις και τις συναρτήσεις που απαιτούνται για τον έλεγχο 
   των χαρακτηριστικών του συστήματος αρχείων και η time.h η οποία περιέχει ορισμούς 
   συναρτήσεων για τη λήψη και τον χειρισμό πληροφοριών ημερομηνίας και ώρας.
   Επίσης, γίνεται χρήση των "error_handling.h" και "file_operations.h" τα 
   οποία είναι header αρχεία για τα αντίστοιχα "error_handling.c"
   και "file_operations.c", όπου σε αυτά βρίσκονται οι δηλώσεις μόνο των συναρτήσεων και
   των σταθερών που αξιοποιούνται στα αρχεία που γίνονται include. */


/* -------------------------------------------------------------- */


/* Τμήμα Υλοποίησης της παραλλαγής mycp */


/* -------------------------------------------------------------- */

/*  Συνάρτηση checkFreeSpace() τύπου int με παράμετρους τα const char *path long file_size 
    η οποία υπολογίζει τον ελεύθερο χώρο που υπάρχει στο εκάστοτε σύστημά και ελέγχει
    αν το μέγεθος του αρχείου χωράει στον δίσκο μας. Σε αντίθετη περίπτωση  εκτυπώνει τα
    αντίστοιχα μήνυμα σφάλματος και τους αντίστοιχους κωδικούς τους. */

int checkFreeSpace(const char *path, long file_size) {
    struct statvfs stat;
    if (statvfs(path, &stat) != 0) {
        perror("Error in statvfs");
        fprintf(stderr, "The program exits with code 8!\n");
        return ERR_FILESYSTEM;
    }

    long available_space = stat.f_bsize * stat.f_bavail;
    printf("Available space: %ld bytes, File size: %ld bytes\n", available_space, file_size);
    
    if (file_size > available_space) {
        fprintf(stderr, "The program exits with code 9!\n");
        return ERR_INSUF_AVAILABLE_SPACE;
    }

    return SUCCESS;
}

/*  Συνάρτηση openFile() τύπου FILE* με παράμετρους τα const char *file_path, const char *mode 
    η οποία ανοίγει ένα αρχείο για το αντίστοιχο mode που θέλουμε. Σε αντίθετη περίπτωση 
    εκτυπώνει τα αντίστοιχα μήνυμα σφάλματος και τους αντίστοιχους κωδικούς τους.*/

FILE* openFile(const char *file_path, const char *mode) {
    FILE *file = fopen(file_path, mode);
    if (file == NULL) {
        fprintf(stderr, "Message: \n\n");
        fprintf(stderr, "   Unable to open file: %s\n\n", strerror(errno));
    }
    return file;
}

/*  Συνάρτηση copyFile() τύπου int με παράμετρους τα FILE *source_file, FILE *dest_file,
    int buffer_size, double *cpu_time_used, double *speed η οποία αντιγράφει στην μία περίπτωση με χρήση
    του buffer, του οποίου το μέγεθος έχει δοθεί από το χρήστη, και στην άλλη περίπτωση 
    με το standard buffer I/O. Επίσης, γίνεται χρονομέτρηση της διαδικασίας αυτής και εκτυπώνεται
    ο χρόνος που απαιτείται να ολοκληρωθεί η διαδιακασία και με ποια ταχύτητα αυτό γίνεται. Σε αντίθετη περίπτωση εκτυπώνει 
    τα αντίστοιχα μήνυμα σφάλματος και τους αντίστοιχους κωδικούς τους.*/

int copyFile(FILE *source_file, FILE *dest_file, int buffer_size, double *cpu_time_used, double *speed, long file_size) {
    clock_t start, end;

    start = clock();

    int ch;
    if (buffer_size > 0) {
        char *buffer = (char *)malloc(buffer_size * sizeof(char));
        if (buffer == NULL) {
            fprintf(stderr, "Message: \n\n");
            fprintf(stderr, "   Memory allocation failed.\n\n");
            fprintf(stderr, "The program exits with code 6!\n");
            return ERR_UNABLE_TO_ALLOCATE_MEMORY;
        }
        size_t bytes_read;
        printf("Copying with buffer size: %d\n", buffer_size);
        while ((bytes_read = fread(buffer, sizeof(char), buffer_size, source_file)) > 0) {
            fwrite(buffer, sizeof(char), bytes_read, dest_file);
        }
        free(buffer);
    } else {
        while ((ch = fgetc(source_file)) != EOF) {
            fputc(ch, dest_file);
        }
    }

    end = clock();
    *cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    *speed = file_size / *cpu_time_used;

    printf("File copied successfully.\n");
    printf("Time taken to copy the file: %f seconds\n", *cpu_time_used);
    printf("Speed: %f bytes per second\n", *speed);


    return SUCCESS;
}

/* -------------------------------------------------------------- */

/* You reached the end of the following file :D 
   CHRISTOS - SPYRIDON KARYDIS & SPYRIDON - EFTYCHIOS KOKOTOS */
