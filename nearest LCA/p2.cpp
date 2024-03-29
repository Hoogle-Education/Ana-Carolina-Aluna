// ------------------------------------------
// headers and definitions
#include <stdio.h>
#include <vector>
#include <stack>

using namespace std;

// ------------------------------------------
// global variables

int nVertices, nEdges;
bool works = true, haveAnswer = false;
vector < vector <int> > graph;

// ------------------------------------------
// in and out control for nodes
struct Node {
  int in = 0, out = 0;
} node;

// ------------------------------------------

void isCyclic(int vertice , vector<int> &flag ){

  flag[vertice] = 1;

  for(int ancestral : graph[vertice]){
    if(flag[ancestral] == 2) continue;
    else if(flag[ancestral] == 1) works = false;
    else if(flag[ancestral] == 0) isCyclic(ancestral, flag);
  }

  flag[vertice] = 2;

}

// ------------------------------------------

void LCA(int yellow, int red ){

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
    if(degree[i].out == 0 and colorFlag[i] == 'b'){
      printf("%d ", i);
      haveAnswer = true;
    } 
  }

}

// ------------------------------------------
// the main

int main(){

  // general inputs
  int v1, v2;
  scanf(" %d %d", &v1, &v2);
  scanf(" %d %d", &nVertices, &nEdges);

  // graph and flags alocation
  graph.resize(nVertices+1);
  vector <int> flag(nVertices+1, 0);

  // graph input
  for(int i=0; i<nEdges; i++){
    int dad, son;
    scanf(" %d %d", &dad, &son);

    graph[son].push_back(dad);
  }

  // genealogic exeptions treatment
  for(int i=nVertices; i>0; --i){

    if(flag[i] == 2) continue;

    isCyclic(i , flag);
    
    if ( (graph[i].size() > 2) or not works) {
      puts("0");
      return 0; // stop the code
    }
  }

  // FINALLY THE NEAREST LCA
  LCA(v1, v2);

  // not found!
  if(not haveAnswer) printf("-");

  printf("\n");
  return 0;
}

// ------------------------------------------