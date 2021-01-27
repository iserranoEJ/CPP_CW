#ifndef TREE_H
#define TREE_H

#include "treenode.h"


template <typename T>
class BinarySearchTree {
private:
    unique_ptr<TreeNode<T>> root;
public:
    BinarySearchTree()= default;

    void copyTree(const BinarySearchTree<T> & copied){
        auto *tempNode = copied.root.get();
        insert(tempNode->data);
        while (tempNode) {
            if (tempNode->leftChild && !find(tempNode->leftChild->data)) {
                tempNode = tempNode->leftChild.get();
                insert(tempNode->data);

            } else{
                if(tempNode->rightChild && !find(tempNode->rightChild->data)) {
                    tempNode = tempNode->rightChild.get();
                    insert(tempNode->data);
                }
                else
                {
                    tempNode = tempNode->parent;
                }
            }

        }

    }


    BinarySearchTree(const BinarySearchTree<T> & copied) {

        copyTree(copied);

    }
    BinarySearchTree<T> & operator=(const BinarySearchTree<T> & other){
        copyTree(other);
        return *this;
    }

    void write(ostream & o) const{
        if(root)
            root->write(o);
    }
    TreeNodeIterator<T>  begin(){
        if(!root){
            return nullptr;
        }
        TreeNodeIterator<T> it(root.get());
            while (it.nodePtr->leftChild){
                --it;
            }
        return it;
    }
    TreeNodeIterator<T> end(){
        if(!root){
            return nullptr;
        }
        TreeNodeIterator<T> it(root.get());
        while (it.nodePtr->rightChild){
            ++it;
        }
        ++it;
        return it;
    }

    TreeNode<T>* insert(T item) {

        if (root) {
            auto *tempNode = root.get();
            while (tempNode) {

                if (item < tempNode->data && tempNode->leftChild) {

                    tempNode = tempNode->leftChild.get();

                } else if (tempNode->data < item && tempNode->rightChild) {

                    tempNode= tempNode->rightChild.get();

                } else {
                    if (item < tempNode->data) {

                        auto *newNode = new TreeNode<T>(item);
                        tempNode->setLeftChild(newNode);
                        TreeNodeIterator<T> it = begin();
                        while (it.nodePtr != tempNode){
                            ++it;
                        }
                        if(it.nodePtr->parent) {
                            TreeNode<T> *newTemp = it.nodePtr->parent;
                            if (unbalanced(newTemp->leftChild.get(), newTemp->rightChild.get())) {
                                if(needRightRot(newTemp)){
                                    rightRotation(newTemp);
                                } else if(needRightLeftRot(newTemp)){
                                    rightLeftRotation(newTemp);

                                }

                            }
                        }

                        return (tempNode->leftChild).get();

                    } else if (tempNode->data < item) {

                        auto *newNode2 = new TreeNode<T>(item);
                        tempNode->setRightChild(newNode2);
                        TreeNodeIterator<T> it = begin();
                        while (it.nodePtr != tempNode){
                            ++it;
                        }
                        if(it.nodePtr->parent) {
                            TreeNode<T> *newTemp = it.nodePtr->parent;
                            if (unbalanced(newTemp->leftChild.get(), newTemp->rightChild.get())) {
                                if(needLeftRot(newTemp)){
                                    leftRotation(newTemp);
                                }
                                if(needLeftRightRot(newTemp)){
                                    leftRightRotation(newTemp);
                                }
                            }
                        }

                        return (tempNode->rightChild.get());


                    }
                    else{
                        return tempNode;
                    }
                }

            }


        }
        else{
            auto *newNode = new TreeNode<T>(item);
            root.reset(newNode);
            return root.get();
        }
    }


    TreeNode<T> * find(T item){

        if (!root) {
            return nullptr;
        }
        auto *tempNode = root.get();

        while (tempNode) {

            if (item < tempNode->data) {
                tempNode = tempNode->leftChild.get();
            } else if (tempNode->data < item) {
                tempNode = tempNode->rightChild.get();
            }
            else {
                return tempNode;
            }


        }
        return nullptr;

    }
    int maxDepth(){
        if(!root){
            return 0;
        }
        else{
            return root.get()->maxDepth();
        }
    }

    bool unbalanced(TreeNode<T>* node, TreeNode<T>* node2){
        if(!node){
            int depth = node2->maxDepth();
            return depth == 2 or depth == -2;
        }
        if(!node2){
            int depth = node->maxDepth();
            return depth == 2 or depth == -2;
        }
        int difference = node->maxDepth() - node2->maxDepth() ;
        return difference == 2 or difference == -2;

    }

    void leftRotation(TreeNode<T> * node){
        if (node->parent) {
            auto temp = node->parent;
            node->rightChild.get()->setLeftChild(node);
            temp->rightChild.release();
            temp->setRightChild(node->parent);
            node->rightChild.release();
        }
        else{
            node->rightChild.get()->setLeftChild(node);
            node->rightChild.release();
            node->parent->parent = nullptr;
            root.release();
            root.reset(node->parent);
        }
    }

    bool needLeftRot(TreeNode<T> * node){

            if (node->rightChild && !node->leftChild) {
                if (node->rightChild->rightChild && !node->rightChild->leftChild) {
                    return true;
                }
            }
        return false;
    }
    void rightRotation(TreeNode<T> * node){

        if (node->parent) {
            auto temp = node->parent;
            node->leftChild.get()->setRightChild(node);
            temp->leftChild.release();
            temp->setLeftChild(node->parent);
            node->leftChild.release();
        }
        else{
            node->leftChild.get()->setRightChild(node);
            node->leftChild.release();
            node->parent->parent = nullptr;
            root.release();
            root.reset(node->parent);
        }

    }
    bool needRightRot(TreeNode<T> * node){
        if(!node->rightChild && node->leftChild){
            if(!node->leftChild->rightChild && node->leftChild->leftChild){
                return true;
            }
        }

        return false;
    }
    void leftRightRotation(TreeNode<T> * node){
        auto * temp = node->leftChild->rightChild.get();
        temp->parent = node;
        temp->setLeftChild(node->leftChild.get());
        temp->leftChild->rightChild.release();
        node->leftChild.release();
        node->setLeftChild(temp);


        rightRotation(node);


    }
    bool needLeftRightRot(TreeNode<T> * node){
        if (!node->rightChild && node->leftChild) {
                if (node->leftChild->rightChild && !node->leftChild->leftChild) {
                    return true;
                }
        }

        return false;
    }

    void rightLeftRotation(TreeNode<T> * node){
        auto * temp = node->rightChild->leftChild.get();
        temp->parent = node;
        temp->setRightChild(node->rightChild.get());
        temp->rightChild->leftChild.release();
        node->rightChild.release();
        node->setRightChild(temp);

        leftRotation(node);

    }
    bool needRightLeftRot(TreeNode<T> * node){
         if (node->rightChild && !node->leftChild) {
                if (!node->rightChild->rightChild && node->rightChild->leftChild) {
                    return true;
                }
         }

        return false;
    }


};



// do not edit below this line

#endif
