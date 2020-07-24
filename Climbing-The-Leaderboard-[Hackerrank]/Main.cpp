#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

vector<string> split_string(string input_string);
vector<int> climbingLeaderboard(vector<int> scores, vector<int> alice);

string filename = "input/input04.txt";

int main()
{
    int n , m;
	vector<int> scores;
	vector<int> alice;

    ifstream input_file(filename);

	if(input_file.is_open())
    {
        vector<string> subStrings;
	    string line;

        getline(input_file, line);
        n = stoi(line);

		getline(input_file, line);
		subStrings = split_string(line);
        for(string subString : subStrings)
        {
            scores.push_back(stoi(subString));
        }

        getline(input_file, line);
        m = stoi(line);

		getline(input_file, line);
		subStrings = split_string(line);
        for(string subString : subStrings)
        {
            alice.push_back(stoi(subString));
        }
    }

	vector<int> ranks = climbingLeaderboard(scores, alice);
	for(int i : ranks)
	{
		cout << i << endl;
	}
}

vector<int> climbingLeaderboard(vector<int> scores, vector<int> alice)
{
    vector<int> ranks;
    vector<int> rankedScores;

    for(unsigned int i=0; i<scores.size();)
    {
        int score = scores[i];
        rankedScores.push_back(score);
        while(scores[i] == score)
        {
            i++;
        }
    }
	// for(int i : rankedScores)
	// {
	// 	cout << i << endl;
	// }

    int i=0,j=rankedScores.size()-1;
    while(i < alice.size())
    {		
		if(j < -1)
		{
			ranks.push_back(1);
			i++;
			continue;
		}
        if(alice[i] < rankedScores[j])
        {
            ranks.push_back(j+2);
            i++;
        }
		else
		{
			j--;
		}
    }

    return ranks;
}

vector<string> split_string(string str)
{
	vector<string> subStrings;
	int subStringStart = 0;
	size_t found = str.find_first_of(' ');
	while (found != string::npos)
	{
		string sub(str, subStringStart, found-subStringStart);
		subStrings.push_back(sub);
		subStringStart = found+1;
		found = str.find_first_of(' ', subStringStart);
	}
	if(subStringStart < str.size())
	{
		string sub(str, subStringStart, str.size()-subStringStart);
		subStrings.push_back(sub);
	}

	return subStrings;
}