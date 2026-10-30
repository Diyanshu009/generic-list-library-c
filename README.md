# Generic List Library in C (Array + Linked List)

Data structures project for CSE 3318 (Algorithms & Data Structures) at UT Arlington, Spring 2026.

The same list interface (`general_list.h`) is implemented twice:

- **`general_list_array.c`**: backed by a dynamic array that grows as needed
- **`general_list_linked_list.c`**: backed by a singly linked list

Both versions support creating and destroying lists, adding and removing items at an index, moving items, sorting, and safe handling of out-of-bounds indexes and `NULL` lists. Both passed the full provided test suite.

## Build & test

```bash
gcc -Wall -o test_add_remove general_list_array.c tests/test_add_remove.c && ./test_add_remove
gcc -Wall -o test_add_remove_ll general_list_linked_list.c tests/test_add_remove.c && ./test_add_remove_ll
```

Test files in `tests/` were provided by the course.

> Built as UT Arlington coursework. If you're taking the course, please don't copy it for your own submission.
# Generic List Library in C (Array + Linked List)

Data structures project for CSE 3318 (Algorithms & Data Structures) at UT Arlington, Spring 2026.

The same list interface (`general_list.h`) is implemented twice:

- **`general_list_array.c`**: backed by a dynamic array that grows as needed
- **`general_list_linked_list.c`**: backed by a singly linked list

Both versions support creating and destroying lists, adding and removing items at an index, moving items, sorting, and safe handling of out-of-bounds indexes and `NULL` lists. Both passed the full provided test suite.

## Build & test

```bash
gcc -Wall -o test_add_remove general_list_array.c tests/test_add_remove.c && ./test_add_remove
gcc -Wall -o test_add_remove_ll general_list_linked_list.c tests/test_add_remove.c && ./test_add_remove_ll
```

Test files in `tests/` were provided by the course.

> Coursework repository, kept private. Please don't redistribute.
