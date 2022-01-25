/**
 * @file main.cpp
 * @brief initial model test for 10 holes with layout similar to the picture
 */

#include <vector>
#include <fstream>
#include <random>
#include <algorithm>
#include <unistd.h>

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
			CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);	
		}
	}

	// add constraints [ forall k in N, k != 0, sum(i,k) x_ik - sum(k,j) x_kj = 1, j!=0]
	for (int k = 1; k < N; k++)
	{
		std::vector<int> idx(2*N-3);
		std::vector<double> coef(2*N-3, 1.0);
		char sense = 'E';
		int a = 0;
		for (int i = 0; i < N; i++)
		{
			if (i == k) continue; // exclude x_kk
			idx[a] = i*(N-1) + k-1; // corresponds to variable x_ik
			a++;
		}
		for (int j = 1; j < N; j++)
		{
			if (j == k) continue; // exclude x_kk
			idx[a] = k*(N-1) + j-1; // corresponds to variable x_kj
			coef[a] = -1; 
			a++;
		}
		int matbeg = 0;
		double rhs = 1;
		CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
	}
	CHECKED_CPX_CALL(CPXwriteprob, env, lp, "ex1.lp", NULL);
}

#define PRINT_ALL_TPSOLVER 0 // print all info for debug and to understand evolution


void computeCost(const int n, const std::vector<std::vector<double>> & pos, std::vector< std::vector<double>> & cost)
{
	// compute costs
	cost.resize(n);
	for (int i = 0; i < n; i++) {
		cost[i].reserve(n);
		for (int j = 0; j < n; j++) {
			double c = abs(pos[i][0]-pos[j][0]) + abs(pos[i][1]-pos[j][1]); // Manhatan distance
			cost[i].push_back(c);
		}
	}
	return;
}

int readPos(const char* filename, std::vector<std::vector<double>>& pos, std::vector<std::vector<double>>& cost)
{
	int n = 0;
	std::ifstream in(filename);

	// read size
	in >> n;

	#if PRINT_ALL_TPSOLVER
            std::cout << "(Pos) number of nodes n = " << n << std::endl;
    #endif

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
	computeCost(n, pos, cost);
	return n;
}

// better seed for srand() using a mix function
unsigned long superSeed()
{	
	unsigned long a = clock();
	unsigned long b = std::time(NULL);
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

// random cost matrix
void randomCost(const int n, std::vector<std::vector<double>>& pos, std::vector<std::vector<double>>& cost, const int classe)
{
	#if PRINT_ALL_TPSOLVER
            std::cout << "(Random class " << classe << " ) number of nodes n = " << n << std::endl;
    #endif

	std::vector<std::vector<double>> allPos;
	
	// Random but from 1 to N-2
	allPos.resize((n-2)*(n-2));
	int max = n - 1;
	int min = 1;	

	if (classe == 1) { // Random from 0 to N-1
		allPos.resize(n*n);
		max = n;
		min = 0;
	}

    // All possible positions
	int a = 0;
    for (int i = min; i < max; i++) 
	{
        for (int j = min; j < max; j++) 
		{
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
		pos[i][1] = allPos[i][1]; // save the firts N postions from all the pairs
    }

	// compute costs
	computeCost(n,pos,cost);
	return;
}

// read dat file with cost matrix
int readDists(const char* filename, std::vector< std::vector<double> > & cost)
{
	std::ifstream in(filename);
	int n = 0;

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
	return n;
}

// save cost matrix to file 
void saveDists(const char* filename, std::vector< std::vector<double> > & cost, const int n)
{
	ofstream out(filename);

	// save size
	out << n << "\n";

	// save costs
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n-1; j++) {
			out << cost[i][j] << "\t\t";
		}
		out << cost[i][n-1] << "\n";
	}

	out.close();
	return;
}

int main (int argc, char const *argv[])
{
	try
	{

		if (argc < 3) throw std::runtime_error("usage: ./main filename.dat savedistsfile.dat [readDists] [Nrandom] [class]");

		std::vector<std::vector<double>> cost;
		std::vector<std::vector<double>> pos;
		int N = 0;
		int classe = 1;

		if (argc >= 5) {
			N = atoi(argv[4]);
			if (argc == 6 && N > 3) classe = atoi(argv[5]); // class 2 only possible for 4x4 maps or larger
			randomCost(N,pos,cost,classe);
			saveDists(argv[2], cost, N);
		}
		else if (argc == 4){
			N = readDists(argv[1], cost);
		}		
		else {
			N = readPos(argv[1],pos,cost);
			saveDists(argv[2], cost, N);
		}

		// init
		DECL_ENV(env);
		DECL_PROB(env, lp);

		// setup LP
		setupLP(env, lp, N, cost);

		// optimize
		Log::Timer t;
		CHECKED_CPX_CALL(CPXmipopt, env, lp );
		std::cout << "Time: " << t.stopMicro()*1e-6 << " s" << std::endl;
		
		// print
		double objval;
		CHECKED_CPX_CALL(CPXgetobjval, env, lp, &objval );
		std::cout << "Objval: " << objval << std::endl;

		int n = CPXgetnumcols(env, lp);
		if (n != 2*N*N-N) { throw std::runtime_error(std::string(__FILE__) + ":" + STRINGIZE(__LINE__) + ": " + "different number of variables"); }

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

