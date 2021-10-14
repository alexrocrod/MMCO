/*********************************************
 * OPL Model
 * Optimal mix: more general model
 *********************************************/

 setof(string) I = { "rose","lily","violet"};
 setof(string) J = { "one", "two" };
 
 float D[I] 	= [27,20,9];
 float P[J] 	= [130,100];
 float Q[I][J] 	= [
 	[1.5 , 1.0],
 	[1.0 , 1.0],
 	[0.3 , 0.5]
 ];
 
 dvar float+ x[J];
 
 maximize sum( j in J ) P[j] * x[j];
 
 subject to {
 	forall ( i in I) {
 		resource: sum ( j in J ) Q[i][j] * x[j] <= D[i]; 	
 	} 
 }
