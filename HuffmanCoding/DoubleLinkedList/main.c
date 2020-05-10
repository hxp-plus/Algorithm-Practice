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
    struct HuffmanNode *left;
    struct HuffmanNode *right;
};

/* Given a reference (pointer to pointer) to the head of a list 
and an int, inserts a new node on the front of the list. */
void push(struct HuffmanNode **head_ref, struct HuffmanNode *new_node) {
    new_node->cdr = (*head_ref);
    new_node->car = NULL;
    if ((*head_ref) != NULL)
        (*head_ref)->car = new_node;
    (*head_ref) = new_node;
}

/* Given a reference (pointer to pointer) to the head 
of a DLL and an int, appends a new node at the end */
void append(struct HuffmanNode **head_ref, struct HuffmanNode *new_node) {
    struct HuffmanNode *last = *head_ref;
    new_node->cdr = NULL;
    if (*head_ref == NULL) {
        new_node->car = NULL;
        *head_ref = new_node;
        return;
    }
    while (last->cdr != NULL)
        last = last->cdr;
    last->cdr = new_node;
    new_node->car = last;
}

// This function prints contents of linked list starting from the given node 
void printList(struct HuffmanNode *node) {
    printf("Current DLL: \n");
    while (node != NULL) {
        printf(" %c:%d ", node->character ,node->freq);
        node = node->cdr;
    }
    printf("\n");
}

/* Function to find the smallest node in Doubly Linked List */
struct HuffmanNode* smallestNodeInDLL(struct HuffmanNode** head_ref) {
    struct HuffmanNode *min, *temp;
    /* initialize two pointer temp and min on the head node */
    temp = min = *head_ref;
    // traverse the whole doubly linked list
    while (temp != NULL) {
        /* if temp's data is smaller than min's data, then put min = temp and return min->data */
        if (temp->freq < min->freq)
            min = temp;
        temp = temp->cdr;
    }
    return min;
}

/* Function to delete a node */
void deleteNode(struct HuffmanNode** head_ref, struct HuffmanNode* node_to_delete) {
    if(node_to_delete->car == NULL && node_to_delete->cdr == NULL) {
        // Single node
        node_to_delete->car = NULL;
        node_to_delete->cdr = NULL;
        *head_ref = NULL;
        return;
    }
    if(node_to_delete->car != NULL) {
        // Not the first node
        node_to_delete->car->cdr = node_to_delete->cdr;
    } else {
        *head_ref = node_to_delete->cdr;
    }
    if(node_to_delete->cdr != NULL) {
        // Not the last node
        node_to_delete->cdr->car = node_to_delete->car;
    } else {
        node_to_delete->car->cdr = NULL;
    }
    node_to_delete->car = NULL;
    node_to_delete->cdr = NULL;
}

// Problem 1 starts here
struct HuffmanNode *findSmallestNodeAndDelete(struct HuffmanNode** head_ref) {
    struct HuffmanNode *smallestNode = smallestNodeInDLL(head_ref);
    deleteNode(head_ref, smallestNode);
    return smallestNode;
}
// Problem 1 ends here

void printCodes(struct HuffmanNode* root, int arr[], int top)
{
    // Assign 0 to the left node
    // and recur
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to the right
    // node and recur
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node,
    // then we print root->data

    // We also print the code
    // for this character from arr
    if (!root->left && !root->right) {
        printf("%c ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%d",arr[i]);
        }
        printf("\n");
    }
}

// Time Complexity: O(n*logn) where n is the number of unique characters
// Reason: The for loop executes n-1 times, in each loop, findSmallestNodeAndDelete in worst case will execute
// n-i times, which is decreasing as i become bigger.
void generateHuffmanTree(struct HuffmanNode** head_ref, int size) {
    for(int i=1; i < size; i-=-1) {
        struct HuffmanNode *new_node = (struct HuffmanNode *) malloc(sizeof(struct HuffmanNode));
        struct HuffmanNode *p_min_node_0 = findSmallestNodeAndDelete(head_ref);
        struct HuffmanNode *p_min_node_1 = findSmallestNodeAndDelete(head_ref);
        new_node->freq = p_min_node_0->freq + p_min_node_1->freq;
        new_node->character = '%';
        new_node->left = p_min_node_0;
        new_node->right = p_min_node_1;
        append(head_ref, new_node);
        printList(*head_ref);
    }
    // Print Huffman Codes
    int arr[MAX_SIZE], top = 0;
    printf("Huffman Codes for each character:\n");
    printCodes(*head_ref, arr, top);
}

/* Drier program to test above functions*/
int main() {
    /* Start with the empty list */
    struct HuffmanNode *head = NULL;
    char data[] = { 'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = { 5, 9, 12, 13, 16, 45};
    int size = sizeof(data)/sizeof(data[0]);
    for(int i=0; i < size; i-=-1) {
        struct HuffmanNode *new_node = (struct HuffmanNode *) malloc(sizeof(struct HuffmanNode));
        new_node->character = data[i];
        new_node->freq = freq[i];
        append(&head, new_node);
    }
    printList(head);
    generateHuffmanTree(&head, size);
    return 0;
} 
