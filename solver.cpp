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
	int iter;
};

void solve(Spot bspot[3][3][3][3], int board[3][3][3][3], int row, int col, int & iter, int & tot);

//Essentially rotates the numbers as a for loop would do
void rotateRowCol(int & row, int & col)
{
	if (col == 8)
	{
		row++;
		col = 0;
	}
	else
	{
		col++;
	}
}
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
////////////////////////////////BOARD + PRETTY THINGS//////////////////////
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
	cout<<endl;
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

bool checkBoard(int board[3][3][3][3], int & row , int & col)
{
	bool result = true;
	for (int i = 0; i < 9 ; i++)
	{
		bool col = checkCol(board, i);
		bool row = checkRow(board, i);
		bool mat = checkMat(board, i);
		if(( col ==false || mat == false)||(row == false))
		{
			cout<<col<<mat<<row<<endl;
			cout<<i<<endl;
			result = false;
			row = i;
			col = i;
		}
	}
	return result;
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
//////////////WHAT NUMBERS ARE NOT INSIDE THE ROW, COLUMN OR MATRIX/////////////////////
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
		count = 10;//count becomes large so that the number is not considered in least amount of possible numbers
	}
	return count;
}

void setSpots(int board[3][3][3][3], Spot bspot[3][3][3][3], int iter)
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			//cout << board[row / 3][row % 3][col / 3][col % 3] << " ";/////////////DEBUG
			bspot[row / 3][row % 3][col / 3][col % 3].val = board[row / 3][row % 3][col / 3][col % 3];
			if (iter == 1)//sets iter to 0 unless told not to change iter
			{
				bspot[row / 3][row % 3][col / 3][col % 3].iter = 0;
			}
			bspot[row / 3][row % 3][col / 3][col % 3].row = row+1;
			bspot[row / 3][row % 3][col / 3][col % 3].col = col+1;
			int x = possTot(board, col+1, row+1,bspot[row / 3][row % 3][col / 3][col % 3].poss);
			bspot[row / 3][row % 3][col / 3][col % 3].numposs = x;
		}
		//cout << endl;
	}
}

//This function checks if the 2 spots have the same possibilites
//because if they do the possibilities are eliminated from the rest of the row col and matrix of each 
//of the two spots
/*
bool checkSamePoss(Spot bspot[3][3][3][3], int row, int col, int checkrow, int checkcol)
{
	bool result = true;
	for (int i = 0; i < 9; i++)
	{
		if (bspot[col / 3][col % 3][row / 3][row % 3].poss[i] != bspot[checkcol / 3][checkcol % 3][checkrow / 3][checkrow % 3].poss[i])
			//if theyre not equal at any point theyre not the same 
		{
			result = false;
		}
	}
	return result;
}

void updatePos(Spot bspot[3][3][3][3])
{

}
*/
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
	//////cout << "For a total of "<< bspot[row / 3][row % 3][col / 3][col % 3].numposs << " values" <<endl;
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
 
void findLeast(Spot bspot[3][3][3][3], int & row, int & col)
{
	int i = 0;
	int j = 0;
	for (int r= 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			if (bspot[c / 3][c % 3][r / 3][r % 3].numposs < bspot[j / 3][j % 3][i / 3][i % 3].numposs)
			{
				i = r;
				j = c;
			}
		}
	}
	//change row and col 
	row = i;
	col = j;
	//i+1 is row j+1 is col
	//cout<<i+1<<j+1<<"row , col"<<endl;
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
find least amount of possible numbers in row and col number 
make recursive function with parameters prevboard and newboard 
have board put in a number and see if the next board is possible 
if not it goes back and goes to next number in line, if 3 then 4 if 9 then 1 

idea is to have a recursive function that checks if it can fill in a number to work 
if not checks the last board to see if it can change that number and then keep going
and the cycle goes on recursively

yea its very intense
*/

int getNumber(Spot bspot[3][3][3][3], int row, int col, int start)
{
	int result = 0;
	int poss = 0;
	for(int i = start; i<9;i++)
	{
		poss = *(bspot[col/3][col%3][row/3][row%3].poss + i);
		if( result == 0 && poss == i+1)
		{
			result = (i+1);
		}
	}
	if (result ==0)
	{
		for(int i = 0; i<start;i++)
		{
			poss = *(bspot[col/3][col%3][row/3][row%3].poss + i);
			if( result == 0 && poss == i+1)
			{
				result = (i+1);
			}	
		}
	}
	return result;
}
/*
int findDiffer(int board[3][3][3][3], int newboard[3][3][3][3], int & row, int & col)
{
	int different = 0;
	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			if (board[c / 3][c % 3][r / 3][r % 3] != newboard[c / 3][c % 3][r / 3][r % 3])
			{
				row = r;
				col = c;
				different = newboard[c / 3][c % 3][r / 3][r % 3];
			}
		}
	}
	cout<<"different is "<<different<<endl;
	return different;
}
*/
//checks which row you previously changed
void checkLastChange(Spot bspot[3][3][3][3], int & row, int & col, int iter)
{
	int currentiter = 0;
	int currentdif = 0;
	int currentlow = iter - bspot[0][0][0][0].iter;
	if (iter ==1)
	{
		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				if (bspot[c / 3][c % 3][r / 3][r % 3].iter == 1)
				{
					row = r;
					col = c;
				}
			}
		}
	}
	else 
	{
		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				if(bspot[c / 3][c % 3][r / 3][r % 3].iter == iter - 1)
				{
					row = r;
					col = c;
				}
			}
		}
	}
}



bool checkFull(int board[3][3][3][3])
{
	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			if (board[c / 3][c % 3][r / 3][r % 3] == 0)
			{
				return false;
			}
		}
	}
	return true; 
}

void goBack(int board[3][3][3][3], Spot bspot[3][3][3][3], int & iter, int & tot)
{
	tot++;
	iter--;
	int row = -1;
	int col = -1;
	int change = 0;
	checkLastChange(bspot,row,col, iter);

	int start = board[col/3][col%3][row/3][row%3]; //its current value 
	board[col/3][col%3][row/3][row%3] = 0;////change last row and col changed back to 0
	if(iter==1)
	{
		setSpots(board,bspot,1);//start the iterations over
	}
	else
	{
		setSpots(board, bspot, 0);//do not change iterations
	}
	bspot[col/3][col%3][row/3][row%3].iter = 0;///change the iter number back to 0
	//cout<<bspot[col/3][col%3][row/3][row%3].numposs<<endl;//////////////////////////////////////////////////////
	//cout<<row<<col<<endl;/////////////////////////////////////////////////////////////////////
	if(bspot[col/3][col%3][row/3][row%3].numposs == 1)
	{
		//cout<<"got here" <<endl;///////////////////////////////////////////////////////
		goBack(board, bspot, iter, tot);
	}
	else
	{
		//cout<<iter<<endl;////////////////////////////////////////////////////////////////////
		//cout<<iter<<" is the iteration"<<endl;///////////////////////////////////////
		change = getNumber(bspot, row, col, start);
		board[col/3][col%3][row/3][row%3] = change;
		if (change == 0)
		{
			cout<<"how"<<endl;
		}
		bspot[col/3][col%3][row/3][row%3].iter = iter;
		//cout<<row<<col<<endl;//////////////////////////////////////////////////////////////////
		solve(bspot, board, row, col, iter, tot);
		printBoard(board);
	}

	
}

void solve(Spot bspot[3][3][3][3], int board[3][3][3][3], int row, int col, int & iter, int & tot)
{
	tot++;
	iter++;
	cout<<"Iteration Number "<<iter<<endl<<endl;
	//row and col refer to the last row and column changed
	/*
	cout<<"original " <<endl;
	printBoard(board);
	cout<<"not original"<<endl;
	printBoard(newboard);
	*/
	setSpots(board, bspot, 0);
	bool isposs = ifPoss(bspot);
	int change = 0;
	int oldrow = 0;
	int oldcol = 0;
	int start = 0;
	
	if (checkFull(board))
	{
		cout<<"ITS FINISHED!!"<<endl;
		cout<<"IN "<< tot<< " STEPS."<<endl;
	}
	else if (checkFull(board) && !checkBoard(board, row, col))
	{
		row = 0;
		col = 0;
		cout<<"It's Done but not right??"<<endl;
		cout<<row<<col<<endl;
	}
	else if ((row == -1 && col == -1) || isposs)
	{
		findLeast(bspot, row, col);
		change = getNumber(bspot, row, col, 0);
		board[col/3][col%3][row/3][row%3] = change;//change the number 
		bspot[col/3][col%3][row/3][row%3].iter = iter;
		printBoard(board);
		cout<<"Change row "<<row<<" and col " <<col << " to "<<change<<endl;
		solve(bspot,board, row, col, iter, tot);
	}
	else if (!isposs)//not possible
	{
		//cout<<"its going in here but not the other"<<endl;
		start = board[col/3][col%3][row/3][row%3];
		change = getNumber(bspot, row, col, start);
		if (change == 0)//there is no other possible number
		{
			goBack(board, bspot, iter, tot);
		}
		else 
		{
			cout<<"not going inside change = 0 "<<endl;
			board[col/3][col%3][row/3][row%3] = change;
			bspot[col/3][col%3][row/3][row%3].val = iter;
			printBoard(board);
			solve(bspot, board, row, col, iter, tot);
		}
	}
	else
	{
		cout<<"who wants to go in here "<<endl;
	}
	
	//reset col and row


}


int main()
{
	int board[3][3][3][3];
	int newboard[3][3][3][3];
	setBoard(board);
	copyboard(board, newboard);
	printBoard(board);
	
	Spot bspot[3][3][3][3];
	bool gameplay = true;
	int replace = 0;
	int row = 0;
	int newrow = 0;
	int newcol = 0;
	int col = 0;
	int iter =0;
	int tot = 0;
	setSpots(board, bspot, 1);
	//printAllSpot(bspot);
	solve(bspot, board,-1, -1, iter, tot);
	
	/*
	row = 7;
	col = 3;
	cout << "board spot 4 8 ";
	cout << board[row / 3][row % 3][col / 3][col % 3] << endl;

	cout << "spots" << endl;
	*/


	
 	return 0;
}      


