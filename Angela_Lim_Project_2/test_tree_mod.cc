// Angela Lim
// Main file for Part2(c) of Homework 2.

#include "avl_tree_modified.h"
// You will have to add #include "sequence_map.h"

#include "sequence_map.h"
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h> //needed for log
#include <iomanip>
using namespace std;

namespace {
    //-------------Same functions as 2a)-----------------
    //@param: takes in a line and returns the enzyme acronym
    string GetEnzymeAcronym(string &db_line) {
        //find the first "/" which is the position at the end of the enzyme acronym
      size_t index = db_line.find("/");
      //get the enzyme substring
      string enzyme = db_line.substr(0, index);
      //update db_line without the enzyme acronym
      db_line = db_line.substr(index+1);
      return enzyme;
    }
    // @param: takes in next db line and checks if theres a recog sequence
    bool GetNextRecognitionSequence(string &db_line, string &recog_seq) {
        //find the first "/" which is the position at the end of the enzyme acronym
      size_t index = db_line.find("/");
       // Return false if found index is at the end of string
      if (index == string::npos){
          return false;
      }
      // Take recog_sequence substring
      recog_seq = db_line.substr(0, index);
      // Update db_line to get rid of found recog sequence
      db_line = db_line.substr(index+1);
      return true;
    }
    // @db_filename: an input filename.
    // @a_tree: an input tree of the type TreeType. It is assumed to be
    //  empty.
    template <typename TreeType>
    void QueryTree(const string &db_filename, TreeType &a_tree) {
    //ifstream the file
      string db_line;
      ifstream inFile;
      inFile.open(db_filename);
      if(inFile.fail()) { exit(1); }
      //the first 10 lines of rebase210.txt is the header, we ignore this.
      for(int i = 0; i < 10; i++) {
          getline(inFile, db_line);
      }
        // Parse through entire file, saving line in db_line
      while(getline(inFile, db_line)) {
        string enzyme_acronym = GetEnzymeAcronym(db_line);
        string recog_sequence;
        // For each line, get all recognition sequences and insert into a_tree
        while (GetNextRecognitionSequence(db_line, recog_sequence)) {
          SequenceMap seqMap (recog_sequence, enzyme_acronym);
          a_tree.insert(seqMap);
        }
      }
      // You can use public functions of TreeType. For example:
      //a_tree.insert(10);
      //a_tree.printTree();
      inFile.close();
    }
    //---------------------End of 2a functions----------------
// Calculates the number of nodes, average depth, average depth to log(n) ratio, and repeats
    template<typename TreeType>
    void calculateValues(TreeType &a_tree, int a) {
      int node_count = a_tree.numberOfNodes();
      //now we're just using type casting and using the tree function
      float average_depth =  (float)a_tree.internalPathLength()/node_count;
      float log_ratio = average_depth/(log2(node_count));
      if (a == 1) {
        cout << "2: " << node_count << endl;
        cout << "3a: " << (float)average_depth << endl;
        cout <<  "3b: " << (float)log_ratio << endl;
      }
      else if (a == 2){
        cout << "6a: " << node_count << endl;
        cout << "6b: " << (float)average_depth << endl;
        cout <<  "6c: " << (float)log_ratio << endl;
      }
    }
    // Function searches a_tree for each string in sequences.txt
    // Then counts the total number of recursive calls for all executions of find()
    template<typename TreeType>
    void queryAndCount(TreeType &a_tree, const string &sequenceFileName) {
      int counter = 0, found = 0, calls = 0;
      //ifstream file
      string recog_seq;
      ifstream inFile;
      inFile.open(sequenceFileName);
      if(inFile.fail()){
          cout << "Error occured" << endl;
          exit(1);
      }
      while(getline(inFile, recog_seq)) {
        counter++;
        // Create new SequenceMap with empty string
        SequenceMap seqMap(recog_seq, "");

        // Check if a_tree contains sequenceMap
        bool ifFound = a_tree.contains(seqMap, calls);
        if(ifFound) {
            found++;
        }
        // Skips every other sequence
        getline(inFile, recog_seq);
      }
      inFile.close();
      cout << "4a: " << counter << endl;
      cout << "4b: " << (float)calls/counter << endl;
    }
    template<typename TreeType>
    void removeSequences(const string &sequenceFileName, TreeType &a_tree) {
        //ifstream file
      ifstream inFile;
      string sequence;
      int counter = 0;
      int counter2 = 0;
      int remove = 0;
      inFile.open(sequenceFileName);
      if(inFile.fail()){
          cout << "Error occured" << endl;
          exit(1);
      }
      while(getline(inFile, sequence)){
        //counter2 represents number of remove calls
        counter2++;
          bool isRemoved = false;
          // Create new SequenceMap with empty string
          SequenceMap seqMap(sequence, "");
          //the counter in this remove function is stored as a parameter to record the amount of recursive calls needed to finish this func
          a_tree.remove(seqMap, counter, isRemoved);
          if (isRemoved == true){
            //increments everytime the item is removed
            remove++;
          }
          //skipping every other sequence
          getline(inFile, sequence);
      }
      inFile.close();
      cout << "5a: "  << remove << endl;
      cout << "5b: "  << (float)counter/counter2 << endl;
    }
// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(b)
  QueryTree(db_filename, a_tree);
  calculateValues(a_tree, 1);
  queryAndCount(a_tree, seq_filename);
  removeSequences(seq_filename, a_tree);
  calculateValues(a_tree, 2);
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);

  return 0;
}
