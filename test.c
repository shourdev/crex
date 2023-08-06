         int j = i + 5;
                    while (j < length && isspace(string[j])) {
                        j++;
                    }
                    if (j < length && string[j] == '"') {
                        j++; // Move past the opening double quote
                        while (j < length) {
                            if (string[j] == '"' && string[j - 1] != '\\') {
                                break; // Found the closing double quote
                            }

                            // Instead of using putchar, append the character to the output string
                            output = (char*)realloc(output, (outputIndex + 2) * sizeof(char));
                            output[outputIndex++] = string[j];
                            output[outputIndex] = '\0'; // Null-terminate the output string

                            j++;
                        }
                       cout(1,output); 
                        free(output);
                        output = NULL;
                        outputIndex = 0;
                    }