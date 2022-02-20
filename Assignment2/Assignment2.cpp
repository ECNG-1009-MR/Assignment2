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



void writedata(vector<vector<int>>& IDvec, vector<vector<int>>& Marksvec, vector<vector<double>> gpa, vector<vector<double>> average)
{
	ofstream output;
	output.open("studentsummary.txt"); // opens summary file
	for (int i = 0; i < IDvec[0].size(); i++)  // loop to determine row to get data from
	{

		output << " Student		ECNG1006	ECNG1009	ECNG1014	ECNG1016	Average		GPA	" << endl;
		output << IDvec[0][i]; // outputs the id number at the i position of the vector
		for (int j = 0; j < 4; j++) // loop to determine column to get data from
		{

			if (Marksvec[j].empty()) //outputs N/A and goes to next value of j if there is no data
			{
				output << "		  N/A";
				continue;

			}

			output << "		   " << Marksvec[j][i]; // outputs data from the j column i row


		}
		output << "		  " << average[0][i] << "		" << gpa[0][i] << endl << endl;

	}
	output.close();


}


int main()
{
	//These two vectors must be declared in which ever fuction 'retrieveData()' is called in.
	vector<vector<int>> IDvec;
	vector<vector<int>> Marksvec;

	retrieveData(IDvec, Marksvec);
	vector<vector<double>> gpa{ {  1.1 ,  1.2 ,  1.3 , 1.4 ,1.5, 1.6, 1.7, 1.8, 1.9  } }; //repalce with real vector

	vector<vector<double>> average { { 2.1 ,  2.2 ,  2.3 , 2.4 ,2.5, 2.6, 2.7, 2.8, 2.9 } }; // repalce with real vector
	//Test cout of the 4th mark in "ecng1014marks.txt"
	cout << Marksvec[2][3];
	writedata(IDvec, Marksvec, gpa , average);

}


