#include <iostream> 
#include <omp.h>
#include<math.h>
using namespace std;

int main(){
//Initialization
int n,i,j,k,p,m;
cout<<"Enter the No. of jobs:";
cin>>n;
int t[n],d[n],s[n],f[n];
cout<<"Enter the processing time of each job below"<<endl;
for(i=0;i<n;i++)cin>>t[i];
cout<<"Enter the deadline of each job below"<<endl;
for(i=0;i<n;i++)cin>>d[i];


//Computing Prefix sum
omp_set_num_threads(n);
#pragma omp parallel for
for(i=0;i<n;i++)s[i]=t[i];
for(j=0;j<log2(n);j++){
  p=pow(2,j);
  #pragma omp parallel for
  for(i=p;i<n;i++){
  s[i]=t[i-p]+t[i];
  //cout<<omp_get_thread_num()<<" ";
  }
  //cout<<endl;
  #pragma omp parallel for 
  for(k=p;k<n;k++){
  t[k]=s[k];
  //cout<<omp_get_thread_num()<<" ";
  }
 //cout<<"\n"<<omp_get_thread_num()<<endl;
}


#pragma omp parallel for
for(i=0;i<n;i++){
if(t[i]<=d[i])f[i]=1;
else f[i]=0;
}

for(j=0;j<log2(n);j++){
  p=pow(2,j);
  #pragma omp parallel for
  for(i=p;i<n;i++){
  s[i]=f[i-p]+f[i];
  }
  #pragma omp parallel for 
  for(k=p;k<n;k++){
  f[k]=s[k];
  }
}
cout<<f[n-1]<<endl;
if(f[n-1]==n)cout<<"Feasible solution"<<endl;
else cout<<"Not feasible"<<endl;
}
