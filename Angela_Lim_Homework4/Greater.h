//Angela Lim
//Comparator
#ifndef GREATER_H
#define GREATER_H

#include <iostream>

using namespace std;

template <class Type>
class Greater{
    public:
        bool operator()(const Type& a, const Type& b){
            return (a->distance > b->distance);
        }
};


#endif //GREATER_H
