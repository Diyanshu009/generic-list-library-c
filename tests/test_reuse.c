#include <stdio.h>
#include <stdlib.h>

#include "general_list.h"  

int main(){
	
	int N1 = 4;

	int arr[100] = {10, 20, 30, 40};

	general_list* list = NULL;
	
	printf("runing test_reuse\n");
	
	list = make_list_from_array(arr, N1);
	print_list(list, "\nList from array {10, 20, 30, 40}\n");
	
	resize_list(list, 2);
	print_list(list, "\nList after resize_list(list, 2):\n");
	
	destroy_list_clean(&list);
	print_list(list, "\nAttempt to print list after it was destroyed:\n");
	
	list = make_list_empty(10);
	print_list(list, "\nEmpty list, but valid.\n");
	
	add_last(list, 201);
	print_list(list, "\nList after adding 201\n");
	
	resize_list(list, 3);
	print_list(list, "\nList after resize_list(list, 3):\n");
	
	destroy_list_clean(&list);
	
	return 0;
}