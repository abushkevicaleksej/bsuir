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

	void read_from_file(const string& path);

	void switch_transl(const string& eng, const string& rus);

	string operator[](const string& eng);

	void del(const string& eng, const string& rus);

	Direction InSubTree(const string& eng);

	int size;
    
	WordPair* left = NULL, * right = NULL;

private:
	
	WordPair* findMinNode();

	WordPair* finder(const string& eng);

	string eng, rus;

};

class Vocabulary
{
public:

	WordPair* push(WordPair* node, const string& eng, const string& rus, Direction direction);

	WordPair* root = NULL;

	Vocabulary();

	~Vocabulary();

	void empty();

	Direction InSubTree(const string& eng);

	int size();

	string  operator[](const string& eng);

	void del(const string& eng, const string& rus);

	void switch_transl(const string& eng, const string& rus);

	void read_from_file(const string& path);

	void push(const string& eng, const string& rus, Direction direction);

};
