#include "vocclasses.h"

Vocabulary::Vocabulary()
{
    root = NULL;
}

Vocabulary::~Vocabulary()
{
     empty();
}

WordPair::WordPair(const string& eng, const string& rus)
{
    this->eng = eng;
    this->rus = rus;
    this->left = nullptr;
    this->right = nullptr;
}

bool Vocabulary::empty()
{
    return this->root == NULL;
}

void Vocabulary::push(const string& eng, const string& rus)
{
    root->push(eng, rus);
}


void WordPair::push(const string& eng, const string& rus)
{
    if (this->eng.empty())
    {
        this->eng = eng;
        this->rus = rus;
        this->left = this->right = NULL;
    }
    else if (eng<this->eng)
    {
        this->left = new WordPair(eng,rus);
    }
    else if (eng > this->eng)
    {
        this->right = new WordPair(eng,rus);
    }
    size++;
}


WordPair* WordPair::del(const string& eng,const string& rus) {
    if (this == nullptr) {
        return this;
    }
    if (eng < this->eng) {
        this->left->del(eng, rus);
    }
    else if (eng > this->eng) {
        this->right->del(eng, rus);
    }
    else {
        if (this->left == nullptr) {
            WordPair* middle = this->right;
            delete this;
            return middle;
        }
        else if (this->right == nullptr) {
            WordPair* middle = this->left;
            delete this;
            return middle;
        }
        WordPair* succParent = this->right;
        WordPair* succ = this->right;
        while (succ->left != nullptr) {
            succParent = succ;
            succ = succ->left;
        }
        if (succParent != succ) {
            succParent->left = succ->right;
        }
        else {
            succParent->right = succ->right;
        }
        this->eng = succ->eng;
        this->rus = succ->rus;
        delete succ;
    }
    return this;
}



WordPair* WordPair::finder(const string& eng) {
    if (this == nullptr || this->eng == eng) 
    {
        return this;
    }
    if (eng < this->eng) 
    {
        return this->left->finder(eng);
    }
    else 
    {
        return this->right->finder(eng);
    }
}

string WordPair::operator[](const string& eng) 
{
    return finder(eng)->rus;
}

void WordPair::read_from_file(const string& path)
{
    ifstream fin;
    string eng, rus;
    fin.open(path);
        while (!fin.eof())
        {
            fin >> eng;
            fin >> rus;
            push(eng, rus);
        }
    fin.close();
}

void WordPair::switch_transl(const string& eng, const string& rus)
{
    finder(eng)->rus = rus;
}

