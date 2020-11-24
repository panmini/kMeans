#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "kmeans.h"
#include "csv_read.h"
void kmeans(data_t instances[], int num_clusters, int loops) {

  	//centroid centroids[num_clusters];
  	centroid *centroids;
  	centroid *previous_centroids;
  	//srand(time(NULL));
  	centroids = create_initial_centroids(centroids, num_clusters, instances);
  	previous_centroids = centroids;

	int flag = -1;
  	while(1){
    		for(int i = 0; i < DATASET_SIZE; i++) {
      			instances[i].center = get_nearest_centroid(centroids, num_clusters, instances[i]);
    		}
    		move_centroids_to_mean(centroids, num_clusters, instances);

  		for(int n = 0; n < num_clusters; n++) {
  			for(int s = 0; s < input_size; s++) {
				if(centroids[n].input[s] - previous_centroids[n].input[s] > 0.000001 && flag != -1) {
					flag = 1;
				}
			}
		}
		if(flag == 0) {
			return;
		}else {
			flag = 0;
			previous_centroids = centroids;
		}
  	}
}
centroid* create_initial_centroids(centroid centroids[], int num_clusters, data_t instances[]) {
  	centroids = malloc(num_clusters * sizeof (double));
  	for(int i = 0; i < num_clusters; i++) {
  			centroids[i].input = malloc(input_size * sizeof (double));
	  	for(int j = 0; j < input_size; j++) {
    			centroids[i].input[j] =  instances[(rand() % DATASET_SIZE)].input[j];
//			printf("%lf\n",centroids[i].input[j]);
	  	}
	}
	return centroids;
}
int get_nearest_centroid(centroid centroids[], int num_clusters, data_t instance) {
  	double min_distance;
  	int nearest_centroid;
//	Initialize values by assuming centroid 0 is closest.
  	min_distance = get_distance(centroids[0], instance);
  	nearest_centroid = 0;
  	for(int i = 1; i < num_clusters; i++) {
 		double distance = get_distance(centroids[i], instance);
		if(distance < min_distance) {
      		min_distance = distance;
      		nearest_centroid = i;
    		}
  	}
  return nearest_centroid;
}

double get_distance(centroid centroid, data_t instance) {
	int counter = 0;
	double t_centroid[input_size];
	while(counter < input_size){
		t_centroid[counter] = instance.input[counter] - centroid.input[counter];
		counter ++;
	}
	double centroid_sum = 0;
	for(counter = 0; counter < input_size; counter++)
		centroid_sum += t_centroid[counter] * t_centroid[counter];

	return (sqrt(centroid_sum));
}
void move_centroids_to_mean(centroid centroids[], int num_clusters, data_t instances[]) {

	centroid mean;
    	mean.input = malloc(input_size *sizeof(double));
 	for(int i = 0; i < num_clusters; i++) {
    		for(int x = 0; x < input_size; x++){
    			mean.input[x] = 0;
    		}
    	double numInstancesInCluster = 0;
  	for(int j =0; j <DATASET_SIZE; j++){
      		if(instances[j].center == i) {
			for(int k = 0;k < input_size; k++){
				mean.input[k] += instances[j].input[k];
			}
        		numInstancesInCluster += 1;
      		}
    	}
    		if(numInstancesInCluster == 0)
	    		break;
		for(int k = 0;k < input_size; k++){
    			centroids[i].input[k] = mean.input[k] / numInstancesInCluster;
		}
  	}
}
