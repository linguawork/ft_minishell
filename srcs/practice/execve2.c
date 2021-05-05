#include <stdlib.h>
#include <string.h>
// code source: https://indradhanush.github.io/blog/writing-a-unix-shell-part-2/
//Let us take a look at the following function. which takes a string as the input.
// We use the library function strtok to split the string by the character space
// and return an array of strings instead. We also terminate the array by NULL.
char **get_input(char *input) {
    char **command = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}
//If the input to the function is the string
// "ls -l -h -a", then the function will create
// an array of the form ["ls", "-l", "-h", "-a", NULL]
// and return the pointer to this array.