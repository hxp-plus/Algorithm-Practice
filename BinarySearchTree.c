/* Practice on Algorithms: Binary Search Tree */
/* author: hxp<hxp201406@gmail.com> */
#include <stdio.h>
#include <stdlib.h>

/* Basic structure of the Binary Search Tree */
struct Node {
    struct Node* p_left_child_node;
    struct Node *p_right_child_node;
    struct Node* p_parent_node;
    unsigned short node_key;
};

/* Create a new node with the given value new_node_value, but not attaching it to the tree */
struct Node* createNewNode(unsigned short new_node_value) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->node_key = new_node_value;
    // Will place the node in correct position later
    new_node->p_parent_node = NULL;
    new_node->p_left_child_node = NULL;
    new_node->p_right_child_node = NULL;
    return(new_node);
}

// Problem 2.3 starts here
/* Insert a node with value rooted in root_node, DO NOT use recursion, use loop instead */
/* Time Complexity: O(n) where n is the height of the tree
 * Reason: The worst case of insert operations when we have to travel from root to the deepest child node.
 *         So when the tree's height is n, the time complexity may be O(n) */
struct Node* insertNewNodeNoRecursion(struct Node* p_root_node, unsigned short new_node_value) {
    struct Node* p_parent_node = NULL;
    struct Node* p_child_node = p_root_node;
    struct Node* p_new_node = createNewNode(new_node_value);
    while(p_child_node != NULL) {
        p_parent_node = p_child_node;
        if(p_new_node->node_key < p_parent_node->node_key)
            p_child_node = p_parent_node->p_left_child_node;
        else
            p_child_node = p_parent_node->p_right_child_node;
    }
    // Link the new node to the current parent node
    p_new_node->p_parent_node = p_parent_node;
    // Link the parent node to the new node
    if(p_parent_node != NULL)
    {
        if(p_new_node->node_key < p_parent_node->node_key) {
            p_parent_node->p_left_child_node = p_new_node;
        } else {
            p_parent_node->p_right_child_node = p_new_node;
        }
    } else {
        p_root_node = p_new_node;
    }
    return(p_root_node);
}
// Problen 2.3 ends here

// Problem 2.4 starts here
/* Insert a node with value rooted in root_node, using recursion */
/* Time Complexity: O(n) where n is the height of the tree
 * Reason: The worst case of insert operations when we have to travel from root to the deepest child node.
 *         So when the tree's height is n, the time complexity may be O(n) */
struct Node* insertNewNode(struct Node* p_root_node, unsigned short new_node_value) {
    // If the tree is empty, return a single node
    if (p_root_node == NULL)
        return(createNewNode(new_node_value));
    else {
        struct Node *temp;
        if (new_node_value <= p_root_node->node_key) {
            // Recursion: the left child as new root
            temp = insertNewNode(p_root_node->p_left_child_node, new_node_value);
            p_root_node->p_left_child_node  = temp;
            temp->p_parent_node= p_root_node;
        } else {
            // Recursion: the right child as new root
            temp = insertNewNode(p_root_node->p_right_child_node, new_node_value);
            p_root_node->p_right_child_node = temp;
            temp->p_parent_node = p_root_node;
        }
        // Return the origin root node
        return(p_root_node);
    }
}
//Problem 2.4 ends here

// Problem 2.1 Starts Here
/* Find the minimum value for a given root node */
struct Node* findMinValue(struct Node* root_node) {
    struct Node* p_current_node = root_node;
    // The leftmost child node has the minimum value, recurse to find it
    while(p_current_node->p_left_child_node != NULL) {
        // Climb one step downward in the tree
        p_current_node = p_current_node->p_left_child_node;
    }
    return(p_current_node);
}
// Problem 2.1 ends Here

// Problem 2.2 starts here
/* Find the in-order successor of a given node in a tree rooted in root_node*/
// Time Complexity: O(n) where n is height of tree.
struct Node* findInOrderSuccessor(struct Node* p_node_given) {
    if(p_node_given->p_right_child_node != NULL)
        return(findMinValue(p_node_given->p_right_child_node));
    struct Node *p_parent_node=p_node_given->p_parent_node;
    while (p_parent_node != NULL && p_node_given == p_parent_node->p_right_child_node) {
        // Climb up the tree
        p_node_given = p_parent_node;
        p_parent_node = p_parent_node->p_parent_node;
    }
    return(p_parent_node);
}
// Problem 2.2 ends here

// Function to print binary tree in 2D
void printTree(struct Node *p_root_node, int number_of_space)
{
    // Base case
    if (p_root_node == NULL)
        return;
    // Increase distance between levels
    number_of_space += 8;
    // Process right child first
    printTree(p_root_node->p_right_child_node, number_of_space);
    // Print current node after space
    printf("\n");
    for (int i = 8; i < number_of_space; i++)
        printf(" ");
    printf("%d\n", p_root_node->node_key);
    // Process left child
    printTree(p_root_node->p_left_child_node, number_of_space);
}

/* Entry point for this program */
int main() {
    struct Node* p_root_node = NULL, *p_given_node, *in_order_successor, *p_minimum_node;
    // Creating a tree
    printf("\nNow creating a Binary Search Tree using code from Problem 2.3\n");
    p_root_node = insertNewNodeNoRecursion(p_root_node, 10);
    p_root_node = insertNewNodeNoRecursion(p_root_node, 17);
    p_root_node = insertNewNodeNoRecursion(p_root_node, 4);
    p_root_node = insertNewNodeNoRecursion(p_root_node, 1);
    p_root_node = insertNewNodeNoRecursion(p_root_node, 5);
    p_root_node = insertNewNodeNoRecursion(p_root_node, 16);
    p_root_node = insertNewNodeNoRecursion(p_root_node, 21);
    printf("Created Binary Search Tree:\n");
    printTree(p_root_node, 0);
    // Find the node which has the minimum key
    printf("\nNow performing: Problem 2.1\n");
    p_minimum_node = findMinValue(p_root_node);
    printf("The minimum key in the tree is: %d\n", p_minimum_node->node_key);
    // Appoint a node and find its in-order successor
    printf("\nNow performing: Problem 2.2\n");
    p_given_node=p_root_node->p_left_child_node->p_left_child_node;
    in_order_successor = findInOrderSuccessor(p_given_node);
    if(in_order_successor != NULL)
        printf("In-order Successor of %d is %d\n", p_given_node->node_key, in_order_successor->node_key);
    else
        printf("In-order Successor doesn't exit\n");
    // Appoint another node and find its in-order successor
    p_given_node=p_root_node->p_right_child_node->p_right_child_node;
    in_order_successor = findInOrderSuccessor(p_given_node);
    if(in_order_successor != NULL)
        printf("In-order Successor of %d is %d\n", p_given_node->node_key, in_order_successor->node_key);
    else
        printf("In-order Successor of %d doesn't exist\n", p_given_node->node_key);
    // Insert a key to the tree
    printf("\nNow performing: Problem 2.4\n");
    unsigned short key_to_insert;
    key_to_insert = 6;
    printf("Inserting %d into the tree...\n", key_to_insert);
    insertNewNode(p_root_node, key_to_insert);
    printf("Tree after inserting %d:\n",key_to_insert);
    printTree(p_root_node, 0);
    // Insert another key to the tree
    key_to_insert = 18;
    printf("Inserting %d into the tree...\n", key_to_insert);
    insertNewNode(p_root_node, key_to_insert);
    printf("Tree after inserting %d:\n",key_to_insert);
    printTree(p_root_node, 0);
    // Insert the other key to the tree
    key_to_insert = 26;
    printf("Inserting %d into the tree...\n", key_to_insert);
    insertNewNode(p_root_node, key_to_insert);
    printf("Tree after inserting %d:\n",key_to_insert);
    printTree(p_root_node, 0);
    return 0;
}