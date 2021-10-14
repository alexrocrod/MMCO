/*********************************************
 * OPL Model
 * Facility location with fixed costs: basic
 *********************************************/

int NumLocations = ...;
setof(int) I = asSet(1..NumLocations);

float W = ...;
float F[I] = ...;
float C[I] = ...;
float R[I] = ...;
float M = 1e10;
int MaxLocations = ...;

dvar float+ x[I];
dvar boolean y[I];

maximize sum(i in I) R[i] * x[i];

subject to {
	budget: sum(i in I) ( C[i]*x[i] + F[i]*y[i] ) <= W;
	
	forall(i in I) {
		relateXtoY: x[i] <= M * y[i]; 	
	}
	
	limitUB: sum(i in I) y[i] <= MaxLocations;
		
}
