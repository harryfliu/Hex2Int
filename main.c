//
//  Quirky_Challenge_Question
//
//  Created by Harry on 2/11/15.
//  Copyright (c) 2015 Harry. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HEXLEN 65
#define MAX_FINARRAYLEN 3

void hex_to_bytearray(const char *hex_in, uint8_t* int_out); //function prototypes
uint8_t* int_to_array(uint32_t big_int);
typedef uint8_t* (*myFunc)(uint32_t); //typedef for function pointer

int main (int argc, char* argv[]){
    const char *hex_in = "8F66BF2AC289B8BF816276C68E97939BB710B739A4BB145DBD8059CAB23F00C9"; //random string of 64 hex chars
    long len = strlen(hex_in); //taking length of hex string for later use
    long len_half = len/2;
    uint8_t* int_out; //initialize int_out
    int_out = (uint8_t*) malloc(sizeof(uint8_t) * (len_half + 1)); //allocate enough memory for int_out (at least half of hex_in)
    
    printf("The hex string is: %s (%ld chars long)\n", hex_in, len);
    hex_to_bytearray(hex_in, int_out); //call hex_to_bytearray function
    free(int_out); //free allocated memory
    
    uint32_t big_int = 0x12345678; //big_int from example
    myFunc run_int_to_array = &int_to_array; //initiliaze func run_int_to_array with dereferenced func
    uint8_t* fin_array = run_int_to_array(big_int); // call run_int_to_array using typedef
    printf("The big_int is: %#x\n", big_int);
    printf("The converted 32-bit integer to 4 8-bit integers are:\n");
    for (int k = 0; k<= MAX_FINARRAYLEN; k++){ //print out contents of pointer of array of 4 8-bit integers
        printf("%#x\n", (uint8_t)fin_array[k]);
    }
    free(fin_array); //free allocated memory
    
    return 0;
}

void hex_to_bytearray(const char *hex_in, uint8_t* int_out){
    int count = 0; //initialize variables
    int two = 0; //this variable counts up to two and then goes back to 0
    int out_count = 0;
    long len_f = strlen(hex_in);
    long len_half_f = len_f/2;
    char *temp; //create temporary pointer to array
    temp = (char*) malloc(sizeof(char) * (2)); //allocate memory for array
    
    while (count<=MAX_HEXLEN) { //while count is less than or equal to max length of hex string
        two++; //increment two
        temp[two-1] = hex_in[count]; //copy over value from hex_in to temp
        if (hex_in[count] == '\0' && two == 1){ //if reaches end of string and is even number of chars then break
            break;
        }
        else if (hex_in[count] == '\0' && two == 2){ //if reaches end of string and is odd number of chars then scan then break
            temp[two] = '\0';
            sscanf(temp, "%x", (int*)&int_out[out_count]);
            break;
        }
        else if (two == 2){ //if reaches two chars then scan then increment to next element of int_out then reset two
            sscanf(temp, "%x", (int*)&int_out[out_count]);
            out_count++;
            two = 0;
        }
        count++; //increment count
    }
    
    printf("The converted hex string in integer form is:\n");
    if(two == 2){ //if hex string is odd, then print out up to half of len of hex string
        for (int i = 0; i<=len_half_f; i++){
            printf("%d) %u\n", i+1, (uint8_t)int_out[i]);
        }
    }
    else if(two == 1){//if hex string is even, then print out up to half of len of hex string - 1
        for (int j = 0; j<=len_half_f-1; j++){
            printf("%d) %u\n", j+1, (uint8_t)int_out[j]);
        }
    }
}

uint8_t* int_to_array(uint32_t big_int){
    char *temp_2; //declare another temp
    int first_four = 0; //variable keeps track of the four chars in temp_2
    temp_2 = (char*) malloc(sizeof(char) * (4)); //allocate memory for temp array
    uint8_t* array_out; //intialize array_out for return value
    array_out = (uint8_t*) malloc(sizeof(uint8_t) * (4)); //allocate memory for the output array
    int arr_count = 0;
    int increment = 0;
    char arr_hold[100]; //the array to hold the converted string from big_int
    sprintf(arr_hold, "%#x", big_int); //print the int into arr_hold
    while (increment<=15){ //while increment is less than or equal to 15
        temp_2[first_four] = arr_hold[first_four]; //copy over four wanted values to temp array
        if (increment == 3){ //if increment is 3, then scan first four wanted values and reset first_four and count up the array
            sscanf(temp_2, "%x", (int*)&array_out[arr_count]);
            first_four = -1;
            arr_count++;
        }
        else if (first_four == 5){ //if first_four is 5, then scan '0x' and then '34' then reset first_four
            sscanf(temp_2, "%x", (int*)&array_out[arr_count]);
            arr_count++;
            first_four = -1;
        }
        else if (first_four == 7){ //if first_four is 7, then scan '0x' and then '56' then reset first_four
            sscanf(temp_2, "%x", (int*)&array_out[arr_count]);
            arr_count++;
            first_four = -1;
        }
        else if (first_four == 9){//if first_four is 9, then scan '0x' and then '78' then break
            sscanf(temp_2, "%x", (int*)&array_out[arr_count]);
            break;
        }
        else if (first_four == 1 && increment == 5){//set first_four to 3 if scanned first two and increment is 5
            first_four = 3;
        }
        else if (first_four == 1 && increment == 9){//set first_four to 5 if scanned first two and increment is 9
            first_four = 5;
        }
        else if (first_four == 1 && increment == 13){//set first_four to 7 if scanned first two and increment is 13
            first_four = 7;
        }
        increment++; //increment increment and first_four
        first_four++;
    }
    
    return (array_out);
}

