#include <iostream> 
#include <vector>
#include <fstream> 
#include <string> 
using namespace std; 

enum Direction{EAST, WEST, SOUTH, NORTH, UP, DOWN}; 
typedef vector<vector<vector<char> > > array3D; 

void solveMaze(array3D maze) {
  

} 

array3D readmaze(string fileName) {
  ifstream infile(fileName); 
  string line; 
  array3D v;
  vector<vector<char> >  vblock; 
  if(infile.is_open()) {
    while(getline(infile,line)) {
      if(line[0]!='#') {
	vector<char> vline; 
	for(int i=0; i<line.length(); ++i) {
	  vline.push_back(line[i]); 
	}
	vblock.push_back(vline); 
      }
      if (line[0]=='#') {
	v.push_back(vblock); 
	vblock.clear(); 
      }
      
    }
  }
  return v; 
}

 
int main() {
  array3D maze; 
  int h=3; 
  int m=3; 
  int n=3; 
  maze.resize(h); 
  for(int i=0; i<h; ++i) {
    maze[i].resize(m); 
    for(int j=0; j<m; ++j) 
      maze[i][j].resize(n); 
  }
  
  
  maze = readmaze("maze.txt"); 
  for(int i=0; i<maze.size();++i) {
    for(int j=0; j<maze[i].size() ; ++j) {
      for(int k=0; k<maze[i][j].size(); ++k) {
	cout << maze[i][j][k]; 
      }
      cout<<endl; 
    }
    cout << endl; 
  }
  cout << maze.size() << endl; 
  solveMaze(maze); 
  return 0; 
}
