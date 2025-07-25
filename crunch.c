#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define VERSION_STR "0.1"

static inline void print_usage();
static inline bool str_equals(const char* str1, const char* str2);
static inline void print_error(char* error_msg);

int filter_for_txt_files(char** params_to_filter, int ptf_size);
int compact_str_array(char** str_array, int size);

int main(int argc, char** argv){

    if(argc == 1){
        printf("Crunch --- Version %s\n", VERSION_STR);
        exit(EXIT_SUCCESS);
    }

    char* output_file_name = "out.crunched";

    char** leftover_params = (char**)malloc(sizeof(char*) * argc);

    if(leftover_params == NULL){
        print_error("Malloc Fail!");
        exit(EXIT_FAILURE);
    }

    for(unsigned int idx = 0; idx < argc; idx++){

        leftover_params[idx] = NULL;

    }

    for(int arg_idx = 1; arg_idx < argc; arg_idx++){

        if(str_equals(argv[arg_idx], "--help")){
            print_usage();
            exit(EXIT_SUCCESS);
        }

        if(str_equals(argv[arg_idx], "-o")){
            arg_idx += 1;
            
            if(arg_idx == argc){
                print_error("No filename passed with '-o' flag");
                exit(EXIT_FAILURE);
            }
            
            output_file_name = argv[arg_idx];
            continue;
        }

        if(argv[arg_idx][0] == '-'){
            print_error("Unknown flag detected!");
            exit(EXIT_FAILURE);
        }

        leftover_params[arg_idx] = argv[arg_idx];
    }

    int ftc_size = filter_for_txt_files(leftover_params, argc);

    if(ftc_size < 1){
        print_error("No files to crunch!");
        free(leftover_params);
        exit(EXIT_FAILURE);
    }

    char* files_to_crunch[ftc_size];
    
    for(unsigned int cpy_idx = 0; cpy_idx < ftc_size; cpy_idx++){
        files_to_crunch[cpy_idx] = leftover_params[cpy_idx];
    }

    free(leftover_params);

    // TODO: open file to store compilations

    // TODO: create a for loop to go through and open the filepath provided and start compilation on it.

    return EXIT_SUCCESS;
}

int filter_for_txt_files(char** params_to_filter, int ptf_size){

    /*
    
        Step 1: Filter Files

    */
    for(int filter_idx = 0; filter_idx < ptf_size; filter_idx++){

        char* current_file = params_to_filter[filter_idx];

        /*
        
            Null pointer check

        */
        if(current_file == NULL){
            continue;
        }

        /*
        
            First Check: is the filepath long enough to have a name and .txt at the end
        
        */
        if(strlen(current_file) < 5){
            params_to_filter[filter_idx] = NULL;
            continue; 
        }

        /*
        
            Second Check: is there a file extension and is the file extension four characters long
        
        */
        current_file = strrchr(current_file, '.');

        if(current_file == NULL || strlen(current_file) != 4){
            params_to_filter[filter_idx] = NULL;
            continue; 
        }

        /*
        
            Final Check: is the file extension ".txt"

        */
        if(str_equals(current_file, ".txt") != true){
            params_to_filter[filter_idx] = NULL;
            continue;
        }

        /*
        
            If code makes it here, that means the file passes all checks and isn't removed from the list

        */

    }    

    /*
    
        Step 2: Compact Array with Bubble Sort
    
    */
    return compact_str_array(params_to_filter, ptf_size);

}

int compact_str_array(char** str_array, int size){

    int first_idx = 0;
    int second_idx = 0;

    while(first_idx < size){
        
        while(str_array[first_idx] != NULL && first_idx < size){
            first_idx += 1;
        }

        second_idx = first_idx;

        while(str_array[second_idx] == NULL && second_idx < size){
            second_idx += 1;
        }

        // if there are only nulls left, early exit
        if(second_idx == size){
            break;
        }

        str_array[first_idx] = str_array[second_idx];
        str_array[second_idx] = NULL;

        first_idx += 1;
    }

    return first_idx;

}

static inline void print_usage(){

    printf("Usage: crunch [OPTIONS]... [FILES]...\n");
    printf("    -o <file>   The output file name\n");
    printf("    --help      Prints this message\n");
    printf("\n");

}

static inline bool str_equals(const char* str1, const char* str2){
    return (strcmp(str1, str2) == 0) ? true : false;
}

static inline void print_error(char* error_msg){
    printf("[Error]: %s\n", error_msg);
}