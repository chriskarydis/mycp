/* Λειτουργικά Συστήματα | Επεισόδιο ΙΙ | Ομάδα Χρηστών ΙΙΙ | Παραλλαγή της cp γνωστή και ως mycp */

/* -------------------------------------------------------------- */

/* Τμήμα εισαγωγής βιβλιοθηκών εισόδου / εξόδου στην C */

#include "report_generator.h"
#include "error_handling.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>

/* Aξιοποιούνται οι: stdio.h η οποία περιλαμβάνει βασικές
   συναρτήσεις εισόδου / εξόδου όπως η fprintf(), scanf()
   fopen(), fclose(), κα. ,η string.h που περιέχει συναρτήσεις 
   για το χειρισμό συμβολοσειρών (πίνακες χαρακτήρων), όπως: strncmp(),
   memset() κα. , η errno.h ορίζει την ακέραια μεταβλητή errno, η οποία 
   ορίζεται από κλήσεις συστήματος και ορισμένες λειτουργίες βιβλιοθήκης σε περίπτωση σφάλματος για να 
   υποδείξει τι πήγε στραβά. Επίσης, γίνεται χρήση των "error_handling.h" και 
   "report_generator.h" τα οποία είναι τα header αρχεία για τα αντίστοιχα 
   "error_handling.c" και "report_generator.c", όπου σε αυτά βρίσκονται οι 
   δηλώσεις μόνο των συναρτήσεων και των σταθερών που αξιοποιούνται στα αρχεία 
   που γίνονται include. Αυτά χειρίζονται τα σφάλματα και δημιουργούν το 
   report.out αρχείο, αντίστοιχα*/

/* -------------------------------------------------------------- */

/*  Δήλωση συνάρτησης generateReport() με παραμέτρους double cpu_time_used, 
    int buffer_size, long file_size η οποία δημιουργεί το αρχείο report.out,
    το οποίο περιέχει τα αποτελέσματα από την κάθε εκτέλεση του mycp. Αν αποτύχει
    η δημιουργία του εκτυπώνεται αντίστοιχο μήνυμα σφάλματος και ο κωδικός του.*/

int generateReport(double cpu_time_used, int buffer_size, long file_size, double speed) {
    FILE *report_file = fopen("report.out", "a");
    if (report_file == NULL) {
        fprintf(stderr, "Message: \n\n");
        fprintf(stderr, "   Unable to create report file: %s\n\n", strerror(errno));
        fprintf(stderr, "The program exits with code 5!\n");
        return ERR_UNABLE_TO_CREATE_REPORT;
    }

    fprintf(report_file, "Time taken: %f seconds | Speed: %f bytes per second | Buffer size: %d | File size: %ld bytes \n", cpu_time_used, speed, buffer_size, file_size);

    fclose(report_file);

    return SUCCESS;
}

/* -------------------------------------------------------------- */

/* You reached the end of the following file :D 
   CHRISTOS - SPYRIDON KARYDIS & SPYRIDON - EFTYCHIOS KOKOTOS */
