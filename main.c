#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYWORDS 2

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
  


    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Unable to open file: %s\n", argv[1]);
        return 1;
    }

    char keywords[MAX_KEYWORDS][50] = {"cout", "cin"};
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        for (int i = 0; i < num_keywords; i++) {
            char *keyword = keywords[i];
            if (strstr(line, keyword) != NULL) {
                if (strcmp(keyword, "cout") == 0) {
                    char *quote_start = strchr(line, '\"');
                    if (quote_start != NULL) {
                        quote_start++;
                        char *quote_end = strchr(quote_start, '\"');
                        if (quote_end != NULL) {
                            *quote_end = '\0';
                            printf("%s", quote_start);
                        }
                    }
                } else if (strcmp(keyword, "cin") == 0) {
                    char opt[10000];
                   scanf("%s",opt);

                  
                }
                break;
            }
        }
    }

    fclose(file);
    return 0;
}
