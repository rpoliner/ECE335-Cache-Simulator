#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MATRIX_SIZE 4 // square matrix
//#define NUM_COLS 4 //number of colums
// call cache sim [i][j]
// cache_sim accepts i and j, then determines appropriate address

// n = 4 ( number of rows and columns)
// determine source address
// src_addr = [i*(n)+j]*4
// blk = src_addr & 0xF
// or for two sets set = (src_addr & 0xF) & 0x3
// tag  =src_addr >>6

//dst_addr = 0x40 + [i*(n-1)+j]

void cache_sim(int address, int cache[4][4], int blk_offset_bits, int set_index_bits, int setLines){
  int i,j; // loop incrementers
// given an address, take the s bit field. then look at that set
  int set = (address >> blk_offset_bits) & set_index_bits;
  int tag = (address >> (blk_offset_bits + set_index_bits));
  printf("ADDRESS: %d: set bits: %d , tag bits: %d\n", address, set, tag);

// first seach the appropriate set
// then, check valid bit (first column)
// if valid bit = 0. result = 0 (miss). then update cache line
// if valid bit =1, then search cache line to see if tag matches
// if tag matches, then result =1 (hit) and leave in cacheline
// if valid bit = 1 and no tag match in any cacheline, then result = 0 (miss)
// and update cache line with LRU
// remember to update the third col with a counter of usage for the LRU replacement

}

int main(){
  int cacheSize;              // Cache size
  int blockSize;              // Block size
  int setNum;                 // Number of sets (S)
  int setLines;               // Number of lines per set (E)
  int i,j;                    // Loop variables
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

  int cache_rows = setNum * setLines;
  int cache_cols = 3;
  int cache[cache_rows][cache_cols];
//  printf("cache_rows: %d\n",cache_rows);
//  printf("cache_cols: %d\n",cache_cols);

// Set every value to 0 initially
  for (i=0; i < cache_rows; i++){
    for (j=0; j<cache_cols; j++){
      cache[i][j] = 0;
    }
  }
/* Debugging -  print initial cache contents
  for (i=0; i < cache_rows; i++){
    for(j=0; j< cache_cols; j++){
      printf("\tcache[%d][%d]: %d\n", i,j, cache[i][j]);
    }
  }
*/
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
      cache_sim(src_address_temp,cache, blk_offset_bits, set_index_bits, setLines);
//      final_src_array[i][j] = cache_sim(src_address_temp,cache, blk_offset_bits, set_index_bits);
      dst_address_temp = dst_address_array[j][i];
//      final_dst_array[j][i] = cache_sim(dst_address_temp, cache, blk_offset_bits, set_index_bits);
      cache_sim(dst_address_temp, cache, blk_offset_bits, set_index_bits, setLines);
    }
  }

   return 0;
}
