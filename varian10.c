/*
 * varian10.c - Peta Segmen Memori & Simbol Biner (Anggota 5)
 *
 * STUB: Anggota 5 ganti isinya: buat variabel lokal, global
 * terinisialisasi, BSS, fungsi, cetak alamat masing-masing, lalu
 * cocokkan dengan /proc/self/maps.
 */


#include <stdio.h>
#include <stdlib.h>

#include "varian10.h"
#include "logger.h"

static int global = 10;
static int uninitialized;

static void print_mem();
static void function(){}

void varian10_run(void) {

    log_printf("--- Varian 10: Peta Segmen ---\n");

    int local = 20;
    int *heap = malloc(sizeof(int));

    if (heap == NULL) {
        perror("malloc");
        return;
    }

    log_printf("Text    : %p\n", (void *) function);
    log_printf("Data    : %p\n", (void *) &global);
    log_printf("BSS     : %p\n", (void *) &uninitialized);
    log_printf("Heap    : %p\n", (void *) heap);
    log_printf("Stack   : %p\n", (void *) &local);

    print_mem();
    free(heap);
}

static void print_mem(){

    char line[256];

    FILE *file = fopen("/proc/self/maps", "r");

    if (file == NULL) {
        perror("fopen");
        return;
    }
   
    while (fgets(line, sizeof(line), file) != NULL) {
        log_printf("%s", line);
    }
    
    fclose(file);  
}