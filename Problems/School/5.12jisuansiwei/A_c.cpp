#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void solve() {
    char s[13];
    while (scanf("%s", s) == 1) {
        bool ok = true;
        int len = strlen(s);
        if(len == 5) {
            if(s[0] == '0' || s[0] == '1') ok = false;

            for (int i = 0; i < len; i++) if(!isdigit(s[i])) ok = false;
        } else if (len == 7) {
            if(s[0] != '0' || s[2] == '0' || s[2] == '1') ok = false;

            for(int i = 0; i < len; i++) if(!isdigit(s[i])) ok = false;
        } else if (len == 8) {
            if(s[0] != '0' || s[3] == '0' || s[3] == '1' || s[2] != '-') ok = false;
            
            for (int i = 0; i < len; i++) if(i != 2 && !isdigit(s[i])) ok = false;
        } else ok = false;
        
        if (ok) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
}
int main() {
    solve();
    return 0;
}
