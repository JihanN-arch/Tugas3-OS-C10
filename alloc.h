/*
 * alloc.h - Modul inti alokasi memori
 *
 * Dua fungsi ini dipanggil dari menu (main.c) setelah log dibuka.
 * Aturan untuk keduanya (sesuai contoh output di soal):
 *   - Semua output pakai log_printf(), bukan printf().
 *   - Urutan output:
 *       VmSize Before: X KB | VmRSS Before: Y KB
 *       How many integers to allocate: <input>
 *       (kosong)
 *       Starting memory address: 0x...
 *       Printing first 10 values in reverse order:
 *       <10 angka>
 *       (kosong)
 *       VmSize After: X KB | VmRSS After: Y KB
 *   - "You picked ..." SUDAH dicetak main.c, jangan dicetak lagi.
 *   - Baca metrik lewat read_mem_metrics() di memstat.h.
 *   - Input angka boleh scanf/fgets dari stdin. Karena input harus
 *     masuk log juga, catat nilainya lewat log_printf().
 */
#ifndef ALLOC_H
#define ALLOC_H

void alloc_malloc_run(void);   /* alloc_malloc.c - Anggota 2 */
void alloc_mmap_run(void);     /* alloc_mmap.c   - Anggota 3 */

#endif /* ALLOC_H */
