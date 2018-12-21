#include <iostream>
#include <cstdlib>
#include <utility>//for pair

#define TEST

template <typename Type>
class Treap{
    struct node{
        Type key;
        int priority;
        node * left;
        node * right;
    };
public:
    node * top;//pointer to the root of treap

    Treap(){
        top = nullptr;
    }

    bool exists(node * root, Type val){
        if(root == nullptr)
            return false;
        if(val == root->key)
            return true;
        if(val > root->key)
            return exists(root->right, val);
        return exists(root->left, val);
    }

    std::pair <node *, node *> split(node * root, Type val){//cutting two trees by value
        if(root == nullptr)
            return {nullptr, nullptr};
        if(root->key <= val){
            auto res = split(root->right, val);
            root->right = res.first;
            return {root, res.second};
        }
        else{
            auto res = split(root->left, val);
            root->left = res.second;
            return {res.first, root};
        }
    }

    node * merge(node * root1, node * root2){//merging two trees with priority
        if(root1 == nullptr)
            return root2;
        if(root2 == nullptr)
            return root1;
        if(root1->priority <= root2->priority){
#ifdef TEST
			std::cout << "Priority " << root1->priority << " <= " << root2->priority << " , go to the right subtree" << std::endl;
#endif
            root1->right = merge(root1->right, root2);
            return root1;
        }
        else{
#ifdef TEST
			std::cout << "Priority " << root1->priority << " > " << root2->priority << " , go to the left subtree" << std::endl;
#endif
            root2->left = merge(root1, root2->left);
            return root2;
        }
    }

    node * insert(node * root, Type val){
        if(exists(root, val)){
            std::cout << "Entered element has already inserted in treap" << std::endl;
            return root;
		}
#ifdef TEST
        std::cout << "Adding:\t" << val << std::endl;
#endif
        auto res = split(root, val);
#ifdef TEST
        std::cout << "Two treaps after split:" << std::endl;
        std::cout << "Treap with key <= " << val << std::endl;
        display(res.first, nullptr, false);
        std::cout << std::endl << "Treap with key > " << val << std::endl;
        display(res.second, nullptr, false);
#endif
        node * newnode = new node;
        newnode->key = val;
        newnode->priority = rand();
        newnode->left = nullptr;
        newnode->right = nullptr;

        node * tmp1 = merge(res.first, newnode);
#ifdef TEST
        std::cout << "Treap after first merge: " << std::endl;
        display(tmp1, nullptr, false);
#endif		
        node * tmp2 = merge(tmp1, res.second);
#ifdef TEST
        std::cout << "Treap after second merge: " << std::endl;
        display(tmp2, nullptr, false);
#endif
        return tmp2;
      //  return merge(merge(res.first, newnode), res.second);
    }
	
	node * erase(node * root, int val){//
		if(!exists(root, val)){
			std::cout << "Entered element has not inserted in treap" << std::endl;
			return root;
		}
#ifdef TEST
		std::cout << "Spliting key - " << val << std::endl << std::endl;
#endif		
		auto res1 = split(root, val);
#ifdef TEST
		std::cout << "Treaps after first split" <<std::endl << std::endl;
		std::cout << "Treap with key <= " << val << std::endl;
		display(res1.first, nullptr, false);
		std::cout << std::endl << "Treap with key > " << val << std::endl;
		display(res1.second, nullptr, false);
#endif		
		auto res2 = split(res1.first, val - 1);
#ifdef TEST
		std::cout << std::endl << "Treaps after second split" <<std::endl << std::endl;
		std::cout << "Treap with key < " << val << std::endl;
		display(res2.first, nullptr, false);
		std::cout << "Treap with " << val << " to be deleted" << std::endl;
		display(res2.second, nullptr, false);
#endif
		delete res2.second;
		node * tmp = merge(res2.first, res1.second);
#ifdef TEST
		display(tmp, nullptr, false);
#endif
		return tmp;
		//return merge(res2.first, res1.second);

	}

    ~Treap(){//destructor
        if(top)
            remove(top);
    }

    void remove(node * root){//remove tree
        if(root == nullptr)
            return;
        remove(root->left);
        remove(root->right);
        delete root;
    }

    struct Trunk {//structure for printing treap
        Trunk *prev;
        std::string branch;
        Trunk(Trunk *prev, std::string branch) {
            this->prev = prev;
            this->branch = branch;
        }
    };
     void showTrunks(Trunk *p) {//An auxiliary method for printing branches of a treap
        if(p == nullptr)
            return;
        showTrunks(p->prev);
        std::cout << p->branch;
    }
     void inorder(node* t, Trunk* prev, bool isRight) {      //method for print treap
        if(t == nullptr)
            return;
        std::string prev_str = "    ";
        Trunk *trunk = new Trunk(prev, prev_str);
        inorder(t->right, trunk, true);
        if(!prev)
            trunk->branch = "---";
        else if(isRight) {
            trunk->branch = ".---";
            prev_str = "   |";
        }
        else {
            trunk->branch = "`---";
            prev->branch = prev_str;
        }
        showTrunks(trunk);
        std::cout << "(" <<t->key << "; " << t->priority << ")" << std::endl;
         if(prev)
            prev->branch = prev_str;
        trunk->branch = "   |";
         inorder(t->left, trunk, false);
        delete trunk;
    }

     void display(node * root, Trunk * prev, bool isRight) {        //method for print treap
            if(!root) {
                std::cout << "Treap is empty!" << std::endl << std::endl;
                return;
            }
            inorder(root, nullptr, false);
            std::cout << std::endl;
        }
};
