/**
 * @file TSP.h
 * @brief TSP data
 *
 */

#ifndef TSP_H
#define TSP_H

// #include <stdlib.h>
// #include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
// #include <numeric>
#include <random>
#include <algorithm>
// #include <iterator>
// #include <math.h>
// #include <cstdio>

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

  void read(const char* filename)
  {
    std::ifstream in(filename);
    // read size
    in >> n;
    std::cout << "number of nodes n = " << n << std::endl;
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
  }
  void setInfinite(){
    // set infinite value
    infinite = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        infinite += cost[i][j];
      }
    }
    infinite *= 2;
  }

  void readPos(const char* filename)
  {
    std::ifstream in(filename);
    // read size
    in >> n;
    std::cout << "number of nodes n = " << n << std::endl;
    // read positions
    std::vector<std::vector<double>> pos;
    pos.resize(n);
    for (int i = 0; i < n; i++) 
    {
      pos[i].reserve(2);
      for (int j = 0; j < 2; j++) 
      {
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
  void computeCost(const std::vector<std::vector<double>> & pos)
  {
    // compute costs
    cost.resize(n);
    for (int i = 0; i < n; i++) 
    {
      cost[i].reserve(n);
      for (int j = 0; j < n; j++) 
      {
        double c = abs(pos[i][0]-pos[j][0]) + abs(pos[i][1]-pos[j][1]); // Manhatan distance
        // double c = sqrt(pow((pos[i][0]-pos[j][0]),2) + pow((pos[i][1]-pos[j][1]),2)); // Euclidean distance
        // std::cout << "(" << i << "," << j << ") -> " << c << std::endl;
        cost[i].push_back(c);
      }
    }
    setInfinite();
    return;
  }
  void randomCost(const int N)
  {
    n = N;
    // std::cout << "number of random nodes n = " << n << std::endl;
    std::vector<int> v1(n) ; // vector with N ints.
    std::iota (std::begin(v1), std::end(v1), 0); // Fill with 0, 1, ..., N.
    std::vector<std::vector<double>> allPos;
    std::vector<std::vector<double>> pos;
    
    // Random from 0 to N-1
    // allPos.resize(n*n);
    // int msize = n;
    // int min = 0;

    // Random but from 1 to N-2
    allPos.resize((n-2)*(n-2));
    int msize = n - 1;
    int min = 1;

      // Nested loop for all possible pairs
    int a = 0;
    for (int i = min; i < msize; i++) 
    {
      for (int j = min; j < msize; j++) 
      {
        allPos[a].resize(2);
        allPos[a][0] = i;
        allPos[a][1] = j;
        a++;
      } 
    }

    // for (int i = 0; i < n*n; i++) {
      //     std::cout << "(" << allPos[i][0] << "," << allPos[i][1] << ")\n"; 
      // }
    // std::cout << "All pairs done\n";

    // std::srand(std::time(0));
    std::srand(time(0));
    std::random_shuffle(allPos.begin(),allPos.end()); // shuffle all pairs

    pos.resize(n);
    for (int i = 0; i < n; i++) 
    {
          // std::cout << "(" << allPos[i][0] << "," << allPos[i][1] << ")\n";
      pos[i].resize(2);
      pos[i][0] = allPos[i][0];
      pos[i][1] = allPos[i][1]; // save postions as the first N from the N*N pairs
      }

    // compute costs
    computeCost(pos);
    return;
  }

};

#endif /* TSP_H */
