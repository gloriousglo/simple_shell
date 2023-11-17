#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

// Declare the `environ` variable for accessing environment variables
extern char **environ;

#define MAX_INPUT_SIZE 1024
#define MAX_ARGUMENTS 32

// Define a data structure for storing alias-name and alias-value pairs
typedef struct Alias {
    char *name;
    char *value;
    struct Alias *next;
} Alias;

Alias *aliases = NULL; // Head of the alias list

// Function to add an alias to the list
void add_alias(const char *name, const char *value) {
    Alias *new_alias = (Alias *)malloc(sizeof(Alias));
    new_alias->name = strdup(name);
    new_alias->value = strdup(value);
    new_alias->next = aliases;
    aliases = new_alias;
}

// Function to find an alias by name
Alias *find_alias(const char *name) {
    Alias *current = aliases;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to expand variables in a command
char *expand_variables(const char *command) {
    char *expanded = (char *)malloc(strlen(command) * 2 + 1); // Make room for variable expansion
    const char *source = command;
    char *dest = expanded;

    while (*source) {
        if (*source == '$') {
            source++;
            if (*source == '?') {
                // Expand the $? variable to the exit status of the last command
                int exit_status = 0; // Default to success
                if (source == command + 1) {
                    // Expand $? at the beginning of the command
                    // Handle $?
                    // You may need to track the exit status of each command execution
                }
                snprintf(dest, 3, "%d", exit_status);
                dest += 2;
                source++;
            } else if (*source == '$') {
                // Expand the $$ variable to the process ID of the shell
                snprintf(dest, 6, "%d", getpid());
                dest += 5;
                source++;
            } else if (*source == '{') {
                // Variable expansion: ${VAR}
                source++; // Skip the {
                const char *variable_start = source;
                while (*source && *source != '}') {
                    source++;
                }
                if (*source == '}') {
                    // Variable found
                    int variable_length = source - variable_start;
                    char variable_name[variable_length + 1];
                    strncpy(variable_name, variable_start, variable_length);
                    variable_name[variable_length] = '\0';

                    // Look up the environment variable by name
                    char *variable_value = getenv(variable_name);
                    if (variable_value) {
                        strcpy(dest, variable_value);
                        dest += strlen(variable_value);
                    }
                    source++; // Skip the }
                }
            }
        } else {
            *dest++ = *source++;
        }
    }
    *dest = '\0';

    return expanded;
}

int execute_command(const char *command) {
    char *expanded_command = expand_variables(command);

    // Tokenize the input to separate the command and its arguments
    char *args[MAX_ARGUMENTS];
    char *token = strtok(expanded_command, " ");
    int argc = 0;
    while (token != NULL) {
        args[argc] = token;
        token = strtok(NULL, " ");
        argc++;
    }
    args[argc] = NULL;

    // Check for comments (lines starting with '#')
    if (argc > 0 && args[0][0] == '#') {
        free(expanded_command);
        return 0; // Ignore and skip comments
    }

    // Check for the "alias" command
    if (argc > 0 && strcmp(args[0], "alias") == 0) {
        if (argc == 1) {
            // Print all aliases
            print_aliases();
        } else {
            // Handle alias name='value' [...]
            for (int i = 1; i < argc; i++) {
                char *arg = args[i];
                char *equal_sign = strchr(arg, '=');
                if (equal_sign != NULL) {
                    *equal_sign = '\0'; // Split name and value
                    char *name = arg;
                    char *value = equal_sign + 1;
                    Alias *existing_alias = find_alias(name);
                    if (existing_alias != NULL) {
                        free(existing_alias->value); // Replace existing alias
                        existing_alias->value = strdup(value);
                    } else {
                        add_alias(name, value); // Add a new alias
                    }
                } else {
                    // Print the alias value for the given name
                    Alias *alias = find_alias(arg);
                    if (alias != NULL) {
                        printf("%s='%s'\n", alias->name, alias->value);
                    }
                }
            }
        }
    }

    // You can handle other commands here...

    free(expanded_command);

    return 0;
}

int execute_commands_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return -1;
    }

    char line[MAX_INPUT_SIZE];
    while (fgets(line, MAX_INPUT_SIZE, file) != NULL) {
        // Remove the trailing newline character
        line[strcspn(line, "\n")] = '\0';
        execute_command(line);
    }

    fclose(file);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        return execute_commands_from_file(argv[1]);
    }

    // Interactive mode
    char input[MAX_INPUT_SIZE];
    char *commands[MAX_ARGUMENTS];
    int num_commands = 0;

    while (1) {
        printf("simple_shell> "); // Display the prompt
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            // Handle "end of file" condition (Ctrl+D)
            break;
        }

        // Remove the trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Skip lines that start with '#'
        if (input[0] == '#') {
            continue;
        }

        // Split the input into separate commands based on semicolons
        char *token = strtok(input, ";");
        while (token != NULL) {
            commands[num_commands] = token;
            num_commands++;
            token = strtok(NULL, ";");
        }

        // Execute each command sequentially
        for (int i = 0; i < num_commands; i++) {
            int status = execute_command(commands[i]);
            if (status == -1) {
                // Exit the shell
                return 0;
            }
        }

        num_commands = 0; // Reset the number of commands
    }

    // Free allocated memory for aliases
    Alias *current = aliases;
    while (current != NULL) {
        Alias *temp = current;
        current = current->next;
        free(temp->name);
        free(temp->value);
        free(temp);
    }

    return 0;
}
