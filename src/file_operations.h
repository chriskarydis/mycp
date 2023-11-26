/* Λειτουργικά Συστήματα | Επεισόδιο ΙΙ | Ομάδα Χρηστών ΙΙΙ | Παραλλαγή της cp γνωστή και ως mycp */

/* -------------------------------------------------------------- */

/* Τμήμα εισαγωγής βιβλιοθηκών εισόδου / εξόδου στην C */

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stdio.h>

/* Aξιοποιείται η stdio.h η οποία περιλαμβάνει βασικές
   συναρτήσεις εισόδου / εξόδου όπως η fprintf(), scanf()
   fopen(), fclose(), κα.*/

/* Δήλωση της συνάρτησης copyFile() με παραμέτρους: 
   FILE *source_file, FILE *dest_file, int buffer_size, double *cpu_time_used, double *speed
   
   Δήλωση της συνάρτησης openFile() με παραμέτρους: 
   const char *file_path, const char *mode

   Δήλωση της συνάρτησης checkFreeSpace() με παραμέτρους: 
   const char *path, long file_size */

int copyFile(FILE *source_file, FILE *dest_file, int buffer_size, double *cpu_time_used, double *speed, long file_size);
FILE* openFile(const char *file_path, const char *mode);
int checkFreeSpace(const char *path, long file_size);

#endif /* FILE_OPERATIONS_H */

/* -------------------------------------------------------------- */

/* You reached the end of the following file :D 
   CHRISTOS - SPYRIDON KARYDIS & SPYRIDON - EFTYCHIOS KOKOTOS */
