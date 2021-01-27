#ifndef TREEMAP_H
#define TREEMAP_H

#include "tree.h"

template<typename Key, typename Value>
class KeyValuePair {
    
public:
    
    const Key k;
    Value v;

    KeyValuePair(Key kIn, Value vIn)
    : k(kIn), v(vIn){};

    KeyValuePair(Key kIn)
            : k(kIn){};

    bool operator<(const KeyValuePair<Key,Value> & other ){
        return k < other.k;
    }


};



template<typename Key, typename Value>
ostream & operator<< (ostream & o, const KeyValuePair<Key,Value> & kv){
o << kv.k << "," << kv.v;
return o;
}



template<typename Key, typename Value>
class TreeMap {

private:
BinarySearchTree<KeyValuePair<Key,Value> > tree;

public:

KeyValuePair<Key,Value> * insert(const Key & k, const Value & v) {
    return &(tree.insert(KeyValuePair<Key,Value>(k,v))->data);
}

void write(ostream & o) const {
    tree.write(o);
}

KeyValuePair<Key,Value>* find(const Key & key ){
         KeyValuePair<Key,Value> newPair(key);
        return & (tree.find(newPair)->data);
}



    
};


// do not edit below this line

#endif
