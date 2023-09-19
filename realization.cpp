#include "vocclasses.h"
#include "realization.h"

Vocabulary::Vocabulary()
{
    root = NULL;
}

Vocabulary::~Vocabulary()
{
     empty();
}

int Vocabulary::size()
{
    return root->size;
}

string Vocabulary::operator[](const string& eng)
{
    return (*root)[eng];
}

void Vocabulary::del(const string& eng, const string& rus)
{
    if (!root)
    {
        return;
    }
    root->del(eng, rus);
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

void Vocabulary::switch_transl(const string& eng, const string& rus)
{
    root->switch_transl(eng, rus);
}

void Vocabulary::read_from_file(const string& path)
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
            push(eng, rus, InSubTree(eng));
        } while (!(fin.eof()) && eng != "");
    }
    fin.close();
}

WordPair::WordPair(const string& eng, const string& rus)
{
    this->eng = eng;
    this->rus = rus;
}

void Vocabulary::empty()
{
    this->root = NULL;
}

Direction Vocabulary::InSubTree(const string& eng)
{
    return root->InSubTree(eng);
}

Direction WordPair::InSubTree(const string& eng)
{
    if (!this)
        {
            return Direction::ROOT;
        }
        if (eng < this->eng)
        {
            return Direction::LEFT;
        }
        else
        {
            return Direction::RIGHT;
        }
}

void Vocabulary::push(const string& eng, const string& rus, Direction direction)
{
    if (direction == Direction::ROOT || this->root == NULL) {
        this->root = new WordPair(eng, rus);
        this->root->size++;
        return;
    }
    try {
        root = push(root, eng, rus, InSubTree(eng));
    } 
    catch(const std::runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }
}



WordPair* Vocabulary::push(WordPair* node, const string& eng, const string& rus, Direction direction)
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
        node->left = push(node->left,eng,rus,direction);
    }
    else if (direction == Direction::RIGHT)
    {
        node->right = push(node->right, eng, rus, direction);
    }
    node->size++;
    return node;
}


void WordPair::del(const string& eng, const string& rus) {
    WordPair* node = this;
    if (node == nullptr) {
        return;
    }
    if (eng < node->eng) {
        node->left->del(eng,rus);
    }
    else if (eng > node->eng) {
        node->right->del(eng, rus);
    }
    else {
        if (node->left == nullptr) {
            WordPair* temp = node->right;
            delete node;
            node = temp;
        }
        else if (node->right == nullptr) {
            WordPair* temp = node->left;
            delete node;
            node = temp;
        }
        else {
            WordPair* temp = node->right->findMinNode();
            node->eng = temp->eng;
            node->rus = temp->rus;
            node->right->del(temp->eng, temp->rus);
        }
    }
    size--;
}

WordPair* WordPair:: findMinNode() {
    if (this->left == nullptr) {
        return this;
    }
    return this->left->findMinNode();
}


WordPair* WordPair::finder(const string& eng) {
    if (this->eng==eng) 
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
    this->read_from_file(path);
}

void WordPair::switch_transl(const string& eng, const string& rus)
{
    finder(eng)->rus = rus;
}

