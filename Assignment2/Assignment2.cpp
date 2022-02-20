// Assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;



void retrieveData(vector<vector<int>>& IDvec, vector<vector<int>>& Marksvec)
{
	//Passes the memory address of IDvec and Marksvec into this function. This allows the vectors to be modified in this function
	//IDvec:		//A 2d vector that will contain vectors of ID numbers from each file
	//Marksvec:		//A 2d vector that will contain vectors of marks from each file

	string ID;
	string marks;
	//inputfile is a string array containing names of all txt files
	string inputfile[] = { "ecng1006marks.txt", "ecng1009marks.txt", "ecng1014marks.txt", "ecng1016marks.txt" }; 
	ifstream input[4]; //An array of ifstreams used to loop.
		 
	vector<int> IDvec_sub;			//A 1d vector that is used to temperarily store all ID numbers in each file
	vector<int> Marksvec_sub;		//A 1d vector that is used to temperarily store all marks in each file
	

	//Creates a loop that opens all text files from 'inputfile' array into respective fstream from 'input' array
	for (int j = 0; j < 4; j++)
	{
		input[j].open(inputfile[j]);
	}


	//Loops through all fstreams in the 'input' array
	for (int j = 0; j < 4; j++)
	{
		//verfiy file essists
		if (!input[j].is_open())
			cout << "Cannot open file: " << inputfile[j] << endl;
		else
		{
			cout << "file found: " << inputfile[j] << endl;
		}

		//Input each string from the current 'input' fstream into 'ID' and 'marks' variables.
		//Assuming each string in the file starts with an Id number then marks, it will alternate between inputting into the 'ID' variable and 'marks' variable
		while (input[j] >> ID >> marks)
		{
			//Converts all Id numbers to a long int, and pushes them into a 1d temp vector.
			IDvec_sub.push_back(stol(ID));	
			//Converts all marks to an int, and pushes them into a 1d temp vector.
			Marksvec_sub.push_back(stof(marks));
		}

		//Entire temp vectors are pushed into respective main vectors.
		//This means each element in the main vectors are vectors which contain the values from the temporary vectors.
		IDvec.push_back(IDvec_sub);
		Marksvec.push_back(Marksvec_sub);
		//The temporary vectors are cleared so that the values from the next file in the loop can be inputted.
		IDvec_sub.clear();
		Marksvec_sub.clear();

		//current fstream in loop is closed
		input[j].close();
			
	}
}



/*Part 2: Nathan ---------------------------------------------------------------------------------------
"Calculate the average and GPA for each student using the mark arrays/vectors as input"







--------------------------------------------------------------------------------------------------------*/



/*Part 2: Alex ---------------------------------------------------------------------------------------
 "Write the required information to a student summary file (as shown in assignment 2 file)"







--------------------------------------------------------------------------------------------------------*/


int main()
{
	//These two vectors must be declared in which ever fuction 'retrieveData()' is called in.
	vector<vector<int>> IDvec;
	vector<vector<int>> Marksvec;

	retrieveData(IDvec, Marksvec);
	
	//Test cout of the 4th mark in "ecng1014marks.txt"
	cout << Marksvec[2][3];

}


