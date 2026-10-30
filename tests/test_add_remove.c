#include <stdio.h>
#include <stdlib.h>

#include "general_list.h"  

int main(){
	int val = 0, res = 0;
	general_list* list = NULL; 
	
	printf("runing test_add_remove\n");
	
	list = make_list_empty(3);
	/*
	if (list == NULL){
		printf("List could not be created. Terminate program.\n");
		return 0;
	}
	*/
	
	printf("\nAdd 4\n");
	add_last(list, 4);
	print_list(list, "");
	
	printf("\nAdd 7 at index 0\n");
	add_at(list, 7, 0);
	print_list(list, "");
	
	printf("\nAdd 12 at index 1\n");
	add_at(list, 12, 1);
	print_list(list, "");
	
	printf("\nAdd 2 at index 3\n");
	add_at(list, 2, 3);
	print_list(list, "");
	
	printf("\nAdd 30 at index 10\n");
	add_at(list, 30, 10);
	print_list(list, "");

	insertion_sort_partial(list, 1, 2);
	print_list(list, "\nAfter insertion_sort_partial(list, 1, 2):\n");

	insertion_sort_all(list);
	print_list(list, "\nAfter insertion_sort_all(list):\n");


	res = binary_search_partial(list, 2, 1, 2);
	printf("\nbinary_search_partial(list, 2, 1, 2) returned %d\n", res);
	
	res = binary_search_all(list, 2);
	printf("\nbinary_search_all(list, 2) returned %d\n", res);

	resize_list(list, 3);
	print_list(list, "\nAfter resize_list(list, 3):\n");
	
	remove_from(list, 1, &val );
	printf("\nRemoved %d from index 1\n", val);
	print_list(list, "");
		
	remove_from(list, -2, &val );
	printf("\nAttempted to remove from index -2. Val is %d\n", val);
	print_list(list, "");

	remove_from(list, 0, &val );
	printf("\nRemoved %d from index 0\n", val);
	print_list(list, "");

	remove_last(list, &val );
	printf("\nRemoved %d with remove_last\n", val);
	print_list(list, "");
	

	printf("Before call to remove from empty list val is %d.\n", val);
	remove_last(list, &val );	
	printf("After call to remove from empty list val is %d.\n", val);
	print_list(list, "The list is:\n");
	
	destroy_list_clean(&list);
	
	if (list != NULL){
		printf("\nFail: destroy_list_clean() did not set struct pointer to NULL.");
	}
	
	
	return 0;
}