#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "strutils.h"
#include <vector>
#include "date.h"
#include "favoriteseries.h"

using namespace std;

void readSeries(vector<series> & allSeries)
{
	ifstream seriesFile;
	string seriesFileName = "series.txt";
	seriesFile.open(seriesFileName.c_str());

	string line;
	
	while (getline(seriesFile, line))
	{
		series entry;
		string code, name = "", actor = "";
		istringstream words(line);
		string word;

		words >> code;
		entry.seriesCode = atoi(code);

		bool gotName = false;

		while (words >> word)
		{
			if (gotName == false)
			{
				if (word.at(word.length()-1) != ';')
				{
					name += word + " ";
				}

				else
				{
					name += word;
					entry.seriesName = UpperString(name.substr(0,name.length()-1));
					gotName = true;
				}
			}

			else
			{
				if (word.at(word.length()-1) != ',')
				{
					actor += word + " ";
				}

				else
				{
					actor += word;
					entry.actorNames.push_back(UpperString(actor.substr(0,actor.length()-1)));
					actor = "";
				}
			}
		}

		entry.actorNames.push_back(UpperString(actor.substr(0,actor.length()-1)));
		allSeries.push_back(entry);
	}

	seriesFile.close();
}

int findInVector(vector<series> allSeries, int seriesCode)
{
	for (int i = 0; i < allSeries.size(); i++)
	{
		if (allSeries[i].seriesCode == seriesCode)
		{
			return i;
		}
	}

	return -1;
}

void readEpisodes(vector<series> & allSeries, vector<episode> & allEpisodes)
{
	ifstream episodesFile;
	string episodesFileName = "episodes.txt";
	episodesFile.open(episodesFileName.c_str());

	string line;
	
	while (getline(episodesFile, line))
	{
		episode ep;
		istringstream words(line);
		string word;

		words >> word;
		ep.seriesCode = atoi(word);
		int index = findInVector(allSeries, ep.seriesCode);

		string tempDate = "", month, day, year;
		words >> word;
		int start = 0, end = 0;

		while (end != -1 & start < word.length() - 1)
		{
			end = word.find("/", start);
			tempDate += word.substr(start, end - start) + " ";
			start = end + 1;
		}

		istringstream temp(tempDate);
		temp >> month >> day >> year;
		Date epDate(atoi(month), atoi(day), atoi(year));
		ep.date = epDate;

		words >> word;
		ep.slot = UpperString(word);

		string name = "";

		while (words >> word)
		{
			name += word + " ";
		}

		ep.episodeName = UpperString(name.substr(0, name.length() - 1));

		allSeries[index].episodes.push_back(ep);
		allEpisodes.push_back(ep);
	}

	episodesFile.close();
}

void sortEpisodes(vector<episode> & allEpisodes)
{
	int j, k, minIndex, numElts = allEpisodes.size();
	episode temp;

	for (k=0; k < numElts - 1; k++)
	{
		minIndex = k;

		for(j=k+1; j < numElts; j++)
		{

			if (allEpisodes[j].date < allEpisodes[minIndex].date)
			{
				minIndex = j;
			}

			else if (allEpisodes[j].date == allEpisodes[minIndex].date)
			{
				if (allEpisodes[j].slot != allEpisodes[minIndex].slot)
				{
					if (allEpisodes[j].slot == "MORNING" && (allEpisodes[minIndex].slot == "AFTERNOON" || allEpisodes[minIndex].slot == "EVENING" || allEpisodes[minIndex].slot == "NIGHT"))
					{
						minIndex = j;
					}
					
					else if (allEpisodes[j].slot == "AFTERNOON" && (allEpisodes[minIndex].slot == "EVENING" || allEpisodes[minIndex].slot == "NIGHT"))
					{
						minIndex = j;
					}

					else if (allEpisodes[j].slot == "EVENING" && allEpisodes[minIndex].slot == "NIGHT")
					{
						minIndex = j;
					}
				}

				else 
				{
					if (allEpisodes[j].seriesCode < allEpisodes[minIndex].seriesCode)
					{
						minIndex = j;
					}
				}
			}
		}

		temp = allEpisodes[k];
		allEpisodes[k] = allEpisodes[minIndex];
		allEpisodes[minIndex] = temp;
	}
}

void displayMENU()
{
	cout << "---\nMENU" << endl;
	cout << "1. Print all TV series" << endl;
	cout << "2. Add TV series" << endl;
	cout << "3. Drop TV series" << endl;
	cout << "4. Print your favorite series with schedule" << endl;
	cout << "5. Print all your favorite actors" << endl;
	cout << "6. Exit\n---" << endl;
	cout << "Please enter your choice: ";
}

int main()
{
	cout << "Welcome to my favorite TV series schedule program!" << endl;
	cout << "Please, enter your name and surname: ";

	string userName, userSurname;
	cin >> userName >> userSurname;
	ToUpper(userName);
	ToUpper(userSurname);

	vector<series> allSeries;
	vector<episode> allEpisodes;
	readSeries(allSeries);
	readEpisodes(allSeries, allEpisodes);
	sortEpisodes(allEpisodes);
	FavoriteSeries favSeries(userName, userSurname);
	string fullName = favSeries.getFullName();

	string choice = "";

	while (choice != "6")
	{
		displayMENU();
		cin >> choice;

		while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6")
		{
			cout << "Invalid option!" << endl;
			displayMENU();
			cin >> choice;
		}

		if (choice == "1")
		{
			cout << "CODE,SERIES,EPISODE,DATE,SLOT" << endl;

			for (int i = 0; i < allEpisodes.size(); i++)
			{
				int index = findInVector(allSeries, allEpisodes[i].seriesCode);
				cout << allEpisodes[i].seriesCode << "," << allSeries[index].seriesName << "," << allEpisodes[i].episodeName << "," << allEpisodes[i].date << "," << allEpisodes[i].slot << endl;
			}
		}

		else if (choice == "2")
		{
			int seriesCode;
			cout << "Enter code for the TV series you want to add: ";
			cin >> seriesCode;
			
			int index = findInVector(allSeries, seriesCode);

			if (index == -1)
			{
				cout << fullName << ", there is no such TV series in the database!" << endl;
			}
			
			else
			{
				if (favSeries.ifExists(seriesCode))
				{
					cout << fullName << ", you can't add this TV series because you already added it!" << endl;
				}

				else if (favSeries.isConflict(allSeries[index]))
				{
					cout << fullName << ", you can't add this TV series because of a date and slot conflict!" << endl;
				}

				else
				{
					favSeries.addSeries(allSeries[index]);
					cout << fullName << ", " << allSeries[index].seriesName << " added to your schedule." << endl;
				}
			}
		}

		else if (choice == "3")
		{
			if (favSeries.isListEmpty())
			{
				cout << fullName << ", you did not add any TV series yet!" << endl;
			}

			else
			{
				int seriesCode;
				cout << "Enter code for the TV series you want to drop: ";
				cin >> seriesCode;

				if (!favSeries.ifExists(seriesCode))
				{
					cout << fullName << ", there is no such TV series in your favorite list!" << endl;
				}

				else
				{
					int index = findInVector(allSeries, seriesCode);
					favSeries.dropSeriesSorted(seriesCode);
					cout << fullName << ", " << allSeries[index].seriesName << " has been dropped from your favorite list!" << endl;
				}
			}
		}

		else if (choice == "4")
		{
			if (favSeries.isListEmpty())
			{
				cout << fullName << ", you did not add any TV series yet!" << endl;
			}

			else
			{
				cout << fullName << ", here is your favorite TV series:" << endl;
				cout << "CODE,SERIES,EPISODE,DATE,SLOT" << endl;
				favSeries.displayFavoriteList();
			}
		}

		else if (choice == "5")
		{
			if (favSeries.isListEmpty())
			{
				cout << fullName << ", you did not add any TV series yet!" << endl;
			}
			
			else
			{
				cout << fullName << ", here is your favorite actors:" << endl;
				favSeries.displayFavoriteActors();
			}
		}
	}

	cout << "Goodbye, " << fullName << "!" << endl;

	return 0;
}