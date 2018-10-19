
#include "functions.h"
#include <iostream>
#include <cstdlib>

namespace h_list
{

//....................................
	lisp head (const lisp s){    // PreCondition: not null (s)
		if (s != NULL) 
			if (!isAtom(s))	
				return s->node.pair.hd;
			else{
				std::cerr << "Error: Head(atom) \n";
				exit(1); 
			}
		else{ 
			std::cerr << "Error: Head(nil) \n";
			exit(1);
		}
	}
//.......................................
	bool isAtom (const lisp s){	
		if(s == NULL) 
			return false;
		else 
			return (s -> tag);
	}
//.......................................
	bool isNull (const lisp s){ 
		return s==NULL;
	}
//.......................................
	lisp tail (const lisp s)
{// PreCondition: not null (s)
		if (s != NULL) 
			if (!isAtom(s))	
				return s->node.pair.tl;
			else{
				std::cerr << "Error: Tail(atom) \n";
				exit(1);
			}
		else{
			std::cerr << "Error: Tail(nil) \n";
			exit(1);
		}
	}
//.......................................
	lisp cons (const lisp h, const lisp t){
	// PreCondition: not isAtom (t)
	lisp p;
	if (isAtom(t)){
		std::cerr << "Error: Tail(nil) \n";
		exit(1);
	}
	else{	
		p = new s_expr; 
		if ( p == NULL){
			std::cerr << "Memory not enough\n";
			exit(1);
		} 	
		else {
			p->tag = false;
			p->node.pair.hd = h;
			p->node.pair.tl = t;
			return p;	
		}
	}
	}
//...........................
	lisp make_atom (const base x){
		lisp s;
		s = new s_expr;
		s -> tag = true;
		s->node.atom = x;
		return s;
	}

//...........................
void destroy (lisp s){
	if ( s != NULL) {
		if (!isAtom(s)) {
			destroy ( head (s));
			destroy ( tail(s));
		}
		delete s;
		// s = NULL;
	}
}
//...........................
	base getAtom (const lisp s)
	{
		if (!isAtom(s)){ 
			std::cerr << "Error: getAtom(s) for !isAtom(s) \n";
			exit(1);
		}
		else 
			return (s->node.atom);
	}

	
//...........................
// enter list from console
	void read_lisp ( lisp& y){	
		base x;
		do{
			std::cin >> x;
		}while (x==' ');
		read_s_expr ( x, y);
	} //end read_lisp
//...........................
	void read_s_expr (base prev, lisp& y)
	{ //prev - early read character
		if ( prev == ')' ) {
			std::cerr << " ! List.Error 1 " << std::endl;
			exit(1);
		} 
		else if ( prev != '(' ) {
			y = make_atom (prev);
		}
		else{ 
			read_seq (y);
		}
	} //end read_s_expr
//...........................
	void read_seq ( lisp& y) 
	{	base x; 
		lisp p1, p2;

		if (!(std::cin >> x)){
			std::cerr << " ! List.Error 2 " << std::endl;
			exit(1);
		}
		else {
			while( x==' ' ) 
				std::cin >> x;
			if ( x == ')' ){ 
				y = NULL;
			}
			else {
				read_s_expr ( x, p1);
				read_seq ( p2);
				y = cons (p1, p2);
			} 
		}
	} //end read_seq
//...........................
// The procedure for displaying a list with brackets framing it - write_lisp,
//  and without framing brackets - write_seq
	void write_lisp (const lisp x){
//	cout << "in write_lisp" << endl;
	//empty list is displayed as () 
	if (isNull(x)) 
		std::cout << " ()";
	else if (isAtom(x)) 
		std::cout << ' ' << x->node.atom;
	else  { //non-empty list
			std::cout << " (" ;
			write_seq(x);
			std::cout << " )";
		}
	} // end write_lisp
//...........................
void write_seq (const lisp x)  
{//displays a sequence of elements of the list without brackets framing it
	if (!isNull(x)) {
		write_lisp(head (x)); 
		write_seq(tail (x));
	}
}
} // end of namespace h_list
