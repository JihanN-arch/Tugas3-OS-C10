/*
 * alloc_malloc.c - Alokasi dengan malloc/free (Anggota 2)
 *
 * STUB: sementara cuma nunjukin pembacaan metrik. Anggota 2 ganti isinya
 * sesuai urutan output di alloc.h (alokasi N integer, isi nilai, cetak
 * alamat + 10 nilai terbalik, free, metrik sesudah).
 */
#include "alloc.h"
#include "logger.h"
#include "memstat.h"

void alloc_malloc_run(void)
{
    MemMetrics m;
    if (read_mem_metrics(&m) == 0)
        log_printf("VmSize Before: %ld KB | VmRSS Before: %ld KB\n",
                   m.vmsize_kb, m.vmrss_kb);
    log_printf("[STUB Anggota 2] alloc_malloc_run() belum diimplementasi\n");
}
