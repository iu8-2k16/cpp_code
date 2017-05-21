#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Struct
{
	struct Dir
	{
		std::vector<std::string> files;
		enum{CREATED = 1, CHANGED, REMOVED};
		size_t amount;
	};
	struct Data
	{
		std::string author;
		std::string branch;
		std::string time;
		std::string label;
		std::string hash;
		Dir* root = nullptr;
	};
	std::vector<Data*> Mas;
	int comm;

public:
	Struct(std::fstream& file)
	{
		std::string str;
		int ind = -1;
		comm = 0;
		std::vector<std::string> line;
		while (!file.eof())
		{
			getline(file, str);
			line = split(str, " => ");
			if (line[0] == "branch")
			{
				ind++;
				Data* el = new Data;
				Mas.push_back(el);
				Mas[ind]->branch = line[1];
			}
			if (line[0] == "name")
				if (!Mas[ind]->author.empty())
					throw std::exception("Wrong format");
				else 
					Mas[ind]->author = line[1];
			if (line[0] == "time")
			{
				if (!Mas[ind]->time.empty())
					throw std::exception("Wrong format");
				time_t t = stoul(line[1]);
				struct tm buf;
				char str[26];
				gmtime_s(&buf, &t);
				asctime_s(str, sizeof str, &buf);
				Mas[ind]->time = str;
			}
			if (line[0] == "files")
			{
				if (Mas[ind]->root != nullptr)
					throw std::exception("Wrong format");
				Mas[ind]->root = new Dir;
				Mas[ind]->root->files.push_back(line[1]);
				getline(file, str);
				line = split(str, " => ");
				while (line[0] != "hash")
				{
					if (!str.empty())
					{
						Mas[ind]->root->files.push_back(line[0]);
					}
					getline(file, str);
					line = split(str, " => ");
				} 
			}
			if (line[0] == "hash")
			if (!Mas[ind]->hash.empty())
					throw std::exception("Wrong format");
				else
					Mas[ind]->hash = line[1];
		}
	}

	~Struct()
	{
		for (auto it = Mas.begin(); it != Mas.end(); it++)
		{
			if ((*it)->root != nullptr)
				delete (*it)->root;
			delete (*it);
		}
	}
	std::vector<std::string> split(std::string& str, std::string del)
	{
		std::vector<std::string> res;
		int num = str.find(del);
		if (num == -1)
		{
			res.push_back(str);
			return res;
		}
		std::string word;
		for (int i = 0; i < num; i++)
		{
			word += str[i];
		}
		res.push_back(word);
		word = "";
		for (int i = num+4; i < str.size(); i++)
		{
			word += str[i];
		}
		res.push_back(word);
		return res;
	}

	Data* InitCommits(std::string Hash)
	{
		if (Hash.empty())
		{
			comm = 0;
			return Mas[0];
		}
		else
		{
			bool fl = false;
			Data* res;
			int k = 0;
			for (auto it = Mas.begin(); it != Mas.end(); it++)
			{
				if ((*it)->hash == Hash)
				{
					fl = true;
					res = *it;
					break;
				}
				k++;
			}
			if (fl)
			{
				comm = k;
				return res;
			}
			else
				throw std::exception("IncorrectHash\n");
		}
	}
	Data* GetNextCommit()
	{
		comm++;
		if (comm >= Mas.size())
			comm = Mas.size() - 1;
		return Mas[comm];
	}

	Data* GetPrevCommit()
	{
		comm--;
		if (comm < 0)
			comm = 0;
		return Mas[comm];
	}

	bool IsFirstCommit()
	{
		return comm == 0;
	}
	bool IsLastCommit()
	{
		return comm == Mas.size() - 1;
	}
};



int main()
{
	std::fstream file;
	file.open("C:/Users/user/Documents/GitHub/project/ConsoleApplication1/output.txt");
	
	Struct Ne1(file);


	file.close();
	return 0;
}
