#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <time.h>
#include <string.h>
#include <math.h>

#define MAX 65535
#define MIN 0
#define n 1000

int * getRandom() {

    static int  random_array[n];

    // Use current time as seed for random generator
    srand(time(0));
 
    for(int i = 0; i<n; i++)
        random_array[i] = rand() % (MAX + 1 - MIN) + MIN;

    return random_array;
} /* get a random array */

/*shuffle functiom*/
void shuffle(char array[][7], size_t size)
{
  if (size > 1) {
    size_t i;
    for (i = 0; i < size - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
      char t[7];

      strcpy(t, array[j]);
      strcpy(array[j], array[i]);
      strcpy(array[i], t);
    }
  }
}

float get_mean(float array[], int size){
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
      sum += array[i];
    }
    return sum/size;
}

float get_std(float array[], int size, float mean){
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
      sum += (array[i] - mean) * (array[i] - mean);
    }
    return sqrt(sum/size);
}