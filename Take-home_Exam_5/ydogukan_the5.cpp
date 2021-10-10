#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "strutils.h"

using namespace std;

struct TV_series
{
	string name, actor;
	unsigned int countRating;
	double totalRating, avgRating;
};

int findInVector(vector<TV_series> v, string name)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].name == name)
		{
			return i;
		}
	}

	return -1;
}

void readRatingsFile(ifstream &ratingsFile, vector<TV_series> & v)
{
	string line;
	
	while (getline(ratingsFile, line))
	{
		istringstream words(line);
		string word;

		TV_series series;
		series.totalRating = 0;
		series.countRating = 0;

		string name;
		bool gotRating = false;

		while (words >> word)
		{
			if (gotRating == false)
			{
				series.totalRating = atof(word);
				series.countRating += 1;
				gotRating = true;
			}

			else
			{
				name += word + " ";
			}
		}

		name = UpperString(name.substr(0,name.length()-1));
		int index = findInVector(v, name);

		if (index == -1)
		{
			series.name = name;
			series.avgRating = series.totalRating / series.countRating;
			v.push_back(series);
		}

		else
		{
			v[index].totalRating += series.totalRating;
			v[index].countRating += 1;
			v[index].avgRating = v[index].totalRating / v[index].countRating;
		}
	}
}

void readActorsFile(ifstream &actorsFile, vector<TV_series> & v)
{
	string line;
	
	while (getline(actorsFile, line))
	{
		istringstream words(line);
		string word;

		string name = "";
		string actor = "";
		bool gotActor = false;

		while (words >> word)
		{
			if (gotActor == false)
			{
				if (word.at(word.length()-1) != ';')
				{
					actor += word + " ";
				}

				else
				{
					actor += word;
					gotActor = true;
				}
			}

			else
			{
				name += word + " ";
			}
		}

		name = UpperString(name.substr(0,name.length()-1));
		StripPunc(actor);
		actor = UpperString(actor);
		int index = findInVector(v, name);
		v[index].actor = actor;
	}
}

void sortByRating(vector<TV_series> & a)
{
	int j, k, minIndex, numElts = a.size();
	TV_series temp;

	for (k=0; k < numElts - 1; k++)
	{
		minIndex = k;

		for(j=k+1; j < numElts; j++)
		{

			if (a[j].avgRating > a[minIndex].avgRating)
			{
				minIndex = j;
			}

			else if (a[j].avgRating == a[minIndex].avgRating)
			{
				if (a[j].name < a[minIndex].name)
				{
					minIndex = j;
				}
			}
		}

		temp = a[k];
		a[k] = a[minIndex];
		a[minIndex] = temp;
	}
}

void displayMENU()
{
	cout << "---\nMENU" << endl;
	cout << "1. Print the series" << endl;
	cout << "2. Search the series according to the rating" << endl;
	cout << "3. Add the series to the favorite list" << endl;
	cout << "4. Print the favorite list" << endl;
	cout << "5. Exit\n---" << endl;
}

bool isInt(string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if(!(isdigit(str.at(i))))
		{
			return false;
		}
	}
	return true;
}

double getMinimum()
{
	double minimum;
	if (!(cin >> minimum) | !(minimum >= 0 & minimum <= 10))
	{
		if (cin.fail())
		{
			string temp;
			cin.clear();
			cin >> temp;
		}

		cout << "This is not a valid rating!" << endl;
		return -1;
	}
	return minimum;
}

int main()
{
	cout << "Welcome to Netflix TV Series Ratings Calculator!" << endl;

	string actorsFileName;
	cout << "Please enter a filename for Series-Actor file: ";
	cin >> actorsFileName;

	ifstream actorsFile;
	actorsFile.open(actorsFileName.c_str());
	
	while (actorsFile.fail())
	{
		cout << "Can not find the specified file."<< endl;
		cout << "Please enter a filename for Series-Actor file: ";
		cin >> actorsFileName;
		actorsFile.open(actorsFileName.c_str());
	}

	string ratingsFileName;
	cout << "Please enter a filename for Rating file: ";
	cin >> ratingsFileName;

	ifstream ratingsFile;
	ratingsFile.open(ratingsFileName.c_str());
	
	while (ratingsFile.fail())
	{
		cout << "Can not find the specified file."<< endl;
		cout << "Please enter a filename for Rating file: ";
		cin >> ratingsFileName;
		ratingsFile.open(ratingsFileName.c_str());
	}

	vector<TV_series> v;
	readRatingsFile(ratingsFile, v);
	readActorsFile(actorsFile, v);
	sortByRating(v);

	vector<TV_series> favorites;

	displayMENU();
	cout << "Enter your choice: ";
	string choice;
	cin >> choice;
	cout << "---" << endl;

	while (choice != "5")
	{
		while (!(isInt(choice)) | !(choice >= "1" & choice <= "5"))
		{
			cout << "This is not a valid option!" << endl;
			displayMENU();
			cout << "Enter your choice: ";
			cin >> choice;
			cout << "---" << endl;
		}

		if (choice == "1")
		{
			cout << "RANK,NAME,ACTOR,POINTS" << endl;

			for (unsigned int i = 0; i < v.size(); i++)
			{
				cout << i + 1 << "," << v[i].name << "," << v[i].actor << "," << v[i].avgRating << endl;
			}
		}

		if (choice == "2")
		{
			cout << "Please enter the minimum rating: ";
			double minimum = getMinimum();

			if (minimum != -1)
			{
				cout << "RANK,NAME,ACTOR,POINTS" << endl;
				for (unsigned int i = 0; i < v.size(); i++)
				{
					if (v[i].avgRating >= minimum)
					{
						cout << i + 1 << "," << v[i].name << "," << v[i].actor << "," << v[i].avgRating << endl;
					}
				}
			}
		}

		if (choice == "3")
		{
			cout << "Please enter the name of series: ";
			
			string error;
			cin.clear();
			getline(cin,error);

			string name;
			getline(cin, name);
			ToUpper(name);

			unsigned int index = findInVector(v, name);
			
			if (index == -1)
			{
				cout << "There is no such TV series!" << endl;
			}

			else
			{
				if (findInVector(favorites,name) == -1)
				{
					favorites.push_back(v[index]);
				}

				else
				{
					cout << "Your favorite list already have " << name << endl;
				}
			}
		}

		if (choice == "4")
		{
			if (favorites.size() == 0)
			{
				cout << "Your favorite list is currently empty!" << endl;
			}

			else
			{
				sortByRating(favorites);
				cout << "RANK,NAME,ACTOR,POINTS" << endl;

				for (unsigned int i = 0; i < favorites.size(); i++)
				{
					cout << i + 1 << "," << favorites[i].name << "," << favorites[i].actor << "," << favorites[i].avgRating << endl;
				}
			}
		}

		displayMENU();
		cout << "Enter your choice: ";
		cin >> choice;
		cout << "---" << endl;
	}

	ratingsFile.close();
	actorsFile.close();

	return 0;
}