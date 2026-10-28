/*
 * banner.h - Antarmuka identitas kelompok dan menu (Anggota 1)
 *
 * Dipanggil dari main.c. Semua modul lain boleh pakai KELOMPOK_ID
 * (mis. untuk nama berkas log: C10-malloc_std-<timestamp>.txt).
 */
#ifndef BANNER_H
#define BANNER_H

#define KELOMPOK_ID   "C10"   /* <KELAS><KELOMPOK>, dipakai di banner & nama log */
#define KELOMPOK_VARIAN 10    /* Varian 10 - Peta Segmen Memori & Simbol Biner  */

/* Nomor pilihan menu (sesuai contoh di soal) */
enum {
    MENU_MALLOC = 1,
    MENU_MMAP   = 2,
    MENU_VARIAN = 3,
    MENU_EXIT   = 4
};

/* Cetak identitas kelompok (nama, NPM, varian). Dipanggil sekali di awal. */
void banner_print_identity(void);

/* Cetak menu utama:  === KELOMPOK C10 - TUGAS MEMORI === ... Input: */
void banner_print_menu(void);

#endif /* BANNER_H */
