#include <iostream>
#include <string>
#include "stack.hpp"
#define TEST

char * readStr(char * bufferStr, char ch, int length){//reading string for false of true
	bufferStr[0] = ch;
	int i;
	for(i = 1; i < (length - 1); i++)
		bufferStr[i] = std::cin.get();
	bufferStr[i] = '\0';
	return bufferStr;
}

bool check(){
	char ch = std::cin.get();
	if(ch == ')' || ch == '&' || ch == '|' || ch == '\n' || ch == EOF || ch == ' '){
		std::cin.putback(ch);
		return true;
	}
	else return false;
}

char * demonstate(bool tmp, char * str){//function for demonstration
	if(tmp)								
		strcpy(str, "true");
	else
		strcpy(str, "false");
	return str;
}
//logical expression validation function
bool analyzer(Stack <char> & stackOperand, Stack <bool>& stackLogik){
	char ch;
	char * bufferStr = nullptr;
	while((ch = std::cin.get()) == ' ')//ignore spaces
		;
	if(ch == 't')
	{
		bufferStr = new char[6];
		if(!strcmp(readStr(bufferStr, ch, 5), "true"))
		{
			delete [] bufferStr;
			if(check()){
				stackLogik.push(true);
				return true;
			}
			return false;
		}
		else{
			delete [] bufferStr;
			return false;
		}
	}
	else if(ch == 'f')
	{
		bufferStr = new char[6];
		if(!strcmp(readStr(bufferStr, ch, 6), "false"))
		{
			delete [] bufferStr;
			if(check()){
				stackLogik.push(false);
				return true;
			}
			return false;
		}
		else{
			delete [] bufferStr;
			return false;
		}
	}
	else if(ch == '('){
		while((ch = std::cin.get()) == ' ')//ignore spaces
			;
		if(ch == '!')
		{
			stackOperand.push(ch);
			if(analyzer(stackOperand, stackLogik))
			{
				while((ch = std::cin.get()) == ' ')//ignore spaces
					;	
				if(ch == ')')
					return true;
				else return false;
			}
			else return false;
		}
		else{
			std::cin.putback(ch);
			if(analyzer(stackOperand, stackLogik))
			{
				while((ch = std::cin.get()) == ' ')//ignore spaces
					;
				if(ch == '&' || ch == '|')
				{
					stackOperand.push(ch);
					if(analyzer(stackOperand, stackLogik))
					{
						while((ch = std::cin.get()) == ' ')
							;
						if(ch == ')')
							return true;
						else return false;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
	}
	else return false;
}

bool calc(Stack <char> & stackOperand, Stack <bool>& stackLogik){
#ifdef TEST
	std::cout<<"Calculating logical expression..."<<std::endl;
#endif
	char * str1 = new char[6];//for
	char * str2 = new char[6];//
	char * str3 = new char[6];//
	bool tmp1, tmp2;		  //demonstate
	char operand;
	bool result;
	while(!stackOperand.isEmpty()){
#ifdef TEST
		std::cout<<"---------"<<std::endl;
#endif	
		if((operand = stackOperand.pop()) == '&'){
			result = ((tmp1 = stackLogik.pop()) & (tmp2 = stackLogik.pop()));
			stackLogik.push(result);
#ifdef TEST
			std::cout<<demonstate(tmp1, str1)<<operand<<demonstate(tmp2, str2)<<'='<<demonstate(result, str3)<<std::endl;
#endif
		}
		else if(operand == '|'){
			result = ((tmp1 = stackLogik.pop()) | (tmp2 = stackLogik.pop()));
			stackLogik.push(result);
#ifdef TEST
			std::cout<<demonstate(tmp1, str1)<<operand<<demonstate(tmp2, str2)<<'='<<demonstate(result, str3)<<std::endl;
#endif
		}
		else{ 
			result = !(tmp1 = stackLogik.pop());
			stackLogik.push(result);
#ifdef TEST
			std::cout<<operand<<demonstate(tmp1, str1)<<'='<<demonstate(result, str3)<<std::endl;
#endif
		}
	}
	if(!stackLogik.isEmpty()){
#ifdef TEST
		std::cout<<"---------"<<std::endl;
#endif
		result = stackLogik.pop();
#ifdef TEST
		std::cout<<demonstate(result, str3)<<std::endl;
#endif
	}
	delete [] str1;
	delete [] str2;
	delete [] str3;
	return result;
}

int main(){
	char ch;
	while((ch = std::cin.get()) == ' ')//ignore spaces
		;
	if(ch == '\n' || ch == EOF){  //if input is empty
		std::cout<<"Input is empty"<<std::endl;
		return 0;
	}
	else 
		std::cin.putback(ch);
	Stack <char> stackOperand(2);//operand stack initialization
	Stack <bool> stackLogik(2);  //stack initialization for logical statements: true, false
#ifdef TEST	
	std::cout<<"Reading logical expression..."<<std::endl;
#endif
	if(analyzer(stackOperand, stackLogik)){
		if(calc(stackOperand, stackLogik))
			std::cout<<"Logical expression is true!"<<std::endl;
		else 
			std::cout<<"Logical expression is false!"<<std::endl;
	}
	else 
		std::cout<<"Incorrect logical expression!"<<std::endl;
}
