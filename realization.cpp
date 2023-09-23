#include "WordPair.h"
#include "realization.h"
#include "../vocabularylib/UnitTest1/vocabulary.h"

Vocabulary::Vocabulary()
{
    root = NULL;
}

Vocabulary::~Vocabulary()
{
     Empty();
}

int Vocabulary::GetSize()
{
    return size;
}

string Vocabulary::operator[](const string& eng)
{
    return (*root)[eng];
}

void Vocabulary::Del(const string& eng, const string& rus)
{
    if (!root)
    {
        return;
    }
    root->Del(eng, rus);
    size--;
}

WordPair* Vocabulary::GetRoot()
{
    return this->root;
}

void Vocabulary::SwitchTransl(const string& eng, const string& rus)
{
    root->SwitchTransl(eng, rus);
}

Direction Vocabulary::InSubTree(const string& eng)
{
    return root->InSubTree(eng);
}

void Vocabulary::ReadFromFile(const string& path)
{
    ifstream fin;
    string eng = "", rus = "";
    fin.open(path);
    if (fin.is_open())
    {
        do
        {
            fin >> eng;
            fin >> rus;
            Push(eng, rus, InSubTree(eng));
        } while (!(fin.eof()) && eng != "");
    }
    fin.close();
}

void Vocabulary::Empty()
{
    this->root = NULL;
}

void Vocabulary::Push(const string& eng, const string& rus, Direction direction)
{
    if (direction == Direction::ROOT || this->root == NULL) {
        this->root = new WordPair(eng, rus);
        size++;
        return;
    }
    try {
        root = Push(root, eng, rus, InSubTree(eng));
        size++;
    }
    catch (const std::runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
}

WordPair* Vocabulary::Push(WordPair* node, const string& eng, const string& rus, Direction direction)
{
    if (node == nullptr)
    {
        node = new WordPair(eng, rus);
        return node;
    }

    if ((node->GetEng() == eng) && (node->GetRus() == rus))
    {
        throw std::runtime_error("Element is already in the tree");
    }

    if (direction == Direction::LEFT)
    {
        node->SetLeft(Push(node->GetLeft(), eng, rus, direction));
    }
    else if (direction == Direction::RIGHT)
    {
        node->SetRight(Push(node->GetRight(), eng, rus, direction));
    }

    return node;
}

string WordPair::GetEng()
{
    return this->eng;
}

string WordPair::GetRus()
{
    return this->rus;
}

WordPair* WordPair::GetLeft()
{
    return this->left;
}

WordPair* WordPair::GetRight()
{
    return this->right;
}

void WordPair::SetLeft(WordPair* left)
{
    this->left = left;
}

void WordPair::SetRight(WordPair* right)
{
    this->right = right;
}

Direction WordPair::InSubTree(const string& eng)
{
    if (!this)
    {
        return Direction::ROOT;
    }
    if (eng < this->GetEng())
    {
        return Direction::LEFT;
    }
    else
    {
        return Direction::RIGHT;
    }
}

WordPair::WordPair(const string& eng, const string& rus)
{
    this->eng = eng;
    this->rus = rus;
}

void WordPair::Del(const string& eng, const string& rus) {
    WordPair* node = this;
    if (node == nullptr) {
        return;
    }
    if (eng < node->eng) {
        node->left->Del(eng,rus);
    }
    else if (eng > node->eng) {
        node->right->Del(eng, rus);
    }
    else {
        if (node->left == nullptr) {
            WordPair* middle_node = node->right;
            delete node;
            node = middle_node;
        }
        else if (node->right == nullptr) {
            WordPair* middle_node = node->left;
            delete node;
            node = middle_node;
        }
        else {
            WordPair* middle_node = node->right->FindMinNode();
            node->eng = middle_node->eng;
            node->rus = middle_node->rus;
            node->right->Del(middle_node->eng, middle_node->rus);
        }
    }
}

WordPair* WordPair:: FindMinNode() {
    if (this->left == nullptr) {
        return this;
    }
    return this->left->FindMinNode();
}


WordPair* WordPair::Finder(const string& eng) {
    if (this->eng==eng) 
    {
        return this;
    }
    if (eng < this->eng) 
    {
        return this->left->Finder(eng);
    }
    else 
    {
        return this->right->Finder(eng);
    }
}

string WordPair::operator[](const string& eng) 
{
    return Finder(eng)->rus;
}


void WordPair::ReadFromFile(const string& path)
{
    this->ReadFromFile(path);
}

void WordPair::SwitchTransl(const string& eng, const string& rus)
{
    Finder(eng)->rus = rus;
}

