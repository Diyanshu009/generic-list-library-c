/*
   Student name: Diyanshu Naag Goli
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "general_list.h"



struct general_list_tag {
    int* items;
    int size;
    int capacity;
};



void print_array(int arr[], int N, int cap, char* message){
    int i;
    printf("%s", message);
    if (arr == NULL) {
        printf("array is NULL\n");
        return;
    }
    printf("Array:  size: %d, capacity : %d", N, cap);
    printf("\nindexes:      ");
    for(i=0; i<N; i++){
        printf("%6d, ", i);
    }
    printf("\nvalues:       ");
    for(i=0; i<N; i++){
        printf("%6d, ", arr[i]);
    }
    printf("\n");
}



static int max_int(int a, int b){ return (a > b) ? a : b; }

bool is_invalid(general_list* list){
    if (list == NULL) return true;
    if (list->capacity < 0) return true;
    if (list->size < 0) return true;
    if (list->size > list->capacity) return true;
    if (list->capacity > 0 && list->items == NULL) return true;
    return false;
}

general_list* make_list_empty(int capacity){
    if (capacity < 0) return NULL;

    general_list* list = (general_list*)malloc(sizeof(general_list));
    if (list == NULL) return NULL;

    list->size = 0;
    list->capacity = capacity;

    if (capacity == 0) {
        list->items = NULL;
        return list;
    }

    list->items = (int*)malloc(sizeof(int) * (size_t)capacity);
    if (list->items == NULL) {
        free(list);
        return NULL;
    }

    return list;
}

general_list* make_list_from_array(int* arr, int sz){
    if (sz < 0) return NULL;
    if (sz > 0 && arr == NULL) return NULL;

    general_list* list = make_list_empty(sz);
    if (list == NULL) return NULL;

    for (int i = 0; i < sz; i++) {
        list->items[i] = arr[i];
    }
    list->size = sz;

    return list;
}

void destroy_list(general_list* list){
    if (list == NULL) return;

    if (list->items != NULL) {
        free(list->items);
        list->items = NULL;
    }
    free(list);
}

void destroy_list_clean(general_list** list){
    if (list == NULL) return;
    destroy_list(*list);
    *list = NULL;
}

int get_size(general_list* list){
    if (is_invalid(list)) return 0;
    return list->size;
}

bool get_item(general_list* list, int pos, int* return_value){
    if (is_invalid(list)) return false;
    if (return_value == NULL) return false;
    if (pos < 0 || pos >= list->size) return false;

    *return_value = list->items[pos];
    return true;
}

int* array_from_list(general_list* list, int* return_array_size){
    if (return_array_size != NULL) *return_array_size = 0;
    if (is_invalid(list)) return NULL;

    int n = list->size;
    if (return_array_size != NULL) *return_array_size = n;

    if (n == 0) return NULL; // matches “array is NULL” style in tests

    int* arr = (int*)malloc(sizeof(int) * (size_t)n);
    if (arr == NULL) {
        if (return_array_size != NULL) *return_array_size = 0;
        return NULL;
    }

    for (int i = 0; i < n; i++) arr[i] = list->items[i];
    return arr;
}

void print_list(general_list* list, char* message){
    if (message != NULL) printf("%s", message);

    if (list == NULL) {
        printf("list is NULL\n");
        return;
    }
    if (is_invalid(list)) {
        printf("list is INVALID\n");
        return;
    }

    if (list->capacity == 0) {
        printf("List: size: %d, capacity: %d\n", list->size, list->capacity);
        printf("(no backing array)\n");
        return;
    }

    print_array(list->items, list->size, list->capacity, "");
}

bool resize_list(general_list* list, int new_capacity){
    if (list == NULL) return false;
    if (is_invalid(list)) return false;
    if (new_capacity < 0) return false;

    // If shrinking, truncate size first
    if (new_capacity < list->size) {
        list->size = new_capacity;
    }

    if (new_capacity == 0) {
        free(list->items);
        list->items = NULL;
        list->capacity = 0;
        return true;
    }

    // realloc backing array
    int* new_items = (int*)realloc(list->items, sizeof(int) * (size_t)new_capacity);
    if (new_items == NULL) {
        return false; // keep old list unchanged
    }

    list->items = new_items;
    list->capacity = new_capacity;
    return true;
}

bool add_last(general_list* list, int new_item){
    if (is_invalid(list)) return false;

    // Ensure capacity
    if (list->size >= list->capacity) {
        int new_cap = (list->capacity == 0) ? 1 : (list->capacity * 2);
        if (!resize_list(list, new_cap)) return false;
    }

    list->items[list->size] = new_item;
    list->size++;
    return true;
}

bool add_at(general_list* list, int new_item, int pos){
    if (is_invalid(list)) return false;
    if (pos < 0 || pos > list->size) return false; // allow insert at end

    if (list->size >= list->capacity) {
        int new_cap = (list->capacity == 0) ? 1 : (list->capacity * 2);
        if (!resize_list(list, new_cap)) return false;
    }

    // shift right
    for (int i = list->size; i > pos; i--) {
        list->items[i] = list->items[i - 1];
    }

    list->items[pos] = new_item;
    list->size++;
    return true;
}

bool remove_last(general_list* list, int* return_value){
    if (is_invalid(list)) return false;
    if (list->size == 0) return false;

    int removed = list->items[list->size - 1];
    list->size--;

    if (return_value != NULL) *return_value = removed;
    return true;
}

bool remove_from(general_list* list, int pos, int* return_value){
    if (is_invalid(list)) return false;
    if (pos < 0 || pos >= list->size) return false;

    int removed = list->items[pos];

    // shift left
    for (int i = pos; i < list->size - 1; i++) {
        list->items[i] = list->items[i + 1];
    }
    list->size--;

    if (return_value != NULL) *return_value = removed;
    return true;
}

/// sorts the entire array
void insertion_sort_all(general_list* list){
    if (is_invalid(list)) return;
    if (list->size <= 1) return;
    insertion_sort_partial(list, 0, list->size - 1);
}

/// sorts the subarray from indexes start to end inclusive
void insertion_sort_partial(general_list* list, int start, int end){
    if (is_invalid(list)) return;
    if (list->size <= 1) return;

    start = max_int(start, 0);
    end = (end >= list->size) ? (list->size - 1) : end;
    if (start >= end) return;

    for (int i = start + 1; i <= end; i++) {
        int key = list->items[i];
        int j = i - 1;
        while (j >= start && list->items[j] > key) {
            list->items[j + 1] = list->items[j];
            j--;
        }
        list->items[j + 1] = key;
    }
}

int binary_search_all(general_list* list, int value){
    if (is_invalid(list)) return -1;
    if (list->size == 0) return -1;
    return binary_search_partial(list, value, 0, list->size - 1);
}

int binary_search_partial(general_list* list, int value, int start, int end){
    if (is_invalid(list)) return -1;
    if (list->size == 0) return -1;

    start = max_int(start, 0);
    end = (end >= list->size) ? (list->size - 1) : end;
    if (start > end) return -1;

    int lo = start, hi = end;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (list->items[mid] == value) return mid;
        if (list->items[mid] < value) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
