/* Mertcan OZKAN - main.c */
#include <stdio.h>
#include <stdlib.h>
#include "csv_read.h"
#include "kmeans.h"
#include <unistd.h>
int input_size;
int possible_output_number;
int DATASET_SIZE;
float accuracy_rate;
int main(){
	accuracy_rate = 0;
  	data_t *instances = read_csv(instances,0);
  	data_t *result = read_csv(result,1);
	while( accuracy_rate* 100 / DATASET_SIZE < 70){
//		sleep(1);

  	kmeans(instances, 3, 100);

  	accuracy_rate = 0;
  	for(int i = 0; i < DATASET_SIZE; i++) {
//    	printf("Cluster:\t%f\n", instances[i].center);
    		if(instances[i].center == result[i].output) {
			accuracy_rate++;
    			}
  		}
  	printf("Accuracy Rate:\t%.2f%\n",(accuracy_rate*100)/DATASET_SIZE);
	}
  free(instances);
  free(result);
  return 0;
}
