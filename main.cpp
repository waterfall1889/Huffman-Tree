#include <iostream>
#include "HuffmanTree.h"
#include "HuffmanCoder.h"

int main() {
    std::vector<char> list;
    std::string str;
    std::cin>>str;
    for(int i=0;i<=str.size()-1;++i){
        list.push_back(str[i]);
    }
    Huffmancoder<char> tree(list);
    tree.printResult(list);
}
