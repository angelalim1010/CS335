// Angela Lim
// Main file for Part2(a) of Homework 2.

#include "avl_tree.h"
// You will have to add #include "sequence_map.h"
#include "sequence_map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

namespace {
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
    //@a_tree:an input tree of the type TreeType. It is assumed to be empty.
    template<typename TreeType>
    void TestTree(TreeType &a_tree) {
      string recog_seq;
      while(getline(std::cin, recog_seq))  {
        SequenceMap seqMap{recog_seq, ""};
            //find and returns a pointer to the sequence map
            SequenceMap *enzymes = a_tree.find(seqMap);
            //if the query is not found, return a nullptr
            if(enzymes == nullptr) {
                cout << "Not Found" << endl;
            }
            //uses sequence map's overloading function
            else cout << *enzymes << endl;
      }
    }
    // @db_filename: an input filename.
    // @a_tree: an input tree of the type TreeType. It is assumed to be
    //  empty.
    template <typename TreeType>
    void QueryTree(const string &db_filename, TreeType &a_tree) {
      // Code for running Part2(a)
      string db_line;
      ifstream inFile;
      inFile.open(db_filename);
      //print an error statement if the file fails
      if(inFile.fail()){
          cout << "Error occured" << endl;
          exit(1);
      }
      //skip the first 10 lines
      for(int i=0; i < 10; i++){
          getline(inFile, db_line);
      }
      while(getline(inFile, db_line)){
          string enzymeAcryonm = GetEnzymeAcronym(db_line);
          string recogSequence;
          while(GetNextRecognitionSequence(db_line, recogSequence)){
              SequenceMap seqMap (recogSequence, enzymeAcryonm);
              a_tree.insert(seqMap);
          }

      }
      // You can use public functions of TreeType. For example:
      inFile.close();
      TestTree(a_tree);
    }

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  //const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  QueryTree(db_filename, a_tree);
  return 0;
}
