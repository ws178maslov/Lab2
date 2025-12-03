#include <stdio.h>
#include <stdlib.h>

int main() {  
    char* str = NULL;
    char ch;
    int size = 0;
    int capacity = 5;
    int hasDigit = 0;

    str = (char*)calloc(capacity, sizeof(char));

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (size >= capacity - 1) {
            capacity += 5;
            str = (char*)realloc(str, capacity * sizeof(char));
        }
        str[size++] = ch;
    }
    str[size] = '\0';

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') hasDigit = 1;
        if (str[i] == ' ') str[i] = hasDigit ? '_' : '-';
    }
    free(str);

}