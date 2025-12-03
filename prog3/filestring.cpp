#include <stdio.h>
#include <stdlib.h>

int main() {
    char* str = NULL;
    char ch;
    int size = 0;
    int hasDigit = 0;

    FILE* in = fopen("input.txt", "r");
    if (!in) {
        return 1;
    }

    while ((ch = fgetc(in)) != EOF && ch != '\n') {
        char* temp = (char*)malloc((size + 2) * sizeof(char));

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
    fclose(in);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            hasDigit = 1;
            break;
        }
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ')
            str[i] = hasDigit ? '_' : '-';
    }

    FILE* out = fopen("output.txt", "w");
    if (!out) {
        free(str);
        return 1;
    }

    fputs(str, out);
    fclose(out);
    free(str);
}