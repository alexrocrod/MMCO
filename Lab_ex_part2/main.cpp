/**
 * @file main.cpp
 * @brief 
 */


#include <stdexcept>

#include "TSPSolver.h"
#include "Timer.h"

// error status and messagge buffer
int status;
char errmsg[255];


int main (int argc, char const *argv[])
{
  try
  {
    if (argc < 4 ) throw std::runtime_error("usage: ./main filename.dat tabulength maxiter [init] [readPos] [Nrandom] "); 
    // filename not used if random, readPos: file to read positions, Nrandom: random number of nodes, initHeu: enable initial heuristic solution
    int tabuLength = atoi(argv[2]);                                                           
    int maxIter    = atoi(argv[3]);                                                           
    TSP tspInstance; 
    int init = 0; // 0 for random, 1 for initHeu1
    if (argc > 4) // get required initalization method
      init = atoi(argv[4]);
    if (argc == 6) // read positions instead of costs
      tspInstance.readPos(argv[1]);
    else if (argc > 6) // use random cost matrix with N nodes
		{
			int N = atoi(argv[5]);
			tspInstance.randomCost(N);
		}
    else
      tspInstance.read(argv[1]);

    TSPSolution aSolution(tspInstance);

    Log::Timer tnew; // start times

    TSPSolver tspSolver; // initialization
    if (init != 0) tspSolver.initHeu1(tspInstance,aSolution);
    else tspSolver.initRnd(aSolution);
    

    TSPSolution bestSolution(tspInstance);
    tspSolver.solve(tspInstance,aSolution, tabuLength, maxIter ,bestSolution); /// solve with TSAC

    double micros = tnew.stopMicro(); 
		
    std::cout << "FROM solution: "; 
    aSolution.print();
    std::cout << "(value : " << tspSolver.evaluate(aSolution,tspInstance) << ")\n";
    std::cout << "TO   solution: "; 
    bestSolution.print();
    std::cout << "(value : " << tspSolver.evaluate(bestSolution,tspInstance) << ")\n";
    std::cout << "in " << micros*1e-6 << " seconds (chrono time)\n";
    
  }
  catch(std::exception& e)
  {
    std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
  }
  return 0;
}
