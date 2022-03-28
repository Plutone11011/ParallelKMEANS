
CC=gcc
OPENMP=-fopenmp
MATH=-lm


all: utils.c kmeans.c main.c
	$(CC) $(OPENMP) $^ -o kmeans ${MATH} 

