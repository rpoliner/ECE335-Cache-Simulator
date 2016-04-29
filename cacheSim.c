#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NUM_ROWS 4
#define NUM_COLS 4

void transpose2(int** dest, int** src, int sets[][2], int srcTable[][3], int destTable[][3]) {
  int i,j;
  for(i=0;i< NUM_ROWS;i++) {
      for(j=0;j<NUM_COLS;j++) {
         dest[j][i] = src[i][j];
       }
     }
}

int main(){
  int cacheSize;              // Cache size
  int blockSize;              // Block size
  int setNum;                 // Number of sets (S)
  int setLines;
  int j, i;                   // Loop variables
  int tag;                    // tag bits (t)
  int rows, cols;

  printf("Enter cache size, block size, and number of lines per set.\n");
  printf("Input Cache Parameters in the format (C B E): ");
  scanf("%d %d %d",&cacheSize,&blockSize,&setLines);

// Calculate number of block index bits (b)
   int blk_index_bits= 0;
   int block_temp = blockSize;

   while ((block_temp >>= 1) >= 1){
     blk_index_bits++;
   }
   printf("Block offset bits: %d \n", blk_index_bits);

// Calculate number of set index bits (s)
  setNum = cacheSize / (blockSize*setLines);      //  S = C / (B*E)

  int set_index_bits = 0;
  int set_temp = setNum;
  while ((set_temp >>= 1) >= 1){
   set_index_bits++;
  }

  printf("Set index bits: %d \n", set_index_bits);
/*
   //initialize and allocate arrays
   int **src; //hit/miss table for source
   int **dest; //hit/miss table for destination
   int srcTable[blockSize][3]; //contains tags and set index for source
   int destTable[blockSize][3]; //contains tags and set index for dest
   int sets[setNum][2]; //initialize the number of sets
   //allocate memory for src and dest
   src = malloc(NUM_ROWS * sizeof(*src));
   dest = malloc(NUM_ROWS * sizeof(*dest));
   for(i=0;i<rows;i++) {
      src[i] = malloc(cols * sizeof(*src[i]));
      dest[i] = malloc(cols * sizeof(*dest[i]));}
   //fill out srcTable
   tag = 0; //tag
   setIdx = 0; //set Index
   int blockSizeBysetNum = blockSize/setNum;
   //fil out src tags
   // besides blcokSizeByNum do (blocksize/4)*setNum (4 is int size)
   for(i=0;i<blockSizeBysetNum;i++) {
      for(j=0;j<blk_index_bits;j++) {
         srcTable[j][0] = tag;
       }
      tag++;}
   //fil out src set indexs
   for(i=0;i<blockSizeBysetNum/b;i++) {
      for(j=0;j<blk_index_bits;j++) {
         srcTable[j][1] = setIdx;}
      if(setIdx < setNum) {
         setIdx++; }
      else {
         setIdx = 0;}}
   //fill out dest tags
    for(i=0;i<blockSizeBysetNum;i++) {
      for(j=0;j<blk_index_bits;j++) {
         destTable[j][0] = tag;
       }
      tag++;}
   //fil out dest set indexs
   for(i=0;i<blockSizeBysetNum/b;i++) {
      for(j=0;j<blk_index_bits;j++) {
         destTable[j][1] = setIdx;}
      if(setIdx < setNum-1) {
         setIdx++; }
      else {
         setIdx = 0;}}
   //run transpose function and pray.
   transpose2(dest, src, rows, cols, sets, srcTable, destTable);
   //deallocate arrays
   for(i=0;i<rows;i++) {
      free(src[i]);
      free(dest[i]);}
   free(src);
   free(dest);
*/
   return 0;
}
