#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct info {
    char name[10];
    int id;
    char job[10];
} info ;

info a[100];
int idx = 0;
void add(info o) {
    a[++idx] = o;
}
bool equal(info a, info b) {
    return strcmp(a.name, b.name) == 0 && a.id == b.id && strcmp(a.job, b.job) == 0;
}
void erase(info o) {
    int i = 1;
    while(i <= idx && !equal(a[i], o)) {
        i++;
    }
    if(i > idx) {
        return;
    }
    for(int j = i; j <= idx - 1; j++) {
        a[j] = a[j + 1];
    }
    idx--;
}
void print() {
    for(int i = 1; i <= idx; i++) {
        printf("%s %d %s\n", a[i].name, a[i].id, a[i].job);
    }
    printf("\n");
}

int main() {

    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int op;
        scanf("%d", &op);
        info cur;
        scanf("%s", cur.name);
        scanf("%d", &cur.id);
        scanf("%s", cur.job);
        if(op == 1) {
            add(cur);
        } else {
            erase(cur);
        }
        print();
    }

    return 0;
}
