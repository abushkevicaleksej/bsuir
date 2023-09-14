#include <fstream>
#include "../vocabularylib/vocclasses.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    string eng="", rus="";
    WordPair* voc = new WordPair(eng,rus);
    while (true) {
        cout << "1. Add word and its translation" << endl;
        cout << "2. Delete the word from vocabulary" << endl;
        cout << "3. Translation" << endl;
        cout << "4. Rewrite the translation" << endl;
        cout << "5. Total number of words in the vocabulary" << endl;
        cout << "6. Load the vocabulary from file" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose the operation:" << endl;
        int ch;
        cin >> ch;
        if (!ch)  break;
        switch (ch) {
        case 1:
            while (true)
            {
                cout << "Write the english word: ";
                cin >> eng;
                cout << "Write the translation of the \" " << eng << "\" ";
                cin >> rus;
                voc->push(eng, rus);
                cout << "Do you want to add more words? (type '1' for 'yes', type '2' for 'no') ";
                int ch2;
                cin >> ch2;
                if (ch2==2) break;
            }
            break;
        case 2:
            while (true) {
                cout << "Write the word for deleting: ";
                string delete_word;
                cin >> delete_word;
                voc->del(delete_word, (*voc)[delete_word]);
                voc->size--;
                cout << "Do you want to delete more words? (type '1' for 'yes', type '2' for 'no') ";
                int ch2;
                cin >> ch2;
                if (ch2 == 2) break;
            }
            break;
        case 3:
            while (true)
            {
                string trans;
                cout << "Write the word that you want to translate: ";
                cin >> trans;
                cout<<(*voc)[trans]<<endl;
                cout << "Do you want to translate more words? (type '1' for 'yes', type '2' for 'no') ";
                int ch2;
                cin >> ch2;
                if (ch2 == 2)
                    break;
            }
            break;
        case 4:
            while (true)
            {
                string catch_word, new_word;
                cout << "Write the word you want to switch translation: ";
                cin >> catch_word;
                cin >> new_word;
                voc->switch_transl(catch_word, new_word);
                cout << "Do you want to switch more translations? (type '1' for 'yes', type '2' for 'no') ";
                  int ch2;
                cin >> ch2;
                if (ch2==2) break; 
       
            }
            break;

        case 5:
            cout << "Number of words in the vocabulary: " << voc->size << endl;
            break;

        case 6:
            while (true) {
        
                string path;
                 voc->read_from_file("vocabulary.txt");
                  break;
            }
            break;
        }
    }
    return 0;
}
