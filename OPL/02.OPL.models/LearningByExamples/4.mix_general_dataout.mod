/*********************************************
 * OPL Model
 * Optimal mix: general model
 *********************************************/

setof(string) I = ...;
setof(string) J = ...;

float D[I] 	= ...;
float P[J] 	= ...;
float Q[I][J] 	= ...;

dvar float+ x[J];

maximize sum ( j in J) P[j] * x[j];

subject to {
	forall ( i in I) {
		resource: sum ( j in J ) Q[i][j] * x[j] <= D[i]; 	
	} 
}