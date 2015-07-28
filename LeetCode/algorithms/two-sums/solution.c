#include <stdlib.h>
#include <time.h>

struct node {
    int *data;
    struct node *next;
};

void hash_insert (struct node **bra, int mo, int *data) {
    int sel = abs(*data) % mo; 
    struct node *newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = data;
    newnode->next = bra[sel];
    bra[sel] = newnode;
}

int *hash_search (struct node **bra, int mo, int key) {
    int sel = abs(key) % mo;
    struct node *p = bra[sel];
    
    while (p) {
        if (*(p->data) == key)
            return p->data;
        p = p->next;
    }

    return NULL;
}

void hash_destroy (struct node **bra, int mo) {
    int i;
    for (i=0; i<mo; i++)
        while (bra[i]) {
            struct node* p = bra[i];
            bra[i] = p->next;
            free(p);
        }
}

int* twoSum(int* nums, int numsSize, int target) {
    int mo, *p, i;
    struct node** bra;

    srand(time(0));
    mo = (numsSize/2 + rand() % numsSize) & 0xFFFFFFFF;

    bra = (struct node**) malloc(mo * sizeof(struct node*));
    for (i=0; i<mo; i++)
        bra[i] = NULL;

    int *result = (int*)malloc(2 * sizeof(int));
    for (p=nums; p; p++) {
        int *g;
        if ((g = hash_search(bra, mo, target - *p)) != NULL) {
            int key1 = g-nums+1, key2 = p-nums+1;
            if (key1 > key2)
                result[0] = key2, result[1] = key1;
            else
                result[0] = key1, result[1] = key2;
            break;
        }
        else
            hash_insert(bra, mo, p);
    }

    hash_destroy(bra, mo);
    free(bra);

    return result;
}
