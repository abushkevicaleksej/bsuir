#pragma once

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class WordPair
{
public:
	
	string GetEng();

	string GetRus();

	WordPair* GetLeft();

	WordPair* GetRight();

	void SetLeft(WordPair* left);

	void SetRight(WordPair* right);

	int GetSize();

	void SetSize(int size);

	WordPair(const string& eng, const string& rus);

	void ReadFromFile(const string& path);

	void SwitchTransl(const string& eng, const string& rus);

	string operator[](const string& eng);

	void Del(const string& eng, const string& rus);

	Direction InSubTree(const string& eng);

private:
	
	WordPair* FindMinNode();

	WordPair* Finder(const string& eng);

	string eng, rus;

	int size;

	WordPair* left = NULL, * right = NULL;
};

