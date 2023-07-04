#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // Include ctype.h for isspace function
char name[1000];
char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return NULL;
    }

    // Find the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Dynamically allocate memory for the string
    char* buffer = (char*)malloc(file_size + 1); // +1 for null terminator
    if (buffer == NULL) {
        printf("Error allocating memory.\n");
        fclose(file);
        return NULL;
    }

    // Read the file into the buffer
    size_t result = fread(buffer, 1, file_size, file);
    if (result != file_size) {
        printf("Error reading the file.\n");
        fclose(file);
        free(buffer);
        return NULL;
    }

    buffer[file_size] = '\0'; // Add null terminator at the end

    fclose(file);
    return buffer;
}

void removeAfterAsterisk(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    FILE* tempFile = tmpfile();  // Create a temporary file
    if (tempFile == NULL) {
        printf("Failed to create a temporary file.\n");
        fclose(file);
        return;
    }

    char* line = NULL;
    size_t lineSize = 0;
    size_t bytesRead;

    while ((bytesRead = getline(&line, &lineSize, file)) != -1) {
        if (bytesRead > 0 && line[bytesRead - 1] == '\n') {
            line[bytesRead - 1] = '\0';  // Remove the newline character from the line
        }

        char* asteriskPtr = strchr(line, '*');
        if (asteriskPtr != NULL) {
            *asteriskPtr = '\0';  // Truncate the line at the position of the asterisk
        }
        fprintf(tempFile, "%s\n", line);  // Write the modified line to the temporary file
    }

    free(line);  // Free the dynamically allocated line

    fclose(file);
    rewind(tempFile);  // Move the temporary file pointer to the beginning

    file = fopen(filename, "w");  // Reopen the original file in write mode
    if (file == NULL) {
        printf("Failed to reopen the file.\n");
        fclose(tempFile);
        return;
    }

    int ch;
    while ((ch = fgetc(tempFile)) != EOF) {
        fputc(ch, file);  // Copy the contents of the temporary file to the original file
    }

    fclose(file);
    fclose(tempFile);
}

void write(char* code) {
    char name[100] = "output"; // Set the desired name for the output file
    strcat(name, ".c");
    
    FILE *file = fopen(name, "w");  // Open file in write mode
    
    fprintf(file, "#include <stdio.h>\n");
    fprintf(file, "int main() {\n");
    
    char* line = strtok(code, "\n"); // Tokenize the input code by lines
    
    while (line != NULL) {
        char* hiPtr = strstr(line, "cout:"); // Find "cout:" in the line
        
        if (hiPtr != NULL) {
     fprintf(file,"printf(%s);\n",hiPtr + 5); // Extract the text after "cout:"
        }
        
        line = strtok(NULL, "\n"); // Move to the next line
    }
    
    fprintf(file, "return 0;\n");
    fprintf(file, "}\n");
    
    fclose(file);
    
    char command[1024];
    snprintf(command, sizeof(command), "gcc -o program %s ", name);
    system(command);
    
    snprintf(command, sizeof(command), "./program");
    system(command);
}

void compstg1(char* code){
      FILE *file;
    
 
    
   file = fopen(name, "w");
       fprintf(file, "%s", code);
       fclose(file);
removeAfterAsterisk(name);

   char* file_content = read_file(name);

remove(name);
write(file_content);
free(file_content);

}
int main(int argc, char *argv[]) {
    

       

    
    if (strcmp(argv[1], "--help") == 0) {
        printf("Crex is a simple programming language designed to do anything! \n");
        printf("Run a file: ./crex <filename>.crf \n");
        printf("Documentation can be found at: https://github.com/shourdev/crex#documentation \n");
        return 0;
    }

   char* file_content = read_file(argv[1]);
    if (file_content == NULL) {
        return 1;
    }

strcpy(name,argv[1]);
strcat(name,".txt");
compstg1(file_content);


    free(file_content);
    return 0;
}
