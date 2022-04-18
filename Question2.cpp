#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<cstdlib>
#include<windows.h>

using namespace std;
void displayBoard(char** grid, int rows, int col);
int strlength(char* str);
void ShowCordinates(char** list, int numberOfWords, char** grid, int rows, int cols);
char** ReadFile(int rows, int col, int readline);
char** words(int testcases, int readline);
void ShowCordinates(char** list, int numberOfWords, char** grid, int rows, int cols);
int* GridSearch(char** grid, int gridRow, int gridCol, char* word);
int* SearchAllDirections(char** grid, int gridRow, int gridCol, int row, int col, char* word);
void PlayGame();
void startDisplay();


void startDisplay()
{
	char choice;
	cout << "\n\t\t\t*******************WORD-SEARCH-GAME*********************\n";
	a:
		cout << "\n\t\t\t\t\tPress 'A' To play \n";
		cout << "\n\t\t\t\t\tPress 'E' to exit\n";
		choice = _getch();
		switch (choice)
		{
		case 'A':
			PlayGame();
			break;
		case 'E':
			cout << "\t\t\t\t\tGAME ENDED!!\n";
			system("pause");
			break;
		default:
			cout << "\tInvalid Input. Enter again\n";
			goto a;
			break;
		}

}
void PlayGame()
{
	int rows, col, word;
	int readline = 2;
	char** matrix = 0;
	char** list = 0;
	ifstream fin("Input2.txt");
	if (fin.is_open())
	{
		fin >> rows >> col >> word;
		matrix = ReadFile(rows, col, readline);
		readline = 2 + rows;
		list = words(word, readline);
		displayBoard(matrix, rows, col);
		ShowCordinates(list, word, matrix, rows, col);
	}
	else
	{
		cout << "No file found\n";
	}
}
int strlength(char* str)   //function to calculate stringlength
{
	int length=0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		length++;
	}
	return length;
}
char** ReadFile(int rows,int col,int readline)
{
	ifstream fin("Input2.txt");
	string temporaryLine;
	for (int i = 0; i < readline; i++) //this skips all the data before grid
	{
		getline(fin, temporaryLine);
	}
	char** matrix = new char* [rows];	
	char ch;
	if (fin.is_open())
		{
			for (int i = 0; i < rows; i++)
			{
				matrix[i] = new char[col];
				for (int j = 0; j < col; j++)
				{
					fin >> ch;
					matrix[i][j] = ch;
				}
			}
			fin.close();
		}
		else
		{
			cout << "No file found\n";
		}
	return matrix;
}
char** words(int testcases, int readline)
{
	ifstream fin("Input2.txt");
	char** wordList = new char* [testcases];
	if (fin.is_open())
	{
		string tempLine;
		for (int i = 0; i < readline; i++)      //this skips all the data before words 
		{
			getline(fin, tempLine);
		}
		for(int i=0;i<testcases;i++)
		{
			char str[80];
			fin.getline(str, 80);
			int cols = 0;
			cols = strlength(str);
			wordList[i] = new char[cols + 1];

			int j = 0;
			for (j = 0; j < cols; j++) // copying data
			{
				wordList[i][j] = str[j];
			}
			wordList[i][j] = '\0';
		}
	}
	else {
		cout << "No file found\n";
	}
	return wordList;

}
void displayBoard(char **grid,int rows,int col)
{    cout<<"\n";
	for (int i = 0; i < rows; i++)
	{
        cout<<"\t\t\t\t\t";
		for (int j = 0; j < col; j++)
		{
			cout  << grid[i][j] << " ";
			Sleep(30);
		}
		cout << '\n';
	}
}
   
void ShowCordinates(char** list, int numberOfWords, char** grid, int rows, int cols)  //function to show start and cordinates  of a word
{
	int index;
	for (int i = 0; i < numberOfWords-1; i++)
	{
		cout << "Enter " << i + 1 << " for word " << list[i] << " to be found\n";
	}
	cin >> index;
	int* resultArr = new int[4];
	resultArr = GridSearch(grid, rows, cols, list[index]);  //this function returns the cordinates

	if (resultArr[0] == -1)
	{
		cout << "NOT FOUND";
	}
	else
	{
		cout << "{" << resultArr[0] << "," << resultArr[1] << "}" << "{" << resultArr[2] << "," << resultArr[3] << "}";
	}
	cout << '\n';
	char choice;
		cout << "Press any key to continue\n";
		choice = getch();
	    	startDisplay();
			delete[]resultArr;
	
}

int* SearchAllDirections(char** grid, int gridRow, int gridCol, int row, int col, char* word)
{
	int rowDirection[] = { 0, 0, 1,-1, 1, 1, -1, -1 };     // 8 directions  in the order (right to left),(left to right),(top to bottom),(bottom to top),(top left to bottom right),(top right to bottom left),(bottom left to top right),(bottom right to top left)
	int colDirection[] = { -1, 1, 0, 0, 1, -1, 1, -1 };

	int* arr = new int[3];    //this array will keep have 1 at 0 position if word is found and record of the end cordinates of the word
							 //if word not found then the array wil will have -1 at 0 position

	if (grid[row][col] != word[0])   //checks if the cordinate have the first letter of word 
	{
		arr[0] = -1;
		arr[1] = 0;
		arr[2] = 0;
		return  arr;
	}


	int length = strlength(word);


	for (int i = 0; i < 8; i++)  //for 8 directions
	{
		int j;
		int moveRow = row + rowDirection[i];
		int moveCol = col + colDirection[i];

		// First character is already checked, match remaining 
		// characters 
		for (j = 1; j < length; j++)  //as first letter is found so starting form 1
		{
			// If out of bound break 
			if (moveRow >= gridRow || moveRow < 0 || moveCol >= gridCol || moveCol < 0)
			{
				break;
			}


			// If not matched,  break 
			if (grid[moveRow][moveCol] != word[j])
			{
				break;
			}



			moveRow = moveRow + rowDirection[i];   //moves in the specuific direction 
			moveCol = moveCol + colDirection[i];
		}


		if (j == length) //if the word is found then j will be equal to length
		{
			moveRow = moveRow - rowDirection[i];
			moveCol = moveCol - colDirection[i];

			arr[0] = 1;
			arr[1] = moveRow;   //end cordinates of the word
			arr[2] = moveCol;

			return arr;
		}

	}
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;
	return  arr;
}
int* GridSearch(char** grid, int gridRow, int gridCol, char* word)  //this function searches all words
{
	int* returnArray = new int[4];
	int* arr = new int[3];

	for (int row = 0; row < gridRow; row++)
	{
		for (int col = 0; col < gridCol; col++)
		{
			arr = SearchAllDirections(grid, gridRow, gridCol, row, col, word);
			if (arr[0] == 1)
			{
				returnArray[0] = row;  //start cordinates of word
				returnArray[1] = col;

				returnArray[2] = arr[1];  //end codinates of the word
				returnArray[3] = arr[2];
				return returnArray;
			}

		}

	}
	delete[]arr;
	returnArray[0] = -1;
	returnArray[1] = 0;
	returnArray[2] = 0;
	returnArray[3] = 0;
	return returnArray;

}
int main(){
    startDisplay();
    return 0;
}