
CC=gcc-11
OPENMP=-fopenmp
GFX=-lX11 -lm


all: gfx.c utils.c kmeans.c main.c
	$(CC) $(OPENMP) $^ -o kmeans $(GFX) 

