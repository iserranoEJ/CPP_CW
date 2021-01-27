#ifndef TREENODE_H
#define TREENODE_H


#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;


template <typename T>
class TreeNode{
public:

    T data;
    unique_ptr<TreeNode> leftChild;
    unique_ptr<TreeNode> rightChild;
    TreeNode<T> * parent;

    TreeNode(T dataIn)
            : data(dataIn)
    { parent = nullptr; };

    void setLeftChild(TreeNode* child){
        leftChild.reset(child);
        child->parent = this;
    }
    void setRightChild(TreeNode* child){
        rightChild.reset(child);
        child->parent = this;
    }
    void write(ostream & o) const {
        if(leftChild) {
            leftChild->write(o);

        }
        o << " " << data << " " ;
        if(rightChild){
            rightChild->write(o);
        }

    }

    int maxDepth() {
        if (!leftChild && !rightChild) {
            return 1;
        }
        else if(leftChild && !rightChild){
            return 1 + leftChild->maxDepth();
        }
        else if(rightChild && !leftChild){
            return 1 + rightChild->maxDepth();
        }
        else{
            int left = leftChild.get()->maxDepth();
            int right = rightChild.get()->maxDepth();

            if (left > right) {
                return 1 + left;
            } else {
                return 1 + right;
            }

        }
    }


};

template<typename I>
class TreeNodeIterator{
public:
    TreeNode<I> * nodePtr;

    TreeNodeIterator(TreeNode<I> * ptrIn)
            : nodePtr(ptrIn)
    {};
    I & operator*(){
        return nodePtr->data;
    }
    bool operator==(TreeNodeIterator<I> other){
        return nodePtr == other.nodePtr;
    }
    bool operator!=(TreeNodeIterator<I> other){
        return nodePtr != other.nodePtr;
    }
    void operator++(){
        if(nodePtr->rightChild){
            nodePtr = nodePtr->rightChild.get();
        }
        else {
            if (nodePtr->parent) {
                while (nodePtr->parent->data < nodePtr->data) {
                    nodePtr = nodePtr->parent;

                    if (!nodePtr->parent) {
                        break;
                    }
                }
                nodePtr = nodePtr->parent;
            }

        }
    }
    void operator--(){
        if(nodePtr->leftChild){
            nodePtr = nodePtr->leftChild.get();
        }
        else {
            if (nodePtr->parent) {
                while (nodePtr->data < nodePtr->parent->data) {
                    nodePtr = nodePtr->parent;

                    if (!nodePtr->parent) {
                        break;
                    }
                }
                nodePtr = nodePtr->parent;
            }
        }
    }


};
// do not edit below this line

#endif
