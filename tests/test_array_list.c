#include <stdio.h>
#include <stdlib.h>

#include "general_list.h"  // note incldue the .h, not the .c

int main(){
	
	int N1 = 4, N2 = 0;

	int arr[100] = {10, 20, 30, 40};
	int *copy_arr = NULL;

	general_list* list = NULL;
	
	printf("runing test_array_list\n");
	
	list = make_list_from_array(arr, N1);
	print_list(list, "\nList from array {10, 20, 30, 40}\n");
		
	copy_arr = array_from_list(list, &N2);
	print_array(copy_arr, N2, N2, "\nThe array copied from list is:\n");

	printf("\nTest that copy_arr and list do not access the same memory.\n");
	
	if (copy_arr != NULL) {
		copy_arr[0] = -7;
	}
	print_array(copy_arr, N2, N2, "\n after copy_arr[0] = -7, **copy_arr** is:\n");

	print_list(list, "\nThe **list** is: \n");
	
	printf("\nTest resize to shrink the list.\n");
	
	resize_list(list, 1);
	print_list(list, "\nThe list after resize(list,1) is:\n");
	
	destroy_list(list);
	free(copy_arr);
	
	return 0;
}