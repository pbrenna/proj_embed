int pow(int a, int b){
	int ret = 1;
	for(;b > 0; b--){
		ret = ret * a;	
	}
	return ret;
}

void nop(){}

int num2string(int num, char* string){
	int i;
	int n_caratteri;
	if(num == 0){	
		string[0] = '+';
		string[1] = '0';
		return 2;
	} 
	if(num<0) {
		string[0] = '-';
	} else {
		string[0] = '+';
	}
	n_caratteri = 0;
	while(num/pow(10,n_caratteri))
		n_caratteri++;
	for(i = n_caratteri;i > 0;i--){
		string[i] = 0x30 + num % 10;
		num = num / 10;
	}			
	return n_caratteri + 1;	
}
