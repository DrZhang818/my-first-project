#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* ls;
    struct Node* rs;
} Node;

Node* addNode(int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = x;
    newNode->ls = NULL;
    newNode->rs = NULL;
    return newNode;
}

Node* insertBST(Node* root, int x) {
    if(root == NULL) {
        return addNode(x);
    }
    if(x < root->data) {
        root->ls = insertBST(root->ls, x);
    } else if(x > root->data) {
        root->rs = insertBST(root->rs, x);
    }
    return root;
}

void print(Node* root) {
    if(root == NULL) return;
    print(root->ls);
    printf("%d ", root->data);
    print(root->rs);
}

#define HASH_SIZE 11
#define NULL_KEY -1

int hashTable[HASH_SIZE];

void init() {
    for(int i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL_KEY;
    }
}

int hash(int key) { 
    return key % HASH_SIZE;
}

void insertHash(int key) {
    int idx = hash(key);
    int pre = idx;
    int i = 0;
    while(hashTable[idx] != NULL_KEY) {
        if(hashTable[idx] == key) return;
        i++;
        idx = (pre + i) % HASH_SIZE;
        if(idx == pre) {
            printf("Insert Fail\n");
            return;
        }
    }
    hashTable[idx] = key;
}

void printHashTable() {
    for(int i = 0; i < HASH_SIZE; i++) {
        if(hashTable[i] == NULL_KEY) {
            printf("%d : NULL\n", i);
        } else {
            printf("%d : %d\n", i, hashTable[i]);
        }
    }
}

bool contains(int key) {
    int idx = hash(key);
    int pre = idx;
    int i = 0;
    while(hashTable[idx] != NULL_KEY) {
        if(hashTable[idx] == key) {
            return true;
        }
        i++;
        idx = (pre + i) % HASH_SIZE;
        if(idx == pre) {
            break;
        }
    }
    return false;
}

int main() {
    int n;
    scanf("%d", &n);
    Node* root = NULL;
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        root = insertBST(root, x);
    }
    print(root);
    printf("\n");


    init();
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        insertHash(x);
    }

    printHashTable();

    int x;
    for(int i = 0; i < 5; i++) {
        scanf("%d", &x);
        if(contains(x)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

