#ifndef GENERAL_LIST_H
#define	GENERAL_LIST_H

#include <stdbool.h>
#include <stddef.h>

/** 
	This is a general list interface.
	Based on the implementation, the list itself can be an array or a linked list.
*/

typedef struct general_list_tag general_list;


void print_array(int arr[], int N, int cap, char* message);

/// Returns NULL if fails
general_list* make_list_empty(int capacity);


/// Returns NULL if fails
general_list* make_list_from_array(int* arr, int sz);

void destroy_list(general_list* list);

/** 
	Calls destroy_list to free all the heap memory, and also 
	sets the pointer variable (from caller function) to NULL.
*/
void destroy_list_clean(general_list** list);

int get_size(general_list* list);
bool get_item(general_list* list, int pos, int* return_value);

bool is_invalid(general_list* list);

int* array_from_list(general_list* list, int* return_array_size);

void print_list(general_list* list, char* message);

bool resize_list(general_list* list, int new_capacity);

/**
    Inserts new_item at the end. 
    If out of space, it will resize. Can fail if resizing failed. 
	Returns true / false based on success.
*/
bool add_last(general_list* list, int new_item);

/**
    Inserts new_item at index pos. 
    If out of space, it will resize. Can fail if resizing failed.
	Returns true / false based on success. 
*/
bool add_at(general_list* list, int new_item, int pos);


bool remove_last(general_list* list, int* return_value);
bool remove_from(general_list* list, int pos, int* return_value);

/// sorts the subarray from indexes from to to inclusive
void insertion_sort_partial(general_list* list,  int start, int end);

/// sorts the entire array
void insertion_sort_all(general_list* list);


int binary_search_partial(general_list* list, int value, int start, int end);
int binary_search_all(general_list* list, int value);

#endif	/* GENERAL_LIST_H */
