#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "ncihan_Nesvat_NurettinCihan_hw4_mystack.h"

using namespace std;

void ReadFile(ifstream& in, cellStruct**& file_data, const int& num_of_rows, const int& num_of_cols) 
{
	//precondition: file is open number of rows and colums are taken as parameters
	//postcondition: a cellstuct is created for each element in the file, cellstruct contains the char from the file, a flag and row,col index of the struct object within the "file_data" matrix
	string line = "";
	char chr;
		
	for (int r = 0; r < num_of_rows; r++)
	{
		getline(in,line);
		istringstream input(line);
		for (int c = 0; c < num_of_cols; c++)
		{
			input >> chr;
			file_data[r][c].info = chr;
			file_data[r][c].flag = false;
			file_data[r][c].row_index = r;
			file_data[r][c].col_index = c;
		}
	}
}

bool FindPath(Stack& cell_stack, string searched, cellStruct** mat, const int num_of_rows, const int num_of_cols)
{
	//precondition: empty cell_stack is taken as a paramter and will be updated accordingly
	//avaiable path is pushed into the cell_stack, flags of the matrix are changed accordingly
	bool found = false;
	
	if(mat[0][0].info == searched[0]) //insert the first element
	{
		cell_stack.push(mat[0][0]);
	}
	else
	{
		return found; //if first element cannot be inserted there's no need to check the rest
	}

	int section = 1; //variable for searched string's sections
	int r = 0; //variable for row indexing
	int c = 0; //variable for column indexing
	while(found == false && mat[0][0].flag == false)
	{
		if(section != searched.length())
		{
			if(c+1 < num_of_cols && mat[r][c+1].flag == false && mat[r][c+1].info == searched[section]) //check right direction
			{
				c++;
				cell_stack.push(mat[r][c]);
				section++;
			}
			else if(r+1 < num_of_rows && mat[r+1][c].flag == false && mat[r+1][c].info == searched[section]) //check down direction
			{
				r++;
				cell_stack.push(mat[r][c]);
				section++;
			}
			else //if both directions fail, do a backtrack and update cell_stack accordingly
			{
				mat[r][c].flag = true;
				cellStruct cell;
				cell = cell_stack.pop();
				if(!cell_stack.isEmpty())
				{
					cell = cell_stack.pop();
					r = cell.row_index;
					c = cell.col_index;
					cell_stack.push(cell);
					section--;
				}
			}
		}
		else
		{
			found = true;
		}

	}
	return found;
}

int main()
{
	int num_of_rows = 0;
	int num_of_cols = 0;

	cout << "Please enter the number of rows: ";
	cin >> num_of_rows;

	cout << "Please enter the number of columns: ";
	cin >> num_of_cols;
	
	string fileName; 
	ifstream in;
	cout << "\nPlease enter the name of the input file that contains the matrix: ";
	bool inValidname = true;
	do
	{
		cin >> fileName;
		in.open(fileName.c_str());
		if (!in.fail())
			inValidname = false;
		else
			cout << "File cannot be opened.\n" << endl << "Please enter the name of the input file again: ";
	} while (inValidname == true); //if file name is invalid, ask again

	bool keepOn = true;
	string searched = "";

	cellStruct** file_data = new cellStruct*[num_of_rows];
	for (int r = 0; r < num_of_rows; r++) //allocate the memory for the matrix
	{
		file_data[r] = new cellStruct[num_of_cols];
	}
	
	ReadFile(in, file_data, num_of_rows, num_of_cols);
	in.close();
	while(keepOn)
	{
		cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
		cin >> searched;
		if(cin.eof()) //if ctrl+z is entered, stop the loop
		{
			keepOn = false;
			cout << "Program ended successfully!\n\n"; 
		}
		else
		{
			Stack stack_data;
			bool found = FindPath(stack_data, searched, file_data, num_of_rows, num_of_cols);
			if(found)
			{
				cout << "The bit string " << searched << " is found following these cells:\n";
				Stack stack_data_revers;
				while(!stack_data.isEmpty())
				{
					cellStruct cell = stack_data.pop();
					cellStruct* new_cell = new cellStruct(cell.info, cell.row_index, cell.col_index);
					stack_data_revers.push(*new_cell); //push the content of the stack_data to stack_data_revers so that printing operation will be in correct order
					delete new_cell;
				}

				while(!stack_data_revers.isEmpty())
				{
					cellStruct cell = stack_data_revers.pop();
					cout << "(" << cell.row_index << "," << cell.col_index << ")\t"; //print the content
				}
				cout << "\n----------------------------------------------------\n";
			}
			else
			{
				cout << "The bit string " << searched << " could not be found." << "\n-------------------------------------------\n";
			}
		} //class destructor is called here

		for (int r = 0; r < num_of_rows; r++) //reset matrix flags so that new searches will be correct
		{
			for(int c = 0; c < num_of_cols; c++)
				file_data[r][c].flag = false;
		}
	}
	for (int i = 0; i < num_of_rows; i++) //deallocate the memory 
	{
		delete[] file_data[i];
	}
	delete[] file_data;
}