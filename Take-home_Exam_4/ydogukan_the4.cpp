#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "strutils.h"

using namespace std;

int main(){

	string poolFileName;
	cout << "Please enter a filename for the word pool: ";
	cin >> poolFileName;

	ifstream poolFile;
	poolFile.open(poolFileName.c_str());
	
	while (poolFile.fail())
	{
		cout << "Cannot open the word pool file."<< endl;
		cout << "Please enter a filename for the word pool: ";
		cin >> poolFileName;
		poolFile.open(poolFileName.c_str());
	}

	string mainFileName;
	cout << "Please enter a filename for the main text: ";
	cin >> mainFileName;

	ifstream mainFile;
	mainFile.open(mainFileName.c_str());
	
	while (mainFile.fail())
	{
		cout << "Cannot open the main text file."<< endl;
		cout << "Please enter a filename for the main text: ";
		cin >> mainFileName;
		mainFile.open(mainFileName.c_str());
	}

	cout << "You may find the results below:" << endl << endl;

	string mainLine;
	
	while (getline(mainFile, mainLine))
	{
		istringstream mainWords(mainLine);
		string mainWord, lineToPrint = "";

		while (mainWords >> mainWord)
		{
			mainWord = LowerString(mainWord);
			bool existsMatch = false, existsCloseMatches = false;
			int maximum = 0;
			string closestMatches = "";
			string poolLine;

			while (getline(poolFile, poolLine))
			{
				istringstream poolWords(poolLine);
				string poolWord;

				while (poolWords >> poolWord)
				{
					if (!existsMatch)
					{
						poolWord = LowerString(poolWord);;

						if (mainWord == poolWord)
						{
							existsMatch = true;
						}

						else
						{
							if (mainWord.length() == poolWord.length())
							{
								int count = 0;

								for (int i = 0; i < mainWord.length(); i++)
								{
									if (mainWord.at(i) == poolWord.at(i))
									{
										count++;
									}
								}

								if (count >= (mainWord.length()/2 + mainWord.length()%2))
								{
									if (count > maximum)
									{
										maximum = count;
										closestMatches = poolWord + ",";
									}

									else if (count == maximum)
									{
										closestMatches += poolWord + ",";
									}

									existsCloseMatches = true;
								}
							}
						}
					}
				}
				poolWords.clear();
				poolWords.seekg(0);
			}

			if (existsMatch == true)
			{
				lineToPrint +=  mainWord + " ";
			}

			else if (existsCloseMatches == true)
			{
				if (closestMatches.substr(0, closestMatches.length()-1).rfind(",") == string::npos)
				{
					lineToPrint += closestMatches.substr(0, closestMatches.length()-1) + " ";
				}
				else 
				{
					lineToPrint += "(" + closestMatches.substr(0, closestMatches.length()-1) + ")" + " ";
				}
			}

			else 
			{
				lineToPrint += "{" + mainWord + "}" + " ";
			}

			poolFile.clear();
			poolFile.seekg(0);
		}

		cout << lineToPrint.substr(0,lineToPrint.length()-1) << endl;
	}

	mainFile.close();
	poolFile.close();
	return 0;
}