/**
 * @file main.cpp
 * @brief initial model test for 10 holes with layout similar to the picture
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <numeric>
#include <fstream>
#include "cpxmacro.h"


using namespace std;

// error status and messagge buffer
int status;
char errmsg[BUF_SIZE];

// data
// const int N = 10;
// const int I = 10;
// const int J = 10;
// const unsigned char nameI[I] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; // origins
// const unsigned char nameJ[J] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; // destinations
// const double C[I*J] = { 0.0,   6.0,  4.0,   7.2, 11.2, 11.0, 11.2, 11.7, 12.5, 14.2,  
// 						6.0,   0.0,  7.2,   4.0, 13.6, 13.0, 11.7, 11.2, 11.0, 11.2,
// 						4.0,   7.2,  0.0,   6.0,  7.3,  7.0,  7.3,  8.1,  7.3,  9.2,
// 						7.2,   4.0,  6.0,   0.0, 10.6,  9.9,  8.6,  7.6,  7.1,  7.3,
// 						11.2, 13.6,  7.3,  10.6,  0.0,  2.0,  4.0,  6.0,  8.0, 11.0,
// 						11.0, 13.0,  7.0,   9.9,  2.0,  0.0,  2.0,  4.0,  6.0,  9.0,
// 						11.2, 11.7,  7.3,   8.6,  4.0,  2.0,  0.0,  2.0,  4.0,  7.0,
// 						11.7, 11.2,  8.1,   7.6,  6.0,  4.0,  2.0,  0.0,  2.0,  5.0,
// 						12.5, 11.0,  7.3,   7.1,  8.0,  6.0,  4.0,  2.0,  0.0,  3.0,
// 						14.2, 11.2,  9.2,   7.3, 11.0,  9.0,  7.0,  5.0,  3.0,  0.0 }; 
// 						// costs(origin, destination) LINEARIZED (just an implementation choice!)

// const int N = 5;
// const int I = 5;
// const int J = 5;
// const unsigned char nameI[I] = { '0', '1', '2', '3', '4'}; // origins
// const unsigned char nameJ[J] = { '0', '1', '2', '3', '4'}; // destinations
// const double C[I*J] = { 0.0,   6.0,  4.0,   7.2, 11.2,  
// 						6.0,   0.0,  7.2,   4.0, 13.6,
// 						4.0,   7.2,  0.0,   6.0,  7.3,
// 						7.2,   4.0,  6.0,   0.0, 10.6,
// 						11.2, 13.6,  7.3,  10.6,  0.0}; 
// 						// costs(origin, destination) LINEARIZED (just an implementation choice
			
const int NAME_SIZE = 512;
char name[NAME_SIZE];
	
void setupLP(CEnv env, Prob lp, const int N, const std::vector<std::vector<double>>& C)
{
	std::vector<int> v(N) ; // vector with N ints.
	std::iota (std::begin(v), std::end(v), 0); // Fill with 0, 1, ..., N.
	unsigned char nameN[N];
	for (int a = 0; a < N; a++)
	{
		nameN[a] = v[a]+ '0';
	}	
	
	const int I = N;
	const int J = N;

	// add x vars [in o.f.: sum{i,j} 0 x_ij + ...]
	for (int i = 0; i < I; i++)
	{
		for (int j = 1; j < J; j++) // no need for x_i0 forall i
		{
			char xtype = 'I';
			double lb = 0.0;
			double ub = CPX_INFBOUND;
			snprintf(name, NAME_SIZE, "x_%c_%c", nameN[i], nameN[j]);
			char* xname = (char*)(&name[0]);
			CHECKED_CPX_CALL( CPXnewcols, env, lp, 1   , 0, &lb, &ub, &xtype, &xname );
			/// status =      CPXnewcols (env, lp, ccnt, obj      , lb  , ub, xctype, colname);
		}
	}
	// add y vars [in o.f.: ... + sum{ij} C_ij y_ij + ... ]
	for (int i = 0; i < I; i++)
	{
		for (int j = 0; j < J; j++)
		{
			char xtype = 'B';
			double lb = 0.0;
			double ub = 1.0;
			snprintf(name, NAME_SIZE, "y_%c_%c", nameN[i], nameN[j]);
			char* xname = (char*)(&name[0]);
			CHECKED_CPX_CALL( CPXnewcols, env, lp, 1   , &C[i][j], &lb, &ub, &xtype, &xname );
			/// status =      CPXnewcols (env, lp, ccnt, obj      , lb  , ub, xctype, colname);
		}
	}
	
	///////////////////////////////////////////////////////////
	//
	// now variables are stored in the following order
	//  x01 x02 ...   x11 x12 ... #xij #    ... ...   y00   y01   ...   	y10   		y11     ... #yij      	  #   ... ...  #
	// with indexes
	//  0   1         J-1 J      #i*(J-1)+j-1#       (I-1)*J (I-1)*J+1    (I-1)*J+J (I-1)*J+J+1     #(I-1)*J+i*J+j#     2*I*J-I#
	//
	///////////////////////////////////////////////////////////

	// add constraints [ forall j, sum{i} y_ij = 1 ]
	for (int j = 0; j < J; j++)
	{
		std::vector<int> idx(I);
		std::vector<double> coef(I, 1.0);
		char sense = 'E';
		for (int i = 0; i < I; i++)
		{
			idx[i] =  (I-1)*J + i*J + j; // corresponds to variable y_ij
		}
		int matbeg = 0;
		double rhs = 1;
		CHECKED_CPX_CALL( CPXaddrows, env, lp, 0     , 1     , idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL      , NULL      );
    	/// status =      CPXaddrows (env, lp, colcnt, rowcnt, nzcnt     , rhs  , sense , rmatbeg, rmatind, rmatval , newcolname, newrowname);
	}

	// add constraints [ forall i, sum{j} y_ij = 1 ]
	for (int i = 0; i < I; i++)
	{
		std::vector<int> idx(J);
		std::vector<double> coef(J, 1.0);
		char sense = 'E';
		for (int j = 0; j < J; j++)
		{
			idx[j] = (I-1)*J + i*J + j; // corresponds to variable y_ij
		}
		int matbeg = 0;
		double rhs = 1;
		CHECKED_CPX_CALL( CPXaddrows, env, lp, 0     , 1     , idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL      , NULL      );
    	/// status =      CPXaddrows (env, lp, colcnt, rowcnt, nzcnt     , rhs  , sense , rmatbeg, rmatind, rmatval , newcolname, newrowname);
	}

	// add constraints [ forall (i,j) in A, j != 0, x_ij <= (N-1)y_ij ]
	// add constraints [ forall (i,j) in A, j != 0, x_ij + (1-N)y_ij <= 0]
	for (int i = 0; i < I; i++)
	{
		for (int j = 1; j < J; j++)
		{
			std::vector<int> idx(2); 
			idx[0] = i*(J-1) + j-1; // x_ij 
			idx[1] = (I-1)*J + i*J + j; // y_ij
			std::vector<double> coef(2);
			coef[0] = 1;
			coef[1] = 1 - N;
			char sense = 'L';
			int matbeg = 0;
			double rhs = 0;
			CHECKED_CPX_CALL( CPXaddrows, env, lp, 0     , 1     , idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL      , NULL      );	
			/// status =      CPXaddrows (env, lp, colcnt, rowcnt, nzcnt     , rhs  , sense , rmatbeg, rmatind, rmatval , newcolname, newrowname);
		}
	}

	// add constraints [ forall k in N, k != 0, sum(i,k) x_ik - sum(k,j) x_kj = 1, j!=0]
	for (int k = 1; k < I; k++)
	{
		std::vector<int> idx(2*J);
		std::vector<double> coef(2*J, 1.0);
		char sense = 'E';
		for (int i = 0; i < I; i++)
		{
			idx[i] = i*(J-1) + k-1; // corresponds to variable x_ik
		}
		for (int j = 0; j < J; j++)
		{
			idx[I+j] = k*(J-1) + j; // corresponds to variable x_kj
			coef[I+j] = -1; 
		}
		int matbeg = 0;
		double rhs = 1;
		CHECKED_CPX_CALL( CPXaddrows, env, lp, 0     , 1     , idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL      , NULL      );
    	/// status =      CPXaddrows (env, lp, colcnt, rowcnt, nzcnt     , rhs  , sense , rmatbeg, rmatind, rmatval , newcolname, newrowname);
	}

	// print (debug)
	CHECKED_CPX_CALL( CPXwriteprob, env, lp, "ex1_v1.lp", NULL );
	/// status =      CPXwriteprob (env, lp, "myprob"    , filetype_str);
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
	cost.resize(n);
	for (int i = 0; i < n; i++) {
		cost[i].reserve(n);
		for (int j = 0; j < n; j++) {
			double c = abs(pos[i][0]-pos[j][0]) + abs(pos[i][1]-pos[j][1]); // Manhatan distance
			// double c = sqrt(pow((pos[i][0]-pos[j][0]),2) + pow((pos[i][1]-pos[j][1]),2)); // Euclidean distance
			// std::cout << "(" << i << "," << j << ") -> " << c << std::endl;
			cost[i].push_back(c);
		}
	}
	return n;
}


int main (int argc, char const *argv[])
{
	try
	{

		if (argc < 2) throw std::runtime_error("usage: ./main filename.dat");
		std::vector<std::vector<double>> cost;
		std::vector<std::vector<double>> pos;
		int N = read(argv[1],pos,cost);


		// init
		DECL_ENV(env);
		DECL_PROB(env, lp);
		// setup LP
		setupLP(env, lp, N, cost);
		// optimize
		CHECKED_CPX_CALL(CPXmipopt, env, lp );
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
  	  	std::cout << "var in position " << i << " : " << varVals[i] << std::endl;
  	  		/// to read variables names the API function ``CPXgetcolname'' may be used (it is rather tricky, see the API manual if you like...)
  	  		/// status = CPXgetcolname (env, lp, cur_colname, cur_colnamestore, cur_storespace, &surplus, 0, cur_numcols-1);
  		}
		CHECKED_CPX_CALL( CPXsolwrite, env, lp, "ex1_v1.sol" );
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

