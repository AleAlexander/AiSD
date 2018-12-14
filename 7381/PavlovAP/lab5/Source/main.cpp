#include <iostream>
#include <cstring>
#include <sstream>

#include "treap.hpp"

int main(){
    std::string list;
    std::cout << "Enter leafs for tree:" << std::endl;
    getline(std::cin, list);
    std::cout << std::endl;
    std::stringstream ss;
    for(size_t i = 0; i < list.size(); i++)   
        if(isalpha(list[i]))
            std::cout << "Error: " << list[i] << " - was not digit! Stop building the tree..." << std::endl;
    ss.str(list);
    Treap<int> tree;
    int value;
    std::cout << "\t\tWork with tree..." << std::endl;
    while(ss >> value) {
       tree.top = tree.insert(tree.top, value);
    }
    
    std::cout << "The built treap:" << std::endl;
    tree.display(tree.top, nullptr, false);

    int element;
    std::cout << "Enter element that you want to insert: ";
    std::cin >> element;
    if(std::cin.fail()){
        std::cout << "Error: entered value is not digit!" << std::endl;
        return 0;
    }

    if(tree.exists(tree.top, element)){
        std::cout << "Entered element exists in treap!" << std:: endl;
        return 0;
    }
    else{
        std::cout << "Adding new element:\t" << element << std::endl;
        tree.insert(tree.top, element);
        tree.display(tree.top, nullptr, false);
    }   
}