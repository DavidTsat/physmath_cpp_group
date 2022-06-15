#pragma once
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>
#include <format>
#include <string>

using namespace std;

void update_count(std::map<std::string, int>& storage, std::string str)
{
	if (storage.count(str))
		++storage[str];
	else
		storage[str] = 1;
}

void split1(std::vector<std::string>& v, const std::string& t,  const std::string& s)
{
	auto b = t.cbegin();

	while (true)
	{
		auto p = find_if(b, t.cend(), [&s](char c) {return find(s.cbegin(), s.cend(), c) != s.cend(); });
		if (p == t.cend()) break;
		v.push_back(string(b, p));
		b = p;
	}
	
}

void split2(std::vector<std::string>& v, const std::string& t, const std::string& s)
{
	string res_s = "\\b[^" + s + "]+\\b"; 
	regex r(res_s);
	sregex_iterator r_begin(t.cbegin(), t.cend(), r);
	sregex_iterator r_end;

	while (r_begin != r_end)
	{
		v.push_back((*r_begin++).str());
	}
}

void test_split()
{
	std::map<std::string, int> wordsCount;
	std::vector<std::string> words;
	std::string text("  some     very long long text-ops somesome");
	//boost::split(words, text, boost::is_any_of(" -"));
	split2(words, text, " -");
	for (const std::string& word : words)
	{
		update_count(wordsCount, word);
	}
	for (const auto& word : wordsCount)
	{
		std::cout << word.first << " : " << word.second << std::endl;
	}

	std::cout << "finished!" << std::endl;
}