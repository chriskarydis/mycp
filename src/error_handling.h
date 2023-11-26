/* Λειτουργικά Συστήματα | Επεισόδιο ΙΙ | Ομάδα Χρηστών ΙΙΙ | Παραλλαγή της cp γνωστή και ως mycp */

/* -------------------------------------------------------------- */

/* Τμήμα εισαγωγής βιβλιοθηκών εισόδου / εξόδου στην C*/

#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

/* Ορισμός των σταθέρων στους αριθμούς που αντιστοιχεί στον κωδικό σφάλματος που επιθυμούμε*/

#define SUCCESS 0
#define ERR_INSUFFICIENT_ARGS 1
#define ERR_INVALID_BUFFER_SIZE 2
#define ERR_UNABLE_TO_OPEN_SOURCE 3
#define ERR_UNABLE_TO_CREATE_DEST 4
#define ERR_UNABLE_TO_CREATE_REPORT 5
#define ERR_UNABLE_TO_ALLOCATE_MEMORY 6
#define ERR_INSUFFICIENT_SPACE 7
#define ERR_FILESYSTEM 8
#define ERR_INSUF_AVAILABLE_SPACE 9

/* Δήλωση της συνάρτησης validateArguments() με παραμέτρους: 
   int argc, char *argv[], int *buffer_size, char **source_path, char **dest_path*/

int validateArguments(int argc, char *argv[], int *buffer_size, char **source_path, char **dest_path);


#endif /* ERROR_HANDLING_H */

/* -------------------------------------------------------------- */

/* You reached the end of the following file :D 
   CHRISTOS - SPYRIDON KARYDIS & SPYRIDON - EFTYCHIOS KOKOTOS */
