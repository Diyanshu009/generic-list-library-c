#include <stdio.h>
#include <stdlib.h>

#include "general_list.h"  // note incldue the .h, not the .c

int main(){	
	
	printf("runing test_NULL\n");		
		
	bool is_bad = is_invalid(NULL);
	printf("is_invalid(NULL) returned: %d\n", is_bad);
	
	print_list(NULL, "\nThe list is: \n");
	
	printf("\nTest resize on NULL.\n");
	
	resize_list(NULL, 1);
	print_list(NULL, "\nThe list after resize(NULL,1) is:\n");
	
	destroy_list(NULL);	
	
	return 0;
}