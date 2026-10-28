/*
 * main.c - Program utama Tugas 3 Memory (Anggota 1)
 *
 * Menampilkan identitas kelompok + menu, lalu memanggil modul sesuai
 * pilihan. Opsi 1 dan 2 dibungkus pembukaan/penutupan log supaya seluruh
 * output pengujian (termasuk VmSize/VmRSS dan alamat memori) tercatat.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banner.h"
#include "logger.h"
#include "alloc.h"
#include "varian10.h"

/* Baca satu baris dari stdin lalu ubah ke angka.
 * Return -1 kalau bukan angka, MENU_EXIT kalau input habis (EOF). */
static int read_choice(void)
{
    char buf[64];

    if (!fgets(buf, sizeof buf, stdin))
        return MENU_EXIT;

    /* Buang sisa baris kalau input lebih panjang dari buffer */
    if (!strchr(buf, '\n')) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    char *end;
    long v = strtol(buf, &end, 10);
    if (end == buf)
        return -1;
    return (int)v;
}

/* Buka log -> cetak "You picked" -> jalankan modul -> tutup log. */
static void run_logged(const char *metode, const char *label, void (*fn)(void))
{
    if (log_open(metode) != 0)
        fprintf(stderr, "[WARN] Berkas log gagal dibuka, lanjut tanpa log.\n");

    log_printf("\nYou picked %s.\n", label);
    fn();
    log_close();
}

int main(void)
{
    banner_print_identity();

    for (;;) {
        banner_print_menu();
        int choice = read_choice();

        switch (choice) {
        case MENU_MALLOC:
            run_logged("malloc", "malloc/free", alloc_malloc_run);
            break;
        case MENU_MMAP:
            run_logged("mmap", "mmap/munmap", alloc_mmap_run);
            break;
        case MENU_VARIAN:
            /* Varian tidak dicatat ke berkas log malloc/mmap (lihat logger.h) */
            log_printf("\nYou picked Eksekusi Fitur Variasi Kelompok.\n");
            varian10_run();
            break;
        case MENU_EXIT:
            printf("\nSampai jumpa!\n");
            return 0;
        default:
            printf("\nPilihan tidak valid, masukkan angka 1-4.\n");
            break;
        }
    }
}
