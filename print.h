#include <stdio.h>
#include <stdlib.h>

void print(int **src, int **dst){
	printf("dst\n");
	printf("_____________________________\n");
	printf("     |Col0 |Col1 |Col2 |Col3 |\n");
	printf("_____________________________\n");
	printf("row0 |%s|%s|%s|%s|\n", dst[0][0] ? "hit  " : "miss ", dst[0][1] ? "hit  " : "miss ", dst[0][2] ? "hit  " : "miss ", dst[0][3] ? "hit  " : "miss ");
	printf("_____________________________\n");
	printf("row1 |%s|%s|%s|%s|\n", dst[1][0] ? "hit  " : "miss ", dst[1][1] ? "hit  " : "miss ", dst[1][2] ? "hit  " : "miss ", dst[1][3] ? "hit  " : "miss ");
	printf("_____________________________\n");
	printf("row2 |%s|%s|%s|%s|\n", dst[2][0] ? "hit  " : "miss ", dst[2][1] ? "hit  " : "miss ", dst[2][2] ? "hit  " : "miss ", dst[2][3] ? "hit  " : "miss ");
	printf("_____________________________\n");
	printf("row3 |%s|%s|%s|%s|\n", dst[3][0] ? "hit  " : "miss ", dst[3][1] ? "hit  " : "miss ", dst[3][2] ? "hit  " : "miss ", dst[3][3] ? "hit  " : "miss ");
	printf("_____________________________\n");
	printf("\n");
	printf("\n");

	printf("src\n");
	printf("_____________________________\n");
	printf("     |Col0 |Col1 |Col2 |Col3 |\n");
	printf("_____________________________\n");
	printf("row0 |%s|%s|%s|%s|\n", src[0][0] ? "hit  " : "miss ", src[0][1] ? "hit  " : "miss ", src[0][2] ? "hit  " : "miss ", src[0][3] ? "hit  " : "miss ");
	printf("_____________________________\n");
	printf("row1 |%s|%s|%s|%s|\n", src[1][0] ? "hit  " : "miss ", src[1][1] ? "hit  " : "miss ", src[1][2] ? "hit  " : "miss ", src[1][3] ? "hit  " : "miss ");
	printf("_____________________________\n");
	printf("row2 |%s|%s|%s|%s|\n", src[2][0] ? "hit  " : "miss ", src[2][1] ? "hit  " : "miss ", src[2][2] ? "hit  " : "miss ", src[2][3] ? "hit  " : "miss ");
	printf("_____________________________\n");
	printf("row3 |%s|%s|%s|%s|\n", src[3][0] ? "hit  " : "miss ", src[3][1] ? "hit  " : "miss ", src[3][2] ? "hit  " : "miss ", src[3][3] ? "hit  " : "miss ");
	printf("_____________________________\n");

}
