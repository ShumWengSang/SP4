#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Scorer
{
public:
	std::string User;
	int HighScore;
};

class Highscore
{
public:
	Highscore();
	~Highscore();

	void LoadHighScore()
	{
		string line;
		ifstream myfile(FileName.c_str());
		if (myfile.is_open())
		{
			int i = 1;
			string user;
			int value;
			Scorer newScorer;

			while (getline(myfile, line))
			{
				if (i % 2 != 0)
				{
					user = line;
				}
				else
				{
					value = atoi(line.c_str());	
					newScorer.HighScore = value;
					newScorer.User = user;
					HighScoreList.push_back(newScorer);
				}

				if (HighScoreList.size() > 10)
					break;
				i++;
			}
			myfile.close();
		}
	}
	
	void SaveHighScore()
	{
		ofstream outData;
		outData.open(FileName.c_str());

		for (int unsigned i = 0; i < HighScoreList.size(); i++)
		{
			outData << HighScoreList[i].User.c_str() << endl;
			outData << HighScoreList[i].HighScore << endl;
		}
		outData.close();
	}

	void InsertHighScore(int newScore, string &user)
	{
		if(HighScoreList.size() > 0)
		{
			for (auto i = HighScoreList.begin(); i != HighScoreList.end(); i++)
			{
				if (newScore >= (*i).HighScore)
				{
					Scorer newScorer;
					newScorer.HighScore = newScore;
					newScorer.User = user;
					HighScoreList.insert(i, newScorer);
					break;
				}
			}
		}else{
			Scorer newScorer;
			newScorer.HighScore = newScore;
			newScorer.User = user;
			HighScoreList.push_back(newScorer);
		}
	}
	std::string FileName;
	std::vector<Scorer> HighScoreList;
};

