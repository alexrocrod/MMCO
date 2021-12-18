/**
 * @file TSPSolver.cpp
 * @brief TSP solver (neighborhood search)
 *
 */

#include "TSPSolver.h"
#include <iostream>

bool TSPSolver::solve ( const TSP& tsp , const TSPSolution& initSol , TSPSolution& bestSol )
{
  try
  {
    bool stop = false;
    					int  iter = 0;	// for displaying

    TSPSolution currSol(initSol);
    double bestValue, currValue;
    bestValue = currValue = evaluate(currSol,tsp);
    TSPMove move;
    while ( ! stop ) {
			/// TODO: local search iteration...
      				if ( tsp.n < 20 ) currSol.print(); //log current solution (only small instances)
      				std::cout << " (" << ++iter << "ls) value " << currValue << " (" << evaluate(currSol,tsp) << ")";
      double bestNeighValue = currValue + findBestNeighbor(tsp,currSol,move);
      	///incremental evaluation: findBestNeighbour returns the cost increment
      				std::cout << " move: " << move.from << " , " << move.to << std::endl;
      if ( bestNeighValue < currValue ) {
        bestValue = currValue = bestNeighValue;
        currSol = applySwapMove(currSol,move);
        stop = false;
      } else {
        stop = true;
      }
			/// ...DONE
    }
    bestSol = currSol;
  }
  catch(std::exception& e)
  {
    std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
    return false;
  }
  return true;
}

TSPSolution& TSPSolver::applySwapMove ( TSPSolution& tspSol , const TSPMove& move ) 
{
  TSPSolution tmpSol(tspSol);
  for ( int i = move.from ; i <= move.to ; ++i ) {
    tspSol.sequence[i] = tmpSol.sequence[move.to-(i-move.from)];
  }
  return tspSol;
}


double TSPSolver::findBestNeighbor ( const TSP& tsp , const TSPSolution& currSol , TSPMove& move )
/* Determine the *move* yielding the best 2-opt neighbor solution
 */
{
  double bestCostVariation = tsp.infinite;
		/// incremental evaluation --> bestCostVariation (instead of best cost)

  /// TODO: check all substring reversal (initial and final position are 
	///				fixed,i.e., initial/final node remains 0) and store the best
	///				one into 'move'...
  for ( uint a = 1 ; a < currSol.sequence.size() - 2 ; a++ ) {
    int h = currSol.sequence[a-1];
    int i = currSol.sequence[a];
    for ( uint b = a + 1 ; b < currSol.sequence.size() - 1 ; b++ ) {
      int j = currSol.sequence[b];
      int l = currSol.sequence[b+1];
      double neighCostVariation = - tsp.cost[h][i] - tsp.cost[j][l]
                                  + tsp.cost[h][j] + tsp.cost[i][l] ;
      if ( neighCostVariation < bestCostVariation ) {
        bestCostVariation = neighCostVariation;
        move.from = a;
        move.to = b;
      }
    }
  }
	/// ...DONE
	/// Exercise: implement a First Improvement exploration strategy
  return bestCostVariation;
}








