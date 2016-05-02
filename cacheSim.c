#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NUM_ROWS 4 //number of rows
#define NUM_COLS 4 //number of colums 
#define NUM_ELE 16 //number of elements

void transpose(int dest[NUM_ROWS][NUM_COLS], int src[NUM_ROWS][NUM_COLS], int srcTable[NUM_ELE][2], int destTable[NUM_ELE][2], int setLines, int setNum) {
  int i,j,k;
//initialiZe cache sets
  int cache_sets[setNum][setLines][2];
//zero out cache_sets
  for(i=0;i<setNum;i++) {
    for(j=0;j<setLines;j++) {
      cache_sets[i][j]=0;
      for(k=0;k<2;k++) { 
        cache_sets[i][j][k] = 0;}}}
//run transpose code for checking hit or miss 
  for(i=0;i< NUM_ROWS;i++) {
      for(j=0;j<NUM_COLS;j++) {
         src[i][j] = cache_sim(i, j, srcTable, cache_sets);
         dest[j][i] = cache_sim(j, i, destTable, cache_sets);
       }
     }
}

//cache_sim will return a hit or miss
// 0=Miss and 1=Hit
int cache_sim(int i, j, Table[NUM_ELE][2], cache_sets[][][2]) {
// i and j are coordinates in src or dest.
//find index based on i and j.
  int Table_index = (i*NUM_ROWS)+(j);
//look at set index and compare tags
  

}

int main(){
  int cacheSize;              // Cache size
  int blockSize;              // Block size
  int setNum;                 // Number of sets (S)
  int setLines;
  int j, i;                   // Loop variables
  int tag;                    // tag bits (t)
  int set_id;                 // set index

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
  printf("setNum (S): %d\n", setNum);

  int set_index_bits = 0;
  int set_temp = setNum;
  while ((set_temp >>= 1) >= 1){
   set_index_bits++;
  }

  printf("Set index bits: %d \n", set_index_bits);

//initialize source and dest arrays
//these will be the arrays storing the hit/miss information
  int src[NUM_ROWS][NUM_COLS];
  int dest[NUM_ROWS][NUM_COLS];

//initialize tables to store tags and set indexes.
//col 0 wil be filled with tags and col 1 will be filled with set indexes 
  int srcTable[NUM_ELE][2];
  int destTable[NUM_ELE][2];
//fill out tags for source  
  tag = 0;
  for(i=0;i<NUM_ELE;i++) {
    if(i>0 && i%(blockSize/setNum)==0) {
      tag++;}
    srcTable[i][0] = tag;}

//fill out tags for dest
  tag = srcTable[NUM_ELE-1][0] + 1;
  for(i=0;i<NUM_ELE;i++) {
    if(i>0 && i%(blockSize/setNum)==0) {
      tag++;}
    destTable[i][0] = tag;}

//fill out source and dest set indexes
//I used for because I don't know how to increment set index.  
  set_id = 0;
  for(i=0;i<NUM_ELE;i+=4) {
    for(j=0;j<4;j++) {
      srcTable[i+j][1] = set_id;
      destTable[i+j][1] = set_id;}
    if(set_id==(setNum-1)) {
      set_id=0;}
    else { 
    set_id++;}}

   printf("dest tags and set index: \n");
   for(i=0;i<NUM_ELE;i++) {
      printf("%d %d\n", destTable[i][0], destTable[i][1]);}

  transpose(src, dest, srcTable, destTable, setLines, setNum);

   return 0;
}
