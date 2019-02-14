// Name: Angela Lim
/*
Points2 is a class that has 2 private member variables
@sequence_ (a pointer that points to a 2d array)
@size_ (size of the sequence)
This class will be implementing the "Big 5" and Overloading the + and [] operators
*/

#ifndef CSCI335_HOMEWORK1_POINTS2_H_
#define CSCI335_HOMEWORK1_POINTS2_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {
  // Points2 is a class that has 2 private member variables
  // @sequence_ (a pointer that points to a 2d array)
  // @size_ (size of the sequence)
  //Implementing constructor, destructor, copy constructor, move and swap
  //This class will also return the addition of sequences using the + operator
template<typename Object>
class Points2 {
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation.

  // Zero-parameter constructor.
  // Set size to 0.
  Points2() : sequence_(nullptr), size_(0){};

  // Copy-constructor.
  Points2(const Points2 &rhs){
    size_ = rhs.size_;
    sequence_ = new std::array<Object, 2> [size_];
    for(size_t i = 0; i < size_; i++){
      sequence_[i][0] = rhs.sequence_[i][0];
      sequence_[i][1] = rhs.sequence_[i][1];
    }


  }

  // Copy-assignment.
  Points2& operator=(const Points2 &rhs){

    Points2 copy = rhs;
    std::swap(*this, copy);
    return *this;

  }

  // Move-constructor.
  Points2(Points2 &&rhs) : sequence_{rhs.sequence_}, size_{rhs.size_}{
    rhs.sequence_ = nullptr;
    rhs.size_ = 0;

  }

  // Move-assignment.
  // Just use std::swap() for all variables.
  Points2& operator=(Points2 &&rhs){
    std::swap(size_, rhs.size_);
    std::swap(sequence_, rhs.sequence_);
    return *this;
  }
//destructor
  ~Points2(){
    sequence_ = nullptr;
    delete[] sequence_;
  }

  // End of big-five.

  // One parameter constructor.
  Points2(const std::array<Object, 2>& item) {
    size_ = 1;
    sequence_ = new std::array<Object, 2> [size_];
    sequence_[0][0] = item[0];
    sequence_[0][1] = item[1];

  }

  // Read a chain from standard input.
  void ReadPoints2() {
    std::string input_line;
    std::getline(std::cin, input_line);
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    int size_of_sequence;
    input_stream >> size_of_sequence;
    // Allocate space for sequence.
    size_ = size_of_sequence;
    sequence_ = new std::array<Object,2>[size_];

    Object token;
    for (int i = 0 ;input_stream >> token; ++i) {
      // Read coordinates.
      // Fill sequence_
      sequence_[i][0] = token;
      input_stream >> token;
      sequence_[i][1] = token;
    }

  }
//returns size of sequence_
  size_t size() const {
    return size_;
  }

  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const {
    //if the location is out of bounds abort
    if (location >= size_){
      std::abort();
    }
    return sequence_[location];

  }

 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their sum. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.
 friend Points2 operator+(const Points2 &c1, const Points2 &c2) {
     Points2 c3;
     size_t min = 0;
     if(c1.size_ > c2.size_){
       c3.size_ = c1.size_;
       min = c2.size_;
     }
     else{
       c3.size_ = c2.size_;
       min = c1.size_;
     }
     //allocate a new array for c3 which will be the sum of c1 and c2
     c3.sequence_ = new std::array<Object, 2>[c3.size_];
     //add c1 and c2 to c3
     for(size_t i = 0; i < min; i++){
       c3.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
       c3.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
     }
     //if c1 > c2 add the rest of c1 to c3
     if(c1.size_ > c2.size_){
       for(size_t j = 0; j < c3.size_; j++){
         c3.sequence_[j][0] = c1.sequence_[j][0];
         c3.sequence_[j][1] = c1.sequence_[j][1];
       }
     }
     else{
       //if c2 > c1 add the rest of c2 to c3
       for(size_t j = 0; j < c3.size_; j++){
         c3.sequence_[j][0] = c2.sequence_[j][0];
         c3.sequence_[j][1] = c2.sequence_[j][1];
       }
     }

     return c3;

 }

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Points2 &some_points2) {
   // if the size is 0 just return empty ()
   if(some_points2.size_ == 0){
     out << "()" << std::endl;
				return out;
   }
   //else return the sequence inside ()
   for(size_t i = 0; i < some_points2.size(); i++){
     out << "("<< some_points2.sequence_[i][0] << ", " << some_points2.sequence_[i][1] << ")";

   }
   out << std::endl;
    return out;
 }

 private:
  // Sequence of points.
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_;

};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2_H_
