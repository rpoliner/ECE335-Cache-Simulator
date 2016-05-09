#include "print.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MATRIX_SIZE 4 // square matrix

int lru;

int cache_sim(int address, int cache[MATRIX_SIZE][MATRIX_SIZE][3], int blk_offset_bits, int set_index_bits, int setLines){
  int i,j, temp1, temp2;
  int temp3 = 32; // loop incrementers
  

  if (set_index_bits == 1){
    temp1 = 0x10;
    temp2 = 0x60;
  }
  else {
    temp1 = 0x30;
    temp2 = 0x40;
    temp3 = 64;
  }

// given an address, take the s bit field. then look at that set
  int set = (address & temp1) / 16;
  int tag = (address & temp2) / temp3;

  int temp, result, earliestUsed, line;
  int finish = 0;
  for (temp = 0; temp < setLines; temp++){
    if (cache[set][temp][0] == 0){              //check the valid bit
      result = 0;                               //indicate a miss
      cache[set][temp][0] = 1;                  //update valid bit
      cache[set][temp][1] = tag;                //update tag
      cache[set][temp][2] = lru;                //update time used
      lru++;                                    //increase time
      finish = 1;
      break;
    }
    else if (cache[set][temp][1] == tag){       //check the tag to see if it matches
      result = 1;                               //indicate a hit
      cache[set][temp][2] = lru;                //update time used
      lru++;                                    //increase time
      finish = 1;                               //indicate finish
      break;
    }
  }

  

  if (finish == 0){                              //check for replacement
    result = 0;
    if (setLines == 1){                         //check if there is only one line
      cache[set][0][1] = tag;                   //update tag
      cache[set][0][2] = lru;                   //update time used
      lru++;                                    //update time
    }
    else{                                       //set associativity is > 1
      earliestUsed = lru;          //Set initial parameters for comparisons                                 
      for (temp = 0; temp < setLines; temp++){  //Cycle through each line
        if(cache[set][temp][2] < earliestUsed){ //If the line is older, update
          earliestUsed = cache[set][temp][2];
          line = temp;
        }
      }
      cache[set][line][1] = tag;                 //Update tag and lru for oldest line
      cache[set][line][2] = lru;
      lru++;
    }
  }

  return result;

}


int main(){
  int cacheSize;              // Cache size
  int blockSize;              // Block size
  int setNum;                 // Number of sets (S)
  int setLines;               // Number of lines per set (E)
  int i,j,k;                    // Loop variables
  lru = 0;                    //time variable
  int mem_addrNum;            // Max # of unique memory addresses
  int tag_bits;                    // tag bits (t)
  int src_address;            // variable used in src_address calculation
  int src_address_temp;
  int dst_address;            // variable used in dst_address calculation
  int dst_address_temp;
  int src_address_array[MATRIX_SIZE][MATRIX_SIZE];
  int dst_address_array[MATRIX_SIZE][MATRIX_SIZE];
  int final_src_array[MATRIX_SIZE][MATRIX_SIZE];
  int final_dst_array[MATRIX_SIZE][MATRIX_SIZE];
  printf("Enter cache size, block size, and number of lines per set.\n");
  printf("Input Cache Parameters in the format (B E S M): ");
  scanf("%d %d %d %d",&blockSize,&setLines,&setNum, &mem_addrNum);
  // M = 128 for our example. This input allows the program to be dynamic, and calculate the tag bits necessary

  cacheSize = blockSize*setLines*setNum;
// Calculate number of block index bits (b)
   int blk_offset_bits= 0;
   int block_temp = blockSize;
   while ((block_temp >>= 1) >= 1){
     blk_offset_bits++;
   }

// Calculate number of set index bits (s)
  int set_index_bits = 0;
  int set_temp = setNum;
  while ((set_temp >>= 1) >= 1){
   set_index_bits++;
  }

// Calculate the number of physical address bits (m)
  int phys_address_bits = 0;
  int phys_temp = mem_addrNum;
  while ((phys_temp >>= 1) >= 1){
    phys_address_bits++;
  }

// Calculate the number of tag bits: t = m - (s+b)
  tag_bits = phys_address_bits - (set_index_bits + blk_offset_bits);
  printf("Cache Parameters\n");
  printf("\tCache Size (C): %d\n", cacheSize);
  printf("\tBlock offset bits (b): %d \n", blk_offset_bits);
  printf("\tSet index bits(s): %d \n", set_index_bits);
  printf("\tLines per set (E): %d\n",setLines);
  printf("\tNumber of physical address bits (m): %d\n", phys_address_bits);
  printf("\tNumber of tag bits (t): %d\n", tag_bits);

// Cache Initialization
// Column 1 = Valid Bit, Column 2 = Tag bits, Column 3 = Usage (counter for LRU replacement)

  //cache[set][line][valid|tag|lru]
  int cache[setNum][setLines][3];


// Set every value to 0 initially
  for (i=0; i < setNum; i++){
    for (j=0; j< setLines; j++){
      for (k=0; k<3; k++){
        cache[i][j][k] = 0;
      }
    }
  }


// Calculating src and destination addresses, to simplify the pass to cache_sim function

// Populate an array to keep track of all of the source addresses
  for (i=0; i < MATRIX_SIZE; i++){
    for( j = 0; j < MATRIX_SIZE; j++){
      src_address = (i*MATRIX_SIZE+j)*4;
      src_address_array[i][j] = src_address;
// DEBUGGING - Print the address of each src array location
//      printf("src_address_array[%d][%d]: %d\n",i,j,src_address_array[i][j]);
    }
  }

// Populate an array to keep track of all of the destination
  for (i=0; i < MATRIX_SIZE; i++){
    for( j = 0; j < MATRIX_SIZE; j++){
      dst_address = 64+(i*MATRIX_SIZE+j)*4;
      dst_address_array[i][j] = dst_address;
// DEBUGGING - Print the address of each destination array location
//      printf("dst_address_array[%d][%d]: %d\n",i,j,dst_address_array[i][j]);
    }
  }

// Pass the address that corresponds with the location to the cachesimulation function
// pass it src address first, then dst address. continue to modify and update cache
// once complete, will place the result of cache_sim() into final_src/dst_arrays

  for(i=0; i < MATRIX_SIZE; i++){
    for (j=0; j< MATRIX_SIZE; j++){
      src_address_temp = src_address_array[i][j];
// The function call below is only for the time being, just to test the function without populating the final arrays
      final_src_array[i][j] = cache_sim(src_address_temp,cache, blk_offset_bits, set_index_bits, setLines);
      dst_address_temp = dst_address_array[j][i];
      final_dst_array[j][i] = cache_sim(dst_address_temp, cache, blk_offset_bits, set_index_bits, setLines);
    }
  }

  print(final_src_array, final_dst_array);

   return 0;
}
