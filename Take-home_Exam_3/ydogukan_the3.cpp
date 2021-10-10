#include <iostream>
#include <string>

using namespace std;

string getString()
{
	string str = "", word;

	cin >> word;

	while ( word != "END" && word != "end" )
	{
		str += " " + word;
		cin >> word;
	}

	return " " + str.substr(1,str.length()-1) + " ";
}

bool checkSource(const string & src)
{
	for ( int i = 0; i < src.length(); i++ )
	{
		if ( (src.at(i) < 'A' || src.at(i) > 'Z') && (src.at(i) < 'a' || src.at(i) > 'z') && (src.at(i) < '0' || src.at(i) > '9') && src.at(i) != ' ' )
		{
			return false;
		}
	}
	
	return true;
}

int checkSearch(const string & srch) // returns 0 for no error, 1 for error, 2 for QUIT or quit
{
	if ( srch == "QUIT" || srch == "quit" )
	{
		return 2;
	}

	else if ( srch.length() == 1 || (srch.at(srch.length()-1) != '+' && srch.at(srch.length()-1) != '.' && srch.at(srch.length()-1) != '*') )
	{
		return 1;
	}

	return 0;
}

string getSearchWord(const string & srch)
{
    string searchWord;

    if ( srch.at(srch.length()-1) == '*' && srch.at(srch.length()-2) == '*' )
	{
        searchWord = srch.substr(0, srch.length()-2);
    }

    else 
	{
        searchWord = srch.substr(0, srch.length()-1);
    }

    return searchWord;
}

void searchPlus(const string & src, int index)
{
	int startpos = index, endpos = index;
	string word;

	if ( src.at(index - 1) == ' ' )
	{
		endpos = src.find(' ', index) - 1;

		word = src.substr(startpos, endpos - startpos + 1);
		cout << "index: " << index - 1 << " word: " << word << endl;
	}
}

void searchDot(const string & src, const string & searchWord, int index)
{
	int startpos = index, endpos = index;
	string word;
	
	if ( src.at(index + searchWord.length()) == ' ' )
	{
		endpos = index + searchWord.length() - 1;
		startpos = src.rfind(' ', endpos) + 1;
		
		word = src.substr(startpos, endpos - startpos + 1);
		cout << "index: " << index - 1 << " word: " << word << endl;
	}
}

void searchStar(const string & src, const string & searchWord, int index)
{
	int startpos = index, endpos = index;
	string word;

	if ( (src.at(index-1) != ' ' && src.at(index + searchWord.length()) != ' ') )
	{
		startpos = src.rfind(' ', endpos) + 1;
		endpos = src.find(' ', index) - 1;

		if ( src.substr(startpos, searchWord.length()) != searchWord && src.substr(endpos - searchWord.length() + 1, searchWord.length()) != searchWord )
		{
			word = src.substr(startpos, endpos - startpos + 1);
			cout << "index: " << index - 1 << " word: " << word << endl;
		}
	}
}

void searchDoubleStar(const string & src, int index)
{
	int startpos = index, endpos = index;
	string word;

	startpos = src.rfind(' ', endpos) + 1;
	endpos = src.find(' ', index) - 1;
	
	word = src.substr(startpos, endpos - startpos + 1);
	cout << "index: " << index - 1 << " word: " << word << endl;
}

void searchMain(const string & src, const string & srch) // All operations under one main function so it is easier to see
{
	string searchWord = getSearchWord(srch);
	int index = src.find(searchWord);

	if ( srch.at(srch.length()-1) == '+' )
	{
		while ( index != string::npos && index < src.length() )
		{
			searchPlus(src, index);
			index += searchWord.length();
			index = src.find(searchWord, index);
		}
	}

	else if ( srch.at(srch.length()-1) == '.' )
	{
		while ( index != string::npos && index < src.length() )
		{
			int index = src.find(searchWord);
			int startpos = index, endpos = index;
			string word;
			if ( src.at(index + searchWord.length()) == ' ' )
			{
				endpos = index + searchWord.length() - 1;
				startpos = src.rfind(' ', endpos) + 1;
		
				word = src.substr(startpos, endpos - startpos + 1);
				cout << "index: " << index - 1 << " word: " << word << endl;
			}
			index += searchWord.length();
			index = src.find(searchWord, index);
		}
	}

	else if ( srch.at(srch.length()-1) == '*' && srch.at(srch.length()-2) != '*' )
	{
		while ( index != string::npos && index < src.length() )
		{
			searchStar(src, searchWord, index);
			index += searchWord.length();
			index = src.find(searchWord, index);
		}
	}

	else if ( srch.at(srch.length()-1) == '*' && srch.at(srch.length()-2) == '*' )
	{
		while ( index != string::npos && index < src.length() )
		{
			searchDoubleStar(src, index);
			index += searchWord.length();
			index = src.find(searchWord, index);
		}
	}
}

int main()
{
	string src, srch;

	cout << "Enter source string: ";
	src = getString();

	while ( checkSource(src) == false )
	{
		cout << "Enter source string: ";
		src = getString();
	}

	cout << "Enter search string: ";
	cin >> srch;

	while ( checkSearch(srch) != 2 )
	{
		if ( checkSearch(srch) == 0 )
		{
			searchMain(src,srch);
		}

		cout << "Enter search string: ";
		cin >> srch;
	}

	return 0;
}