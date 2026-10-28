/*
 * memstat.h - Pembacaan metrik memori dari /proc/self/status (Anggota 2)
 *
 * KONTRAK: modul lain (alloc_mmap.c, varian10.c, dll.) cukup panggil
 * read_mem_metrics() untuk dapat VmSize dan VmRSS dalam KB.
 */
#ifndef MEMSTAT_H
#define MEMSTAT_H

typedef struct {
    long vmsize_kb;   /* VmSize: ukuran memori virtual proses  */
    long vmrss_kb;    /* VmRSS : memori fisik yang dipakai     */
} MemMetrics;

/* Return 0 kalau sukses, -1 kalau gagal baca /proc/self/status. */
int read_mem_metrics(MemMetrics *out);

#endif /* MEMSTAT_H */
