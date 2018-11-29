#include <algorithm>
#include <string>
#include <iostream>
#include "BinTree.hpp"
bool analyzer(std::string& inputStr, int& index);
bool treatment(std::string& inputStr, int& index);

bool treatment(std::string& inputStr, int& index){
    inputStr.erase(std::remove_if(inputStr.begin(), inputStr.end(), isspace), inputStr.end());//delete spaces

    if(inputStr.empty()){
        std::cout << "Input is empty!" << std::endl;
        return false;
    }
    if(analyzer(inputStr, index)){
        if(inputStr[index+1] != '\0'){
            std::cout << "Extra characters in the input!" << std::endl;
            return false;
        }
    }
    else {
        std::cout << "Binary tree record is wrong!" <<std::endl;
        return false;
    }
    index = 0;
	return true;
}

bool analyzer(std::string& inputStr, int& index){
    if(inputStr[index] == '('){
        ++index;
        if (isprint(inputStr[index]) && inputStr[index] != '#') {
            if(analyzer(inputStr, ++index) && analyzer(inputStr, ++index)){          
                if(inputStr[++index] == ')')
                    return true;
                else return false;
            }
            else return false;
        }
        else return false;
    }
    else if(inputStr[index] == '#')
        return true;
    else return false;
}

int main(){
    int index = 0;
    std::string inputStr1;
    std::string inputStr2;

    std::cout << "Enter binary tree1: mark empty as '#'" << std::endl << "Example: (a(b##)(c##))" << std::endl;
    std::getline(std::cin, inputStr1);
    if(!treatment(inputStr1, index))
        return 0;
    
    std::cout << "Enter binary tree2: mark empty as '#'" << std::endl << "Example: (a(b##)(c##))" << std::endl;
    std::getline(std::cin, inputStr2);
    if(!treatment(inputStr2, index))
        return 0;

    std::cout << "Binary tree1..." << std::endl;
    binTree tree1(inputStr1, index);
    tree1.print();
    index = 0;
    std::cout << std::endl << std::endl;

    std::cout << "Binary tree2..." << std::endl;
    binTree tree2(inputStr2, index);
    tree2.print();
    std::cout << std::endl << std::endl;

    std::cout << std::endl << "Cheking for similarity and equality..." << std::endl;
    if (binTree::similarityTree(&tree1, &tree2))
        std::cout << "Binary trees are similar" << std::endl;
    else std::cout << "Binary trees are not similar" << std::endl;

    if (binTree::equalTree(&tree1, &tree2))
        std::cout << "Binary trees are equal" << std::endl;
    else std::cout << "Binary trees are not equal" << std::endl;

    std::cout << std::endl << "Cheking for mirror similarity and symmetry..." << std::endl;
    if (binTree::isMirrowTree(&tree1, &tree2))
        std::cout << "Binary trees are mirrored" << std::endl;
    else std::cout << "Binary trees are not mirrored" << std::endl;
    
    if(binTree::isMirrowEqualTree(&tree1, &tree2))
         std::cout << "Binary trees are symmetrical" << std::endl;
    else std::cout << "Binary trees are not symmetrical" << std::endl;
    return 0;
}