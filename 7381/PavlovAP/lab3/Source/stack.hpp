#include <iostream>
#define TEST
template <typename Type>
class Stack
{
private:
    Type *array;                   //stack pointer
    size_t size;                   //maximum number of items in the stack
    int topElem;                   //current stack item number
public:
	Stack();
    Stack(size_t size);              
    ~Stack();                       //destructor
    void push(Type);     			//put an item at the top of the stack
    Type pop();                   	//remove an item from the top of the stack and return it
	bool isEmpty();					//check for stack emptiness
};
 
//Stack constructor
template <typename Type>
Stack<Type>::Stack(){
	array = nullptr;
	size = 0;
	topElem = 0;
}

template <typename Type>
Stack<Type>::Stack(size_t maxSize){
	array = new Type[maxSize]; //allocate stack memory
    size = maxSize; 		   //stack size initialization
    topElem = 0;               //initializing the current element to zero
}
 
//destructor
template <typename Type>
Stack<Type>::~Stack(){
    delete [] array; //remove stack
}
 
//add item to stack function
template <typename Type>
void Stack<Type>::push(Type value){
#ifdef TEST
	std::cout<<"Push element: "<<value<<std::endl;
#endif
	array[topElem] = value;
    ++topElem;
    //If the stack is full, the amount of allocated memory increases in 2 times
    if (topElem == size) {
        size_t new_size = size * 2;
		//Copying the contents of the stack to a new memory area
        Type *new_array = new Type[new_size];
        for (size_t index = 0; index < size; ++index)
            new_array[index] = array[index];
        delete[] array; //remove old data

        size = new_size;
        array = new_array;
    }
}
 
//function to remove an item from the stack
template <typename Type>
Type Stack<Type>::pop()
{
    if(isEmpty()){
		std::cout<<"Error: Stack is empty"<<std::endl;
		exit(1);
	}
#ifdef TEST
	std::cout<<"Pop element: "<<array[topElem-1]<<std::endl;
#endif	
    return array[--topElem];
}

template <typename Type>
bool Stack<Type>::isEmpty(){
	if(!topElem)
		return true;
	return false;
}


 