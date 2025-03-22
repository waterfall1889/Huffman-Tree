//
// Created by 30884 on 25-3-22.
//

#ifndef HUFFMAN_TREE_HUFFMANCODER_H
#define HUFFMAN_TREE_HUFFMANCODER_H

#include <string>
#include <iostream>
#include "HuffmanTree.h"

template <class V>
class Huffmancoder{
private:
    void CountWeight(std::vector<V> &table,std::vector<TreeNode<V>*> &nodeTable);//count the weight and store in the nodeTable;
    void buildTree(std::vector<TreeNode<V>*> &nodeTable);// build from node table;
    bool isOnTree(const V &data,TreeNode<V> *target){
        if(!target){
            return false;
        }
        if(!target->leftChild && !target->rightChild){
            return (data == target->value);
        }
        bool onLeft = isOnTree(data,target->leftChild);
        bool onRight = isOnTree(data,target->rightChild);
        return (onLeft||onRight);
    }

public:
    HuffmanTree<V> Tree;
    Huffmancoder()=default;
    Huffmancoder(std::vector<V> &table); //build from this vector
    void printResult(std::vector<V> &table);
};

template<class V>
void Huffmancoder<V>::printResult(std::vector<V> &table){
    std::cout<<"||";
    if(table.empty()){
        std::cout<<"No elements!"<<std::endl;
    }
    for(auto item = table.begin();item != table.end();++item){
        TreeNode<V> *begin = Tree.root;
        if(!isOnTree(*item,begin)){
            std::cout<<"???||";
        }
        while(begin->leftChild || begin->rightChild){
            if(isOnTree(*item,begin->leftChild)){
                std::cout<<"0";
                begin = begin->leftChild;
            }
            else if(isOnTree(*item,begin->rightChild)){
                std::cout<<"1";
                begin = begin->rightChild;
            }
        }
        std::cout << "||";

    }
}

template<class V>
void Huffmancoder<V>::CountWeight(std::vector<V> &table, std::vector<TreeNode<V> *> &nodeTable) {
    if(table.empty()){
        return;
    }
    for(auto item = table.begin();item != table.end();++item){
        bool isExisted = false;
        auto Node = nodeTable.begin();
        for(;Node != nodeTable.end();++Node){
            if((*Node)->value == (*item)){
                isExisted = true;
                break;
            }
            else{
                continue;
            }
        }
        if(isExisted){
            (*Node)->weight++;
        }
        else{
            auto *newNode = new TreeNode<V>(1,(*item), nullptr, nullptr);
            nodeTable.push_back(newNode);
        }
    }



}

template<class V>
void Huffmancoder<V>::buildTree(std::vector<TreeNode<V> *> &nodeTable) {
    Tree.build(nodeTable);
}

template<class V>
Huffmancoder<V>::Huffmancoder(std::vector<V> &table) {
    std::vector<TreeNode<V> *> nodeTable;
    CountWeight(table,nodeTable);
    buildTree(nodeTable);
}


#endif //HUFFMAN_TREE_HUFFMANCODER_H
