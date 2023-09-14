#pragma once

#include<iostream>
#include<string>
#include<fstream>

using namespace std;



class WordPair
{
public:

	WordPair(const string& eng, const string& rus);

	int size;

	string eng, rus;

	WordPair* left = NULL, * right = NULL;

	void read_from_file(const string& path);

	void switch_transl(const string& eng, const string& rus);

	string operator[](const string& eng);

	void push(const string& eng, const string& rus);

	WordPair* del(const string& eng, const string& rus);

private:

	WordPair* finder(const string& eng);
};

class Vocabulary
{
public:

	WordPair* root = NULL;

	Vocabulary();

	~Vocabulary();

	bool empty();

	void push(const string& eng, const string& rus);

};