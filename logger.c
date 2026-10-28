/*
 * logger.c - Pencatatan log (Anggota 4)
 *
 * STUB: sementara hanya cetak ke terminal supaya program bisa jalan
 * end-to-end. Anggota 4 ganti dengan implementasi dua metode:
 *   1) fopen / fprintf / fclose     -> <KELOMPOK>-<metode>_std-<timestamp>.txt
 *   2) open / write / close         -> <KELOMPOK>-<metode>_sys-<timestamp>.txt
 * Tanda tangan fungsi (lihat logger.h) JANGAN diubah.
 */
#include <stdarg.h>
#include <stdio.h>
#include "logger.h"

int log_open(const char *metode)
{
    (void)metode;   /* TODO Anggota 4: buka dua berkas log */
    return 0;
}

void log_printf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);   /* TODO Anggota 4: tulis juga ke _std dan _sys */
    va_end(ap);
}

void log_close(void)
{
    /* TODO Anggota 4: tutup kedua berkas log */
}
