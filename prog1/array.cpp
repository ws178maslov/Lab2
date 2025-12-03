#include <stdio.h>
#include <stdlib.h>

int main() {
    char* str = NULL;
    char ch;
    int size = 0;
    int hasDigit = 0;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        char* temp = (char*)malloc((size + 2) * sizeof(char));
        if (temp == NULL) {
            free(str);
            return 1;
        }

        if (str != NULL) {
            for (int i = 0; i < size; i++) {
                temp[i] = str[i];
            }
            free(str); 
        }

        
        temp[size] = ch;
        temp[size + 1] = '\0';
        str = temp;
        size++;
    }

    if (str != NULL) {
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] >= '0' && str[i] <= '9') {
                hasDigit = 1;
            }
            if (str[i] == ' ') {
                str[i] = hasDigit ? '_' : '-';
            }
        }
        free(str);
    }
}