// -----------------------
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

// -----------------------
// vairáveis globais

stack <int> sequency;

// -----------------------
// funcao auxiliar da readSequency

int stringToInteger( string numberString ){

// 198 = 8 + 9*10 + 1*100

  int number = 0;

  for(int i=numberString.size()-1; i>=0 ; i--){
    number += (int)(numberString[i] - 48)*pow(10, numberString.size() - i - 1);
  }

  return number;

}

// -----------------------

void readSequency( string line ){

  string acumulado = "";
  vector < int > aux;
  
  for(int i=0; i < line.size(); i++){

    if(line[i] == ' '){
      int number = stringToInteger(acumulado);
      aux.push_back(number);
      acumulado.clear();
    }else{
      acumulado += line[i];
    }

    if(i == line.size()-1){
      int number = stringToInteger(acumulado);
      aux.push_back(number);
      acumulado.clear();
    }
  }

  for(int i=aux.size()-1; i>=0 ; i--){
    sequency.push( aux[i] );
  }

}

// -----------------------

pair <int , int> LIS( stack <int> sequency ){

  stack <int> subSequencies [ sequency.size() ];
  int numberOfStacks = 1, possibilities = 1;

  subSequencies[0].push(sequency.top());
  sequency.pop();

  while( not sequency.empty() ){
    int chosen = sequency.top();

    for(int i=0; i<numberOfStacks; i++){
      if(chosen > subSequencies[i].top() and i == numberOfStacks-1 ){
        subSequencies[i+1].push( chosen );
        numberOfStacks++;
        break;
      }else if( chosen <= subSequencies[i].top() ){
        subSequencies[i].push(chosen);
        break;
      } 
    }

    sequency.pop();
  }

  for(int i=0; i<numberOfStacks; i++){
    possibilities *= subSequencies[i].size();
  }

  return make_pair(numberOfStacks, possibilities);

}

// -----------------------

int main(void){

    int option;
    cin >> option;
    cin.get();

    if (option == 1){
      
      string line;
      getline(cin, line );

      readSequency(line);

      pair <int,int> answer = LIS(sequency);
      cout << answer.first << " " << answer.second << endl;
    }

    return 0;
}

// -----------------------