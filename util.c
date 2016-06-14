#include "util.h"
int pow(int a, int b){
	int ret = 1;
	for(;b > 0; b--){
		ret = ret * a;	
	}
	return ret;
}

void nop(){}

int num2string(int num, char precision, char* string){
	int i = 0;
	int n_caratteri = 0;
	if(num == 0){	
		string[0] = '+';
		string[1] = '0';
		return 2;
	} 
	if(num<0) {
		string[0] = '-';
		num = -num;
	} else {
		string[0] = '+';
	}
	n_caratteri = 0;
	while(num/pow(10,n_caratteri))
		n_caratteri++;
	if(precision > 0)
		n_caratteri++;
	for(i = n_caratteri;i > 0;i--){
		if( n_caratteri - i == precision)
			string[i] = '.';
		else{
			string[i] = ASCII0 + num % 10;
			num = num / 10;
		}
	}			
	return n_caratteri + 1;	
}
