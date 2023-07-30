#include<bits/stdc++.h>
using namespace std;

int main(){
    int res=4, proc=5;
    int finish[proc]={ }, ans[proc]={-1}, m=0, need[proc][res];
    int available[res] = {1, 5, 2, 0};
    int allocation[proc][res] = {
                        {0, 0, 1, 2},
                        {1, 0, 0, 0},
                        {1, 3, 5, 4},
                        {0, 6, 3, 2},
                        {0, 0, 1, 4}};

    int max[proc][res] = {
                    {0, 0, 1, 2},
                    {1, 7, 5, 0},
                    {2, 3, 5, 6},
                    {0, 6, 5, 2},
                    {0, 6, 5, 6}};

    for(int i=0;i<proc;i++){
        for(int j=0;j<res;j++){
            need[i][j] = max[i][j] - allocation[i][j];}
    }

    cout << "Need: " << endl;

    for(int i=0;i<proc;i++){

        for(int j=0;j<res;j++){
            cout << need[i][j] << " ";
        }

        cout << endl;
    }

    for(int i=0; i<proc; i++){
        finish[proc]=0;
    }

    for(int k=1;k<=3;k++){
        for(int i=0;i<proc;i++){
            if(finish[i] == 0){
                int flag=0;

                for(int j=0;j<res;j++){
                    if (need[i][j] > available[j]){
                        flag = 1;
                         break;
                    }
                }
 
                if(flag == 0){
                    ans[m++] = i;
                    for (int j=0;j<res;j++){
                        available[j]+=allocation[i][j];
                    }
                    finish[i] = 1;
                }
            }
        }
    }

    int flag=1;
    for(int i=0;i<proc;i++){

       if(finish[i]==0){
        flag=0;
        cout << "**** Not Safe System ****" << endl;
        break;
      }
    }

    if(flag){  

        cout << "Sequence of safe system:" << endl; 
        for(int i=0;i<proc-1;i++){
            cout << ans[i] << " , ";
        }
        cout << ans[proc-1] << endl;
    }

}
