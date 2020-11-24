/*Mertcan OZKAN csvRead.c*/
#include "csv_read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void set_dataset_size(FILE *file) {
	DATASET_SIZE = 0;
  	char buf[BUFFER_SIZE];
	while (fgets(buf, BUFFER_SIZE, file) ) {
		DATASET_SIZE++;
  }
	//printf("%d\n\n\n\n",DATASET_SIZE);
	fseek(file, 0, SEEK_SET);
}
void set_possible_output_number(data_t* arr)
{
	int res = 1;
//	Pick all elements one by one
    	for (int i = 1; i < DATASET_SIZE; i++) {
        	int j = 0;
        for (j = 0; j < i; j++)
            	if (arr[i].output == arr[j].output)
                	break;

//	If not printed earlier, then print it
        if (i == j)
            	res++;
    	}
	possible_output_number = res;
}
void set_input_size(FILE *file) {
  	char buf[BUFFER_SIZE];
	fgets(buf, BUFFER_SIZE, file);

	int field_count = 0;
        char *field = strtok(buf, ",");

	while (field) {
		field_count++;
		field = strtok(NULL, ",");

	}
	input_size = field_count - 1;
	fseek(file, 0, SEEK_SET);
//  	printf("input size: %d\n",input_size);
}


data_t *read_csv(data_t *csv_data, int read_mode ) {
  	int counter = 0;
  	char buf[BUFFER_SIZE + 1];
  	FILE *file_csv;
  	if(read_mode){
		file_csv = fopen("result.csv", "r");
//		file_csv = fopen("random.csv", "r");
  	} else{
  		file_csv = fopen("iriskmeans.csv", "r");
//		file_csv = fopen("random.csv", "r");
  	}

  	set_input_size(file_csv);
  	set_dataset_size(file_csv);
  	csv_data = malloc(((DATASET_SIZE ) * ((input_size + 2)*sizeof(double))));
//	csv_data = malloc((DATASET_SIZE ) * sizeof(double));
  	if (!file_csv) {
   	 	printf("File could not be found\n");
    		exit(EXIT_FAILURE);

	}
  	while (fgets(buf, BUFFER_SIZE, file_csv) ) {
        	char *field = strtok(buf, ",");
		int column = 0;

  	csv_data[counter].input = malloc(( ((input_size)*sizeof(double))));
        while (field) {
		if(column < input_size ) {
			csv_data[counter].input[column] = atof(field);
			column++;
		}else {
			csv_data[counter].output = atof(field);
			csv_data[counter].center = 0;

		}
        	field = strtok(NULL, ",");
	}
	counter++;
  }

  set_possible_output_number(csv_data);
  fclose(file_csv);

  return csv_data;
}

