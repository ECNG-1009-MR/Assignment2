/*Program by Group MR
Members:
1)Nathan Ragoobar
2)Nyckel St. Louis
3)Matthias Elliot
4)Nikolai Pillai
5)Quinton Aleong
6)Rajiv Sahadeo
7)Chad Moore
8)Matthew Williams
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>



//Function forward declarations
void retrieveData(std::vector<std::vector<int>>& IDvec, std::vector<std::vector<int>>& Marksvec);
void GPACalculation(std::vector<std::vector<int>>& Marksvec, std::vector<double>& average, std::vector<float>& gpa);
void writedata(std::vector<std::vector<int>>& IDvec, std::vector<std::vector<int>>& Marksvec, std::vector<float> gpa, std::vector<double> average);

int main()
{
	std::vector<double> average;
	std::vector<float> gpa;
	std::vector<std::vector<int>> IDvec;
	std::vector<std::vector<int>> Marksvec;

	retrieveData(IDvec, Marksvec);
	GPACalculation(Marksvec, average, gpa);
	writedata(IDvec, Marksvec, gpa, average);


	return 0;
}


void retrieveData(std::vector<std::vector<int>>& IDvec, std::vector<std::vector<int>>& Marksvec)
{
	//Passes the memory address of IDvec and Marksvec into this function. This allows the vectors to be modified in this function
	//IDvec:		//A 2d vector that will contain vectors of ID numbers from each file
	//Marksvec:		//A 2d vector that will contain vectors of marks from each file

	std::string ID;
	std::string marks;
	//inputfile is a string array containing names of all txt files
	std::string inputfile[] = { "ecng1006marks.txt", "ecng1009marks.txt", "ecng1014marks.txt", "ecng1016marks.txt" };
	std::ifstream input[4]; //An array of ifstreams used to loop.

	std::vector<int> IDvec_sub;			//A 1d vector that is used to temporarily store all ID numbers in each file
	std::vector<int> Marksvec_sub;		//A 1d vector that is used to temporarily store all marks in each file


	//Creates a loop that opens all text files from 'inputfile' array into respective fstream from 'input' array
	for (int j = 0; j < 4; j++)
	{
		input[j].open(inputfile[j]);
	}


	//Loops through all fstreams in the 'input' array
	for (int j = 0; j < 4; j++)
	{
		//Verify that file exists. If not, it exits.
		if (!input[j].is_open())
		{
			std::cout << "Cannot open file: " << inputfile[j] << std::endl;
			std::cout << "Program will now end." << std::endl;
			exit(0);
		}
			
		else
		{
			std::cout << "File found: " << inputfile[j] << std::endl;
		}

		//Input each string from the current 'input' fstream into 'ID' and 'marks' variables.
		//Assuming each string in the file starts with an Id number then marks, 
		//it will alternate between inputting into the 'ID' variable and 'marks' variable
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


void GPACalculation(std::vector<std::vector<int>>& Marksvec, std::vector<double> &average, std::vector<float> &gpa)
{
	//Passes the memory address of Marksvec, average and gpa into this function. This allows the vectors to be modified
	// in this function
	//average:	A 1d vector that will store the values for the average grade
	//gpa:		A 1d vector that will store the values for the gpa
	

	int N;
	float totalGrade;
	float totalqPoints;
	float qPoints_temp;
	//An array which holds the quality points and respective upper limit of its grade range.
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
		for (int i = 0; i < Marksvec[0].size(); i++)
	{
			//Assigns a value of zero for the following variable on each iteration of the for loop
			totalGrade = 0; 
			totalqPoints = 0;
			N = 0; 

		//Loop iterates through each grade for a specific student
		for (int j = 0; j < 4; j++)
		{
			 			
			if (!Marksvec[j].empty()) //Checks if each row of data has a value
			{
				float grade = Marksvec[j][i]; //Assigns each mark in the Marksvec vector to the temp variable "grade"

				totalGrade = totalGrade + grade; //Find the total marks for a specific student
				
				N = N++;	//Counts the number of grades present in the mark text files

				for (int k = 0; k < 11; k++) //Loop iterates through the quality points array
				{
					//Determines if the grade is less than or equal to the upper bound of a quality point grade range
					//and assigns the respective quality point
					if (grade <= qPoints[k][1]) 
						qPoints_temp = qPoints[k][0];
						
				}

				totalqPoints = totalqPoints + qPoints_temp;

			}
			
		}
		
		double avg = totalGrade / (double)N;
		float GPAtemp = totalqPoints / (float)N;

		//Attaches the calculated values to the end of the average and gpa vectors
		average.push_back(avg);
		gpa.push_back(GPAtemp);
	}

}


void writedata(std::vector<std::vector<int>>& IDvec, std::vector<std::vector<int>>& Marksvec, std::vector<float> gpa, std::vector<double> average)
{
	std::ofstream output;
	output.open("studentsummary.txt"); // opens summary file
	for (int i = 0; i < IDvec[0].size(); i++)  // loop to determine row to get data from
	{

		output << " Student		ECNG1006	ECNG1009	ECNG1014	ECNG1016	Average		GPA	" << std::endl;
		output << IDvec[0][i]; // outputs the id number at the i position of the vector
		for (int j = 0; j < 4; j++) // loop to determine column to get data from
		{

			if (Marksvec[j].empty()) 
			{
				output << "		  N/A"; //outputs N/A if there is no data
			}
			else
			{
				output << "		   " << Marksvec[j][i]; // outputs data from the j column i row if there is data
			}


		}
		output << "		  " << std::fixed<< std::setprecision(1)<< average[i] << "		" << gpa[i] << std::endl << std::endl;

	}
	output.close();

	std::cout << "\nFile 'studentsummary.txt' successfully created." << std::endl;

}







