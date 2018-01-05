#ifndef _HASHCACHE_H_
#define _HASHCACHE_H_

#include<string>
#include<vector>
#include"hashFunction.h"
#include"caching.h"

//#define maximumBucketSize 8
#define cacheSize 3

using namespace std;

int *counter,numberOfBucket=8;
//int *localDepth,globalDepth=2;

template<class K,class V>

class HashCache{
private:
    Node<K,V>*table;
    void deleteValue(K key,int hashValue);

public:
    HashCache();
    void setCachingAlgorithm(CachingAlgorithm algorithm);
    void insertElement(K key,V value);
    Node<K,V>* searchElement(K searchKey);
    void deleteElement(K key);
    void displayHashTable();
    ~HashCache();
};

//constructor

template<class K,class V>

HashCache<K,V>::HashCache()
{
    counter=new int[numberOfBucket];     //counts the number of element in a linked list
    //localDepth=new int[maximumBucketSize];   //for dynamic hashing
    table=new Node<K,V>[numberOfBucket];
    for(int i=0;i<numberOfBucket;i++){
        counter[i]=0;
        //localDepth[i]=2;
    }
    algorithmChoosed=Least_Frequently_Used;
}

//choosing caching algorithm

template<class K,class V>

void HashCache<K,V>::setCachingAlgorithm(CachingAlgorithm algorithm)
{
    algorithmChoosed=algorithm;
}

// insert element into the hash table

template<class K,class V>

void HashCache<K,V>::insertElement(K key,V value)
{
    int hashValue=findHashValue(key);
    Node<K,V>*newNode=new Node<K,V>[1];

    newNode->value=value;
    newNode->key=key;

    if(searchElement(key)==NULL){
        if(table[hashValue].next==NULL){
            table[hashValue].next=newNode;
        }

        else{
            Node<K,V>*currentNode=table[hashValue].next;

            while(currentNode->next!=NULL){
                currentNode=currentNode->next;
            }
            currentNode->next=newNode;
        }

        counter[hashValue]++;

        mergeSort(&table[hashValue].next);

        /*if(counter[hashValue]>cacheSize){
            extendHashTable(hashValue);
        }*/

        if(counter[hashValue]>cacheSize ){
            table[hashValue].next=table[hashValue].next->next;
            counter[hashValue]--;
        }
    }
}

template<class K,class V>

void HashCache<K,V>::deleteElement(K key)
{
    if(searchElement(key)!=NULL)
        deleteValue(key,findHashValue(key));
}

//print all the contents of the hash table

template<class K,class V>

void HashCache<K,V>::displayHashTable()
{
    for(int i=0;i<numberOfBucket;i++){
        cout<<"values in bucket "<<i+1<<':'<<endl;
        Node<K,V>*currentNode=table[i].next;

        while(currentNode!=NULL){
            cout<<currentNode->key<<' '<<currentNode->value<<endl;
            currentNode=currentNode->next;
        }
        cout<<endl;
    }
}

template<class K,class V>

Node<K,V>* HashCache<K,V>::searchElement(K searchKey)
{
   int hashValue=findHashValue(searchKey);

   Node<K,V>*currentNode=table[hashValue].next;

   while(currentNode!=NULL){

        if(currentNode->key==searchKey){

            (currentNode->totalAccess)++;
            time_t now=time(NULL);
            currentNode->accessTime=*localtime(&now);
            mergeSort(&table[hashValue].next);
            return currentNode;
        }
        currentNode=currentNode->next;
   }

   return NULL;
}

//delete a specified value from the hash table

template<class K,class V>

void HashCache<K,V>::deleteValue(K key,int hashValue)
{

    if(table[hashValue].next->key==key){
        table[hashValue].next=table[hashValue].next->next;
    }

    else{
        Node<K,V>* currentNode=table[hashValue].next;

        while(currentNode->next!=NULL){
            if(currentNode->next->key==key){
                currentNode->next=currentNode->next->next;
                break;
            }
            currentNode=currentNode->next;
        }
    }

    counter[hashValue]--;
}

// destructor

template<class K,class V>

HashCache<K,V>::~HashCache()
{
    for(int i=0;i<numberOfBucket;i++){
        while(table[i].next!=NULL){
            K key =table[i].next->key;
            deleteValue(key,i);
        }
    }

    delete[]table;
    delete[]counter;
    //delete[]localDepth;
}

#endif
