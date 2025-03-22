//
// Created by 30884 on 25-3-22.
//

#ifndef HUFFMAN_TREE_HUFFMANTREE_H
#define HUFFMAN_TREE_HUFFMANTREE_H


#include <vector>
#include <algorithm>

template <class V>
class TreeNode{
public:
    int weight;
    V value;
    TreeNode *leftChild;
    TreeNode *rightChild;

    TreeNode():weight(0),value(0),leftChild(nullptr),rightChild(nullptr){};
    TreeNode(int weight,const V &NodeValue,TreeNode *left = nullptr,TreeNode *right = nullptr):
            weight(weight),value(NodeValue),leftChild(left),rightChild(right){};
};

template <class V>
class HuffmanTree{
private:

    void clear(TreeNode<V> *target);
public:
    TreeNode<V> *root;

    HuffmanTree():root(nullptr){};
    ~HuffmanTree();
    void clear();

    TreeNode<V> *build(std::vector<TreeNode<V> *> &nodeArray);
    void sortNodesByWeight(std::vector<TreeNode<V> *>& nodeArray);
};

template<class V>
void HuffmanTree<V>::sortNodesByWeight(std::vector<TreeNode<V> *> &nodeArray) {
    if (nodeArray.size() > 1) {
        std::sort(nodeArray.begin(), nodeArray.end(), [](TreeNode<V>* a, TreeNode<V>* b) {
            return a->weight < b->weight;
        });
    }
}

template<class V>
TreeNode<V> *HuffmanTree<V>::build(std::vector<TreeNode<V> *> &nodeArray) {
    if(nodeArray.empty()){
        return nullptr;
    }
    else if(nodeArray.size() == 1){
        this->root = new TreeNode<V>(nodeArray[0]->weight,nodeArray[0]->value, nullptr, nullptr);
        return this->root;
    }
    //1.first we need to sort the nodes by weight
    sortNodesByWeight(nodeArray);

    //2.build subtree and then continue until one tree left.
    while(nodeArray.size()!=1){
        auto *internalNode = new TreeNode<V>(nodeArray[0]->weight+nodeArray[1]->weight,
                                             0,nodeArray[0],nodeArray[1]);
        nodeArray.erase(nodeArray.begin(), nodeArray.begin() + 2);
        bool inserted = false;
        for (auto item = nodeArray.begin(); item != nodeArray.end(); ++item) {
            if ((*item)->weight >= internalNode->weight) {
                nodeArray.insert(item, internalNode);
                inserted = true;
                break;
            }
        }
        if (!inserted) {
            nodeArray.push_back(internalNode);
        }

    }
    //3.return the root.
    this->root = nodeArray[0];
    return nodeArray[0];
}

template<class V>
HuffmanTree<V>::~HuffmanTree() {
    clear();
}

template<class V>
void HuffmanTree<V>::clear() {
    clear(this->root);
}

template<class V>
void HuffmanTree<V>::clear(TreeNode<V> *target) {
    if(!target){
        return;
    }
    clear(target->leftChild);
    clear(target->rightChild);
    delete target;
}


#endif //HUFFMAN_TREE_HUFFMANTREE_H
