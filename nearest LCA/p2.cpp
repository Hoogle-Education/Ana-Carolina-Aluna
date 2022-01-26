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
bool works = true;

// ------------------------------------------
// in and out control for nodes
struct Node {
  int in = 0, out = 0;
} node;

// ------------------------------------------

void isCyclic(int vertice, vector<vector<int>> graph , vector<bool> flag ){

  flag[vertice] = true;

  for(int ancestral : graph[vertice]){
    if(flag[ancestral] == true) works = false;
    else if(flag[ancestral] == false) isCyclic(ancestral, graph, flag);
  }

}

// ------------------------------------------

void LCA(int yellow, int red, vector <vector <int>> graph, set <int> &answer){

  vector <char> colorFlag(nVertices+2, 'w');
  stack <int> processor;
  vector <Node> degree(nVertices+2);

  // coloring the main nodes
  colorFlag[yellow] = 'y';  
  colorFlag[red] = 'r';

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
  vector < vector <int> > graph (nVertices+2);
  vector <bool> flag(nVertices+2, false);

  // graph input
  for(int i=0; i<nEdges; i++){
    int dad, son;
    cin >> dad >> son;

    graph[son].push_back(dad);
  }

  // cout << "| ";
  // for(int i=0; i<=nVertices; i++) cout << i << " | ";
  // cout << endl;

  // genealogic exeptions treatment
  for(int i=1; i<=nVertices; i++){
    isCyclic(i, graph, flag);
    if ( (graph[i].size() > 2) or not works) {
      cout << "0" << endl;
      return 0; // stop the code
    }
  }

  // FINALLY THE NEAREST LCA
  set <int> nearestAncestrals;
  LCA(v1, v2, graph, nearestAncestrals);

  // found any LCA?
  for(int valid : nearestAncestrals){
    cout << valid << " ";
  }

  // not found!
  if(nearestAncestrals.empty()) cout << "-";

  cout << endl;
  return 0;
}

// ------------------------------------------