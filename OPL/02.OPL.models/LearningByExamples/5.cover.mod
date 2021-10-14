/*********************************************
 * OPL Model
 * Min Cost Cover: general model
 *********************************************/

setof(string) I = ...;
setof(string) J = ...;

float C[I] 	= ...;
float R[J] 	= ...;
float A[I][J] 	= ...;

dvar float+ x[I];

minimize sum ( i in I) C[i] * x[i];

subject to {
	forall ( j in J) {
		resource: sum ( i in I ) A[i][j] * x[i] >= R[j]; 	
	} 
}
