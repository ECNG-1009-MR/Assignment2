// Assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;


//Function forward declarations
void retrieveData(vector<vector<int>>& IDvec, vector<vector<int>>& Marksvec);
void GPACalculation(vector<vector<int>>& Marksvec, vector<double>& average, vector<float>& gpa);
void writedata(vector<vector<int>>& IDvec, vector<vector<int>>& Marksvec, vector<float> gpa, vector<double> average);

int main()
{
	vector<double> average;
	vector<float> gpa;
	vector<vector<int>> IDvec;
	vector<vector<int>> Marksvec;

	retrieveData(IDvec, Marksvec);
	GPACalculation(Marksvec, average, gpa);
	writedata(IDvec, Marksvec, gpa, average);


	return 0;
}


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
		//verfiy file exists
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


void GPACalculation(vector<vector<int>>& Marksvec, vector<double> &average, vector<float> &gpa)
{
	

	int N;
	float totalGrade;
	float totalqPoints;
	float qPoints_temp;

	float qPoints[11][2]{
		{ 4.3, 100},
		{ 4.0, 89 },
		{ 3.7, 79 },
		{ 3.3, 74 },
		{ 3.0, 69 },
		{ 2.7, 64 },
		{ 2.3, 59 },
		{ 2.0, 54 },
		{ 1.7, 49 },
		{ 1.3, 44 },
		{ 0.0, 39 },
	};

	//Creates a loop which iterates though each line of grades for all students
		for (int i = 0; i < 9; i++)
	{
			totalGrade = 0; //Intilize a temp variable to sum grades for each student
			totalqPoints = 0;
			N = 0; //Resets for each iteration 
		//Loop interates through each grade for a specfic student
		for (int j = 0; j < 4; j++)
		{
			 			
			if (!Marksvec[j].empty())
			{
				float grade = Marksvec[j][i]; //Assignes each grade to the temp variable grade

				totalGrade = totalGrade + grade; //Find the total marks for a specific student
				//Counts the number of grades present in the mark text files
				if (grade >= 0)
				{
					N = N++;
				}
				for (int k = 0; k < 11; k++)
				{
					//qPoints_temp = 0; //Rests the variable for each iteration
					if (grade <= qPoints[k][1]) 
						qPoints_temp = qPoints[k][0];
						//break;
				}

				totalqPoints = totalqPoints + qPoints_temp;

				//delete &grade; // Deletes the variable grade so that if a grade is missing it won't hold the grade from the previous iteration
				//grade.clear();
			}
			else{
				continue;
			}
			
		}
		
		double avg = totalGrade / (double)N;
		float GPAtemp = totalqPoints / (float)N;

		average.push_back(avg);
		gpa.push_back(GPAtemp);
	}

}


void writedata(vector<vector<int>>& IDvec, vector<vector<int>>& Marksvec, vector<float> gpa, vector<double> average)
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
		output << "		  " <<fixed<<setprecision(1)<< average[i] << "		" << gpa[i] << endl << endl;

	}
	output.close();


}







