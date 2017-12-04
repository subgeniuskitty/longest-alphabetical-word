/*
 * (c) 2017 Aaron Taylor <ataylor at subgeniuskitty dot com>
 * See LICENSE file for copyright and license details.
 */

#define DICTIONARY "words_alpha.txt"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * Verify input data.
 * Current requirements:
 *   - All characters are lowercase
 *   - No control characters other than newlines
 */
void verify_input( FILE * fp ) {
    int c;
    while((c = getc(fp)) != EOF) {
        if(!((c == '\n') || ((c >= 'a') && (c <= 'z')))) {
            fprintf(stderr, "Invalid input character: %c\n", c);
            exit(EXIT_FAILURE);
        }
    }
}

/*
 * Determine the number of words in the dictionary file and the max word length.
 */
void size_dict( FILE * fp, uint_fast32_t * word_count, uint_fast8_t * max_length ) {
    int c;
    uint_fast8_t word_length = 0;
    while((c = getc(fp)) != EOF) {
        if(c != '\n') {
            word_length++;
        } else {
            if(word_length > *max_length) {
                *max_length = word_length;
            }
            (*word_count)++;
            word_length = 0;
        }
    }
}

/*
 * Load each word from the dictionary file into an array.
 */
void populate_dict( FILE * fp, char ** dict_array, uint_fast32_t * word_count, uint_fast8_t * max_length ) {
    int c;
    int_fast32_t cw = *word_count - 1;

    for(int i = 0; cw >= 0; cw--, i = 0) {
        dict_array[cw] = malloc(*max_length + 1);
        while((c = getc(fp)) != '\n') {
            dict_array[cw][i++] = c;
        }
        dict_array[cw][i] = '\0';
    }
}

/*
 * Master function to load the dictionary file into a 2D array.
 */
void * load_dict( uint_fast32_t * num_entries ) {
    uint_fast8_t max_length = 0;
    FILE * fp = NULL;

    fp = fopen( DICTIONARY , "r" );
    if(fp) {
        verify_input(fp);
    } else {
        fprintf(stderr, "ERROR: Unable to open file " DICTIONARY "\n");
        exit(EXIT_FAILURE);
    }

    rewind(fp);
    size_dict(fp, num_entries, &max_length);

    rewind(fp);
    char ** dict_array = malloc(*num_entries * sizeof(char*));
    populate_dict(fp, dict_array, num_entries, &max_length);

    fclose(fp);

    return dict_array;
}

/*
 * Prune entries from the dictionary array which do not have alphabetical character order.
 */
void prune_dict( char ** dict_array, uint_fast32_t * num_entries ) {
    int_fast32_t cw = *num_entries - 1;

    for(int i = 1; cw >= 0; cw--, i = 1) {
        while(dict_array[cw][i] != '\0') {
            if(!(dict_array[cw][i-1] <= dict_array[cw][i])) {
                dict_array[cw][0] = '\0';
                break;
            }
            i++;
        }
    }
}

/*
 * Print entries from the dictionary in order of length.
 */
void print_dict( char ** dict_array, uint_fast32_t * num_entries ) {
    uint_fast32_t cw = *num_entries - 1;
    uint_fast8_t max_length = 0;

    while(cw) {
        if(dict_array[cw][0] != '\0') {
            for(int i = 0; dict_array[cw][i] != '\0'; i++) {
                if((i+1) > max_length) max_length = (i+1);
            }
        }
        cw--;
    }

    while(max_length) {
        cw = *num_entries - 1;
        while(cw) {
            for(int i = 0; dict_array[cw][i] != '\0'; i++) {
                if(((i+1) == max_length) && (dict_array[cw][i+1] == '\0')) {
                    printf("%d: %s\n", max_length, dict_array[cw]);
                }
            }
            cw--;
        }
        max_length--;
    }
}

int main( int argc, char ** argv ) {
    uint_fast32_t num_entries = 0;

    char ** dict_array = load_dict(&num_entries);
    prune_dict(dict_array, &num_entries);
    print_dict(dict_array, &num_entries);
}
