
#include <iostream>

void print_tabs(size_t tabs_count);
enum side_t { LEFT, RIGHT };

void print_tabs(size_t tabs_count) {
    for (size_t i = 0; i < tabs_count; ++i)
        std::cout << '\t';
}

class binTree{
    private:
        binTree* root;
        binTree* left;
        binTree* right;
        char data;
    public:
        binTree();
        binTree(const std::string& inputStr, int& index);
        ~binTree();
        binTree * leftTree();
        binTree * rightTree();
        void destroy();
        binTree * read_non_empty_binary_tree(const std::string& inputStr, int& index); 
        void read_binary_tree(const std::string& inputStr, int& index, side_t side);  
        void _print(size_t tabs_count);
        void print();
        size_t height() const;
        static int checkRoot(binTree * tree1, binTree * tree2);
        static bool similarityNode(binTree * tree1, binTree * tree2, size_t tabs_count);
        static bool similarityTree(binTree * tree1, binTree * tree2);
        static bool equalTree(binTree * tree1, binTree * tree2);
        static bool equalNode(binTree * tree1, binTree * tree2);
        static bool isMirrowTree(binTree * tree1, binTree * tree2);
        static bool isMirrowNode(binTree * tree1, binTree * tree2, size_t tabs_count);
        static bool isMirrowEqualTree(binTree * tree1, binTree * tree2);
        static bool isMirrowEqualNode(binTree * tree1, binTree * tree2);
};

binTree::binTree() : root(nullptr), left(nullptr), right(nullptr) { }

binTree::binTree(const std::string& inputStr, int& index) : binTree() {
    root = read_non_empty_binary_tree(inputStr, index);
}

binTree *  binTree::read_non_empty_binary_tree(const std::string& inputStr, int& index){//create tree
    if(inputStr[index] == '#')
        return nullptr;
    ++index;
    data = inputStr[index];
    left = nullptr;
	right = nullptr;
    ++index;
    read_binary_tree(inputStr, index, LEFT);
    ++index;
    read_binary_tree(inputStr, index, RIGHT);
    ++index;
    return this;
}

void binTree::read_binary_tree(const std::string& inputStr, int& index, side_t side) {//create branches
    if (inputStr[index] == '#')
        return;
    else {
        if (side == LEFT) {
            left = new binTree;
            left->read_non_empty_binary_tree(inputStr, index);
        }
        else {
            right = new binTree;
            right->read_non_empty_binary_tree(inputStr, index);
        }
    }       
}

void binTree::_print(size_t tabs_count) {//display tree
    print_tabs(tabs_count);
    std::cout << data << std::endl;
    if (right)
        right->_print(tabs_count + 1);
    else {
        print_tabs(tabs_count + 1);
        std::cout << '#'<<std::endl;
    }
    if (left)
        left->_print(tabs_count + 1);
    else {
        print_tabs(tabs_count + 1);
        std::cout << '#' <<std::endl;
    }
    
}

void binTree::print() {//display tree
    size_t h = height();
    if(!root){
        std:: cout << '#' << std::endl;
        return;
    }
    for (size_t i = 0; i < h + 1; ++i)
        std::cout << i << '\t';
    std::cout << std::endl;
    _print(0);
    for (size_t i = 0; i < h + 1; ++i)
        std::cout << i << '\t';
    std::cout << std::endl;
}

size_t binTree::height() const {
    size_t height_left = 0;
    if (left)
        height_left = left->height();
    size_t height_right = 0;
    if (right)
        height_right = right->height();
    return 1 + std::max(height_left, height_right);
}

int binTree::checkRoot(binTree * tree1, binTree * tree2){
    if((tree1->root) == (tree2->root)){
        std::cout << "comparing: [#]  [#]"<< std::endl;
        return 1;
    }
    else if((tree1->root == nullptr) || (tree2->root == nullptr))
        return 2;
    else return 3;
}

bool binTree::similarityTree(binTree * tree1, binTree * tree2){
    int result = checkRoot(tree1, tree2);
    if(result == 1)
        return true;
    else if(result == 3){
        if(binTree::similarityNode(tree1, tree2, 0))
            return true;
        return false;
    }
    else return false;
}
bool binTree::similarityNode(binTree * tree1, binTree * tree2, size_t tabs_count){
    if(tree1 == tree2)//if tree1 = tree2 = nullptr
        return true;
    
    if(tree1 == nullptr){
        print_tabs(tabs_count);
        std::cout << "comparing: " <<"[#]  " << '[' << tree2->data << ']' << std::endl;
        return false;
    }
    if(tree2 == nullptr){
        print_tabs(tabs_count);
        std::cout << "comparing: " <<'[' << tree1->data << "]  " << "[#]" << std::endl;
        return false;
    }
    print_tabs(tabs_count);
    std::cout << "comparing: " <<'[' << tree1->data << "]  " << '[' << tree2->data << ']' << std::endl;
    return (binTree::similarityNode(tree1->left, tree2->left, tabs_count+1) && binTree::similarityNode(tree1->right, tree2->right, tabs_count+1));
}

bool binTree::equalTree(binTree * tree1, binTree * tree2){
    int result = checkRoot(tree1, tree2);
    if(result == 1)
        return true;
    else if(result == 3){
        if(binTree::equalNode(tree1, tree2))
            return true;
        return false;
    }
    else return false;
}

bool binTree::equalNode(binTree * tree1, binTree * tree2){
    if(tree1 == tree2)//if tree1 = tree2 = nullptr
        return true;
    if(tree1 == nullptr)
        return false;
    if(tree2 == nullptr)
        return false;
    if(tree1->data != tree2->data)
        return false;
    return (binTree::equalNode(tree1->left, tree2->left) && binTree::equalNode(tree1->right, tree2->right));
}

bool binTree::isMirrowTree(binTree * tree1, binTree * tree2){
    int result = checkRoot(tree1, tree2);
    if(result == 1)
        return true;
    else if(result == 3){
        if(binTree::isMirrowNode(tree1, tree2, 0))
            return true;
        return false;
    }
    else return false;
}

bool binTree::isMirrowNode(binTree * tree1, binTree * tree2, size_t tabs_count){
    if(tree1 == tree2)//if tree1 = tree2 = nullptr
        return true;
    if(tree1 == nullptr){
        print_tabs(tabs_count);
        std::cout << "comparing: " <<"[#]  " << '[' << tree2->data << ']' << std::endl;
        return false;
    }
    if(tree2 == nullptr){
        print_tabs(tabs_count);
        std::cout << "comparing: " <<'[' << tree1->data << "]  " << "[#]" << std::endl;
        return false;
    }
    print_tabs(tabs_count);
    std::cout << "comparing: " <<'[' << tree1->data << "]  " << '[' << tree2->data << ']' << std::endl;
    return((binTree::isMirrowNode(tree1->left, tree2->right, tabs_count+1)) && (binTree::isMirrowNode(tree1->right, tree2->left, tabs_count+1)));
}

bool binTree::isMirrowEqualTree(binTree * tree1, binTree * tree2){
    int result = checkRoot(tree1, tree2);
    if(result == 1)
        return true;
    else if(result == 3){
        if(binTree::isMirrowEqualNode(tree1, tree2))
            return true;
        return false;
    }
    else return false;
}

bool binTree::isMirrowEqualNode(binTree * tree1, binTree * tree2){
    if(tree1 == tree2)//if tree1 = tree2 = nullptr
        return true;
    if(tree1 == nullptr)
        return false;
    if(tree2 == nullptr)
        return false;
    if(tree1->data != tree2->data)
        return false;
    return((binTree::isMirrowEqualNode(tree1->left, tree2->right)) &&(binTree::isMirrowEqualNode(tree1->right, tree2->left)));
}

binTree::~binTree(){
    if (left)
		delete left;
	if (right)
		delete right;
} 


