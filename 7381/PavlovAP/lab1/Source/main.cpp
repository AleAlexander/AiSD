
#include <iostream>
#include <cstdlib>
#include "functions.h"


using namespace h_list;
void printTabs(int count);
void deleteHead(lisp s_cur, lisp tmpAtom);
void deleteTail(lisp s_cur, lisp tmpAtom);
void throwing_pointers(lisp s_cur, lisp s_prev);
void deleteAtom(lisp s_prev, lisp s_cur, base element, int flag, int count);// delete function

int main(){
	
	lisp s_prev, s_cur, start;// s_prev - pointer on Atom ; start - pointer on fictitious head for delete the true head of list; s_cur - poinet on true list
	base element;
	std::cout << std::boolalpha;
	std::cout << "Enter list:" << std::endl;
	read_lisp (s_cur);
	
	std::cout << "Entered list: " << std::endl;
	write_lisp (s_cur);
	std::cout << std::endl;
	
	s_prev = make_atom('S');//atom creation
	start = cons(s_prev, s_cur);//merging the list with a fictitious head
	
	std::cout << "Enter atom that you want to delete" << std::endl;
	std::cin >> element;
	
	deleteAtom(start, s_cur, element, 0, 0);
	
	std::cout << "List without deleted atoms" << std::endl;
	write_lisp(tail(start));
	std::cout << std::endl;
	
	std::cout << "destroy list: " << std::endl;
	destroy (start);
	
	std::cout << "end! " << std::endl;
	return 0;
}                                                     //duplicate
void deleteTail(lisp s_cur, lisp tmpAtom){            //
	tmpAtom = head(s_cur);                            //
	s_cur -> node.pair.hd = NULL;                     //lines
	delete tmpAtom;                                   //
}                                                     //are
                                                      //
void deleteHead(lisp s_cur, lisp tmpAtom){            //separated
	tmpAtom = head(s_cur);                            //      
	s_cur -> node.pair.hd = NULL;                     //into
	delete tmpAtom;                                   //
}                                                     //separatefunctions

void printTabs(int count){                            //show recursion
	for(int i = 0; i < count; i++)
		std::cout << '\t';
}

void deleteAtom(lisp s_prev, lisp s_cur, base element, int flag, int count){//s_prev - pointer on previous element of list
	printTabs(count);                                                       //s_cur - pointer on current element of list
	std::cout << "call deleteAtom" << std::endl;
	count++;
	if(s_cur == NULL){
		return;
		printTabs(count-1);
		std::cout << "llac deleteAtom" <<std::endl;
	}
	lisp tmpAtom = NULL; //variable to store an atom
	while(s_cur!= NULL)
	{
		if(isAtom(head(s_cur)))//if head is atom 
		{
			if(getAtom(head(s_cur)) == element)  //check atom 
			{	
				if(isAtom(head(s_prev)) || (flag==1))
				{
					if(tail(s_cur) == NULL)//to delete the tail of list
					{
						deleteTail(s_cur, tmpAtom);
						s_prev -> node.pair.tl = NULL;
						delete s_cur;
						s_cur = NULL;
					}
					else                  //to delete the any correct element expect tail
					{
						deleteTail(s_cur, tmpAtom);
						s_prev -> node.pair.tl = s_cur -> node.pair.tl;
						tmpAtom = s_cur -> node.pair.tl;
						delete s_cur;
						s_cur = tmpAtom;						
					}	
				}
				else
				{
					flag = 1;
					if(tail(s_cur) == NULL)//to delete the tail of list on next level
					{
						deleteHead(s_cur, tmpAtom);
						s_prev -> node.pair.hd = NULL;
						delete s_cur;
						s_cur = NULL;
					}
					else
					{
						deleteHead(s_cur, tmpAtom);
						tmpAtom = tail(s_cur);
						s_prev -> node.pair.hd = tmpAtom;
						delete s_cur;
						s_cur = tmpAtom;
					}
				}
			}
			else{                          //throwing pointers to move through the list
				s_prev = s_cur;
				s_cur = s_cur -> node.pair.tl;
			}
		}
		else if(!isAtom(head(s_cur))){     //call deleteAtom for next level
			flag = 0;
			deleteAtom(s_cur, s_cur->node.pair.hd, element, flag, count);
			flag = 1;
			s_prev = s_cur;
			s_cur = s_cur->node.pair.tl;
		}
	}
	printTabs(count-1);
	std::cout << "llac deleteAtom" <<std::endl;
}
	