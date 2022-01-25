/**
 * @file TSP.h
 * @brief TSP data
 *
 */

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>

#define PRINT_ALL_TPSOLVER 0 // print all info for debug and to understand evolution

/**
 * Class that describes a TSP instance (a cost matrix, nodes are identified by integer 0 ... n-1)
 */
class TSP
{
public:
    TSP() : n(0) , infinite(1e10) { }
    int n; //number of nodes
    std::vector< std::vector<double> > cost;
    double infinite; // infinite value (an upper bound on the value of any feasible solution)

    void readDists(const char* filename) // read cost matrix from file
    {
        std::ifstream in(filename);

        // read size
        in >> n;

        #if PRINT_ALL_TPSOLVER
            std::cout << "(Dists) number of nodes n = " << n << std::endl;
        #endif

        // read costs
        cost.resize(n);
        for (int i = 0; i < n; i++) {
            cost[i].reserve(n);
            for (int j = 0; j < n; j++) {
                double c;
                in >> c;
                cost[i].push_back(c);
            }
        }
        in.close();

        setInfinite();
    }

    void setInfinite(){ // set infinite value
        infinite = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                infinite += cost[i][j];
            }
        }
        infinite *= 2;
    }

    void readPos(const char* filename) // read positions from file
    {
        std::ifstream in(filename);

        // read size
        in >> n;

        #if PRINT_ALL_TPSOLVER
            std::cout << "(Pos) number of nodes n = " << n << std::endl;
        #endif

        // read positions
        std::vector<std::vector<double>> pos;
        pos.resize(n);
        for (int i = 0; i < n; i++) {
            pos[i].reserve(2);
            for (int j = 0; j < 2; j++) {
                double c;
                in >> c;
                pos[i].push_back(c);
            }
        }
        in.close();

        // compute costs
        computeCost(pos);
        return;
    }

    void computeCost(const std::vector<std::vector<double>>& pos) // compute costs from positions
    {
        cost.resize(n);
        for (int i = 0; i < n; i++) {
            cost[i].reserve(n);
            for (int j = 0; j < n; j++) {
                double c = abs(pos[i][0]-pos[j][0]) + abs(pos[i][1]-pos[j][1]); // Manhatan distance
                cost[i].push_back(c);
            }
        }
        setInfinite();
        return;
    }

    // better seed for srand() using a mix function
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

    void randomCost(const int N, const int classe) // random positions generations
    {
        n = N;

        #if PRINT_ALL_TPSOLVER
            std::cout << "(Random class " << classe << " ) number of nodes n = " << n << std::endl;
        #endif

        std::vector<std::vector<double>> allPos;
        std::vector<std::vector<double>> pos;
        
        // Random but from 1 to N-2
        allPos.resize((n-2)*(n-2));
        int max = n - 1;
        int min = 1;	

        if (classe == 1) { // Random from 0 to N-1
            allPos.resize(n*n);
            max = n;
            min = 0;
        }

        // Nested loop for all possible pairs
        int a = 0;
        for (int i = min; i < max; i++) {
            for (int j = min; j < max; j++){
                allPos[a].resize(2);
                allPos[a][0] = i;
                allPos[a][1] = j;
                a++;
            } 
        }

        #if PRINT_ALL_TPSOLVER
            for (int i = 0; i < allPos.size(); i++) {
                std::cout << "(" << allPos[i][0] << "," << allPos[i][1] << ")\n"; 
            }
            std::cout << "All pairs done\n";
        #endif

        std::srand(superSeed());
        std::random_shuffle(allPos.begin(),allPos.end()); // shuffle all pairs

        pos.resize(n);
        for (int i = 0; i < n; i++) {
            #if PRINT_ALL_TPSOLVER
                std::cout << "(" << allPos[i][0] << "," << allPos[i][1] << ")\n";
            #endif
            pos[i].resize(2);
            pos[i][0] = allPos[i][0];
            pos[i][1] = allPos[i][1]; // save postions as the first N from all the pairs
        }

        // compute costs
        computeCost(pos);
        return;
    }

};

