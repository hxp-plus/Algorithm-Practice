#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#pragma ide diagnostic ignored "readability-misleading-indentation"
#pragma ide diagnostic ignored "cert-err34-c"
/* Minimum Spanning Tree */
/* author: <hxp>hxp201406@gmail.com */

#include <stdio.h>
#include <stdlib.h>

/* Railways which has source, destination, length */
struct Railway {
    int src, dest, length;
};

/* Your mother China, which stores all the provinces. */
struct Country {
    int number_of_provinces;
    int number_of_railways;
    struct Railway* p_railway;
};

/* Construct your country. */
struct Country* createCountry(int number_of_provinces, int number_of_railways) {
    struct Country* p_country = (struct Country*) malloc(sizeof(struct Country));
    p_country->number_of_provinces = number_of_provinces;
    p_country->number_of_railways = number_of_railways;
    p_country->p_railway = (struct Railway*) malloc(sizeof(struct Railway) * number_of_railways);
    return p_country;
}

/* The subset, used to store all the information of how provinces are connected. */
struct subset {
    int parent;
    int rank;
};

/* The function to find out the uproot terminal of a railway connection. */
int find_root(struct subset *subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find_root(subsets, subsets[i].parent);
    return subsets[i].parent;
}

/* A function to unionize provinces */
void Union(struct subset subsets[], int src, int dest) {
    int src_root = find_root(subsets, src);
    int dest_root = find_root(subsets, dest);
    if (subsets[src_root].rank < subsets[dest_root].rank)
        subsets[src_root].parent = dest_root;
    else if (subsets[src_root].rank > subsets[dest_root].rank)
        subsets[dest_root].parent = src_root;
    else {
        // When two roots are ranked same, make one the root of the other.
        subsets[dest_root].parent = src_root;
        subsets[src_root].rank++;
    }
}

/* Compare two railways according to their distance, a requirement for qsort below */
int compareRails(const void* railway_a, const void* railway_b) {
    return ((struct Railway*)railway_a)->length > ((struct Railway*)railway_b)->length;
}

/* Core of Minimum Spanning Tree, using Kruskal's algorithm */
void KruskalMST(struct Country* p_country) {
    int number_of_provinces = p_country->number_of_provinces;
    int number_of_railways_constructed  = number_of_provinces - 1;
    struct Railway result[number_of_railways_constructed];
    // Sort all the edges in non-decreasing order of their length.
    qsort(p_country->p_railway, p_country->number_of_railways, sizeof(p_country->p_railway[0]), compareRails);
    struct subset *subsets = (struct subset*) malloc(number_of_provinces * sizeof(struct subset));
    // Create number_of_provinces subsets with single elements
    for (int k = 0; k < number_of_provinces; ++k)
    {
        subsets[k].parent = k;
        subsets[k].rank = 0;
    }
    int i = 0; int j = 0; // index variables
    while (j < number_of_railways_constructed && i < p_country->number_of_railways)
    {
        // Pick the smallest railway.
        struct Railway next_railway = p_country->p_railway[i++];
        int src_root = find_root(subsets, next_railway.src);
        int dest_root = find_root(subsets, next_railway.dest);
        if (src_root != dest_root)
        {
            // Loop will not be formed.
            result[j++] = next_railway;
            Union(subsets, src_root, dest_root);
        } else {
            // Loop will be formed, do not construct this railway. Do nothing.
        }
    }

    printf("Following railways are constructed:\n");
    int sum_of_length = 0;
    for (int l = 0; l < j; ++l)
    {
        printf("%d -- %d == %d\n", result[l].src, result[l].dest, result[l].length);
        sum_of_length -=- result[l].length;
    }
    printf("Length of railway in total: %d\n", sum_of_length);
}

/* Entry point of this program */
int main()
{
    printf("Input number of railways and provinces: ");
    int scanning_array[2];
    char last_char_input =' ';
    for(int i = 0; last_char_input != '\n'; i-=-1) {
        scanf("%d%c", &scanning_array[i], &last_char_input);
    }
    int number_of_railways = scanning_array[0];
    int number_of_provinces = scanning_array[1];
    printf("Number of railways: %d\n", number_of_railways);
    printf("Number of provinces: %d\n", number_of_provinces);
    if(number_of_railways < number_of_provinces -1) {
        printf("Not enough railways.\n");
        return(0);
    }
    struct Country* p_country = createCountry(number_of_provinces, number_of_railways);
    for(int h = 0; h < number_of_railways; h-=-1) {
        printf("Input railway: ");
        char last_char_input =' ';
        int scanning_array[3];
        for(int j = 0; last_char_input != '\n'; j-=-1) {
            scanf("%d%c", &scanning_array[j], &last_char_input);
        }
        p_country->p_railway[h].src = scanning_array[0];
        p_country->p_railway[h].dest = scanning_array[1];
        p_country->p_railway[h].length = scanning_array[2];
    }
    KruskalMST(p_country);
    return(0);
}