// ------------------------------------------
// headers and definitions
#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;
// ------------------------------------------
// global variables

int nVertices, nEdges;

// ------------------------------------------

bool dfs(int vertice, vector<int> graph[], vector<int> &flag){

  stack <int> processor;
  flag[vertice] = 1; // visited
  processor.push(vertice);

  while(not processor.empty()){

    int top = processor.top();
    processor.pop();

    // cout << "acessing: " << top << endl; //DEBUG

    for(int ancestral : graph[top]){

      // cout << ancestral << " ancestral of " << top << " has " << flag[ancestral] << " flag\n"; //DEBUG

      if(flag[ancestral] == 2) continue; // already works!

      if(flag[ancestral] == 1) {
        // cout << "error founded! vertice: " << ancestral << "\n"; //DEBUG
        return false; // cycle founded
      }

      if(flag[ancestral] == 0){ // not visited ancestral
        processor.push(ancestral);
        flag[ancestral] = 1;
        // cout << "going to " << ancestral << endl; // DEBUG
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

  // graph input
  for(int i=0; i<nEdges; i++){
    int dad, son;
    cin >> dad >> son;

    graph[son].push_back(dad);
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

  if(nearestAncestrals.empty()) cout << "-" << endl;

  return 0;
}

// ------------------------------------------