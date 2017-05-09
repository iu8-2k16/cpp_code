#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
std::vector<std::string> split(const std::string& text, const std::string& delims)
{
	std::vector<std::string> tokens;
	std::size_t start = text.find_first_not_of(delims), end = 0;

	while ((end = text.find_first_of(delims, start)) != std::string::npos)
	{
		tokens.push_back(text.substr(start, end - start));
		start = text.find_first_not_of(delims, end);
	}
	if (start != std::string::npos)
		tokens.push_back(text.substr(start));

	return tokens;
}

std::string random_string(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[std::rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

std::vector<std::map <std::string, std::string>> getLogHistory(std::string git_url) {
	static std::string current_path = "C:/Users/user/Documents/GitHub/project/ConsoleApplication1/"; //путь до проекта (внутри проекта папка gits

	//filter
	std::replace(git_url.begin(), git_url.end(), '\0', '_');
	std::replace(git_url.begin(), git_url.end(), ';', '_');
	std::replace(git_url.begin(), git_url.end(), '$', '_');
	std::replace(git_url.begin(), git_url.end(), '|', '_');
	if (system(NULL)) puts("Ok");
	else exit(EXIT_FAILURE);

	int status = 0;

	std::string path_to_git = random_string(10);
	std::string sys_request;

	//если юникс
	//#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))

	sys_request = "git clone " + git_url + " " + current_path + "gits/" + path_to_git;

	status = std::system(sys_request.c_str());
	std::cout << "Status: " << status << std::endl;

	//обязательно создать папку gits!

	std::string seperator = " ; ";
#if defined(_WIN32)
	seperator = " & ";
#endif

	sys_request = "cd " + current_path + "gits/" + path_to_git + seperator + " git log --pretty=format:\"%H---%d---%cn---%ce---%ct---%f\" > ../log.txt";

	std::cout << sys_request << std::endl;

	status = std::system(sys_request.c_str());

	std::ifstream myfile(current_path + "gits/log.txt");
	std::string line;
	std::vector<std::map <std::string, std::string>> answer;
	std::vector <std::string> splited_line;
	std::map <std::string, std::string> tmp_map;
	tmp_map["hash"] = "";
	tmp_map["branch"] = "";
	tmp_map["name"] = "";
	tmp_map["email"] = "";
	tmp_map["time"] = "";
	//tmp_map["file"] = "";


	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::cout << "Read: " << line << '\n';
			splited_line = split(line, "---");
			//hash---branch---name--email--time
			tmp_map["hash"] = splited_line[0];
			tmp_map["branch"] = splited_line[1];
			tmp_map["name"] = splited_line[2];
			tmp_map["email"] = splited_line[3];
			tmp_map["time"] = splited_line[4];
			//tmp_map["file"] = splited_line[5];
			answer.push_back(tmp_map);
		}
		myfile.close();
	}

	std::string files = "";

	for (int x = 0; x < answer.size(); x++) {

		sys_request = "cd " + current_path + "gits/" + path_to_git + seperator + " git show --name-only --pretty=\"\" " + answer[x]["hash"] + " > ../log.txt";
		std::system(sys_request.c_str());
		std::ifstream t(current_path + "gits/log.txt");
		files.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
		answer[x]["files"] = files;
		files.clear();

	}

	return answer;
}



int main() {
	std::vector<std::map <std::string, std::string>> ans = getLogHistory("https://github.com/IlyaShaposhnikov/lab1_ppc.git");

	std::ofstream fout;
	fout.open("output.txt");

	//выведем все время и коммит хеш

	for (auto it = ans.begin(); it != ans.end(); ++it) {

		for (auto i = (*it).begin(); i != (*it).end(); ++i)
		{
			fout << i->first << " => " << i->second << '\n';
		}
		std::cout << (*it).at("hash") << " - " << (*it).at("files") << '\n';

	}
	fout.close();
	return 0;
}
