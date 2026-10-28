/*
 * memstat.c - Baca VmSize dan VmRSS dari /proc/self/status (Anggota 2)
 *
 * STATUS: implementasi awal (sudah jalan) supaya anggota lain bisa
 * langsung memakai. Anggota 2 bebas menyempurnakan/menambah komentar.
 */
#include <stdio.h>
#include <string.h>
#include "memstat.h"

int read_mem_metrics(MemMetrics *out)
{
    FILE *f = fopen("/proc/self/status", "r");
    if (!f)
        return -1;

    char line[256];
    int got = 0;
    out->vmsize_kb = 0;
    out->vmrss_kb = 0;

    /* Baris yang dicari berformat:  "VmSize:   1148 kB" */
    while (fgets(line, sizeof line, f)) {
        if (sscanf(line, "VmSize: %ld", &out->vmsize_kb) == 1)
            got |= 1;
        else if (sscanf(line, "VmRSS: %ld", &out->vmrss_kb) == 1)
            got |= 2;
        if (got == 3)
            break;
    }
    fclose(f);
    return (got == 3) ? 0 : -1;
}
