/*
 * alloc_mmap.c - Alokasi dengan mmap anonymous / munmap (Anggota 3)
 *
 * Urutan output (sama dengan komentar alloc.h / contoh di soal):
 *   VmSize Before: X KB | VmRSS Before: Y KB
 *   How many integers to allocate: <input>
 *   (kosong)
 *   Starting memory address: 0x...
 *   Printing first 10 values in reverse order:
 *   <10 angka>
 *   (kosong)
 *   VmSize After: X KB | VmRSS After: Y KB
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#include "alloc.h"
#include "logger.h"
#include "memstat.h"

#define PRINT_COUNT   10          // banyaknya nilai yg ditampilkan 
#define MAX_INTEGERS  268435456LL 

// buat cetak metrik dgn label "before"/"after"
static void print_metrics(const char *label, const MemMetrics *m)
{
    log_printf("VmSize %s: %ld KB | VmRSS %s: %ld KB\n",
               label, m->vmsize_kb, label, m->vmrss_kb);
}

// minta jumlh integer dri user. return 0 jika valid, -1 jika tidak
static int read_count(long long *out)
{
    char buf[64];

    log_printf("How many integers to allocate: ");
    fflush(stdout);

    if (!fgets(buf, sizeof buf, stdin))
        return -1;

    // buang sisa baris klo input lbh panjng dri buffer
    if (!strchr(buf, '\n')) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    char *end;
    errno = 0;
    long long v = strtoll(buf, &end, 10);
    if (end == buf || errno != 0 || v <= 0 || v > MAX_INTEGERS)
        return -1;

    /* Sesuai alloc.h: input harus masuk log, jadi dicatat lewat
     * log_printf(). Di terminal angka ini tampil sekali lagi di bawah
     * echo ketikan pengguna; di berkas log tampil tepat sekali. */
    log_printf("%lld\n", v);

    *out = v;
    return 0;
}

void alloc_mmap_run(void)
{
    MemMetrics before, after;

    if (read_mem_metrics(&before) != 0) {
        log_printf("Gagal membaca /proc/self/status\n");
        return;
    }
    print_metrics("Before", &before);

    long long n;
    if (read_count(&n) != 0) {
        log_printf("\nInput tidak valid (masukkan angka 1 - %lld).\n",
                   MAX_INTEGERS);
        return;
    }
    size_t bytes = (size_t)n * sizeof(int);

    /* mmap anonymous: ga terikat berkas, diisi nol oleh kernel, hanya bisa dibaca/ditulis proses ini (MAP_PRIVATE). */
    int *arr = mmap(NULL, bytes, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (arr == MAP_FAILED) {
        log_printf("\nmmap gagal: %s\n", strerror(errno));
        return;
    }

    /* Isi array. untuk memicu page fault jdi kernel nyedian RAM fisik (VmRSS naik). */
    for (long long i = 0; i < n; i++)
        arr[i] = (int)(i + 1);

    log_printf("\nStarting memory address: %p\n", (void *)arr);
    log_printf("Printing first %d values in reverse order:\n", PRINT_COUNT);
    long long shown = (n < PRINT_COUNT) ? n : PRINT_COUNT;
    for (long long k = 0; k < shown; k++)
        log_printf("%d\n", arr[n - 1 - k]);

    /* Metrik dibaca sblm munmap. */
    if (read_mem_metrics(&after) == 0) {
        log_printf("\n");
        print_metrics("After", &after);
        /* munjukkan perubahan VmSize/VmRSS dibandingkan antara malloc dan mmap. baris ini ngebuat selisihnya lgsg terbaca di terminal dan log. */
        log_printf("Perubahan: VmSize %+ld KB | VmRSS %+ld KB\n",
                   after.vmsize_kb - before.vmsize_kb,
                   after.vmrss_kb - before.vmrss_kb);
    }

    if (munmap(arr, bytes) != 0)
        log_printf("munmap gagal: %s\n", strerror(errno));
}
