// Angela Lim
//Assignment Part 3
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string removePunctuation(string &word){
    string cleanWord = "";
    //parse through each character in word
    for(auto & character : word){
        //if the word is part of the alphabet, hyphen, or an apostrophe
        if(isalpha(character) || character == '-'  || character == '\''){
            character = tolower(character);
            cleanWord += character;
        }
    }
    return cleanWord;
}

//Helper function for case a, b, and c
template<typename HashTableType>
vector<string> SpellCheckCases(HashTableType &hash_table, string word){
    vector<string> match_word;
    string copy_word = word;
    //Case a
    for(int i = 0; i < word.length()+1; i++){
        //for each character in the alphabet
        for(char character = 'a'; character <= 'z'; character++){
            //insert the character at position i
            copy_word.insert(i,1,character);
            if(hash_table.Contains(copy_word)){
                //if table has this copied word add it to the vector
                match_word.push_back(copy_word);
            }
            //reset word
            copy_word = word;
        }
    }
    //reset word
    copy_word = word;
    //Case B
    for(int i = 0; i < word.length(); i++){
        //remove character i
        copy_word.erase(i, 1);
        //if hash table has this word add it
        if(hash_table.Contains(copy_word)){
            match_word.push_back(copy_word);
        }
        //reset word
        copy_word = word;
    }
    //reset word
    copy_word = word;
    //Case c
    for(int i = 0; i < word.length()-1; i++){
        //swap adjacent characters
        swap(copy_word[i], copy_word[i+1]);
        //if table contains this word add it
        if(hash_table.Contains(copy_word)){
            match_word.push_back(copy_word);
        }
        //reset word
        copy_word = word;
    }
    //return the vector
    return match_word;
}

template <typename HashTableType>
void SpellCheck(HashTableType &hash_table, const string &document_filename, const string &dictionary_filename){
    hash_table.MakeEmpty();
    ifstream dictionary_stream;
  	string dictionary_line;

  	dictionary_stream.open(dictionary_filename);
  	if (dictionary_stream.fail())
  	{
  		cout << "Unable to open dictionary" << endl;
  		exit(1);
  	}

  	while (getline(dictionary_stream, dictionary_line))
  	{
  		hash_table.Insert(dictionary_line);
  	}
    ifstream document_stream;
    string document_line;

    document_stream.open(document_filename);
    if (document_stream.fail())
    {
        cout << "Unable to open document" << endl;
        exit(1);
    }
    cout<< "Possible Misspelled Words with Possible Corrections: " <<endl;

    //parse through document file and save each word in document line
    while(document_stream >> document_line){
        string word = removePunctuation(document_line);
        vector<string> correct_words;
        //if empty keep going
        if(word == ""){
            continue;
        }
        //if the word is "i" keeo going
        if (word == "i"){
            continue;
        }
        //if the table doesn't have the word check for misspelled corrections
        if(!hash_table.Contains(word)){
            correct_words = SpellCheckCases(hash_table, word);
        }
        //if theres any possible spellcheck strings print the vector
        if(correct_words.size()> 0){
            cout << word << " -> ";
            for(auto & character : correct_words){
                cout << "(" << character << ") ";
            }
            cout << endl;
        }
    }
    dictionary_stream.close();
    document_stream.close();
}


// Sample main for program spell_check
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    return 0;
  }

  const string document_filename(argv[1]);
  const string dictionary_filename(argv[2]);

  cout << "Input document filename is " << document_filename << endl;
  cout << "Input dictionary filename is " << dictionary_filename << endl;

  // Call functions implementing the assignment requirements.
  HashTableDouble<string> hash_table;
  SpellCheck(hash_table, document_filename, dictionary_filename);

  return 0;
}
