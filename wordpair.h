#pragma once

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

enum class Direction
{
	LEFT,
	RIGHT,
	ROOT
};

class WordPair
{
public:

	string GetEng();

	string GetRus();

	WordPair* GetLeft();

	WordPair* GetRight();

	WordPair(const string& eng, const string& rus);

	void ReadFromFile(const string& path);

	void SwitchTransl(const string& eng, const string& rus);

	string operator[](const string& eng);

	void Del(const string& eng, const string& rus);

	Direction InSubTree(const string& eng);

	int size;
    
	WordPair* left = NULL, * right = NULL;

private:
	
	WordPair* FindMinNode();

	WordPair* Finder(const string& eng);

	string eng, rus;

};

