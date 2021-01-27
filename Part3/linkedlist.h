#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <utility>
#include <initializer_list>
using std::initializer_list;

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:


template <typename T>
class LinkedList{
private:
    Node<T> * head = nullptr;
    Node<T> * tail = nullptr;
    int listSize = 0;
public:

    LinkedList()= default;
    LinkedList(initializer_list<T> i)
    {
        for(auto el : i){
            push_back(el);
        }
    }
    ~LinkedList() {
        Node<T>* current = head;
        if(listSize!=0) {
            while (current->next != nullptr) {
                auto *next = current->next;
                delete current;
                current = next;

            }
            delete current;
            listSize = 0;
        }

    }

    void push_front(T item) {
        auto * first = new Node<T>(item);
        if (!head) {
            head = first;
            tail = head;

        }
        else{
            head->previous = first;
            first->next = head;
            head = first;
        }
        ++listSize;
    }


    void push_back(T newTail){
        auto * last = new Node<T>(newTail);
        if(!head){
            head = last;
            tail = head;
        } else{
            tail->next = last;
            last->previous = tail;
            tail = last;

        }
        ++listSize;
    }

    NodeIterator<T> insert(NodeIterator<T> insertIt, T el){

        Node<T> * newNode = new Node<T>(el);
        if(!head || insertIt == head){
            push_front(el);
        }
        else if(insertIt == tail){
            push_back(el);
        }
        else {

            newNode->next = insertIt.getItPointer();
            newNode->previous = insertIt.getItPointer()->previous;
            insertIt.getItPointer()->previous = newNode;
            --insertIt;
            --insertIt;
            insertIt.getItPointer()->next = newNode;

            ++insertIt;
        }
        ++listSize;

        return insertIt;


    }
    NodeIterator<T> erase(NodeIterator<T> eraseIt){
        if(head) {
            if (eraseIt == head) {
                ++eraseIt;
                head = eraseIt.getItPointer();
                cout << head->data << endl;
                head->previous = nullptr;
            } else if (eraseIt == tail) {
                --eraseIt;
                tail = eraseIt.getItPointer();
                tail->next = nullptr;

            } else {

                eraseIt.getItPointer()->next->previous = eraseIt.getItPointer()->previous;
                eraseIt.getItPointer()->previous->next = eraseIt.getItPointer()->next;
                ++eraseIt;
                delete eraseIt.getItPointer()->previous;
                head = eraseIt.getItPointer();


            }
            --listSize;

        }
        return eraseIt;


    }


    int size(){
        return listSize;
    }
    T & front(){
        return head->data;
    }
    T & back(){
        return tail->data;
    }

    NodeIterator<T> begin() {
        return NodeIterator<T>(head);
    }
    NodeIterator<T> end() {
        return NodeIterator<T>(tail->next);
    }

    ConstNodeIterator<T> begin() const{
        return ConstNodeIterator<T>(head);
    }
    ConstNodeIterator<T> end() const {
        return ConstNodeIterator<T>(tail->next);
    }

    void reverse(){
        Node<T> * currentNode;
        Node<T> * nextNode;

        if(!head){
            cout << "Empty list, please add some values" << endl;
        }
        else{
            currentNode = head;
            while (currentNode != nullptr){
                nextNode = currentNode->next;
                currentNode->next = currentNode->previous;
                currentNode->previous = nextNode;
                currentNode = nextNode;

            }
            Node<T> * tempHead = head;
            head = tail;
            tail = tempHead;
        }

    }



};

// do not edit below this line

#endif
