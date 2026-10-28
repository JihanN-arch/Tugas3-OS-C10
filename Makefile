# Makefile - Tugas 3 Memory, Kelompok C10 (Anggota 1)
#
# Target:
#   make          -> sama dengan make all (bikin versi statis dan dinamis)
#   make static   -> tugas3_static  (gcc -static)
#   make dynamic  -> tugas3_dynamic (gcc biasa)
#   make clean    -> hapus semua hasil build
#
# Semua berkas *.c di folder ini otomatis ikut dikompilasi.

CC      = gcc
CFLAGS  = -Wall -Wextra -std=gnu11 -O2
SRCS    = $(wildcard *.c)
OBJS    = $(SRCS:.c=.o)
DEPS    = $(OBJS:.o=.d)

BIN_STATIC  = tugas3_static
BIN_DYNAMIC = tugas3_dynamic

.PHONY: all static dynamic clean

all: static dynamic

static: $(BIN_STATIC)

dynamic: $(BIN_DYNAMIC)

$(BIN_STATIC): $(OBJS)
	$(CC) $(CFLAGS) -static -o $@ $(OBJS)

$(BIN_DYNAMIC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Objek dipakai bersama oleh kedua versi; beda hanya di tahap link.
%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(BIN_STATIC) $(BIN_DYNAMIC)

-include $(DEPS)
