#ifndef FUNCTION_H  
#define FUNCTION_H 

struct list_node_s;
int Insert(int value, struct list_node_s** head_pp);
int Member(int value, struct list_node_s* head_p);
int Delete(int value, struct list_node_s** head_pp);
int * getRandom();
void shuffle(char array[][7], size_t size);
float get_mean(float array[], int size);
float get_std(float array[], int size, float mean);

#endif
