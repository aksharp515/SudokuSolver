//Akshar Patel
//Created December 2013 to January 2014
//Code attempts to solve a sudoku board using a smarter, recursive, brute force 
//algorithm that fills in possible numbers and re-evaluates the board until the
//board is no longer solvable than goes backwards and changes numbers to move further

//Does not work all of the time, can be a bit buggy at times, given few numbers and 
//given most numbers the program can solve it but in between it can get caught in a
//cycle, not sure why. 

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

//determine for each pos, a list of numbers that could be the value

//for all sets, ie row column matrix

//STRUCT for later parts
struct Spot
{
	int row;
	int col;
	int poss[9];
	int numposs;
	int val;
};
//NECESSARY FOR COMPARING
//////////////////////DETERMINE NUMBER IN SEQUENCE///////////////
int determinePos(int first, int second)
{
	if (first == 0)
	{
		return (second + 1);
	}
	else if (first == 1)
	{
		int n = 3 + (second + 1);
		return n;
	}
	else
	{
		int n = 6 + (second + 1);
		return n;
	}
	return 0;
}

int determineMatPos(int row, int col)
{
	int rowdiv = row / 3;
	int coldiv = col / 3; 
	
	int result = (coldiv * 3) + rowdiv;
	//cout << "result " << result << endl;///////////////////////////////DEBUGG
	return result;
}
///////////////////////////////Rotate through////////////////////////////
void rotatePos(int &first , int &second)
{
	if (second >= 2 && first>=2)
	{
		second = 0; 
		first = 0;
	}
	else if (second == 2)
	{
		first++;
		second = 0;
	}
	else
	{
		second++;
	}
}

void setBoard(int board[3][3][3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					cin >> board[i][j][k][l];
				}
			}
			
		}		
	}
}

//////////////////////////////// Print Functions//////////////////////////
////////////////////////////////BOARD //////////////////////
void printBoard(int  board[3][3][3][3])
{
	cout << "    1 2 3   4 5 6   7 8 9 " << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "  +-------+-------+-------+" << endl;
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					if (k == 0 && l==0)
					{
						cout << (((3 * (i)) + j) + 1) << " | ";
					}
					if (board[i][j][k][l] == 0)
					{
						cout << "-";
					}
					else
					{
						cout << board[i][j][k][l];
					}
					cout << " ";
				}
				cout << "| ";
			}
			cout << endl;
		}
	}
	cout << "  +-------+-------+-------+" << endl;
}

//////////////////////////////////PRINT ROW/////////////////////////////
void printRow(int board[3][3][3][3], int rownumb)
{
	rownumb--;
	int i = rownumb / 3;
	int j = rownumb % 3;
	int k = 0;
	int l = 0;
	for (int n = 0; n < 9; n++)
	{
		cout << board[i][j][k][l] << " ";
		rotatePos(k, l);
	}
	cout << endl;
}

///////////////////////////////////PRINT COLUMN///////////////////////////
void printCol(int board[3][3][3][3], int colnumb)
{
	colnumb--;
	int k = colnumb / 3;
	int l = colnumb % 3;
	int i = 0;
	int j = 0;
	for (int n = 0; n < 9; n++)
	{
		cout << board[i][j][k][l] <<endl;
		rotatePos(i, j);
	}
}

///////////////////////////////////////PRINT MATRIX/////////////////////////
void printMat(int board[3][3][3][3], int matnumb)
{
	matnumb--;
	int i = matnumb / 3;
	int k = matnumb % 3;
	int j = 0;
	int l = 0;
	for (int n = 0; n < 9; n++)
	{
		cout << board[i][j][k][l] << endl;
		rotatePos(j, l);
	}
}


//////////////////////////////CHECKING IF CORRECT FUNCTiONS/////////////////////////////////
//////////////////////////////CHECK ROW////////////////////////////////////
bool checkRow(int board[3][3][3][3], int rownumb)
{
	rownumb--;
	int i = rownumb / 3;
	int j = rownumb % 3;
	//starting with first spot 0 , 0
	int fk = 0;
	int fl = 0;
	//starting with second spot, 0,1
	int sk = 0;
	int sl = 0;
	for (int m = 0; m < 9; m++)
	{
		//write determine position figure out which spot number in the row
		for (int n =determinePos(sk, sl); n < 9; n++)//by def, 0, 0 returns 1
		{
			rotatePos(sk, sl);
			if ((board[i][j][fk][fl] == board[i][j][sk][sl]) && (board[i][j][fk][fl !=0]))
			{
				return false;
			}
		}
		rotatePos(fk, fl);
		//reset them to the first value 
		//once in the loop they will be rotated
		sk = fk;
		sl = fl;
	}
	return true;
}

//////////////////////////////////CHECK COLUMN////////////////////////
bool checkCol(int board[3][3][3][3], int colnumb)
{
	colnumb--;
	int k = colnumb / 3;
	int l = colnumb % 3;
	//starting with first spot 0 , 0
	int fi = 0;
	int fj = 0;
	//starting with second spot, 0,1
	int si = 0;
	int sj = 0;
	for (int m = 0; m < 9; m++)
	{
		//write determine position figure out which spot number in the row
		for (int n = determinePos(si, sj); n < 9; n++)//by def, 0, 0 returns 1
		{
			rotatePos(si, sj);
			//if not 0 and not equal return false
			//else dont do anything
			if ((board[fi][fj][k][l] == board[si][sj][k][l]) && (board[si][sj][k][l] != 0))
			{
				return false;
			}
		}
		rotatePos(fi, fj);
		//reset them to the first value 
		//once in the loop they will be rotated
		si = fi;
		sj = fj;
	}
	return true;
}

////////////////////////////////////CHECK MATRIX//////////////////////////////
bool checkMat(int board[3][3][3][3], int matnumb)
{
	matnumb--;
	int i = matnumb / 3;
	int k = matnumb % 3;
	//starting with first spot 0 , 0
	int fj = 0;
	int fl = 0;
	//starting with second spot, 0,1
	int sj = 0;
	int sl = 0;
	for (int m = 0; m < 9; m++)
	{
		//write determine position figure out which spot number in the row
		for (int n = determinePos(sj, sl); n < 9; n++)//by def, 0, 0 returns 1
		{
			rotatePos(sj, sl);
			//if not 0 and not equal return false
			//else dont do anything
			if ((board[i][fj][k][fl] == board[i][sj][k][sl]) && (board[i][sj][k][sl] != 0)) 
			{
				return false;
			}
		}
		rotatePos(fj, fl);
		//reset them to the first value 
		//once in the loop they will be rotated
		sj = fj;
		sl = fl;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////COPY FUNCTION/////////////////////
/////////////////////////////////////////////////////////////////////////
void copyboard(int board[3][3][3][3], int newboard[3][3][3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					newboard[i][j][k][l] = board[i][j][k][l];
				}
			}

		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////WHAT NUMBERS ARE NOT INSIDE THE ROW COLUMN OR MATRIX/////////////////////
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////DETERMINE POSS ROW NUMBERS//////////////////////////////////
void possRow(int board[3][3][3][3], int * poss, int rownumb, int colnumb)
{
	//colnumb--;
	//rownumb--;
	int i = colnumb / 3;
	int j = colnumb % 3;
	int k = 0;
	int l = 0;
	int count = 0;
	for (int n = 0; n < 9; n++)
	{
		count = 0;
		for (int m = 0; m < 9; m++)
		{
			//cout << board[i][j][k][l] << endl;//////////////////////////////////////////DEBUG
			if (board[i][j][k][l] != (n+1))
			{
				count++;
			}
			if (count == 9)//number is not in row at all
			{
				*(poss + n) = (n + 1);
			}
			if (m == 8 && count != 9)//number is in row
			{
				*(poss + n) = 0;//set the number to 0
			}
			rotatePos(k, l);
		}
		//reset k and l
		k = 0;
		l = 0;
	}
}

////////////////////////////////DETERMINE NUMBERS COLUMN////////////////////////////////
void possCol(int board[3][3][3][3], int * poss, int rownumb, int colnumb)
{
	//colnumb--;
	//rownumb--;
	int i = 0;
	int j = 0;
	int k = rownumb / 3;
	int l = rownumb % 3;
	int count = 0;
	for (int n = 0; n < 9; n++)
	{
		count = 0;
		for (int m = 0; m < 9; m++)
		{
			if (board[i][j][k][l] != (n + 1))
			{
				count++;
			}
			if (count == 9)//number is not in row at all
			{
				*(poss + n) = (n + 1);
			}
			if (m == 8 && count != 9)//number is in row
			{
				*(poss + n) = 0;//set the number to 0
			}
			rotatePos(i, j);
		}
		//reset j and l
		i = 0;
		j = 0;
	}
}

//////////////////////DETERMINE POSS MATRIX NUMBERS////////////////////////
void possMat(int board[3][3][3][3], int *poss, int row, int col)
{
	int mat = determineMatPos(row, col);
	//cout << endl;////////////////////////////////////////DEBUG
	//cout << "mat numb "<< mat << endl;/////////////////////////////////////////////DEBUG
	int i = mat / 3;
	int k = mat % 3; 
	int j = 0;
	int l = 0;
	int count = 0;
	for (int n = 0; n < 9; n++)
	{
		count = 0;
		for (int m = 0; m < 9; m++)
		{
			//cout << board[i][j][k][l] << endl;//////////////////////////////////////////DEBUG
			if (board[i][j][k][l] != (n + 1))
			{
				count++;
			}
			if (m==8 && count == 9)//number is not in row at all
			{
				*(poss + n) = (n + 1);
			}
			if (m == 8 && count != 9)//number is in row
			{
				*(poss + n) = 0;//set the number to 0
			}
			rotatePos(j, l);
		}
		//reset j and l
		j = 0;
		l = 0;
	}
}
//////////RETURNS NUMBER OF VALUES POSSIBLE IN row,col/////////////
int possTot(int board[3][3][3][3], int col, int row, int poss[9])
{
	row--;
	col--;
	int count = 0;
	int poss_Row[9];
	int poss_Col[9];
	int poss_Mat[9];
	if (board[row / 3][row % 3][col / 3][col % 3] == 0)
	{	
		possRow(board, poss_Row, col, row);
		possCol(board, poss_Col, col, row);
		possMat(board, poss_Mat, col, row);
		/*
		for (int i = 0; i < 9; i++)
		{
		if (*(poss_Row + i) != 0)
		{
		cout << *(poss_Row + i) << " ";
		}
		}
		cout << endl;
		for (int i = 0; i < 9; i++)
		{
		if (*(poss_Col + i) != 0)
		{
		cout << *(poss_Col + i) << " ";
		}
		}
		cout << endl;
		for (int i = 0; i < 9; i++)
		{
		if (*(poss_Mat + i) != 0)
		{
		cout << *(poss_Mat + i) << " ";
		}
		}
		cout << endl;
		cout << "common numbers" << endl;
		*/
		for (int i = 0; i < 9; i++)
		{
			//all numbers are in the arrays and are not 0
			if ((*(poss_Row + i) == *(poss_Col + i)) && (*(poss_Col + i) == *(poss_Mat + i)) && (*(poss_Col + i) != 0))
			{
				//cout << *(poss_Col + i) << " "; //////////////////////////////DEBUG
				*(poss + i) = *(poss_Col + i);
				count++;
			}
			else
			{
				*(poss + i) = 0;
			}
		}
	}
	else//number was already taken..
	{
		for (int i = 0; i < 9; i++)
		{
			*(poss + i) = 0;
		}
		count = 1;
	}
	return count;
}

void setSpots(int board[3][3][3][3], Spot bspot[3][3][3][3])
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			//cout << board[row / 3][row % 3][col / 3][col % 3] << " ";/////////////DEBUG
			bspot[row / 3][row % 3][col / 3][col % 3].val = board[row / 3][row % 3][col / 3][col % 3];
			bspot[row / 3][row % 3][col / 3][col % 3].row = row+1;
			bspot[row / 3][row % 3][col / 3][col % 3].col = col+1;
			int x = possTot(board, col+1, row+1,bspot[row / 3][row % 3][col / 3][col % 3].poss);
			bspot[row / 3][row % 3][col / 3][col % 3].numposs = x;
		}
		//cout << endl;
	}
}

void printSpot(Spot bspot[3][3][3][3], int col, int row)
{
	cout << "List of possible values for " << col+1 << ", " << row+1 << endl;
	for (int i = 0; i < 9; i++)
	{
		if (*(bspot[row / 3][row % 3][col / 3][col % 3].poss + i) != 0)
		{
			cout << *(bspot[row / 3][row % 3][col / 3][col % 3].poss + i) << " ";
		}
	}
	cout << endl;
	cout << "For a total of "<< bspot[row / 3][row % 3][col / 3][col % 3].numposs << " values" <<endl;
}

void printAllSpot(Spot bspot[3][3][3][3])
{
	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			printSpot(bspot, r, c);
		}
	}
}

double numCombinations(Spot bspot[3][3][3][3])
{
	double result = 1;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			result *= bspot[i / 3][i % 3][j / 3][j % 3].numposs;
		}
	}
	return result;
}
 
void findLeast(Spot bspot[3][3][3][3])
{
	int i = 0;
	int j = 0;
	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			if (bspot[r / 3][r % 3][c / 3][c % 3].numposs < bspot[i / 3][i % 3][j / 3][j % 3].numposs)
			{
				i = r;
				j = c;
			}
		}
	}
}


bool ifPoss(Spot bspot[3][3][3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					if (bspot[i][j][k][l].numposs == 0)
					{
						return false;
					}
				}
			}

		}
	}
	return true;
}
/*
have a true value for the struct Spot, then have another struct with a bool for the the possible numbers
rotate through until the 

*/
int getNumber(Spot spot[3][3][3][3], int row, int col)
{
	return 2;
}
int main()
{
	int board[3][3][3][3];
	int newboard[3][3][3][3];
	setBoard(board);
	copyboard(board, newboard);
	printBoard(board);
	/*
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					cout << board[i][j][k][l];
					cout << " ";
				}
				cout << " ";
			}
			cout << endl;
		}
	}
	*/
	bool gameplay = true;
	int replace = 0;
	int row = 0;
	int col = 0;
	/*
	printRow(board, 5);//Test Print row
	printCol(board, 5);

	cout << checkRow(board, 4) << endl;
	cout << checkCol(board, 4) << endl;
	cout << checkMat(board, 1) << endl;
	
	
	int poss[9];
	cout << "using func" << endl;
	int x = possTot(board, 4,1, poss);
	cout << x << endl;
	for (int i = 0; i < 9; i++)
	{
		if (*(poss + i) != 0)
		{
			cout << *(poss + i) << " ";
		}
	}
	cout << endl;
	*/

	row = 7;
	col = 3;
	cout << "board spot 4 8 ";
	cout << board[row / 3][row % 3][col / 3][col % 3] << endl;
	Spot bspot[3][3][3][3];
	cout << "spots" << endl;
	
	setSpots(board, bspot);
	//printSpot(bspot, 5, 3);
	//printSpot(bspot, 4, 2);
	//printSpot(bspot, 1, 1);
	
	printAllSpot(bspot);
	cout << "number of combos "<<numCombinations(bspot) << endl;
	cout << ifPoss(bspot) << endl;
	/*	row = 3;
	col = 5;
	x = possTot(board, row, col, poss);
	cout << "not spots" << endl;
	cout << x << endl;
	for (int i = 0; i < 9; i++)
	{
		if (*(poss + i) != 0)
		{
			cout << *(poss + i) << " ";
		}
	}
	cout << endl;
	cout << "for spots" << endl;
	row--;
	col--;
	printSpot(bspot, 0, 0);
	for (int i = 0; i < 9; i++)
	{
		if (*(bspot[row / 3][row % 3][col / 3][col % 3].poss + i) != 0)
		{
			cout << *(bspot[row / 3][row % 3][col / 3][col % 3].poss + i) << " ";
		}
	}
	cout << endl;
	cout << "end of values " << endl;
	cout << board[row / 3][row % 3][col / 3][col % 3] << endl;
	cout << bspot[row / 3][row % 3][col / 3][col % 3].numposs << endl;
	cout << bspot[row / 3][row % 3][col / 3][col % 3].row << endl;
	cout << bspot[row / 3][row % 3][col / 3][col % 3].col << endl;
	cout << bspot[row / 3][row % 3][col / 3][col % 3].val << endl;
	cout << endl;
	*/
	//numbers in board rotate through 0,0  0,1 0,2 1,0 1,1 1,2 2,0 2,1 2,2
	//first 2 rotate for columns and second 2 for rows
	//the other 2 use col--/row--; then row/col / 3 and row/col % 3
	//matrices use [matrix/3][0][matrix%3][0] rotate pos with 0s

	/*
	while (gameplay)
	{
		cout << "what number do you want to place"<<endl;
		cin >> replace;
		cout << "where do you want to place it (row col)" << endl;
		cin >> row >> col;
		row = row--;
		col = col--;
		if (row > 8 || row < 0 || col <0 || col>8)
		{
			cout << "you entered an invalid number" << endl;
		}
		else
		{
			if (board[col / 3][col % 3][row / 3][row % 3] == 0)
			{
				newboard[col / 3][col % 3][row / 3][row % 3] = replace;
				printBoard(newboard);
			}
		}
		cout << "do u want to keep goin?? (1 or 0)" << endl;
		cin >> gameplay;		
	}
	*/
 	return 0;
}      


