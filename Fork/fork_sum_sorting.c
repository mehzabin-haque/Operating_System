#include<bits/stdc++.h>
#include<unistd.h>
int main(){
	pid_t pid = fork();
	pid_t pid2= fork();
	int n;
	cout << "Enter the number of elements : " ;
	cin >> n;
	int count=0,arr[n],sum=0,sum1=0;
	map<int,int> mp;
	cout << endl << "Enter the numbers : " ;
	for(int i=0;i<n;i++){
		cin >> arr[i];
		mp[arr[n]]++;
	}
	for(int i=0;i<n;i++){
		if(arr[i]%2 == 0){
			sum = sum + arr[i] ;
		}
		sum1 = sum1 + arr[i];
		if(arr[i]>arr[i+1]){
			swap(arr[i],arr[i+1]);
		}
	}
	
	int num;
	
	if(pid!=0 && pid2!=0){
		cout << "Enter the number wanna know : " << endl;
		cin >> num;
		cout << "Frequency : " << mp[num] << endl;
	}

	else if(pid==0 && pid2!=0){
		cout << "Even num sum : " << sum << endl;
	}

	else if(pid!=0 && pid2==0){
		cout << "Sum : " << sum1 << endl;
	}
	
	else{
		cout << "Sorting : " ;
		for(int i=0;i<n;i++){
			cout << arr[i] << "  " ;
		}
	}

}
