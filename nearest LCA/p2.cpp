// ------------------------------------------
// headers and definitions
#include <iostream>
#include <vector>
#include <stack>
#include <set>

#define debugDFS false
#define debugFlag false
#define debugLCA false

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

bool dfs(int vertice, vector<int> graph[], vector<int> &flag){

  stack <int> processor;
  flag[vertice] = 1; // visited
  processor.push(vertice);

  while(not processor.empty()){

    int top = processor.top();
    processor.pop();

    if(debugDFS) cout << "acessing: " << top << endl;

    for(int ancestral : graph[top]){

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
  for(int i=0; i<nVertices; i++) {
    if(flag[i] == 1) flag[i] = 0;
  }

  return true;

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
  vector <Node> degree(nVertices);

  // graph input
  for(int i=0; i<nEdges; i++){
    int dad, son;
    cin >> dad >> son;

    graph[son].push_back(dad);
    degree[dad].out++;
    degree[son].in++;
  }

  // exceptions treatment
  for(int i=nVertices; i>0; i--){
    if ( dfs(i, graph, flag) ) flag[i] = 2;
    else {
      cout << "0" << endl;
      return 0; // stop the code
    }
  }

  // FINALLY THE NEAREST LCA

  set <int> nearestAncestrals;

  if(debug) for(int i=1; i<=nVertices; i++) cout << "Vertice " << i << ": in = " << degree[i].in << " || out = " << degree[i].out << "\n";

  if(nearestAncestrals.empty()) cout << "-" << endl;

  return 0;
}

// ------------------------------------------