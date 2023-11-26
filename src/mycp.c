/* Λειτουργικά Συστήματα | Επεισόδιο ΙΙ | Ομάδα Χρηστών ΙΙΙ | Παραλλαγή της cp γνωστή και ως mycp */

/* -------------------------------------------------------------- */

/* Τμήμα εισαγωγής βιβλιοθηκών εισόδου / εξόδου στην C */

#include <stdio.h>
#include <stdlib.h>
#include "file_operations.h"
#include "error_handling.h"
#include "report_generator.h"

/* Aξιοποιούνται οι: stdio.h η οποία περιλαμβάνει βασικές
   συναρτήσεις εισόδου / εξόδου όπως η fprintf(), scanf()
   fopen(), fclose(), κα. και η stdlib.h η οποία περιλαμβάνει διάφορες συναρτήσεις
   που σχετίζονται με την λειτουργία του εκάστοτε συστήματος όπως:
   malloc(), atoi(), exit(), system() κα. Επίσης, γίνεται χρήση των "error_handling.h", 
   "report_generator.h" και "file_operations.h" τα οποία είναι τα header αρχεία για τα αντίστοιχα 
   "error_handling.c", "report_generator.c" και "file_operations.c", όπου σε αυτά βρίσκονται οι 
   δηλώσεις μόνο των συναρτήσεων και των σταθερών που αξιοποιούνται στα αρχεία 
   που γίνονται include. Αυτά χειρίζονται τα σφάλματα, δημιουργούν το 
   report.out αρχείο και υλοποιούν όλες τις διεργασίες που θέλουμε για το αυγκεκριμένο
   πρόγραμμα, όπως το την αντιγραφή του αρχείου, το άνοιγμα ενός αρχείου κα. , αντίστοιχα*/

/* -------------------------------------------------------------- */

int main(int argc, char *argv[]) {

    /*  Δήλωση μεταβλητών  */

    int buffer_size = 0;
    char *source_path = NULL;
    char *dest_path = NULL;
    long file_size = 0;
    double cpu_time_used = 0.0;
    double speed =0.0;

    /*  Έλεγχος ορθότητας ορισμάτων εισόδου  */

    if (validateArguments(argc, argv, &buffer_size, &source_path, &dest_path) != SUCCESS) {
        return ERR_INSUFFICIENT_ARGS;
    }

    printf("Arguments validated.\n");

    /*  Άνοιγμα του πηγαίου αρχείου  */

    FILE *source_file = openFile(source_path, "rb");
    if (source_file == NULL) {
        fprintf(stderr, "The program exits with code 3!\n");
        return ERR_UNABLE_TO_OPEN_SOURCE;
    }

    printf("Source file opened.\n");

    /*  Δημιουργία του αρχείου προορισμού  */

    FILE *dest_file = openFile(dest_path, "wb");
    if (dest_file == NULL) {
        fclose(source_file);
        fprintf(stderr, "The program exits with code 4!\n");
        return ERR_UNABLE_TO_CREATE_DEST;
    }
    
    printf("Destination file opened.\n");
    
    /*  Υπολογισμός μεγέθους του πηγαίου αρχείου  */

    fseek(source_file, 0, SEEK_END);
    file_size = ftell(source_file);
    rewind(source_file);

    /*  Έλεγχος ελεύθερου χώρου στο δίσκο  */

    if (checkFreeSpace(dest_path, file_size) != SUCCESS) {
        fclose(source_file);
        fclose(dest_file);
        return ERR_INSUFFICIENT_SPACE;
    }

    /*  Αντιγραφή του περιεχομένου του αρχείου  */

    if (copyFile(source_file, dest_file, buffer_size, &cpu_time_used, &speed, file_size) != SUCCESS) {
        fclose(source_file);
        fclose(dest_file);
        return EXIT_FAILURE;
    }

    /*  Δημιουργία αναφοράς για την αντιγραφή  */

    if (generateReport(cpu_time_used, buffer_size, file_size, speed) != SUCCESS) {
        fclose(source_file);
        fclose(dest_file);
        return EXIT_FAILURE;
    }

    /*  Κλείσιμο αρχείων  */

    fclose(source_file);
    fclose(dest_file);

    return SUCCESS;
}

/* -------------------------------------------------------------- */

/* You reached the end of the following file :D 
   CHRISTOS - SPYRIDON KARYDIS & SPYRIDON - EFTYCHIOS KOKOTOS */
