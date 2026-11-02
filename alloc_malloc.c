/*
 * alloc_malloc.c - Alokasi dengan malloc/free (Anggota 2)
 *
 * Modul ini membaca VmSize/VmRSS sebelum dan sesudah alokasi, meminta
 * jumlah integer, mengalokasikan array dengan malloc(), mengisi seluruh
 * elemen agar halaman memorinya benar-benar diakses, lalu membebaskannya
 * dengan free(). Semua keluaran memakai log_printf() agar dapat diteruskan
 * ke terminal dan kedua berkas log oleh modul logger.
 */
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alloc.h"
#include "logger.h"
#include "memstat.h"

#define PRINT_COUNT   10
#define MAX_INTEGERS  268435456LL

/* Cetak sepasang metrik dengan format yang sama seperti contoh soal. */
static void print_metrics(const char *label, const MemMetrics *metrics)
{
    log_printf("VmSize %s: %ld KB | VmRSS %s: %ld KB\n",
               label, metrics->vmsize_kb, label, metrics->vmrss_kb);
}

/*
 * Baca jumlah integer sebagai satu baris agar input seperti "12abc" dapat
 * ditolak. Nilai yang valid dicatat ulang melalui log_printf() karena echo
 * dari terminal tidak otomatis masuk ke berkas log.
 */
static int read_count(long long *out)
{
    char buffer[64];

    log_printf("How many integers to allocate: ");
    fflush(stdout);

    if (fgets(buffer, sizeof buffer, stdin) == NULL)
        return -1;

    /* Buang sisa baris jika input lebih panjang daripada buffer. */
    if (strchr(buffer, '\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        return -1;
    }

    errno = 0;
    char *end;
    long long value = strtoll(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || value <= 0 ||
        value > MAX_INTEGERS)
        return -1;

    /* Setelah angka, hanya whitespace yang diperbolehkan. */
    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n')
        end++;
    if (*end != '\0')
        return -1;

    if ((unsigned long long)value > SIZE_MAX / sizeof(int))
        return -1;

    log_printf("%lld\n", value);
    *out = value;
    return 0;
}

void alloc_malloc_run(void)
{
    MemMetrics before, after;

    if (read_mem_metrics(&before) != 0) {
        log_printf("Gagal membaca /proc/self/status\n");
        return;
    }
    print_metrics("Before", &before);

    long long count;
    if (read_count(&count) != 0) {
        log_printf("\nInput tidak valid (masukkan angka 1 - %lld).\n",
                   MAX_INTEGERS);
        return;
    }

    size_t bytes = (size_t)count * sizeof(int);
    int *values = malloc(bytes);
    if (values == NULL) {
        log_printf("\nmalloc gagal mengalokasikan %zu byte.\n", bytes);
        return;
    }

    /*
     * Menulis setiap elemen memicu demand paging. Tanpa akses ini, kenaikan
     * VmRSS dapat kecil karena sebagian halaman belum mendapat RAM fisik.
     */
    for (long long i = 0; i < count; i++)
        values[i] = (int)(i + 1);

    log_printf("\nStarting memory address: %p\n", (void *)values);
    log_printf("Printing first %d values in reverse order:\n", PRINT_COUNT);

    long long shown = count < PRINT_COUNT ? count : PRINT_COUNT;
    for (long long i = 0; i < shown; i++)
        log_printf("%d\n", values[count - 1 - i]);

    /* Metrik sesudah dibaca sebelum free agar efek alokasi masih terlihat. */
    if (read_mem_metrics(&after) != 0) {
        log_printf("\nGagal membaca /proc/self/status setelah alokasi.\n");
        free(values);
        return;
    }

    log_printf("\n");
    print_metrics("After", &after);
    log_printf("Perubahan: VmSize %+ld KB | VmRSS %+ld KB\n",
               after.vmsize_kb - before.vmsize_kb,
               after.vmrss_kb - before.vmrss_kb);

    free(values);
}
