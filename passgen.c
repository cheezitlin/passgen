#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// Function to generate random password
void generate_password(int length, int exclude_unicode, int exclude_numbers, int exclude_letters, int exclude_spaces) {
    // Default character pool (ASCII and Unicode)
    char *ascii_letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *digits = "0123456789";
    char *spaces = " ";
    
    // Define the full Unicode range (U+0021 to U+E0FFF)
    char *unicode_chars = NULL;
    int unicode_length = 0;

    // Allocate a buffer for Unicode characters
    if (!exclude_unicode) {
        // Allocate a large enough space for Unicode characters.
        unicode_chars = (char *)malloc(917999 * sizeof(char));  // From U+0021 to U+E0FFF
        if (!unicode_chars) {
            fprintf(stderr, "Memory allocation for Unicode characters failed\n");
            exit(1);
        }
        unicode_length = 0;
        
        // Adding all the printable Unicode characters from U+0021 to U+E0FFF
        for (int cp = 0x21; cp <= 0xE0FFF; cp++) {
            if ((cp >= 0x0021 && cp <= 0x7E) || (cp >= 0xA1 && cp <= 0xFF)) {
                // Only adding printable or reasonable characters
                unicode_chars[unicode_length++] = cp;
            }
        }
    }

    // Set up the character pool
    char char_pool[2048];  // Large enough to hold all characters
    int pool_size = 0;

    if (!exclude_letters) {
        strcat(char_pool, ascii_letters);
        pool_size += strlen(ascii_letters);
    }
    if (!exclude_numbers) {
        strcat(char_pool, digits);
        pool_size += strlen(digits);
    }
    if (!exclude_spaces) {
        strcat(char_pool, spaces);
        pool_size += strlen(spaces);
    }
    if (!exclude_unicode) {
        for (int i = 0; i < unicode_length; i++) {
            char_pool[pool_size++] = unicode_chars[i];
        }
    }

    // Seed the random number generator
    srand(time(NULL));

    // Generate the password
    printf("Generated password: ");
    for (int i = 0; i < length; i++) {
        int random_index = rand() % pool_size;
        putchar(char_pool[random_index]);
    }
    printf("\n");

    // Free the memory for Unicode characters
    if (unicode_chars != NULL) {
        free(unicode_chars);
    }
}

// Main function to parse the arguments and call the password generator
int main(int argc, char *argv[]) {
    int length = 16;  // Default password length
    int exclude_unicode = 0;
    int exclude_numbers = 0;
    int exclude_letters = 0;
    int exclude_spaces = 0;

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0 && i + 1 < argc) {
            length = atoi(argv[++i]);
        } else if (strncmp(argv[i], "-e:", 3) == 0) {
            char *exclusions = argv[i] + 3;  // Skip "-e:"
            for (int j = 0; exclusions[j] != '\0'; j++) {
                switch (exclusions[j]) {
                    case 'u':
                        exclude_unicode = 1;
                        break;
                    case 'n':
                        exclude_numbers = 1;
                        break;
                    case 'l':
                        exclude_letters = 1;
                        break;
                    case 's':
                        exclude_spaces = 1;
                        break;
                    default:
                        fprintf(stderr, "Unknown exclusion: %c\n", exclusions[j]);
                        return 1;
                }
            }
        } else {
            fprintf(stderr, "Unknown argument: %s\n", argv[i]);
            return 1;
        }
    }

    // Generate the password
    generate_password(length, exclude_unicode, exclude_numbers, exclude_letters, exclude_spaces);

    return 0;
}

