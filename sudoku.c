/*
 * Author: Dinesh
 * Program to solve Sudoku using Recursive Backtracking with no Heuristic.
 * It finds all candidate solutions for given empty cell and tries them out one by one. ( Brute Forcing )
 * Simplest Improvement is to find all candidates and start filling the cell with minimum number of candidates ..
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * This function prints the sudoku given
 * WHITE CELL if empty cell
 * Note: Empty cell denoted by '0'
 *
 */
void printSudoku(int sudoku[9][9]){
	printf("\n");
	for ( int i = 0 ; i < 9 ; i ++ ) {
		if ( i == 3 || i == 6 ) {
			for ( int j = 0 ; j < 9 ; j ++ ) {
				if ( j == 3 || j == 6 ) 
					printf("\033[040m \033[0m");
				printf("\033[040m   \033[0m");
			}
			printf("\n");
		}
		for ( int j = 0 ; j < 9 ; j ++ ) {
			if ( j == 3 || j == 6 ) 
				printf("\033[040m \033[0m");
			if ( sudoku[i][j] > 0 )
				printf(" %d ", sudoku[i][j]);
			else 
				printf("\033[047m   \033[0m");
		}
		printf("\n");
	}
}
/*
 * This function is used to print sudoku while reading the input sudoku
 * It colors the specified cell with green
 */
void printReadSudoku(int sudoku[9][9], int x, int y){
	printf("\n");
	for ( int i = 0 ; i < 9 ; i ++ ) {
		if ( i == 3 || i == 6 ) {
			for ( int j = 0 ; j < 9 ; j ++ ) {
				if ( j == 3 || j == 6 ) 
					printf("\033[040m \033[0m");
				printf("\033[040m   \033[0m");
			}
			printf("\n");
		}
		for ( int j = 0 ; j < 9 ; j ++ ) {
			if ( j == 3 || j == 6 ) 
				printf("\033[040m \033[0m");
			if ( sudoku[i][j] > 0 )
				printf(" %d ", sudoku[i][j]);
			else 
				if ( i == x && j == y ) 
					printf("\033[042m   \033[0m");
				else	
					printf("\033[047m   \033[0m");
		}
		printf("\n");
	}
}
/*
 * This function is used to print the final sudoku
 * This function takes initial sudoku as well to color the solution
 */
void printResultSudoku(int sudoku[9][9], int originalSudoku[9][9]){
	printf("\n");
	for ( int i = 0 ; i < 9 ; i ++ ) {
		if ( i == 3 || i == 6 ) {
			for ( int j = 0 ; j < 9 ; j ++ ) {
				if ( j == 3 || j == 6 ) 
					printf("\033[040m \033[0m");
				printf("\033[040m   \033[0m");
			}
			printf("\n");
		}
		for ( int j = 0 ; j < 9 ; j ++ ) {
			if ( j == 3 || j == 6 ) 
				printf("\033[040m \033[0m");
			if ( sudoku[i][j] > 0 )
				if ( originalSudoku[i][j] > 0 )
					printf(" %d ", sudoku[i][j]);
				else 
					printf("\033[047;032m %d \033[0m", sudoku[i][j]);
			else 
				printf("\033[047m   \033[0m");
		}
		printf("\n");
	}
}
// Note: x and y are 0 indexed 
// Assuming value at [x,y] is 0
/*
 * This function finds all candidate solutions at given cell on given sudoku
 * Empty cells denoted by '0'
 */
int validsolutions(int sudoku[9][9], int x, int y, bool candidates[9]) {
	for ( int n = 0 ; n < 9 ; n ++ ) 
		candidates[n] = true; 
	for ( int i = 0 ; i < 9 ; i ++ ) {
		if ( sudoku[i][y] > 0 ) candidates[sudoku[i][y]-1] = false;
		if ( sudoku[x][i] > 0 ) candidates[sudoku[x][i]-1] = false;
	} 
	for ( int i = 0 ; i < 3 ; i ++ ) 
		for ( int j = 0 ; j < 3 ; j ++ )
			if ( sudoku[(x/3)*3 + i][(y/3)*3 + j] > 0 )
				candidates[ sudoku[(x/3)*3 + i][(y/3)*3 + j] - 1] = false;
	int totalcandidates = 0;
	for ( int i = 0 ; i < 9 ; i ++ ) 
		if ( candidates[i] ) totalcandidates ++;
	return totalcandidates;
}
/*
 * THis function simply copies sudoku from 'fromsudoku' to 'tosudoku'
 */
void copySudoku(int fromSudoku[9][9], int toSudoku[9][9]) {
	for ( int i = 0 ; i < 9 ; i ++ )
		for ( int j = 0 ; j < 9 ; j ++ ) 
			toSudoku[i][j] = fromSudoku[i][j];
}

/*
 * This function uses recursive backtracking to solve the sudoku
 */
int choice; // Set this to zero before calling the 'solveSudoku' function
bool solveSudoku(int sudoku[9][9]){
	int tmpSudoku[9][9];
	bool candidates[9];
	int totalcandidates;
	for ( int i = 0 ; i < 9 ; i ++ ) {
		for ( int j = 0 ; j < 9 ; j ++ ) {
			if ( sudoku[i][j] == 0 ) { // If position need to be filled ...
				if ( (totalcandidates = validsolutions(sudoku, i, j, candidates)) == 0 ) return false; // if no solution is possible
				int currentcandidate = 0;
				for ( int x = 0 ; x < 9 ; x ++ ) {
					if ( candidates[x] ) {
						printf("Choice: %d Possible Candidate for [%d,%d] is %d. (%d out of %d candidates)\n",++choice, i, j, x + 1, ++currentcandidate, totalcandidates );
						// This is a possible candidate
						copySudoku(sudoku, tmpSudoku);
						tmpSudoku[i][j] = x + 1 ; // Update the sudoku with possible candidate
						if ( solveSudoku(tmpSudoku) ) {
							// If sudoku solved with this choice
							copySudoku(tmpSudoku, sudoku);
							return true;
						}
					}
				}
				// If no candidate works
				return false; 
			}
		}
	}
}
/*
 * This checks if given sudoku is a valid sudoku or not
 */
bool validSudoku(int sudoku[9][9]){
	bool present[9];
	for ( int i = 0 ; i < 9 ; i ++ ) {
		//  Check Row
		for ( int j = 0 ; j < 9 ; j ++ )
			present[j] = false;
		for ( int j = 0 ; j < 9 ; j ++ ) {
			if ( sudoku[i][j] > 0 )
				if ( present[sudoku[i][j]-1] ) return false; // If number already present
				else present[sudoku[i][j]-1] = true; // Make it present
		}
		//  Check Column
		for ( int j = 0 ; j < 9 ; j ++ )
			present[j] = false;
		for ( int j = 0 ; j < 9 ; j ++ ) {
			if ( sudoku[j][i] > 0 )
				if ( present[sudoku[j][i]-1] ) return false; // If number already present
				else present[sudoku[j][i]-1] = true; // Make it present
		}
		// Check Square
		for ( int j = 0 ; j < 9 ; j ++ )
			present[j] = false;
		for ( int x = 0 ; x < 3 ; x ++ ) 
			for ( int y = 0 ; y < 3 ; y ++ )
				if ( sudoku[(i/3)*3+x][(i%3)*3+y] > 0 )
					if ( present[ sudoku[(i/3)*3+x][(i%3)*3+y] - 1] ) return false;
					else  present[ sudoku[(i/3)*3+x][(i%3)*3+y] - 1] = true ; 
	}
	return true;
}
/*
 * THis function is used to scan sudoku ..
 * Fills zero if empty cell
 */
void scanSudoku(int sudoku[9][9]){
	int value;
	for ( int i = 0 ; i < 9 ; i ++ )
		for ( int j = 0 ; j < 9 ; j ++ )
			sudoku[i][j] = 0;
	for ( int i = 0 ; i < 9 ; i ++ ) {
		for ( int j = 0 ; j < 9 ; j ++ ) {
			printReadSudoku(sudoku, i, j);
			printf("ENTER SUDOKU[%d][%d]:", i+1,j+1);
			if ( scanf("%d",&value) > 0 )
				if ( value > 0 && value < 10 ) 
					sudoku[i][j] = value;
				else 
					sudoku[i][j] = 0;
			else 
				sudoku[i][j] = 0;
		}
	}
	printSudoku(sudoku);
}

int main() {
	int sudoku[9][9];
	int originalSudoku[9][9];
	printf("NOTE: Enter '0' if empty cell\n");
	scanSudoku(sudoku); // Scan the user input sudoku
	printSudoku(sudoku); // Print the scanned sudoku 
	copySudoku(sudoku, originalSudoku); // Keep a copy of original
	if ( validSudoku(sudoku) ) { // Check if valid sudoku
		printf("\033[032mVALID SUDOKU\033[0m\n");
		choice = 0; // Set choice to 0
		if ( solveSudoku(sudoku) ) { // Check if it can be solved ..	
			printf("\033[032mSOLVED SUDOKU\033[0m\n");
			printResultSudoku(sudoku, originalSudoku); // THen print the result
		}
		else {	
			printf("\033[031mNO VALID SUDOKU SOLUTION\033[0m\n");
			printSudoku(sudoku); // Print the partial solution
		}
	}
	else printf("\033[031mINVALID SUDOKU\033[0m\n");
	return 0;
}
