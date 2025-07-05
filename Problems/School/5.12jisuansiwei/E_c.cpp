#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_RECORDS 1000
#define MAX_TAG_LEN 30
#define MAX_NAMES_PER_RECORD 100
#define MAX_NAME_LEN 30
#define MAX_UNIQUE_STUDENTS 300
#define MAX_LINE_LEN 4000

typedef struct {
    char name[MAX_NAME_LEN + 1];
    int count;
} Student;

typedef struct {
    char s[MAX_NAME_LEN + 1];
    int cnt;
} info;

int compareInfos(const void *a, const void *b) {
    info *infoA = (info *)a;
    info *infoB = (info *)b;

    if (infoA->cnt != infoB->cnt) {
        return infoB->cnt - infoA->cnt;
    }
    return strcmp(infoA->s, infoB->s);
}

void solve() {
    int n;
    scanf("%d", &n);
    getchar();

    Student students[MAX_UNIQUE_STUDENTS];
    int unique_student_count = 0;

    char line[MAX_LINE_LEN];

    for (int i = 0; i < MAX_UNIQUE_STUDENTS; i++) {
        students[i].count = 0;
    }

    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), stdin);

        char *space_ptr = strchr(line, ' ');

        if (space_ptr != NULL) {
            char *names_start = space_ptr + 1;

            char *name_token = strtok(names_start, " \t\n");
            while (name_token != NULL) {
                bool found = false;
                for (int j = 0; j < unique_student_count; j++) {
                    if (strcmp(students[j].name, name_token) == 0) {
                        students[j].count++;
                        found = true;
                        break;
                    }
                }

                if (!found && unique_student_count < MAX_UNIQUE_STUDENTS) {
                    strncpy(students[unique_student_count].name, name_token, MAX_NAME_LEN);
                    students[unique_student_count].name[MAX_NAME_LEN] = '\0';
                    students[unique_student_count].count = 1;
                    unique_student_count++;
                }

                name_token = strtok(NULL, " \t\n");
            }
        }
    }

    info ans[MAX_UNIQUE_STUDENTS];
    int ans_count = 0;
    int threshold = (n + 1) / 2;

    for (int i = 0; i < unique_student_count; i++) {
        if (students[i].count >= threshold) {
            strncpy(ans[ans_count].s, students[i].name, MAX_NAME_LEN);
            ans[ans_count].s[MAX_NAME_LEN] = '\0';
            ans[ans_count].cnt = students[i].count;
            ans_count++;
        }
    }

    qsort(ans, ans_count, sizeof(info), compareInfos);

    if (ans_count == 0) {
        printf("None\n");
    } else {
        for (int i = 0; i < ans_count; i++) {
            printf("%s\n", ans[i].s);
        }
    }
}

int main() {
    solve();
    return 0;
}
