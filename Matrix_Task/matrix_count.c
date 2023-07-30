#include<stdio.h>
int a[3][9000];
int c;
int main(){

	for(int i=0;i<3;i++){
	  for(int j=0;j<9000;j++){
		a[i][j] = 1;
	  }
	}
	
	for(int i=0;i<3;i++){
	  for(int j=0;j<9000;j++){
		if((a[i][j] == 1)){
			c++;
		}
	  }
	}

	printf("%d",c);
}
