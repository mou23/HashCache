#ifndef _NODE_H_
#define _NODE_H_

#include<ctime>
#include<string>

using namespace std;

template<class K,class V>

class Node
{
public:
    K key;
    V value;
    Node<K,V>*next;
    tm accessTime;    //holds time
    int totalAccess;

    //default constructor
    Node()
    {
        time_t now=time(NULL);

        this->next=NULL;
        this->accessTime=*localtime(&now);  // returns a pointer to the tm structure representing local time
        this->totalAccess=1;
    }

    // parameterized constructor (creates a node with specified value)

    Node(K key,V value)
    {
        time_t now=time(NULL);     // current time based on current system

        this->value=value;
        this->key=key;
        this->next=NULL;
        this->accessTime=*localtime(&now);  // returns a pointer to the tm structure representing local time
        this->totalAccess=1;
    }
};
#endif

