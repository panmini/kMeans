/* Mertcan OZKAN- csv_read.h */

#ifndef CSV_READ_h
#define CSV_READ_h
#include <stdio.h>
#define BUFFER_SIZE 1024

extern int input_size;
extern int possible_output_number;
extern int DATASET_SIZE;
typedef struct{

	double *input;
	double output;
	double center;

}data_t;

data_t *read_csv(data_t *csv_data, int read_mode);
void set_input_size(FILE *file);
void set_possible_output_number(data_t* arr);
void set_data_size(FILE *file);
#endif
