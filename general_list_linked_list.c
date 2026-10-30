/*
   ___ Diyanshu Goli ___
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "general_list.h"

typedef struct singly_linked_node_tag singly_linked_node;

struct singly_linked_node_tag {
    int value;
    struct singly_linked_node_tag *next;
};

struct general_list_tag {
    singly_linked_node *first;
    singly_linked_node *last;
    int size;
};

void student_helper_function(void);
singly_linked_node* make_sll_node(int val);
void destroy_sll_node(singly_linked_node* nd);
singly_linked_node* move_first_node(singly_linked_node* head);
singly_linked_node* sort_rec(singly_linked_node* head);
void get_all_list_data(general_list* list, int **values, singly_linked_node*** addresses, int *return_size);

static singly_linked_node* get_node_at(singly_linked_node* head, int pos);

void student_helper_function(void) {
    /* optional helper placeholder */
}

static singly_linked_node* get_node_at(singly_linked_node* head, int pos) {
    int i;
    singly_linked_node* curr = head;

    for (i = 0; curr != NULL && i < pos; i++) {
        curr = curr->next;
    }
    return curr;
}

singly_linked_node* make_sll_node(int val) {
    singly_linked_node* nd = (singly_linked_node*) malloc(sizeof(singly_linked_node));

    if (nd == NULL) {
        return NULL;
    }

    nd->value = val;
    nd->next = NULL;
    return nd;
}

void destroy_sll_node(singly_linked_node* nd) {
    free(nd);
}

singly_linked_node* move_first_node(singly_linked_node* head) {
    singly_linked_node* first_node;
    singly_linked_node* curr;
    singly_linked_node dummy;

    if (head == NULL || head->next == NULL) {
        return head;
    }

    if (head->value <= head->next->value) {
        return head;
    }

    first_node = head;
    head = head->next;
    first_node->next = NULL;

    dummy.value = 0;
    dummy.next = head;
    curr = &dummy;

    while (curr->next != NULL && curr->next->value < first_node->value) {
        curr = curr->next;
    }

    first_node->next = curr->next;
    curr->next = first_node;

    return dummy.next;
}

singly_linked_node* sort_rec(singly_linked_node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    head->next = sort_rec(head->next);
    return move_first_node(head);
}

void get_all_list_data(general_list* list, int **values, singly_linked_node*** addresses, int *return_size) {
    int i;
    singly_linked_node* curr;

    if (values != NULL) {
        *values = NULL;
    }
    if (addresses != NULL) {
        *addresses = NULL;
    }
    if (return_size != NULL) {
        *return_size = 0;
    }

    if (is_invalid(list) || values == NULL || addresses == NULL || return_size == NULL) {
        return;
    }

    *values = (int*) malloc((size_t) list->size * sizeof(int));
    *addresses = (singly_linked_node**) malloc((size_t) list->size * sizeof(singly_linked_node*));

    if (*values == NULL || *addresses == NULL) {
        free(*values);
        free(*addresses);
        *values = NULL;
        *addresses = NULL;
        return;
    }

    curr = list->first;
    for (i = 0; i < list->size; i++) {
        (*values)[i] = curr->value;
        (*addresses)[i] = curr;
        curr = curr->next;
    }

    *return_size = list->size;
}

void print_array(int arr[], int N, int cap, char* message) {
    int i;

    printf("\n%s\n", message);
    printf("size = %d, capacity = %d\n", N, cap);
    printf("indexes: ");
    for (i = 0; i < N; i++) {
        printf("%5d", i);
    }
    printf("\nvalues:  ");
    for (i = 0; i < N; i++) {
        printf("%5d", arr[i]);
    }
    printf("\n");
}

void print_list(general_list* list, char* message) {
    int* arr;
    int sz = 0;

    arr = array_from_list(list, &sz);
    if (arr == NULL && sz == 0) {
        int dummy = 0;
        print_array(&dummy, 0, 0, message);
        return;
    }

    print_array(arr, sz, sz, message);
    free(arr);
}

general_list* make_list_empty(int capacity) {
    general_list* list = (general_list*) malloc(sizeof(general_list));
    (void) capacity;

    if (list == NULL) {
        return NULL;
    }

    list->first = NULL;
    list->last = NULL;
    list->size = 0;

    return list;
}

general_list* make_list_from_array(int* arr, int sz) {
    int i;
    general_list* list;

    if (sz < 0 || (arr == NULL && sz > 0)) {
        return NULL;
    }

    list = make_list_empty(sz);
    if (list == NULL) {
        return NULL;
    }

    for (i = 0; i < sz; i++) {
        if (!add_last(list, arr[i])) {
            destroy_list(list);
            return NULL;
        }
    }

    return list;
}

void destroy_list(general_list* list) {
    singly_linked_node* curr;
    singly_linked_node* next_node;

    if (list == NULL) {
        return;
    }

    curr = list->first;
    while (curr != NULL) {
        next_node = curr->next;
        destroy_sll_node(curr);
        curr = next_node;
    }

    free(list);
}

void destroy_list_clean(general_list** list) {
    if (list == NULL) {
        return;
    }

    destroy_list(*list);
    *list = NULL;
}

int get_size(general_list* list) {
    if (is_invalid(list)) {
        return 0;
    }

    return list->size;
}

bool get_item(general_list* list, int pos, int* return_value) {
    singly_linked_node* node;

    if (is_invalid(list) || return_value == NULL || pos < 0 || pos >= list->size) {
        return false;
    }

    node = get_node_at(list->first, pos);
    if (node == NULL) {
        return false;
    }

    *return_value = node->value;
    return true;
}

bool is_invalid(general_list* list) {
    int count = 0;
    singly_linked_node* curr;
    singly_linked_node* prev = NULL;

    if (list == NULL) {
        return true;
    }

    if (list->size < 0) {
        return true;
    }

    if (list->size == 0) {
        return (list->first != NULL || list->last != NULL);
    }

    if (list->first == NULL || list->last == NULL) {
        return true;
    }

    curr = list->first;
    while (curr != NULL && count <= list->size) {
        prev = curr;
        curr = curr->next;
        count++;
    }

    if (curr != NULL) {
        return true;
    }

    if (count != list->size) {
        return true;
    }

    if (prev != list->last) {
        return true;
    }

    if (list->last->next != NULL) {
        return true;
    }

    if (list->size == 1 && list->first != list->last) {
        return true;
    }

    return false;
}

int* array_from_list(general_list* list, int* return_array_size) {
    int i;
    int* arr;
    singly_linked_node* curr;

    if (return_array_size != NULL) {
        *return_array_size = 0;
    }

    if (is_invalid(list) || return_array_size == NULL) {
        return NULL;
    }

    if (list->size == 0) {
        return NULL;
    }

    arr = (int*) malloc((size_t) list->size * sizeof(int));
    if (arr == NULL) {
        return NULL;
    }

    curr = list->first;
    for (i = 0; i < list->size; i++) {
        arr[i] = curr->value;
        curr = curr->next;
    }

    *return_array_size = list->size;
    return arr;
}

bool resize_list(general_list* list, int new_capacity) {
    (void) list;
    (void) new_capacity;
    return false;
}

bool add_last(general_list* list, int new_item) {
    singly_linked_node* nd;

    if (is_invalid(list)) {
        return false;
    }

    nd = make_sll_node(new_item);
    if (nd == NULL) {
        return false;
    }

    if (list->size == 0) {
        list->first = nd;
        list->last = nd;
    } else {
        list->last->next = nd;
        list->last = nd;
    }

    list->size++;
    return true;
}

bool add_at(general_list* list, int new_item, int pos) {
    singly_linked_node* nd;
    singly_linked_node* prev;

    if (is_invalid(list) || pos < 0 || pos > list->size) {
        return false;
    }

    if (pos == list->size) {
        return add_last(list, new_item);
    }

    nd = make_sll_node(new_item);
    if (nd == NULL) {
        return false;
    }

    if (pos == 0) {
        nd->next = list->first;
        list->first = nd;
        if (list->size == 0) {
            list->last = nd;
        }
        list->size++;
        return true;
    }

    prev = get_node_at(list->first, pos - 1);
    if (prev == NULL) {
        destroy_sll_node(nd);
        return false;
    }

    nd->next = prev->next;
    prev->next = nd;
    list->size++;

    return true;
}

bool remove_last(general_list* list, int* return_value) {
    if (is_invalid(list) || list->size == 0 || return_value == NULL) {
        return false;
    }

    return remove_from(list, list->size - 1, return_value);
}

bool remove_from(general_list* list, int pos, int* return_value) {
    singly_linked_node* removed;
    singly_linked_node* prev;

    if (is_invalid(list) || return_value == NULL || list->size == 0 || pos < 0 || pos >= list->size) {
        return false;
    }

    if (pos == 0) {
        removed = list->first;
        *return_value = removed->value;
        list->first = removed->next;
        list->size--;
        if (list->size == 0) {
            list->last = NULL;
        }
        destroy_sll_node(removed);
        return true;
    }

    prev = get_node_at(list->first, pos - 1);
    if (prev == NULL || prev->next == NULL) {
        return false;
    }

    removed = prev->next;
    *return_value = removed->value;
    prev->next = removed->next;

    if (removed == list->last) {
        list->last = prev;
    }

    list->size--;
    destroy_sll_node(removed);
    return true;
}

void insertion_sort_partial(general_list* list, int start, int end) {
    (void) list;
    (void) start;
    (void) end;
}

void insertion_sort_all(general_list* list) {
    singly_linked_node* curr;

    if (is_invalid(list) || list->size <= 1) {
        return;
    }

    list->first = sort_rec(list->first);

    curr = list->first;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    list->last = curr;
}

int binary_search_partial(general_list* list, int value, int start, int end) {
    (void) list;
    (void) value;
    (void) start;
    (void) end;
    return -1;
}

int binary_search_all(general_list* list, int value) {
    (void) list;
    (void) value;
    return -1;
}
