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
        if (argc < 4 ) throw std::runtime_error("usage: ./main filename.dat tabulength maxiter [init] [readPos] [Nrandom] [class] "); 
        // filename not used if random, readPos: file to read positions, Nrandom: random number of nodes, initHeu: enable initial heuristic solution

        int tabuLength = atoi(argv[2]);                                                           
        int maxIter    = atoi(argv[3]);                                                           
        TSP tspInstance; 
        int init = 0; // 0 for random, 1 for initHeu1

        if (argc > 4) init = atoi(argv[4]); // get required initalization method
            
        if (argc == 6) tspInstance.readPos(argv[1]); // read positions instead of costs
        else if (argc > 6) { // use random cost matrix with N nodes
            int N = atoi(argv[6]);
            int classe = 1;
            if (argc == 8 && N > 3) classe = atoi(argv[7]); // class 2 only possible for 4x4 maps or larger
            tspInstance.randomCost(N, classe);
        }
        else tspInstance.readDists(argv[1]);

        TSPSolution aSolution(tspInstance);

        Log::Timer t; // start timer

        TSPSolver tspSolver; // initialization
        if (init != 0) tspSolver.initHeu1(tspInstance,aSolution);
        else tspSolver.initRnd(aSolution);

        TSPSolution bestSolution(tspInstance);
        tspSolver.solve(tspInstance,aSolution, tabuLength, maxIter ,bestSolution); /// solve with TSAC

        double micros = t.stopMicro(); 
            
        std::cout << "FROM solution: "; 
        aSolution.print();
        std::cout << "(value : " << tspSolver.evaluate(aSolution,tspInstance) << ")\n";
        std::cout << "TO   solution: "; 
        bestSolution.print();
        std::cout << "(value : " << tspSolver.evaluate(bestSolution,tspInstance) << ")\n";
        std::cout << "in " << micros*1e-6 << " seconds\n";
        
    }
    catch(std::exception& e)
    {
        std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
    }
    return 0;
}
