/**
 * @file TSPSolver.h
 * @brief TSP solver (neighborhood search)
 *
 */

#ifndef TSPSOLVER_H
#define TSPSOLVER_H

// #include <vector>
#include <unistd.h>
#include "TSPSolution.h"

/**
 * Class representing substring reversal move
 */
typedef struct move {
  int      from;
  int      to;
} TSPMove;

/**
 * Class that solves a TSP problem by neighbourdood search and 2-opt moves
 */
class TSPSolver
{
public:

  TSPSolver ( ) { }

  double evaluate ( const TSPSolution& sol , const TSP& tsp ) const {
    double total = 0.0;
    for ( uint i = 0 ; i < sol.sequence.size() - 1 ; ++i ) {
      int from = sol.sequence[i]  ;
      int to   = sol.sequence[i+1];
      total += tsp.cost[from][to];
    }
    return total;
  }
  unsigned long superSeed()
  {	
    unsigned long a = clock();
    unsigned long b = time(NULL);
    unsigned long c = getpid();
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
  }
  bool initRnd ( TSPSolution& sol ) {
    srand(superSeed());
    for ( uint i = 1 ; i < sol.sequence.size() ; ++i ) {
      // intial and final position are fixed (initial/final node remains 0)
      int idx1 = rand() % (sol.sequence.size()-2) + 1;
      int idx2 = rand() % (sol.sequence.size()-2) + 1;
      int tmp = sol.sequence[idx1];
      sol.sequence[idx1] = sol.sequence[idx2];
      sol.sequence[idx2] = tmp;
    }
    std::cout << "### "; sol.print(); std::cout << " ###" << std::endl;
    return true;
  }
  // heuristic init -> choose min from each row
  bool initHeu1 (const TSP& tsp ,TSPSolution& sol ) 
  {
    std::cout << "B### "; sol.print(); std::cout << " ###" << std::endl;

    for ( uint i = 1 ; i < sol.sequence.size()-1 ; ++i ) {
      // intial and final position are fixed (initial/final node remains 0)
      sol.sequence[i] = -1;
    }

    std::cout << "B### "; sol.print(); std::cout << " ###" << std::endl;


    std::vector<int> visited;
    int i = 0;
    visited.push_back(0);
    int prev=0;

    while (visited.size() < tsp.n)
    {
      // sort as indices
      
      std::vector<int> V(tsp.n);
      std::iota(V.begin(),V.end(),0); //Initializing
      // sort(V.begin(),V.end(), [&](int a,int j){return tsp.cost[i][a]<tsp.cost[i][j];} );
      // std::cout << " ###" << std::endl;
      sort(V.begin(),V.end(), [&](int a,int j){return tsp.cost[prev][a]<tsp.cost[prev][j];} );

      // std::cout << "prev: " << prev << " " << std::endl;
      // for ( uint i = 0 ; i < V.size() ; ++i ) {
      //   std::cout << V[i] << " ";
      // }
      // std::cout << " ###" << std::endl;

      for (uint b = 1; b < V.size(); b++){ // exclude actual min because it is 0
        // std::cout << "i = " << i << ", index: " << V[b] << std::endl;
        int temp = V[b];
        if (!std::count(visited.begin(), visited.end(), temp))
        {
          sol.sequence[i+1] = temp;
          visited.push_back(temp);
          prev = temp;
          i++;
          // std::cout << "### "; sol.print(); std::cout << " ###" << std::endl;

          break;
        }
      }
    }
    std::cout << "### "; sol.print(); std::cout << " ###" << std::endl;
    return true;
  }



  bool solve ( const TSP& tsp , const TSPSolution& initSol , int tabulength , int maxIter , TSPSolution& bestSol ); /// TS: new parameters
protected:
  double    findBestNeighbor ( const TSP& tsp , const TSPSolution& currSol , int currIter , double aspiration , TSPMove& move );	//**// TSAC: use aspiration!
  TSPSolution&  swap        ( TSPSolution& tspSol , const TSPMove& move );
  
  ///Tabu search (tabu list stores, for each node, when (last iteration) a move involving that node have been chosen)
  ///  a neighbor is tabu if the generating move involves two nodes that have been chosen in the last 'tabulength' moves
  ///  that is, currentIteration - LastTimeInvolved <= tabuLength
  int               tabuLength;
  std::vector<int>  tabuList;
  void  initTabuList ( int n ) {
    for ( int i = 0 ; i < n ; ++i ) {
      tabuList.push_back(-tabuLength-1);
          // at iterarion 0, no neighbor is tabu --> iteration(= 0) - tabulistInit > tabulength --> tabulistInit < tabuLength + 0
    }
  }
	void updateTabuList( int nodeFrom, int nodeTo , int iter) {
      tabuList[nodeFrom] = iter;
      tabuList[nodeTo]   = iter;
	}
	bool isTabu( int nodeFrom, int nodeTo , int iter ) {
		return ( (iter - tabuList[nodeFrom] <= tabuLength) && (iter - tabuList[nodeTo] <= tabuLength) );
  }
///
};

#endif /* TSPSOLVER_H */
