/*
 * logger.c - Pencatatan log (Anggota 4)
 *
 * Setiap pemanggilan log_printf() menghasilkan satu string terformat yang
 * dikirim ke tiga tujuan sekaligus:
 *   1) terminal (stdout)
 *   2) berkas _std, ditulis dengan Standard C Library (fopen/fprintf/fclose)
 *   3) berkas _sys, ditulis dengan system call (open/write/close)
 *
 * Nama berkas: <KELOMPOK_ID>-<metode>_std-<timestamp>.txt
 *              <KELOMPOK_ID>-<metode>_sys-<timestamp>.txt
 * contoh     : C10-malloc_std-20261028_111800.txt
 *
 * Kalau log belum dibuka (misalnya opsi varian), log_printf() hanya
 * mencetak ke terminal.
 */
#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "banner.h"
#include "logger.h"

static FILE *log_fp = NULL;   /* berkas _std (Standard C Library) */
static int   log_fd = -1;     /* berkas _sys (System Call)        */

int log_open(const char *metode)
{
    char timestamp[32];
    char name_std[128];
    char name_sys[128];
    time_t now = time(NULL);
    struct tm tm_now;

    /* Tutup log lama kalau masih terbuka, supaya tidak bocor. */
    log_close();

    if (metode == NULL)
        return -1;

    if (localtime_r(&now, &tm_now) == NULL)
        return -1;
    strftime(timestamp, sizeof timestamp, "%Y%m%d_%H%M%S", &tm_now);

    snprintf(name_std, sizeof name_std, "%s-%s_std-%s.txt",
             KELOMPOK_ID, metode, timestamp);
    snprintf(name_sys, sizeof name_sys, "%s-%s_sys-%s.txt",
             KELOMPOK_ID, metode, timestamp);

    /* Metode 1: Standard C Library */
    log_fp = fopen(name_std, "w");
    if (log_fp == NULL) {
        fprintf(stderr, "fopen %s: %s\n", name_std, strerror(errno));
        return -1;
    }

    /* Metode 2: System Call */
    log_fd = open(name_sys, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (log_fd < 0) {
        fprintf(stderr, "open %s: %s\n", name_sys, strerror(errno));
        /* Gagal sebagian dianggap gagal total, biar kedua log selalu
         * berpasangan. main.c akan lanjut tanpa log. */
        fclose(log_fp);
        log_fp = NULL;
        return -1;
    }

    return 0;
}

/*
 * write() boleh menulis lebih sedikit byte daripada yang diminta
 * (partial write), jadi diulang sampai semua byte tertulis.
 */
static void write_all(int fd, const char *buf, size_t len)
{
    while (len > 0) {
        ssize_t written = write(fd, buf, len);
        if (written < 0) {
            if (errno == EINTR)
                continue;   /* terinterupsi sinyal, coba lagi */
            fprintf(stderr, "write: %s\n", strerror(errno));
            return;
        }
        buf += written;
        len -= (size_t)written;
    }
}

void log_printf(const char *fmt, ...)
{
    char buf[1024];
    va_list ap;
    int len;

    /* Format sekali ke buffer, supaya ketiga tujuan isinya identik. */
    va_start(ap, fmt);
    len = vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);

    if (len < 0)
        return;

    /* Kalau lebih panjang dari buffer, vsnprintf sudah memotongnya;
     * sesuaikan len dengan isi buffer yang sebenarnya. */
    if ((size_t)len >= sizeof buf)
        len = (int)sizeof buf - 1;

    /* 1) Terminal */
    fputs(buf, stdout);

    /* 2) Berkas _std: fprintf (ter-buffer di user space) */
    if (log_fp != NULL)
        fprintf(log_fp, "%s", buf);

    /* 3) Berkas _sys: write (langsung ke kernel) */
    if (log_fd >= 0)
        write_all(log_fd, buf, (size_t)len);
}

void log_close(void)
{
    if (log_fp != NULL) {
        fclose(log_fp);     /* flush buffer stdio lalu tutup */
        log_fp = NULL;
    }
    if (log_fd >= 0) {
        close(log_fd);
        log_fd = -1;
    }
}