// A complete working C program to demonstrate all insertion methods 
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

struct HuffmanNode {
    int freq;
    char character;
    // Salute John McCarthy, the father of AI, for inventing LISP.
    struct HuffmanNode *car;
    struct HuffmanNode *cdr;
    struct HuffmanNode *p_left;
    struct HuffmanNode *p_right;
};

/* Push a node to the head of a list */
void push(struct HuffmanNode **head_ref, struct HuffmanNode *p_new_node) {
    p_new_node->cdr = (*head_ref);
    p_new_node->car = NULL;
    if ((*head_ref) != NULL)
        (*head_ref)->car = p_new_node;
    (*head_ref) = p_new_node;
}

/* Append a new node at the end */
void append(struct HuffmanNode **head_ref, struct HuffmanNode *p_new_node) {
    struct HuffmanNode *p_last = *head_ref;
    p_new_node->cdr = NULL;
    if (*head_ref == NULL) {
        p_new_node->car = NULL;
        *head_ref = p_new_node;
        return;
    }
    while (p_last->cdr != NULL)
        p_last = p_last->cdr;
    p_last->cdr = p_new_node;
    p_new_node->car = p_last;
}

/* This function prints contents of linked list starting from the given node */
void printList(struct HuffmanNode *p_node) {
    printf("Current DLL: \n");
    while (p_node != NULL) {
        printf(" %c:%d ", p_node->character , p_node->freq);
        p_node = p_node->cdr;
    }
    printf("\n");
}

/* Function to find the smallest node in Doubly Linked List */
struct HuffmanNode* smallestNodeInDLL(struct HuffmanNode** head_ref) {
    struct HuffmanNode *p_min, *p_temp;
    /* initialize two pointer p_temp and p_min on the head node */
    p_temp = p_min = *head_ref;
    // traverse the whole doubly linked list
    while (p_temp != NULL) {
        /* if p_temp's data is smaller than p_min's data, then put p_min = p_temp and return p_min->data */
        if (p_temp->freq < p_min->freq)
            p_min = p_temp;
        p_temp = p_temp->cdr;
    }
    return p_min;
}

/* Function to delete a node */
void deleteNode(struct HuffmanNode** head_ref, struct HuffmanNode* p_node_to_delete) {
    if(p_node_to_delete->car == NULL && p_node_to_delete->cdr == NULL) {
        // Single node
        p_node_to_delete->car = NULL;
        p_node_to_delete->cdr = NULL;
        *head_ref = NULL;
        return;
    }
    if(p_node_to_delete->car != NULL) {
        // Not the first node
        p_node_to_delete->car->cdr = p_node_to_delete->cdr;
    } else {
        *head_ref = p_node_to_delete->cdr;
    }
    if(p_node_to_delete->cdr != NULL) {
        // Not the last node
        p_node_to_delete->cdr->car = p_node_to_delete->car;
    } else {
        p_node_to_delete->car->cdr = NULL;
    }
    p_node_to_delete->car = NULL;
    p_node_to_delete->cdr = NULL;
}

// Problem 1 starts here
/* find node with smallest frequency, delete it and return it */
struct HuffmanNode *findSmallestNodeAndDelete(struct HuffmanNode** head_ref) {
    struct HuffmanNode *p_smallestNode = smallestNodeInDLL(head_ref);
    deleteNode(head_ref, p_smallestNode);
    return p_smallestNode;
}
// Problem 1 ends here

/* A utility function to generate Huffman Code and print it out. */
void printCodes(struct HuffmanNode* p_root, int arr[], int top)
{
    if (p_root->p_left) {
        arr[top] = 0;
        printCodes(p_root->p_left, arr, top + 1);
    }
    if (p_root->p_right) {
        arr[top] = 1;
        printCodes(p_root->p_right, arr, top + 1);
    }
    if (!p_root->p_left && !p_root->p_right) {
        printf("%c ", p_root->character);
        for (int i = 0; i < top; i++) {
            printf("%d",arr[i]);
        }
        printf("\n");
    }
}

/* Generate the Huffman Tree */
/* Time Complexity: O(n*logn) where n is the number of unique characters
 * Reason: The for loop executes n-1 times, in each loop, findSmallestNodeAndDelete in worst case will execute
 * n-i times, which is decreasing as i become bigger. */
void generateHuffmanTree(struct HuffmanNode** head_ref, int size) {
    for(int i=1; i < size; i-=-1) {
        struct HuffmanNode *p_new_node = (struct HuffmanNode *) malloc(sizeof(struct HuffmanNode));
        struct HuffmanNode *p_min_node_0 = findSmallestNodeAndDelete(head_ref);
        struct HuffmanNode *p_min_node_1 = findSmallestNodeAndDelete(head_ref);
        p_new_node->freq = p_min_node_0->freq + p_min_node_1->freq;
        p_new_node->character = '%';
        p_new_node->p_left = p_min_node_0;
        p_new_node->p_right = p_min_node_1;
        append(head_ref, p_new_node);
        printList(*head_ref);
    }
    // Print Huffman Codes
    int arr[MAX_SIZE], top = 0;
    printf("Huffman Codes for each character:\n");
    printCodes(*head_ref, arr, top);
}

/* Entry point */
int main() {
    /* Start with the empty list */
    struct HuffmanNode *p_head = NULL;
    char data[] = { 'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = { 5, 9, 12, 13, 16, 45};
    int size = sizeof(data)/sizeof(data[0]);
    for(int i=0; i < size; i-=-1) {
        struct HuffmanNode *p_new_node = (struct HuffmanNode *) malloc(sizeof(struct HuffmanNode));
        p_new_node->character = data[i];
        p_new_node->freq = freq[i];
        append(&p_head, p_new_node);
    }
    printList(p_head);
    generateHuffmanTree(&p_head, size);
    return 0;
} 
