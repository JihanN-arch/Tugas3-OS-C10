/*
 * memstat.c - Baca VmSize dan VmRSS dari /proc/self/status (Anggota 2)
 *
 * /proc/self/status adalah berkas virtual yang disediakan kernel Linux.
 * Fungsi ini mencari baris VmSize dan VmRSS, lalu mengembalikan nilainya
 * dalam kB melalui struktur MemMetrics.
 */
#include <stdio.h>
#include "memstat.h"

int read_mem_metrics(MemMetrics *out)
{
    if (out == NULL)
        return -1;

    FILE *f = fopen("/proc/self/status", "r");
    if (!f)
        return -1;

    char line[256];
    int got = 0;
    out->vmsize_kb = 0;
    out->vmrss_kb = 0;

    /* Baris yang dicari berformat: "VmSize:    1148 kB". */
    while (fgets(line, sizeof line, f)) {
        long value;

        if (sscanf(line, "VmSize: %ld kB", &value) == 1) {
            out->vmsize_kb = value;
            got |= 1;
        } else if (sscanf(line, "VmRSS: %ld kB", &value) == 1) {
            out->vmrss_kb = value;
            got |= 2;
        }

        if (got == 3)
            break;
    }
    fclose(f);
    return (got == 3) ? 0 : -1;
}
