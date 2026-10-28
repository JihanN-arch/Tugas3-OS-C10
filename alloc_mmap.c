/*
 * alloc_mmap.c - Alokasi dengan mmap anonymous/munmap (Anggota 3)
 *
 * STUB: Anggota 3 ganti isinya sesuai urutan output di alloc.h, memakai
 * mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0)
 * dan munmap. Perbandingan perubahan VmSize/VmRSS malloc vs mmap
 * juga di sini.
 */
#include "alloc.h"
#include "logger.h"
#include "memstat.h"

void alloc_mmap_run(void)
{
    MemMetrics m;
    if (read_mem_metrics(&m) == 0)
        log_printf("VmSize Before: %ld KB | VmRSS Before: %ld KB\n",
                   m.vmsize_kb, m.vmrss_kb);
    log_printf("[STUB Anggota 3] alloc_mmap_run() belum diimplementasi\n");
}
