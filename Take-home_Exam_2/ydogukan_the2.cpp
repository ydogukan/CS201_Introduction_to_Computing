#include <iostream>
#include <iomanip>
#include <string>
#include "strutils.h"

using namespace std;

bool check_input(string color, double length, double width, double height)
{
	if ( length > 0 && width > 0 && height > 0 )
	{
		return true;
	}

	else
	{
		cout << "Invalid entry for " << color << " cuboid. Dimensions should be positive real numbers!" << endl;
		return false;
	}
}

void checkCubeandDisplay(string color, double length, double width, double height)
{
	if ( length == width && width == height )
	{
		cout << color << " cuboid is a cube." << endl << endl;
	}

	else
	{
		cout << color << " cuboid is not a cube." << endl << endl;
	}
}

void display(string color, double area, double volume)
{
	cout << "Results for the " << color << " cuboid:" << endl << "Area: " << area << endl << "Volume: " << volume << endl;
}

void calculate(string color, double length, double width, double height, double &area, double &volume)
{
	area = 2 * ( height * width + width * length + height * length );
	volume = length * width * height;
	display(color, area, volume);
	checkCubeandDisplay(color, length, width, height);
}

string compare(string color1, double value1, string color2, double value2, string desired_metric)
{
	if (desired_metric == "Volume")
	{
		if (value1 > value2)
		{
			return color1 + " has the largest volume.";
		}

		else if (value1 == value2)
		{
			return "Two cuboids have the same volume.";
		}

		else
		{
			return color2 + " has the largest volume.";
		}
	}

	else if (desired_metric == "Area")
	{
		if (value1 > value2)
		{
			return color1 + " has the largest area.";
		}

		else if (value1 == value2)
		{
			return "Two cuboids have the same area.";
		}

		else
		{
			return color2 + " has the largest area.";
		}
	}
}

int main()
{
	cout.setf(ios::fixed);
	cout.precision(2);

	string color1, color2;
	double length1, width1, height1, area1, volume1, length2, width2, height2, area2, volume2;

	cout << "Hello! This program compares two cuboids..." << endl <<"Please enter colors for the two cuboids: ";
	cin >> color1 >> color2;

	if ( LowerString(color1) != LowerString(color2) )
	{
		cout << "Please enter length, width and height of the "<< color1 << " cuboid: ";
		cin >> length1 >> width1 >> height1;

		if ( check_input(color1, length1, width1, height1) == true ) 
		{
			cout << "Please enter length, width and height of the "<< color2 << " cuboid: ";
			cin >> length2 >> width2 >> height2;
		
			if ( check_input(color2, length2, width2, height2) == true )
			{

				calculate(color1, length1, width1, height1, area1, volume1);
				calculate(color2, length2, width2, height2, area2, volume2);

				cout << "Comparison of the two cuboids:" << endl;
				cout << compare(color1, volume1, color2, volume2, "Volume") << endl;;
				cout << compare(color1, area1, color2, area2, "Area") << endl;
			}
		}
	}

	else
	{
		cout << "Color names cannot be the same, good bye..." << endl;
	}

	return 0;
}