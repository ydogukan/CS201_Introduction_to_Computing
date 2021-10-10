#include "favoriteseries.h"

FavoriteSeries::FavoriteSeries(string uName, string uSurname)
{
	userName = uName;
	userSurname = uSurname;
}

string FavoriteSeries::getFullName() const
{
	return userName + " " + userSurname;
}

void FavoriteSeries::addSeries(const series & v)
{
	favSeries.push_back(v);
}


bool FavoriteSeries::ifExists(int seriesCode)
{
	for (int i = 0; i < favSeries.size(); i++)
	{
		if (favSeries[i].seriesCode == seriesCode)
		{
			return true;
		}
	}

	return false;
}

bool FavoriteSeries::isListEmpty() const
{
	if (favSeries.size() == 0)
	{
		return true;
	}

	return false;
}

int FavoriteSeries::findSeries(const vector<series> & favSeries, int seriesCode) const
{
	for (int i = 0; i < favSeries.size(); i++)
	{
		if (favSeries[i].seriesCode == seriesCode)
		{
			return i;
		}
	}

	return -1;
}

void FavoriteSeries::dropSeriesSorted(int seriesCode)
{
	int pos = findSeries(favSeries, seriesCode);
	int lastIndex = favSeries.size()-1;
	favSeries[pos] = favSeries[lastIndex];
	favSeries.pop_back();
}

vector<episode> FavoriteSeries::allEpisodesSorted(const vector<series> & favSeries) const
{
	vector<episode> allEpisodes;
	for (int i = 0; i < favSeries.size(); i++)
	{
		for (int j = 0; j < favSeries[i].episodes.size(); j++)
		{
			allEpisodes.push_back(favSeries[i].episodes[j]);
		}
	}

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

	return allEpisodes;
}

void FavoriteSeries::displayFavoriteList() const
{
	vector<episode> allEpisodes = allEpisodesSorted(favSeries);

	for (int i = 0; i < allEpisodes.size(); i++)
	{
		int index = findSeries(favSeries, allEpisodes[i].seriesCode);
		cout << allEpisodes[i].seriesCode << "," << favSeries[index].seriesName << "," << allEpisodes[i].episodeName << "," << allEpisodes[i].date << "," << allEpisodes[i].slot << endl;
	}
}

int FavoriteSeries::findActor(const vector<actor> & actors, string actorName) const
{
	for (int i = 0; i < actors.size(); i++)
	{
		if (actors[i].actorName == actorName)
		{
			return i;
		}
	}

	return -1;
}

void FavoriteSeries::sortActors(vector<actor> & actors) const
{
	int j, k, minIndex, numElts = actors.size();
	actor temp;

	for (k=0; k < numElts - 1; k++)
	{
		minIndex = k;

		for(j=k+1; j < numElts; j++)
		{

			if (actors[j].score > actors[minIndex].score)
			{
				minIndex = j;
			}

			else if (actors[j].score == actors[minIndex].score)
			{
				if (actors[j].actorName < actors[minIndex].actorName)
				{
					minIndex = j;
				}
			}
		}

		temp = actors[k];
		actors[k] = actors[minIndex];
		actors[minIndex] = temp;
	}
}

void FavoriteSeries::displayFavoriteActors() const
{
	vector<actor> actors;
	actor person;

	for (int i = 0; i < favSeries.size(); i++)
	{
		for (int j = 0; j < favSeries[i].actorNames.size(); j++)
		{
			int index = findActor(actors, favSeries[i].actorNames[j]);

			if (index == -1)
			{
				person.actorName = favSeries[i].actorNames[j];
				person.score = 1;
				actors.push_back(person);
			}

			else
			{
				actors[index].score += 1;
			}
		}
	}

	sortActors(actors);

	for (int i = 0; i < actors.size(); i++)
	{
		cout << actors[i].actorName << ": " << actors[i].score << endl;
	}
}

bool FavoriteSeries::isConflict(const series & inSeries) const
{
	for (int i = 0; i < favSeries.size(); i++)
	{
		for (int j = 0; j < favSeries[i].episodes.size(); j++)
		{
			for (int k = 0; k < inSeries.episodes.size(); k++)
			{
				if (favSeries[i].episodes[j].date == inSeries.episodes[k].date && favSeries[i].episodes[j].slot == inSeries.episodes[k].slot)
				{
					return true;
				}
			}
		}
	}
	
	return false;
}