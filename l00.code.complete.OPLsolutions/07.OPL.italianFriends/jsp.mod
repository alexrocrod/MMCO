/*********************************************
 * OPL 12.6.1.0 Model
 * Author: luigi
 * Creation Date: Oct 11, 2017 at 8:31:31 PM
 *********************************************/

setof(string) I = ...;		// jobs
setof(string) K = ...;		// machines
setof(int) P = asSet(0..card(K)-1);

float	R[I] = ...;			// release times
float 	D[I][K] = ...; 		// processing times
string 	sigma[I][P] = ...;	// task order
float 	M = max(i in I)R[i] + sum(i in I, k in K)(D[i][k]);

dvar float+		y;								// makespan
dvar float+		h[i in I][K] in R[i]..infinity;	// start time
dvar boolean 	x[i in I][j in I][k in K] in 0 .. ((i==j)?0:1);	
												// precedence
/* the fact that x_ij^k are "not defined" for i==j is here
 * implemented by fixing those variables to 0. This can be
 * obtained as an upper bound (see above) or with specific
 * constraints (see commented constraints below).
 * In both cases, variables are created and then fixed to 0
 * (in the first case the process is more efficient). In fact
 * the "dvar" statement is not flexible enough to allow "holes" 
 * in the variable vectors (you may want to resort to the
 * "tuple" statement to define subsets of triplets <i,j,k>, and 
 * define "dvar" on tuples: tuples are not the object of our
 * introduction to OPL).
 */


minimize y;

subject to {

forall ( i in I ) {
makespan:	y >= h[i][sigma[i][card(K)-1]] + D[i][sigma[i][card(K)-1]];
release:	h[i][sigma[i][0]] >= R[i]; 
	forall (p in P: p >= 1) { 
	taskSeq:	h[i][sigma[i][p]] >= h[i][sigma[i][p-1]] + D[i][sigma[i][p-1]];
	}
	forall ( j in I, k in K : i != j) {
	machSeq1:	h[i][k] >= h[j][k] + D[j][k] - M * x[i][j][k];
	machSeq2:	h[j][k] >= h[i][k] + D[i][k] - M * (1 - x[i][j][k]);
	}
}
//forall ( i in I, j in I, k in K : i == j) notUsedX: x[i][j][k] == 0;
}





 
 
