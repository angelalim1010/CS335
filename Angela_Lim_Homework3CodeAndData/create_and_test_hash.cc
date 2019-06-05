// Angela Lim.
//Assignment Part 1 and 2
#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();
  //..Insert your own code
  ifstream word_stream;
	string words_line;

	word_stream.open(words_filename);
	if (word_stream.fail())
	{
		cout << "Unable to open file" << endl;
		exit(1);
	}
    //adds words to hash table
	while (getline(word_stream, words_line))
	{
		hash_table.Insert(words_line);
	}

  cout << "Collisions: " << hash_table.getNumberofCollisions() <<endl;
  cout << "Number of items: " << hash_table.getCurrentSize() << endl;
  cout << "Size of hash table: " << hash_table.getTableSize() << endl;
  cout << "Load factor: " << hash_table.getCurrentSize() / (double)hash_table.getTableSize()<< endl;
  cout << "Avg. number of collisions: " << hash_table.getNumberofCollisions() / (double) hash_table.getCurrentSize()<< endl;
  
  ifstream query_stream;
	string query_line;

	query_stream.open(query_filename);
	if (query_stream.fail())
	{
		cout << "Unable to open file\n";
		exit(1);
	}

	while (getline(query_stream, query_line))
	{
		if (hash_table.Contains(query_line))
		{
			cout << query_line << ": Found in " << hash_table.getNumberofProbes() << " probes" << endl;

		}
		else
		{
			cout << query_line << ": Not found in " << hash_table.getNumberofProbes() << " probes" << endl;


		}
	}

	word_stream.close();
	query_stream.close();
}

// Sample main for program create_and_test_hash
int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }

  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
  } else if (param_flag == "double") {
    HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
  } else {
    cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
