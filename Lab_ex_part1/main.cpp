/**
 * @file main.cpp
 * @brief initial model test for 10 holes with layout similar to the picture
 */

// #include <cstdio>
// #include <iostream>
#include <vector>
// #include <stdio.h>
// #include <math.h>
// #include <numeric>
#include <fstream>
#include <random>
#include <algorithm>
// #include <iterator>
// #include <ctime>
#include "cpxmacro.h"
#include "Timer.h"



using namespace std;

// error status and messagge buffer
int status;
char errmsg[BUF_SIZE];

const int NAME_SIZE = 512;
char name[NAME_SIZE];
	
void setupLP(CEnv env, Prob lp, const int N, const std::vector<std::vector<double>>& C)
{
	std::vector<int> nameN(N) ; // vector with N ints.
	std::iota (std::begin(nameN), std::end(nameN), 0); // Fill with 0, 1, ..., N.
	// add x vars [in o.f.: sum{i,j} 0 x_ij + ...]
	for (int i = 0; i < N; i++)
	{
		for (int j = 1; j < N; j++) // no need for x_i0 forall i
		{
			char xtype = 'I';
			double lb = 0.0;
			double ub = CPX_INFBOUND;
			snprintf(name, NAME_SIZE, "x_%d_%d", nameN[i], nameN[j]);
			char* xname = (char*)(&name[0]);
			CHECKED_CPX_CALL( CPXnewcols, env, lp, 1   , 0, &lb, &ub, &xtype, &xname );
		}
	}
	// add y vars [in o.f.: ... + sum{ij} C_ij y_ij + ... ]
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			char xtype = 'B';
			double lb = 0.0;
			double ub = 1.0;
			snprintf(name, NAME_SIZE, "y_%d_%d", nameN[i], nameN[j]);
			char* xname = (char*)(&name[0]);
			CHECKED_CPX_CALL( CPXnewcols, env, lp, 1   , &C[i][j], &lb, &ub, &xtype, &xname );
		}
	}
	
	///////////////////////////////////////////////////////////
	//
	// now variables are stored in the following order
	//  x01 x02 ...   x11 x12 ... #xij #    ... ...   y00   y01   ...   y10   	y11     ... #yij      	  #   ... ...  #
	// with indexes
	//  0   1         N-1 N      #i*(N-1)+j-1#       (N-1)*N (N-1)*N+1  N*N 	N*N+1     #(N-1)*N+i*N+j#     2*N*N-N#
	//  0   1         N-1 N      #i*(N-1)+j-1#       (N-1)*N (N-1)*N+1  N*N 	N*N+1     #N*(N+i-1)+j#       2*N*N-N#
	//
	///////////////////////////////////////////////////////////
	// add constraints [ forall j, sum{i} y_ij = 1 ]
	for (int j = 0; j < N; j++)
	{
		std::vector<int> idx(N);
		std::vector<double> coef(N, 1.0);
		char sense = 'E';
		for (int i = 0; i < N; i++)
		{
			idx[i] =  N*(N+i-1)+j; // corresponds to variable y_ij
		}
		int matbeg = 0;
		double rhs = 1;
		CHECKED_CPX_CALL( CPXaddrows, env, lp, 0     , 1     , idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL      , NULL      );
	}
	// add constraints [ forall i, sum{j} y_ij = 1 ]
	for (int i = 0; i < N; i++)
	{
		std::vector<int> idx(N);
		std::vector<double> coef(N, 1.0);
		char sense = 'E';
		for (int j = 0; j < N; j++)
		{
			idx[j] = N*(N+i-1)+j; // corresponds to variable y_ij
		}
		int matbeg = 0;
		double rhs = 1;
		CHECKED_CPX_CALL( CPXaddrows, env, lp, 0     , 1     , idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL      , NULL      );
	}
	// add constraints [ forall (i,j) in A, j != 0, x_ij <= (N-1)y_ij ]
	// add constraints [ forall (i,j) in A, j != 0, x_ij + (1-N)y_ij <= 0]
	for (int i = 0; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			std::vector<int> idx(2); 
			idx[0] = i*(N-1) + j-1; // x_ij 
			idx[1] = N*(N+i-1)+j; // y_ij

			std::vector<double> coef(2);
			coef[0] = 1;
			coef[1] = 1 - N;

			char sense = 'L';
			int matbeg = 0;
			double rhs = 0;
			CHECKED_CPX_CALL( CPXaddrows, env, lp, 0     , 1     , idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL      , NULL      );	
		}
	}
	// add constraints [ forall k in N, k != 0, sum(i,k) x_ik - sum(k,j) x_kj = 1, j!=0]
	for (int k = 1; k < N; k++)
	{
		std::vector<int> idx(2*N);
		std::vector<double> coef(2*N, 1.0);
		char sense = 'E';
		for (int i = 0; i < N; i++)
		{
			idx[i] = i*(N-1) + k-1; // corresponds to variable x_ik
		}
		for (int j = 0; j < N; j++)
		{
			idx[N+j] = k*(N-1) + j; // corresponds to variable x_kj
			coef[N+j] = -1; 
		}
		int matbeg = 0;
		double rhs = 1;
		CHECKED_CPX_CALL( CPXaddrows, env, lp, 0     , 1     , idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL      , NULL      );
	}
	CHECKED_CPX_CALL( CPXwriteprob, env, lp, "ex1.lp", NULL );
}

void computeCost(const int n, const std::vector<std::vector<double>> & pos, std::vector< std::vector<double>> & cost)
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
	return;
}

int read(const char* filename, std::vector<std::vector<double>> & pos, std::vector< std::vector<double> > & cost)
{
	int n = 0;
	std::ifstream in(filename);
	// read size
	in >> n;
	std::cout << "number of nodes n = " << n << std::endl;
	// read positions
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
	computeCost(n, pos, cost);
	return n;
}

void randomCost(const int n, std::vector<std::vector<double>> & pos, std::vector< std::vector<double> > & cost)
{
	std::cout << "number of random nodes n = " << n << std::endl;
	std::vector<int> v1(n) ; // vector with N ints.
	std::iota (std::begin(v1), std::end(v1), 0); // Fill with 0, 1, ..., N.
	std::vector<std::vector<double>> allPos;
	
	// Random but from 0 to N-1
	allPos.resize(n*n);
	int msize = n;
	int min = 0;

	// Random but from 1 to N-2
	// allPos.resize((n-2)*(n-2));
	// int msize = n - 1;
	// int min = 1;

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

	std::srand(std::time(0));
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
	computeCost(n,pos,cost);
	return;
}

int main (int argc, char const *argv[])
{
	try
	{

		if (argc < 2) throw std::runtime_error("usage: ./main filename.dat [Nrandom]");
		std::vector<std::vector<double>> cost;
		std::vector<std::vector<double>> pos;
		int N = 0;
		if (argc == 3)
		{
			N = atoi(argv[2]);
			randomCost(N,pos,cost);
		}	
		else N = read(argv[1],pos,cost);


		// init
		DECL_ENV(env);
		DECL_PROB(env, lp);
		// setup LP
		setupLP(env, lp, N, cost);
		// optimize
		using Log::Timer;
		Timer t;
		CHECKED_CPX_CALL(CPXmipopt, env, lp ); // SEG FAULT for n=5,6,7,8,9
		std::cout << "Time: " << t.stop()/1000 << " s" << std::endl;
		// std::cout << "Time: " << t.stop() << " s" << std::endl;
		
		// print
		double objval;
		CHECKED_CPX_CALL(CPXgetobjval, env, lp, &objval );
		std::cout << "Objval: " << objval << std::endl;
		int n = CPXgetnumcols(env, lp);
		if (n != 2*N*N-N) { throw std::runtime_error(std::string(__FILE__) + ":" + STRINGIZE(__LINE__) + ": " + "different number of variables"); }
	  	std::vector<double> varVals;
		varVals.resize(n);
  		CHECKED_CPX_CALL( CPXgetx, env, lp, &varVals[0], 0, n - 1 );
		/// status =      CPXgetx (env, lp, x          , 0, CPXgetnumcols(env, lp)-1);
  		for ( int i = 0 ; i < n ; ++i ) {
  	  	// std::cout << "var in position " << i << " : " << varVals[i] << std::endl;
  	  		/// to read variables names the API function ``CPXgetcolname'' may be used (it is rather tricky, see the API manual if you like...)
  	  		/// status = CPXgetcolname (env, lp, cur_colname, cur_colnamestore, cur_storespace, &surplus, 0, cur_numcols-1);
  		}
		CHECKED_CPX_CALL( CPXsolwrite, env, lp, "ex1.sol" );
		// free
		CPXfreeprob(env, &lp);
		CPXcloseCPLEX(&env);
	}
	catch(std::exception& e)
	{
		std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
	}
	return 0;
}

