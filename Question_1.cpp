#include<iostream>
#include<fstream>
#include<conio.h>
#include<windows.h>
#include<string>
using namespace std;

int main(){

	string nameOfInputFile, currentWord;
    char grid[10][10];
    string words[10];


	cout << "Enter the name of text file to load the words: ";
	cin >> nameOfInputFile;
	if(nameOfInputFile.size() >=4 && (nameOfInputFile.substr(nameOfInputFile.size() - 4, 4) != ".txt"))
	{
		nameOfInputFile += ".txt";
	}
	ifstream inputFile(nameOfInputFile.c_str());
	if(!inputFile)
	{
		cout << "Text file could not be loaded. Please verify its name and location.\n";
		system("pause>0");
		return 0;
	}
	while(!inputFile.eof())
	{
        for(int i=0; i<10; i++){
		getline(inputFile, currentWord);
              words[i]=currentWord;       //store the currentword from file into a string array of words
        }
         
	}
     int count=0;  
	char alpha;
    //random words generate
	for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            int randomNum;
            randomNum= rand() % 26;   // generate a random number
            alpha= 'a' + randomNum;    // Convert to a character from a-z
            grid[i][j]=alpha;
        }
    }
     while(count!=5)   //to generate more than one word and store it in the grid
     {
    int index = rand() % 10;  //to generate a random word from string array of words
	string display = words[index];     
    //for storing word horizontally 
	if (words[index].length() % 2 == 0) //to make sure the word will fit in the given range in rows
	{
		
		int row = rand() % 10;  //generating  a row number in range
		int col = rand() % 2;    //generating  a column number in range
		for (int i = 0; display[i] != '\0'; i++, col++)
		{
			grid[row][col] = display[i];  
        }
	}
    //storing the word vertically in grid
	else if(words[index].length() % 3 == 0)   //to make sure the word will fit in the given range in columns
	{
		int row = rand() % 2;
		int col = rand() % 10;
		for (int i = 0; display[i] != '\0'; i++, row++)
		{
			grid[row][col] = display[i];
		}
	}
    //Storing the word diagonally
    else if (words[index].length() % 5 == 0)  //to make sure the word will fit in the given range diagonally
	{
		
		int row;
		row = rand() % 3;  // generate random row number (in range) for the word to be stored diagonally
        for(int i=0; display[i]!='\0'; i++, row++){
            grid[row][row]=display[i];
        }
	}
    count++;
    }
    // writing the grid in a output.txt file
    ofstream file("output.txt");
	file << "---------WORD SEARCH GRID--------" << endl<<endl;
    for (int y = 0; y < 10; y++) {
        file<< "\t\t";
        for (int x = 0; x < 10; x++)
        {
            file << grid[x][y]<<" ";
        }
        file << endl;
    }
    file<< "-----------------------------------"<<endl;
    cout<<"File created with stored grid of words!"<<endl;
    file.close();
     
	system("pause>0");
	return 0;

    
}