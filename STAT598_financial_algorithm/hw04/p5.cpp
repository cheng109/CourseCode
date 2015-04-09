#include <iostream> 
#include <vector>
#include <fstream> 
#include <string> 
#include <limits.h>
#include <queue> 

using namespace std; 

enum Direction{EAST, WEST, SOUTH, NORTH, UP, DOWN}; 

typedef vector<vector<vector<char> > > array3D;

template<typename T>
vector<vector<vector<T> > > create3Darray(T val){
  vector<vector<vector<T> > >  maze; 
  int h=3; 
  int m=3; 
  int n=3; 
  maze.resize(h); 
  for(int i=0; i<h; ++i) {
    maze[i].resize(m); 
    for(int j=0; j<m; ++j) 
      maze[i][j].resize(n,val); 
  }
  return maze; 
}

struct index {
  int i, j, k; 
  index(int a, int b, int c): i(a), j(b),k(c) {}
}; 
  
void solveMaze(array3D maze) {
  vector<vector<vector<int> > >  dist = create3Darray(INT_MAX);
  vector<Direction> vD; 
  vector<vector<vector<vector<Direction> > > > Path = create3Darray(vD) ;  
  queue<index::index> q;
  q.push(index::index(0,0,0)); 
  dist[0][0][0] = 0; 
  while(!q.empty()) {
    index::index c = q.front(); 
    //Down
    if(c.i+1<3 && maze[c.i+1][c.j][c.k]!='o' && dist[c.i+1][c.j][c.k]==INT_MAX) {
      q.push(index::index(c.i+1, c.j, c.k)); 
      dist[c.i+1][c.j][c.k] = dist[c.i][c.j][c.k] + 1;
      Path[c.i+1][c.j][c.k] = Path[c.i][c.j][c.k]; 
      Path[c.i+1][c.j][c.k].push_back(DOWN); 
    }
    //up
    if(c.i-1>=0 && maze[c.i-1][c.j][c.k]!='o' && dist[c.i-1][c.j][c.k]==INT_MAX) {
      q.push(index::index(c.i-1, c.j, c.k)); 
      dist[c.i-1][c.j][c.k] = dist[c.i][c.j][c.k] + 1; 
      Path[c.i-1][c.j][c.k] = Path[c.i][c.j][c.k]; 
      Path[c.i-1][c.j][c.k].push_back(UP); 

    }
    // South
    if(c.j+1<3 && maze[c.i][c.j+1][c.k]!='o' && dist[c.i][c.j+1][c.k]==INT_MAX) {
      q.push(index::index(c.i, c.j+1, c.k)); 
      dist[c.i][c.j+1][c.k] = dist[c.i][c.j][c.k] + 1; 
      Path[c.i][c.j+1][c.k] = Path[c.i][c.j][c.k]; 
      Path[c.i][c.j+1][c.k].push_back(SOUTH); 

    }
    // North
    if(c.j-1>=0 && maze[c.i][c.j-1][c.k]!='o' && dist[c.i][c.j-1][c.k]==INT_MAX) {
      q.push(index::index(c.i, c.j-1, c.k)); 
      dist[c.i][c.j-1][c.k] = dist[c.i][c.j][c.k] + 1; 
      Path[c.i][c.j-1][c.k] = Path[c.i][c.j][c.k]; 
      Path[c.i][c.j-1][c.k].push_back(NORTH); 

    }
    // East
    if(c.k+1<3 && maze[c.i][c.j][c.k+1]!='o' && dist[c.i][c.j][c.k+1]==INT_MAX) {
      q.push(index::index(c.i, c.j, c.k+1)); 
      dist[c.i][c.j][c.k+1] = dist[c.i][c.j][c.k] + 1; 
      Path[c.i][c.j][c.k+1] = Path[c.i][c.j][c.k]; 
      Path[c.i][c.j][c.k+1].push_back(EAST); 

    }
    // West
    if(c.k-1>=0 && maze[c.i][c.j][c.k-1]!='o' && dist[c.i][c.j][c.k-1]==INT_MAX) {
      q.push(index::index(c.i, c.j, c.k-1)); 
      dist[c.i][c.j][c.k-1] = dist[c.i][c.j][c.k] + 1; 
      Path[c.i][c.j][c.k-1] = Path[c.i][c.j][c.k]; 
      Path[c.i][c.j][c.k-1].push_back(WEST); 

    }

    q.pop(); 
  }
  
  for(int i=0; i<Path[2][2][2].size(); ++i) {
    cout << Path[2][2][2][i] << endl;
  }
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
  array3D maze = create3Darray('0'); 
  
  maze = readmaze("maze.txt"); 
  cout << "Map: \n################# " << endl; 
  for(int i=0; i<3; ++i) {
    for(int j=0; j<3; ++j) {
      for(int k=0; k<3; ++k) {
	cout << maze[i][j][k] << "\t" ; 
      }
      cout<< endl; 
    }
  cout << "#################" << endl;
  }
  cout << "Solution is:" << endl;  
  solveMaze(maze); 
  return 0; 
}
