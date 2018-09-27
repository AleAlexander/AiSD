#include <stdio.h>

int rowsBrackets(int index, int * checkCallRows, char a);

void print_tabs(int index){//for print tabs
	for(int i = 0; i < index; i++)
		printf("\t");
}

enum err_num{err1 = 1, err2, err3, err4};
void errorMessage(enum err_num numberError, int index){
	print_tabs(index-1);
	switch(numberError){
		case 1: 
			printf("ERROR: Unknown symbol\n");
			break;
		case 2: 
			printf("ERROR: Missing '('\n");
			break;
		case 3:  
			printf("ERROR: Missing ')'\n");
			break;
		default: 
			printf("ERROR: Unkown command\n");
		}
}

int brackets(int index, int * checkCallRows){
	int result = 0;
    char a = getchar();
    print_tabs(index);
    printf("CALL_BRACKETS with symbol '%c'\n", a);
    index++;
    if (a == 'A')
    {
        a = getchar();
        if (a == '(')
        {
            if(rowsBrackets(index, checkCallRows, a))
            {
                a = getchar();
                if(a == ')')
                    result = 1;
                else {
                    errorMessage(3, index);
                    result = 0;
                }
            }
        }
        else if((a == EOF)||(a == '\n'))//for single A
        {
        	ungetc(a, stdin);
        	result = 1;
        }
        else if(a == ';' || a == ')')
        {
        	if((*checkCallRows)!=0)
        	{
        		ungetc(a, stdin);
            	result = 1;
        	}
        	else {
        		errorMessage(2, index);
        		result = 0;
        	}
        }
        else{
        	errorMessage(1, index);
        	result = 0;
        } 
    }   
    else{
    	errorMessage(1,index);
    	result = 0;
    }  
    print_tabs(index-1);
	printf("END_BRACKETS\n");
    return result;
}

int rowsBrackets(int index, int * checkCallRows, char a){
	print_tabs(index);
	printf("CALL_ROW_BRACKETS with symbol '%c'\n", a);
	int result = 0;
	(*checkCallRows) = 1;
	index++;
    if (brackets(index, checkCallRows))
    {
        a = getchar();
        if (a == ';')
        {
            if(rowsBrackets(index, checkCallRows, a))
                result = 1;
        }   
        else{
        	ungetc(a, stdin);
        	result = 1;
        }          
    }
    print_tabs(index-1);
	printf("END_ROW_BRACKETS\n");
    return result;
}

int main(){
	int checkCallRows = 0;//to check the function call
	int index = 0;//index for tabs
	char ch = getchar();
	if(ch == '\n' || ch == EOF){
		printf("Input empty\n");
		return 0;
	}
    else
    	ungetc(ch, stdin);
    if(brackets(index, &checkCallRows))
        printf("It is brackets\n");
    else 
    	printf("It isn't brackets\n");
    return 0;
}