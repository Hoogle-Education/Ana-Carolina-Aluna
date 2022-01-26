// ------------------------------------------
// headers and definitions
#include <iostream>
#include <vector>
#include <stack>
#include <set>

#define debugDFS true
#define debugColors false

using namespace std;
// ------------------------------------------
// global variables

int nVertices, nEdges;

// ------------------------------------------
// in and out control for nodes
struct Node {
  int in = 0, out = 0;
} node;

// ------------------------------------------

bool dfs(int vertice, vector<int> graph[], vector<int> &flag ){

  // two progenitors limitation
  if(graph[vertice].size() > 2) return false;

  stack <int> processor;
  flag[vertice] = 1; // visited
  processor.push(vertice);

  while(not processor.empty()){

    int top = processor.top();
    processor.pop();

    if(debugDFS) cout << "acessing: " << top << endl;

    for(int ancestral : graph[top]){

      if(graph[ancestral].size() > 2) return false;

      if(debugDFS) cout << ancestral << " ancestral of " << top << " has " << flag[ancestral] << " flag\n";

      if(flag[ancestral] == 2) continue; // already works!

      if(flag[ancestral] == 1) {
        if(debugDFS) cout << "error founded! vertice: " << ancestral << "\n";
        return false; // cycle founded
      }

      if(flag[ancestral] == 0){ // not visited ancestral
        processor.push(ancestral);
        flag[ancestral] = 1;
        if(debugDFS) cout << "going to " << ancestral << endl;
      }
    }

  }

  // just remove my temporary flags
  for(int i=1; i<=nVertices; i++) {
    if(flag[i] == 1) flag[i] = 0;
  }

  return true;

}

// ------------------------------------------

void LCA(int yellow, int red, vector <int> graph[] , set <int> &answer){

  vector <char> colorFlag(nVertices+1, 'w');
  // w -> white -> without color
  // y -> just ancestral of yellow
  // r -> just ancestral of red
  // b -> common ancestrals

  // coloring the main nodes
  colorFlag[yellow] = 'y';  
  colorFlag[red] = 'r';
  stack <int> processor;
  vector <Node> degree(nVertices+1);

  // dfs starting in yellow
  processor.push(yellow);
  while (not processor.empty()) {

    int top = processor.top();
    colorFlag[top] = 'y';
    processor.pop();

    for(int ancestral : graph[top] ) processor.push(ancestral);
    
  }

   // dfs starting in reds and blacks
  processor.push(red);
  while (not processor.empty()) {

    int top = processor.top();

    if(colorFlag[top] == 'y') colorFlag[top] = 'b';
    else if(colorFlag[top] == 'w') colorFlag[top] = 'r';

    processor.pop();

    for(int ancestral : graph[top] ) processor.push(ancestral);
  }

  if(debugColors){
    for(int i=0; i<=nVertices; i++) cout << i << " ";
    cout << endl;
    for(char color : colorFlag) cout << color << " ";
    cout << endl;
  } 

  for(int i=1; i<=nVertices; i++){
    if(colorFlag[i] == 'b'){
      for(int ancestral : graph[i]){
        if(colorFlag[ancestral] == 'b'){
          degree[i].in++;
          degree[ancestral].out++;
        }
      }
    }
  }

  for(int i=1; i<=nVertices; i++){
    if(degree[i].out == 0 and colorFlag[i] == 'b') answer.insert(i);
  }

}

// ------------------------------------------
// the main

int main(){

  // desynchronizing stdio optimization
  ios::sync_with_stdio(false);

  // general inputs
  int v1, v2;
  cin >> v1 >> v2;
  cin >> nVertices >> nEdges;

  // graph and flags alocation
  vector <int> graph[nVertices+1];
  vector <int> flag(nVertices+1, 0);

  // graph input
  for(int i=0; i<nEdges; i++){
    int dad, son;
    cin >> dad >> son;

    graph[son].push_back(dad);
  }

  // exceptions treatment
  for(int i=nVertices; i>0; --i){
    if ( dfs(i, graph, flag) ) flag[i] = 2;
    else {
      cout << "0" << endl;
      return 0; // stop the code
    }
  }

  // FINALLY THE NEAREST LCA

  set <int> nearestAncestrals;
  // LCA(v1, v2, graph, nearestAncestrals);


  // for(int valid : nearestAncestrals){
  //   cout << valid << " ";
  // }

  if(nearestAncestrals.empty()) cout << "-";

  cout << endl;
  return 0;
}

// ------------------------------------------