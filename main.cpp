#include <iostream>
#include "hashCache.h"

using namespace std;

int main()
{
    HashCache<int,char>hc;
    hc.setCachingAlgorithm(Least_Recently_Used);
    hc.insertElement(1,'a');
    hc.insertElement(2,'b');
    hc.insertElement(3,'c');
    hc.insertElement(4,'d');
    hc.insertElement(5,'e');
    hc.insertElement(6,'f');
    hc.insertElement(7,'g');
    hc.insertElement(8,'h');
    hc.insertElement(9,'i');
    hc.insertElement(0,' ');
    hc.insertElement(12,'l');
    if(hc.searchElement(11)){
        cout<<"\nfound\n";
    }
    hc.displayHashTable();


    hc.deleteElement(8);
    hc.deleteElement(4);
    hc.deleteElement(0);

    hc.displayHashTable();

    return 0;
}
