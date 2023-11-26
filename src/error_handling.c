/* Λειτουργικά Συστήματα | Επεισόδιο ΙΙ | Ομάδα Χρηστών ΙΙΙ | Παραλλαγή της cp γνωστή και ως mycp */

/* -------------------------------------------------------------- */

/* Τμήμα εισαγωγής βιβλιοθηκών εισόδου / εξόδου στην C*/

#include "error_handling.h"
#include "file_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Aξιοποιούνται οι: stdio.h η οποία περιλαμβάνει βασικές
   συναρτήσεις εισόδου / εξόδου όπως η fprintf(), scanf()
   fopen(), fclose(), κα. , η stdlib.h η οποία περιλαμβάνει διάφορες συναρτήσεις
   που σχετίζονται με την λειτουργία του εκάστοτε συστήματος όπως:
   malloc(), atoi(), exit(), system() κα. και string.h που περιέχει συναρτήσεις 
   για το χειρισμό συμβολοσειρών (πίνακες χαρακτήρων), όπως: strncmp(), memset() κα. 
   Επίσης, γίνεται χρήση των "error_handling.h" και "file_operations.h" τα οποία
   είναι τα header αρχεία για τα αντίστοιχα "error_handling.c" και "file_operations.c",
   όπου σε αυτά βρίσκονται οι δηλώσεις μόνο των συναρτήσεων και των σταθερών
   που αξιοποιούνται στα αρχεία που γίνονται include.*/

/* -------------------------------------------------------------- */


/* Τμήμα Υλοποίησης της παραλλαγής mycp */


/* -------------------------------------------------------------- */


/* Αρχικοποίηση της συνάρτησης validateArguments() */

/* Η παρακάτω συνάρτηση validateArguments δέχεται για παραμέτρους τις εξής μεταβλητές:
   int argc, char *argv[], int *buffer_size, char **source_path, char **dest_path με τις 
   οποίες ελέγχει αν ο χρήστης έχει αποδώσει με τον σωστό τρόπο την εντολή για να 
   χρησιμοποιήσει την mycp. */

int validateArguments(int argc, char *argv[], int *buffer_size, char **source_path, char **dest_path) { 

    /* Έλεγχος για το αν το πλήθος του argc είναι εκτός του διαστήματος [3,4]. Εφόσον
       δεν πληροί τις προϋποθέσεις, το πρόγραμμα εκτυπώνει το αντίστοιχο σφάλμα λάθους,
       τον κωδικό του (σφάλματος) και την ορθή χρήση της εντολής. */

    if (argc < 3 || argc >= 5) {  
      fprintf(stderr, "Validation of arguments failed.\n");
        fprintf(stderr, "Usage: \n\n");
        fprintf(stderr, "      To copy without buffer size: mycp <source> <destination>\n");
        fprintf(stderr, "      To copy with buffer size: mycp -b<buffer_size> <source> <destination>\n\n");
        fprintf(stderr, "The program exits with code 1!\n");
        return ERR_INSUFFICIENT_ARGS;
    }

    /* Έλεγχος για το αν το πλήθος του argc είναι ίσο του 4 και αν το argv[1] 
       στους δύο πρώτους χαρακτήρες είναι το ίδιο με το "-b" με τη χρήση του strncmp(). Εφόσον αν
       πληρούνται οι προϋποθέσεις παραβλέπονται οι 2 πρώτοι χαρακτήρες του argv[1] και
       οι υπόλοιποι μετατρέπονται σε int μέσω του atoi() (δηλαδή το μέρος που μας δίνει το μέγεθος του buffer). 
       Στην πέριπτωση που το μέγεθος του buffer_size είναι αρνητικό ή μηδέν 
       το πρόγραμμα εκτυπώνει το αντίστοιχο σφάλμα λάθους και
       τον κωδικό του σφάλματος. */

    if (argc == 4 && strncmp(argv[1], "-b", 2) == 0) {
        *buffer_size = atoi(argv[1] + 2);
        if (*buffer_size <= 0) {
            fprintf(stderr, "Message: \n\n");
            fprintf(stderr, "   Invalid buffer size.\n\n");
            fprintf(stderr, "The program exits with code 2!\n");
            return ERR_INVALID_BUFFER_SIZE;
        }
    } else if (argc > 4 || (argc == 4 && strncmp(argv[1], "-b", 2) != 0)) {
        fprintf(stderr, "Message: \n\n");
        fprintf(stderr, "   Invalid option or too many arguments. Use -b<buffer_size> to specify the buffer size.\n\n");
        fprintf(stderr, "The program exits with code 2!\n");
        return ERR_INVALID_BUFFER_SIZE;
    }

    *source_path = argv[argc - 2];
    *dest_path = argv[argc - 1];

    return SUCCESS;
}

/* -------------------------------------------------------------- */

/* You reached the end of the following file :D 
   CHRISTOS - SPYRIDON KARYDIS & SPYRIDON - EFTYCHIOS KOKOTOS */
