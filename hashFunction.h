#ifndef _HASHFUCNTION_H_
#define _HASHFUCNTION_H_

#include<string>
#include <sstream>
#include "hashTable.h"

using namespace std;

extern int *localDepth;     //for dynamic hashing
extern int globalDepth;     //for dynamic hashing
extern int numberOfBucket;

//finding hash value

template<typename K>

int findHashValue(K key)
{
    stringstream ss;
    ss<<key;
    string text=ss.str();
    int hashValue = 0, strlen = text.length();

    for (int i = 0; i < strlen; i++) {
        int character = text[i];
        hashValue = (31 * hashValue) + character;
    }

    hashValue=hashValue%numberOfBucket;

    /*if(hashValue>=(numberOfBucket/2) && localDepth[hashValue]<globalDepth){
        return (hashValue-(numberOfBucket/2));
    }
    else*/
    return hashValue;
}

#endif
