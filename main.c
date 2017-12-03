/*
 * (c) 2017 Aaron Taylor <ataylor at subgeniuskitty dot com>
 * See LICENSE file for copyright and license details.
 */

#define DICTIONARY "words_alpha.txt"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
 * This function mallocs memory.
 */
void populate_dict( FILE * fp, char ** dict_array, uint_fast32_t word_count, uint_fast8_t max_length ) {
    int c;
    int_fast32_t cw = word_count - 1;

    for(int i = 0; cw >= 0; cw--, i = 0) {
        dict_array[cw] = malloc(max_length + 1);
        while((c = getc(fp)) != '\n') {
            dict_array[cw][i++] = c;
        }
        dict_array[cw][i] = '\0';
    }
}

/*
 * Master function to load the dictionary file into a 2D array.
 * This function mallocs memory.
 */
void load_dict( char ** dict_array ) {
    uint_fast32_t word_count = 0;
    uint_fast8_t max_length = 0;
    FILE * fp;

    fp = fopen( DICTIONARY , "r" );
    if(fp) {
        size_dict(fp, &word_count, &max_length);
    } else {
        fprintf(stderr, "ERROR: Unable to open file " DICTIONARY "\n");
        exit(EXIT_FAILURE);
    }

    printf("Word count: %d\nMax length: %d\n", word_count, max_length);

    rewind(fp);
    dict_array = malloc(word_count * sizeof(char*));
    populate_dict(fp, dict_array, word_count, max_length);
}

int main( int argc, char ** argv ) {
    char ** dict_array = NULL;

    load_dict(dict_array);

    /*
    scan array and delete ineligible entries
      keep track of number of entries and max length
    allocate new memory
    load entries into new array, in order of length
    free original array
    print entries of new array
    free new array
    */
}
