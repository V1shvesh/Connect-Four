#include<bits/stdc++.h>
using namespace std;

typedef struct player
{
string name;
int score;
}player;

int main()
{
  multimap <int,string, greater <int>> boxer;
  cout<<"Enter no. of boxers"<<endl;
  int n;
  cin>>n;
  for(int i=0;i<n;i++)
  {
      string naam;
      cout<<"Enter "<<i+1<<" Name"<<endl;
      cin>>naam;
      cout<<"Enter score"<<endl;
      int sc;
      cin>>sc;
      boxer.insert(make_pair(sc, naam) );
  }

   multimap<int,string> :: iterator it;
   for (it=boxer.begin() ; it!=boxer.end() ; it++)
     cout << "(" << (*it).first << ", "
             << (*it).second << ")" << endl;
}
