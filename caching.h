#ifndef _CACHING_H_
#define _CACHING_H_
#include "node.h"

enum CachingAlgorithm
{
  Least_Frequently_Used,
  Most_Recently_Used,
  Least_Recently_Used
};

CachingAlgorithm algorithmChoosed;

template<class K,class V>

//merge sort the hash table using caching algorithm

bool sortingRule(Node<K,V> *node1,Node<K,V> *node2)
{
    if(algorithmChoosed==Least_Frequently_Used){
        if(node1->totalAccess<node2->totalAccess)
            return true;
        else
            return false;
    }

    else{
        if(node1->accessTime.tm_yday>node2->accessTime.tm_yday){
            if(algorithmChoosed==Most_Recently_Used)
                return true;
            else if(algorithmChoosed==Least_Recently_Used)
                return false;
        }

        else if(node1->accessTime.tm_yday==node2->accessTime.tm_yday){
            if(node1->accessTime.tm_mon>node2->accessTime.tm_mon){
                if(algorithmChoosed==Most_Recently_Used)
                    return true;
                else if(algorithmChoosed==Least_Recently_Used)
                    return false;
            }

            else if(node1->accessTime.tm_mon==node2->accessTime.tm_mon){
                if(node1->accessTime.tm_mday>node2->accessTime.tm_mday){
                    if(algorithmChoosed==Most_Recently_Used)
                        return true;
                    else if(algorithmChoosed==Least_Recently_Used)
                        return false;
                }

                else if(node1->accessTime.tm_mday==node2->accessTime.tm_mday){
                    if(node1->accessTime.tm_hour>node2->accessTime.tm_hour){
                        if(algorithmChoosed==Most_Recently_Used)
                            return true;
                        else if(algorithmChoosed==Least_Recently_Used)
                            return false;
                    }

                    else if(node1->accessTime.tm_hour==node2->accessTime.tm_hour){
                        if(node1->accessTime.tm_min>node2->accessTime.tm_min){
                            if(algorithmChoosed==Most_Recently_Used)
                                return true;
                            else if(algorithmChoosed==Least_Recently_Used)
                                return false;
                        }

                        else if(node1->accessTime.tm_min==node2->accessTime.tm_min){
                            if(node1->accessTime.tm_sec>node2->accessTime.tm_sec){
                                if(algorithmChoosed==Most_Recently_Used)
                                    return true;
                                else if(algorithmChoosed==Least_Recently_Used)
                                    return false;
                            }

                            else{
                                if(algorithmChoosed==Most_Recently_Used)
                                    return false;
                                else if(algorithmChoosed==Least_Recently_Used)
                                    return true;
                            }
                        }

                        else{
                            if(algorithmChoosed==Most_Recently_Used)
                                return false;
                            else if(algorithmChoosed==Least_Recently_Used)
                                return true;
                        }
                    }

                    else{
                        if(algorithmChoosed==Most_Recently_Used)
                            return false;
                        else if(algorithmChoosed==Least_Recently_Used)
                            return true;
                    }
                }

                else{
                    if(algorithmChoosed==Most_Recently_Used)
                        return false;
                    else if(algorithmChoosed==Least_Recently_Used)
                        return true;
                }
            }
            else{
                if(algorithmChoosed==Most_Recently_Used)
                    return false;
                else if(algorithmChoosed==Least_Recently_Used)
                    return true;
            }
        }
        else{
            if(algorithmChoosed==Most_Recently_Used)
                return false;
            else if(algorithmChoosed==Least_Recently_Used)
                return true;
        }
    }
}

template<class K,class V>

//merges two sorted lists and returns the head

Node<K,V>* mergeTwoLists(Node<K,V> *firstList,Node<K,V> *secondList)
{
    Node<K,V>*currentHead;

    if(firstList==NULL && secondList!=NULL)
        currentHead=secondList;

    else if(firstList!=NULL && secondList==NULL)
        currentHead=firstList;

    else{
        Node<K,V>*currentNode;
        if(sortingRule(firstList,secondList)){
            currentHead=firstList;
            currentNode=firstList;
            firstList=firstList->next;
        }
        else{
            currentHead=secondList;
            currentNode=secondList;
            secondList=secondList->next;
        }

        while(1){
            if(firstList==NULL || secondList==NULL) break;

            else if(sortingRule(firstList,secondList)){
                currentNode->next=firstList;
                currentNode=firstList;
                firstList=firstList->next;
            }

            else{
                currentNode->next=secondList;
                currentNode=secondList;
                secondList=secondList->next;
            }
        }

        if(firstList!=NULL){
            currentNode->next=firstList;
        }

        else if(secondList!=NULL){
            currentNode->next=secondList;
        }
    }

    return currentHead;
}

template<class K,class V>

//dividing a linked list into two lists

void divideLinkedList(Node<K,V>*currentHead,Node<K,V>**firstList,Node<K,V>**secondList)
{
    if(currentHead==NULL || currentHead->next==NULL){
        *firstList=currentHead;
        *secondList=NULL;
    }

    else{
        Node<K,V>*firstPointer=currentHead;
        Node<K,V>*secondPointer=currentHead->next;

        while(secondPointer!=NULL){
            secondPointer=secondPointer->next;
            if(secondPointer!=NULL){
                firstPointer=firstPointer->next;
                secondPointer=secondPointer->next;
            }
        }

        *firstList=currentHead;
        *secondList=firstPointer->next;
        firstPointer->next=NULL;
    }
}

template<class K,class V>

void mergeSort(Node<K,V>**currentHead)
{
    Node<K,V>*firstList=NULL;
    Node<K,V>*secondList=NULL;

    if(*currentHead==NULL || (*currentHead)->next==NULL)
        return;

    divideLinkedList(*currentHead,&firstList,&secondList);

    mergeSort(&firstList);
    mergeSort(&secondList);

    *currentHead=mergeTwoLists(firstList,secondList);
}

#endif
