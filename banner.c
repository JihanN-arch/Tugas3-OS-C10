/*
 * banner.c - Identitas kelompok dan menu pilihan (Anggota 1)
 */
#include <stdio.h>
#include "banner.h"

/* TODO: isi nama dan NPM seluruh anggota kelompok C10 */
static const char *anggota[] = {
    "Anggota 1 - Fanny (NPM ...)",
    "Anggota 2 - <nama> (NPM ...)",
    "Anggota 3 - <nama> (NPM ...)",
    "Anggota 4 - <nama> (NPM ...)",
    "Anggota 5 - <nama> (NPM ...)"
};

void banner_print_identity(void)
{
    printf("=============================================================\n");
    printf(" TUGAS 3 - MEMORY | CSCM602055 Sistem Operasi Gasal 2026/2027\n");
    printf(" Kelompok %s | Varian %d - Peta Segmen Memori & Simbol Biner\n",
           KELOMPOK_ID, KELOMPOK_VARIAN);
    printf("-------------------------------------------------------------\n");
    for (size_t i = 0; i < sizeof(anggota) / sizeof(anggota[0]); i++)
        printf(" %s\n", anggota[i]);
    printf("=============================================================\n");
}

void banner_print_menu(void)
{
    printf("\n=== KELOMPOK %s - TUGAS MEMORI ===\n", KELOMPOK_ID);
    printf("%d. Allocate with malloc/free\n", MENU_MALLOC);
    printf("%d. Allocate with mmap/munmap\n", MENU_MMAP);
    printf("%d. Eksekusi Fitur Variasi Kelompok\n", MENU_VARIAN);
    printf("%d. Exit\n", MENU_EXIT);
    printf("Input: ");
    fflush(stdout);
}
