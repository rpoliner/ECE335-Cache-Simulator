#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void transpose2(int** dest, int** src, int rows, int cols, int sets[][2], int srcTable[][3], int destTable[][3]) {
   int i,j;
   i = rows;
   j = cols;
   for(i=0;i<4;i++) {
      for(j=0;j<4;j++) {
         dest[j][i] = src[i][j];}}
}

int main(){
   int blockSize, b, temp, j, i, tag, setIdx, setNum, setSize, cacheSize, rows, cols;
   printf("Assumptions: sizeof(int) = 4\n");
   printf("src array starts at address 0 and dest array starts at address64\n");
   printf("Enter a block size (bytes) as an integer:\n");
   printf("Be sure to enter something that is to the power of two\n");
   scanf("%d", &blockSize);
   printf("Enter a cache size (bits) as an integer:\n");
   scanf("%d", &cacheSize);
   printf("Be sure to enter something that is to the power of two\n");
   b = 0;
   temp = 1;
   for(i=0;i<blockSize;i++) {
      if(temp != blockSize) {   
      temp = temp << 1;
      b++;}}
   setNum = cacheSize/blockSize;
   setSize = 0;
   for(i=0;i<setNum;i++) {
      if(temp != setNum) {   
      temp = temp << 1;
      setSize++;}}
   //change to numers (4)
   cols = blockSize/4; //sizeof(int) = 4
   rows = 64/blockSize; //src and dest arrays are 64bits 
   //initialize and allocate arrays
   int **src; //hit/miss table for source
   int **dest; //hit/miss table for destination
   int srcTable[blockSize][3]; //contains tags and set index for source
   int destTable[blockSize][3]; //contains tags and set index for dest
   int sets[setNum][2]; //initialize the number of sets
   //allocate memory for src and dest
   src = malloc(rows * sizeof(*src));
   dest = malloc(rows * sizeof(*dest));
   for(i=0;i<rows;i++) {
      src[i] = malloc(cols * sizeof(*src[i]));
      dest[i] = malloc(cols * sizeof(*dest[i]));}
   //fill out scrTable
   tag = 0 //tag
   setIdx = 0; //set Index
   blocksizeBysetNum = blockSize/setNum;
   //fil out src tags
   // besides blcokSizeByNum do (blocksize/4)*setNum (4 is int size)
   for(i=0;i<blockSizeBysetNum;i++) {
      for(j=0;j<b;j++) {
         srcTable[j][0] = tag}   
      tag++;}
   //fil out src set indexs
   for(i=0;i<blockSizeBysetNum/b;i++) {
      for(j=0;j<b;j++) {
         scrTable[j][1] = setIdx;}
      if(setIdx < setNum) {
         setIdx++; }
      else {
         setIdx = 0;}}
   //fill out dest tags
    for(i=0;i<blockSizeBysetNum;i++) {
      for(j=0;j<b;j++) {
         destTable[j][0] = tag}   
      tag++;}
   //fil out dest set indexs
   for(i=0;i<blockSizeBysetNum/b;i++) {
      for(j=0;j<b;j++) {
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
   
   return 0;
}
   
