/*
 * logger.h - Pencatatan log (Anggota 4)
 *
 * KONTRAK PENTING untuk semua anggota:
 *   Jangan pakai printf() untuk output yang harus masuk log.
 *   Pakai log_printf() -> otomatis tampil di terminal DAN tertulis ke
 *   dua berkas log sekaligus (Standard C Library dan System Call).
 *
 * Alur yang dipanggil main.c untuk opsi 1 / 2:
 *   log_open("malloc");     // atau "mmap"
 *   log_printf("\nYou picked malloc/free.\n");
 *   alloc_malloc_run();     // semua output lewat log_printf
 *   log_close();
 *
 * Nama berkas (format dari soal), timestamp mis. 20261028_111800:
 *   C10-malloc_std-<timestamp>.txt   (fopen/fprintf/fclose)
 *   C10-malloc_sys-<timestamp>.txt   (open/write/close)
 *   C10-mmap_std-<timestamp>.txt
 *   C10-mmap_sys-<timestamp>.txt
 *
 * Kalau belum ada log yang dibuka, log_printf() cukup cetak ke terminal.
 */
#ifndef LOGGER_H
#define LOGGER_H

/* metode: "malloc" atau "mmap". Return 0 sukses, -1 gagal. */
int  log_open(const char *metode);

/* printf-style: ke terminal + berkas _std + berkas _sys. */
void log_printf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

/* Tutup kedua berkas log. Aman dipanggil walau log belum dibuka. */
void log_close(void);

#endif /* LOGGER_H */
