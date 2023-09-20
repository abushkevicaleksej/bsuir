#pragma once

#include "../vocabularylib/wordpair.h"
class Vocabulary
{
public:

	WordPair* Push(WordPair* node, const string& eng, const string& rus, Direction direction);

	WordPair* root = NULL;

	Vocabulary();

	~Vocabulary();

	void Empty();

	Direction InSubTree(const string& eng);

	int Size();

	string  operator[](const string& eng);

	void Del(const string& eng, const string& rus);

	void SwitchTransl(const string& eng, const string& rus);

	void ReadFromFile(const string& path);

	void Push(const string& eng, const string& rus, Direction direction);

};
