#include <iostream>
#include <string>

using namespace std;

int main()
{
	string studentName, courseName, notTakenBefore, currentGrade, previousGrade, studentPermission = "UNCHECKED", chosenGrade;

	int errorCheck = 0;

	cout << "Welcome to the Fall 2020-2021 Semester grading system. What is your name? ";
	cin >> studentName;
	
	cout << "Hello " << studentName << "! " << "Please enter the name of the course to be processed: ";
	cin >> courseName;
	
	cout << "Hello " << studentName << "! " << "If you take the " << courseName << " for the first time, enter YES otherwise NO: ";
	cin >> notTakenBefore;

	if (notTakenBefore == "YES") 
	{
		cout << "What is your grade from (A,B,C,D,F)? ";
		cin >> currentGrade;

		if (currentGrade == "A" || currentGrade == "B" || currentGrade == "C" || currentGrade == "D") 
		{
			cout << "Do you want to switch your grade from " << currentGrade << " to S (YES or NO)? ";
			cin >> studentPermission;
			
			if (studentPermission == "YES")
			{
				chosenGrade = "S";
			}
		}

		else if (currentGrade == "F")
		{
			cout << "Do you want to switch your grade from " << currentGrade << " to U (YES or NO)? ";
			cin >> studentPermission;
			
			if (studentPermission == "YES")
			{
				chosenGrade = "U";
			}
		}

		else
		{
			cout << "Invalid grade selection. Goodbye..." << endl;
			errorCheck = 1;
		}

		if (studentPermission == "NO")
		{
			chosenGrade = currentGrade;
		}

		else if (studentPermission != "YES" && studentPermission != "NO" && studentPermission != "UNCHECKED")
		{
			cout << "Invalid grade selection. Goodbye..." << endl;
			errorCheck = 1;
		}
	}

	else if (notTakenBefore == "NO")
	{
		cout << "Please enter your previous grade from (A,B,C,D,F,S,U): ";
		cin >> previousGrade;

		if (previousGrade == "A" || previousGrade == "B" || previousGrade == "C" || previousGrade == "D" || previousGrade == "F" || previousGrade == "S" || previousGrade == "U")
		{
			cout << "Please enter your current grade from (A,B,C,D,F): ";
			cin >> currentGrade;
			
			if (currentGrade == "A" || currentGrade == "B" || currentGrade == "C" || currentGrade == "D" || currentGrade == "F")
			{
				cout << "Please enter the grade you want to choose from (A,B,C,D,F,S,U): ";
				cin >> chosenGrade;

				if (chosenGrade == "A" || chosenGrade == "B" || chosenGrade == "C" || chosenGrade == "D" || chosenGrade == "F" || chosenGrade == "S" || chosenGrade == "U")
				{
					if (currentGrade == "A" || currentGrade == "B" || currentGrade == "C" || currentGrade == "D")
					{
						 if (chosenGrade != currentGrade && chosenGrade != "S")
						 {
							if (previousGrade == "U")
							{
								cout << "Invalid grade selection. If you received U before, you may choose S or current letter grade." << endl; 
								errorCheck = 1;
							}

							else
							{
								cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl; 
								errorCheck = 1;
							}
						}
					}

					else 
					{
						if (chosenGrade != "F")
						{
							if (previousGrade == "S")
							{
								cout << "Invalid grade selection. If you received S before and fail this semester, you get F." << endl;
								errorCheck = 1;
							}

							else if (previousGrade == "F")
							{
								cout << "Invalid grade selection. If you received F before, and fail this semester, you get F." << endl;
								errorCheck = 1;
							}
						}
					}
				}

				else
				{
					cout << "Invalid grade selection. Goodbye..." << endl;
					errorCheck = 1;
				}
			}
			
			else
			{
				cout << "Invalid grade selection. Goodbye..." << endl;
				errorCheck = 1;
			}
		}
		
		else
		{
			cout << "Invalid grade selection. Goodbye..." << endl;
			errorCheck = 1;
		}
	}

	else
	{
		errorCheck = 1;
	}

	if (errorCheck == 0)
	{
		cout << studentName << ", your final grade for " << courseName << " is " << chosenGrade << ". Goodbye..." << endl;
	}

	return 0;
}