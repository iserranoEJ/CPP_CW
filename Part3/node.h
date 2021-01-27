#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;



template<typename T>
class Node{
public:
    T data;
    Node<T> * next;
    Node<T> * previous;
    Node(T dataIn)
    : data(dataIn)
    {
        next  = nullptr;
        previous = nullptr;
    }

};


template<typename T>
class NodeIterator {
  
private:
    
    Node<T>* current;
    
public:
    

    NodeIterator(Node<T>* currentIn)
        : current(currentIn) {        
    }

    T & operator*() {
        return current->data;
    }


    T & operator++(){
        current = current->next;
    }
    T & operator--(){
        current = current->previous;
    }

    bool operator==(NodeIterator<T> other) const {
        return (current == other.current);
    }


    bool operator!=(NodeIterator<T> other) const {
        return (current != other.current);
    }
   Node<T>* getItPointer(){
       return current;
    }



};
template<typename T>
class ConstNodeIterator {

private:

    Node<T> *current;

public:


    ConstNodeIterator(Node<T> *currentIn)
            : current(currentIn) {
    }

    T &operator*() {
        return current->data;
    }


    T &operator++() {
        current = current->next;
    }

    T &operator--() {
        current = current->previous;
    }

    bool operator==(ConstNodeIterator<T> other) const {
        return (current == other.current);
    }

    //Wrong
    bool operator!=(ConstNodeIterator<T> other) const {
        return (current != other.current);
    }

    //Note you may edit your iterator class to provide a function to access the Node pointer from inside the iterator.
    Node<T> *getItPointer() {
        return current;
    }


};

// do not edit below this line

#endif
