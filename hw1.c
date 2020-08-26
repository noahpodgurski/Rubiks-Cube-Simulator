#include <stdio.h>

enum sides {
	FRONT, BACK, UP, DOWN, LEFT, RIGHT
};

void swap(char *B1, char *B2){
	char temp;
	temp = *B1;
	*B1 = *B2;
	*B2 = temp;
}

void swapSide(char A[2][2], char B[2][2]){
	int i, j;
	for (i = 0; i < 2; i++){
		for (j = 0; j < 2; j++){
			swap(&A[i][j], &B[i][j]);
		}
	}
}

void rotateFace(char A[2][2], int counterclockwise){
	if (counterclockwise == 1){ /* cc */
		swap(&A[0][0], &A[0][1]); /* B1 <-> B2 */
		swap(&A[0][1], &A[1][1]); /* B1 <-> B4 */
		swap(&A[1][1], &A[1][0]); /* B1 <-> B3 */
	} else { 					/* clockwise */
		swap(&A[0][0], &A[1][0]); /* B1 <-> B3 */
		swap(&A[1][0], &A[1][1]); /* B1 <-> B4 */
		swap(&A[1][1], &A[0][1]); /* B1 <-> B2 */
	}
}

		/*  [face][row][col] */
static char cube[6][2][2] = {
	{{'B', 'B'}, {'B', 'B'}}, /* F Front */
	{{'G', 'G'}, {'G', 'G'}}, /* B Back */
	{{'W', 'W'}, {'W', 'W'}}, /* U Up */
	{{'Y', 'Y'}, {'Y', 'Y'}}, /* D Down */
	{{'R', 'R'}, {'R', 'R'}}, /* L Left */
	{{'O', 'O'}, {'O', 'O'}}, /* R Right */
};

/* REFERENCE
	     UP
	   +--------+
	  / W2  W4 / |RIGHT
	 / W1  W3 /B2|
	+--------+B1 |  FRONT
BACK| R1  R2 | B4|
	| LEFT   |B3 +
	| R3  R4 | /
	+--------+ 
	   DOWN
cube[FRONT][0][0] TOP LEFT B
{{'B1', 'B2'}, {'B3', 'B4'}}, F Front
{{'G', 'G'}, {'G', 'G'}}, B Back
{{'W1', 'W2'}, {'W3', 'W4'}}, U Up
{{'Y', 'Y'}, {'Y', 'Y'}}, D Down
{{'R', 'R'}, {'R', 'R'}}, L Left
{{'O', 'O'}, {'O', 'O'}}, R Right 

		BACKSIDE
	    
	     DOWN
	   +--------+
	  / Y2  Y4 / |LEFT
	 / Y1  Y3 /G3|
	+--------+G4 |  BACK
FRON| O4  O3 | G1|
	| RIGHT  |G2 +
	| O2  O1 | /
	+--------+ 
	   UP




*/



void rotateCube(char axis, int counterclockwise){
	/* X Y Z rotate cube about R U F */
	/* DONE */
	if (axis == 'X'){
		if (counterclockwise == 1){

			/* rotate faces */
			rotateFace(cube[RIGHT], 1); /*right side cc*/
			rotateFace(cube[LEFT], 0); /*left side clockwise*/

			
			/* rotate CC along X axis */
			swapSide(cube[BACK], cube[DOWN]); /* G <-> Y */
			swapSide(cube[DOWN], cube[FRONT]); /* G <-> B */
			swapSide(cube[FRONT], cube[UP]); /* G <-> W */

			rotateFace(cube[BACK], 0);
			rotateFace(cube[UP], 0);
			rotateFace(cube[UP], 0);
			rotateFace(cube[DOWN], 0);
		} else {

			/* rotate faces */
			rotateFace(cube[RIGHT], 0); /*right clockwise */
			rotateFace(cube[LEFT], 1); /*left cc */

			/* rotate along X axis */
			swapSide(cube[BACK], cube[UP]); /* G <-> W */
			swapSide(cube[UP], cube[FRONT]); /* G <-> B */
			swapSide(cube[FRONT], cube[DOWN]); /* G <-> Y */		
			
			rotateFace(cube[FRONT], 1);
			rotateFace(cube[BACK], 0);
			rotateFace(cube[BACK], 0);
			rotateFace(cube[DOWN], 1);
		}
	}
	/* DONE */
	if (axis == 'Y'){
		if (counterclockwise == 1){
			/* rotate faces */
			rotateFace(cube[UP], 1);
			rotateFace(cube[DOWN], 0);
	
			/* rotate CC along Y axis */
			swapSide(cube[FRONT], cube[LEFT]); /* B <-> R */
			swapSide(cube[LEFT], cube[BACK]); /* B <-> G */
			swapSide(cube[BACK], cube[RIGHT]); /* B <-> O */


		} else {
			/* rotate faces */
			rotateFace(cube[UP], 0);
			rotateFace(cube[DOWN], 1);

			/* rotate along Y axis */
			swapSide(cube[FRONT], cube[RIGHT]); /* B <-> O */
			swapSide(cube[RIGHT], cube[BACK]); /* B <-> G */
			swapSide(cube[BACK], cube[LEFT]); /* B <-> R */

		}
	}

	if (axis == 'Z'){
		if (counterclockwise == 1){
			/* rotate faces */
			rotateFace(cube[FRONT], 1);
			rotateFace(cube[BACK], 0);

			/* rotate CC along Z axis */
			swapSide(cube[UP], cube[RIGHT]); /* W <-> O */
			swapSide(cube[RIGHT], cube[DOWN]); /* W <-> Y */
			swapSide(cube[DOWN], cube[LEFT]); /* W <-> R */

			rotateFace(cube[UP], 1);
			rotateFace(cube[LEFT], 1);
			rotateFace(cube[RIGHT], 0);
			rotateFace(cube[RIGHT], 0);

		} else {
			/* rotate faces */
			rotateFace(cube[FRONT], 0);
			rotateFace(cube[BACK], 1);

			/* rotate along Z axis */
			swapSide(cube[UP], cube[LEFT]); /* W <-> R */
			swapSide(cube[LEFT], cube[DOWN]); /* W <-> Y */
			swapSide(cube[DOWN], cube[RIGHT]); /* W <-> O */

			rotateFace(cube[UP], 0);
			rotateFace(cube[DOWN], 0);
			rotateFace(cube[DOWN], 0);
			rotateFace(cube[RIGHT], 0);
		}
	}
}


void turnFrontFace(int counterclockwise){
	if (counterclockwise == 1){
		/* change front side {{'B1', 'B2'}, {'B3', 'B4'}} to {{'B3', 'B1'}, {'B4', 'B2'}} */
		rotateFace(cube[FRONT], 1);

		swap(&cube[LEFT][0][1], &cube[UP][1][1]); /* R2 <-> W4 */
		swap(&cube[UP][1][1], &cube[RIGHT][1][0]); /* R2 <-> O3 */
		swap(&cube[RIGHT][1][0], &cube[DOWN][0][1]); /* R2 <-> Y2 */

		swap(&cube[LEFT][1][1], &cube[UP][1][0]); /* R4 <-> W3 */
		swap(&cube[UP][1][0], &cube[RIGHT][0][0]); /* R4 <-> O1 */
		swap(&cube[RIGHT][0][0], &cube[DOWN][1][1]); /* R4 <-> Y4 */
	} else {

		/* change front side {{'B1', 'B2'}, {'B3', 'B4'}} to {{'B3', 'B1'}, {'B4', 'B2'}} */
		rotateFace(cube[FRONT], 0);

		swap(&cube[LEFT][0][1], &cube[DOWN][0][1]); /* R2 <-> Y2 */
		swap(&cube[DOWN][0][1], &cube[RIGHT][1][0]); /* R2 <-> O3 */
		swap(&cube[RIGHT][1][0], &cube[UP][1][1]); /* R2 <-> W4 */

		swap(&cube[LEFT][1][1], &cube[DOWN][1][1]); /* R4 <-> Y4 */
		swap(&cube[DOWN][1][1], &cube[RIGHT][0][0]); /* R4 <-> O1 */
		swap(&cube[RIGHT][0][0], &cube[UP][1][0]); /* R4 <-> W3 */
	}
}

void printCube(){
	printf("   +------+\n");
	printf("  / %c  %c /|\n", cube[UP][0][1], cube[UP][1][1]);
	printf(" / %c  %c /%c|\n", cube[UP][0][0], cube[UP][1][0], cube[FRONT][0][1]);
	printf("+------+%c |\n", cube[FRONT][0][0]);
	printf("| %c  %c | %c|\n", cube[LEFT][0][0], cube[LEFT][0][1], cube[FRONT][1][1]);
	printf("|      |%c +\n", cube[FRONT][1][0]);
	printf("| %c  %c | /\n", cube[LEFT][1][0], cube[LEFT][1][1]);
	printf("+------+\n"); 

	/*
	printf("	+------+");
	printf("	+------+\n");
	printf("   / %c  %c /|", cube[UP][0][1], cube[UP][1][1]);
	printf("   / %c  %c /|\n", cube[DOWN][0][0], cube[DOWN][0][1]);
	printf("  / %c  %c /%c|", cube[UP][0][0], cube[UP][1][0], cube[FRONT][0][1]);
	printf("  / %c  %c /%c|\n", cube[DOWN][1][0], cube[DOWN][1][1], cube[RIGHT][0][1]);
	printf(" +------+%c |", cube[FRONT][0][0]);
	printf(" +------+%c |\n", cube[RIGHT][0][0]);
	printf(" | %c  %c | %c|", cube[LEFT][0][0], cube[LEFT][0][1], cube[FRONT][1][1]);
	printf(" | %c  %c | %c|\n", cube[BACK][0][0], cube[BACK][0][1], cube[RIGHT][1][1]);
	printf(" |      |%c +", cube[FRONT][1][0]);
	printf(" |      |%c +\n", cube[RIGHT][1][0]);
	printf(" | %c  %c | /", cube[LEFT][1][0], cube[LEFT][1][1]);
	printf("  | %c  %c | /\n", cube[BACK][1][0], cube[BACK][1][1]);
	printf(" +------+");
	printf("    +------+\n"); */

}

void turnFace(char face, int counterclockwise){
	if (face == 'F'){
		turnFrontFace(counterclockwise);
	}
	if (face == 'B'){
		rotateCube('Y', 0);
		rotateCube('Y', 0);
		turnFrontFace(counterclockwise);
		rotateCube('Y', 0);
		rotateCube('Y', 0);
	}
	if (face == 'L'){
		rotateCube('Y', 1);
		turnFrontFace(counterclockwise);
		rotateCube('Y', 0);
	}
	if (face == 'R'){
		rotateCube('Y', 0);
		turnFrontFace(counterclockwise);
		rotateCube('Y', 1);
	}
	if (face == 'U'){
		rotateCube('X', 1);
		turnFrontFace(counterclockwise);
		rotateCube('X', 0);
	}
	if (face == 'D'){
		rotateCube('X', 0);
		turnFrontFace(counterclockwise);
		rotateCube('X', 1);
	}
}

void printData(char cube[2][2]){
	int i;
	int j;
	printf("{");
	for (i = 0; i < 2; i++){
		printf("{");
		for (j = 0; j < 2; j++){
			printf("%c", cube[i][j]);
		}
		printf("}");
	}
	printf("}\n");
}

void printAway(){
	printf("this is how the back of the cube looks!\n");
	printf("   +------+\n");
	printf("  / %c  %c /|\n", cube[DOWN][0][0], cube[DOWN][0][1]);
	printf(" / %c  %c /%c|\n", cube[DOWN][1][0], cube[DOWN][1][1], cube[RIGHT][1][1]);
	printf("+------+%c |\n", cube[RIGHT][1][0]);
	printf("| %c  %c | %c|\n", cube[BACK][0][0], cube[BACK][0][1], cube[RIGHT][0][1]);
	printf("|      |%c +\n", cube[RIGHT][0][0]);
	printf("| %c  %c | /\n", cube[BACK][1][0], cube[BACK][1][1]);
	printf("+------+\n");
}

/* X */
void testX(){
	turnFace('F', 0);
	rotateCube('X', 1);
	turnFace('F', 0);
	rotateCube('X', 0);
	rotateCube('Y', 1);
	turnFace('F', 0);
	rotateCube('X', 1);
}

/* X */
void testZ(){
	turnFace('F', 0);
	rotateCube('Z', 1);
	turnFace('F', 0);
	rotateCube('Z', 0);
	rotateCube('Y', 1);
	turnFace('F', 0);
	rotateCube('Z', 1);
}

void test3(){
	turnFace('B', 0);
	turnFace('R', 0); /*flipped?*/
	rotateCube('X', 0);
	turnFace('L', 0);
	turnFace('F', 0);
}

int isSolved(){
	int i = 0;
	for (i = 0; i < 6; i++){
		if (cube[i][0][0] != cube[i][0][1] || cube[i][0][0] != cube[i][1][0] || cube[i][0][0] != cube[i][1][1] || cube[i][0][1] != cube[i][1][0] || cube[i][0][1] != cube[i][1][1] || cube[i][1][0] != cube[i][1][1])
			return 0;
	}
	return 1;
}


int main(int argc, char *argv[]) {
	int i = 0;
	if (argc > 1){
		while (argv[1][i] != '\0'){
			if (argv[1][i] == 'X' || argv[1][i] == 'Y' || argv[1][i] == 'Z'){
				/* check for next token */
				if (argv[1][i+1] == '+'){
					rotateCube(argv[1][i], 1);
					i++;
				}
				else if (argv[1][i+1] == '2'){
					rotateCube(argv[1][i], 0);
					rotateCube(argv[1][i], 0);
					i++;
				}
				else
					rotateCube(argv[1][i], 0);
			}
			else{
				if (argv[1][i+1] == '+'){
					turnFace(argv[1][i], 1);
					i++;
				}
				else if (argv[1][i+1] == '2'){
					turnFace(argv[1][i], 0);
					turnFace(argv[1][i], 0);
					i++;
				}
				else
					turnFace(argv[1][i], 0);
			}
			i++;
		}
	}
	printCube();
	if (isSolved())
		printf("Hurrah!");
	return 0;
}