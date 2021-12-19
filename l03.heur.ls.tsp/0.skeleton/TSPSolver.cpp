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
        int  iter = 0;

        TSPSolution currSol(initSol);
        // double bestValue, currValue;
        double currValue;
        // bestValue = currValue = evaluate(currSol,tsp);
        currValue = evaluate(currSol,tsp);
        TSPMove move;
        while ( ! stop ) {
            /// local search iteration...
            if ( tsp.n < 20 ) currSol.print(); //log current solution (only small instances)
                std::cout << " (" << ++iter << "ls) value " << currValue << " (" << evaluate(currSol,tsp) << ")";
            double bestNeighValue = currValue + findBestNeighborIncrement(tsp, currSol, move);
            ///incremental evaluation: findBestNeighbour returns the cost increment
      				std::cout << " move: " << move.from << " , " << move.to << std::endl;
            if (bestNeighValue < currValue){
                // bestValue = currValue = bestNeighValue;
                currValue = bestNeighValue;
                currSol = applySwapMove(currSol,move);
                stop = false;
            }
            else{
                stop = true;
            }
        // DONE;
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

//TODO: "internal methods", if any
double TSPSolver::findBestNeighborIncrement( const TSP& tsp, const TSPSolution& currSol, TSPMove& move){
    double bestCostVariation = tsp.infinite;

    // 0.padova 1.c 2. .... n-1.c n.padova  [currSol]
    for (size_t a = 1; a < currSol.sequence.size()-2; ++a)
    {
        int h = currSol.sequence[a-1];
        int i = currSol.sequence[a];
        for (size_t b = a + 1; b < currSol.sequence.size()-1; ++b)
        {
            int j = currSol.sequence[b];
            int l = currSol.sequence[b+1];
            double costVariaton = - tsp.cost[h][i] - tsp.cost[j][l] + tsp.cost[h][j] + tsp.cost[i][l];
            
            if (costVariaton < bestCostVariation)
            {
                bestCostVariation = costVariaton;
                move.from = a;
                move.to = b;
            }
        }
    }

    return bestCostVariation;
}

TSPSolution TSPSolver::applySwapMove(TSPSolution& currSol, const TSPMove& move){
    TSPSolution impSol(currSol);
    for ( int i = move.from; i <= move.to; ++i)
    {
        currSol.sequence[i] = impSol.sequence[move.to-(i-move.from)];
    }
    return currSol;
}