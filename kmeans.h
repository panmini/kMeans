#include <stdio.h>
#include "csv_read.h"

#ifndef KMEANS_H
#define KMEANS_H
extern int input_size;

typedef struct centroid {
	double *input;
} centroid;

void kmeans(data_t[], int, int);
struct centroid* create_initial_centroids(centroid[], int, data_t[]);
int get_nearest_centroid(centroid[], int,data_t);
double get_distance(centroid, data_t);
void move_centroids_to_mean(centroid[], int, data_t[]);
void evaluate_clustering(data_t[], int);

#endif
