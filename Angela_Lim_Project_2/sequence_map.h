

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class SequenceMap {
    public:
        SequenceMap() = default;
		~SequenceMap() = default;
		SequenceMap(const SequenceMap &rhs) = default;
		SequenceMap &operator=(const SequenceMap &rhs) = default;
		SequenceMap(SequenceMap &&rhs) = default;
		SequenceMap &operator=(SequenceMap &&rhs) = default;


        SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
            recognition_sequence_ = a_rec_seq;
            enzyme_acronyms_.push_back(an_enz_acro);
        }
        bool operator < (const SequenceMap &rhs) const {
            return (recognition_sequence_ < rhs.recognition_sequence_);
        }
        friend std::ostream &operator << (std::ostream &out, const SequenceMap &a_map){
            for(auto &i: a_map.enzyme_acronyms_){
                out << i << " ";
            }
            // for(auto i = 0; i < a_map.enzyme_acronyms_.size(); i++ ){
            //     out << i << " ";
            // }
            return out;
        }
        void Merge(const SequenceMap &other_sequence){
            for (auto &x: other_sequence.enzyme_acronyms_){
			            enzyme_acronyms_.push_back(x);
		        }
        }

    private:
        string recognition_sequence_ ;
        vector<string> enzyme_acronyms_;
};
#endif
