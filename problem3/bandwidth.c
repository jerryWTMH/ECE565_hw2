#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

const int stride = 16;
int num_elements;
int num_traversals;
uint64_t *array;
uint64_t *array2;
uint64_t *array3;
uint64_t *array4;
uint64_t *array5;
uint64_t *array6;
struct timespec start_time, end_time;

double calc_time(struct timespec start, struct timespec end) {
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;
  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}

void init_array(){
  for(int i=0; i < num_elements; i++){
    array[i] = i + 1;
    array2[i] = i + 1000;
    array3[i] = i + 10000;
  }
}

void write_traffic(){
  printf("===========================================================================\n");
  int i;
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  for(int j = 0; j < num_traversals; j++){
    for (int i = 0; i < (num_elements); i++){
      array[i] = 1000;
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  double result = calc_time(start_time, end_time);
  printf("Write Traffice Only Time Cost: %f (ns)\n", result);
  double time = 1.0 * num_elements * num_traversals * sizeof(uint64_t) / result;
  printf("Write Traffice Only Bandwidth: %f (GB/s)\n", time);
  printf("===========================================================================\n");
}

void read_write_one_traffic(){
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  for(int j = 0; j < (num_traversals); j++){
    for (int i = 0; i < (num_elements); i++){
      array[i] = array2[i];
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  double result = calc_time(start_time, end_time);
  printf("One Read One Write Time Cost: %f (ns)\n", result);
  double time = 2.0 * num_elements * num_traversals * sizeof(uint64_t)/ result;
  printf("One Read One Write Bandwidth: %f (GB/s)\n", time);
  printf("===========================================================================\n");
}

void read_write_two_traffic(){
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  for(int j = 0; j < num_traversals; j++){
    for (int i = 0; i < (num_elements); i++){
      array[i] = array2[i] + array3[i];
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  double result = calc_time(start_time, end_time);
  printf("Two Read One Write Time Cost: %f (ns)\n", result);
  double time = 3.0 * num_elements * num_traversals * sizeof(uint64_t) / result;
  printf("Two Read One Write Bandwidth: %f (GB/s)\n", time);
  printf("===========================================================================\n");
}



int main(int argc, char *argv[]) {
  int i;
  uint64_t index = 0;
  struct timespec start_time, end_time;
  
  num_elements = atoi(argv[1]); // 400000000
  num_traversals = atoi(argv[2]);
  array = (uint64_t*)malloc(num_elements * sizeof(uint64_t) * stride);
  array2 = (uint64_t*)malloc(num_elements * sizeof(uint64_t) * stride);
  array3 = (uint64_t*)malloc(num_elements * sizeof(uint64_t) * stride);
  init_array();
  write_traffic();
  read_write_one_traffic();
  read_write_two_traffic();
  free(array);
  free(array2);
  return 0;
}
