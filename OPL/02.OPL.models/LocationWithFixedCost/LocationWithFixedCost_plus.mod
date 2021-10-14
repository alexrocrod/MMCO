/*********************************************
 * OPL Model
 * Facility location with fixed costs: additional constraints
 *********************************************/

int NumLocations = ...;
setof(int) I = asSet(1..NumLocations);

float W = ...;
float F[I] = ...;
float C[I] = ...;
float R[I] = ...;
//float M = max (i in I ) ((W - F[i]) / C[i]) ;
float M[i in I] = (W - F[i]) / C[i];
int MaxLocations = ...;
int MinLocations = ...;
float MinOpen = ...;

dvar float+ x[I];
dvar boolean y[I];

maximize sum(i in I) R[i] * x[i];

subject to {
	budget: sum(i in I) ( C[i]*x[i] + F[i]*y[i] ) <= W;
	
	forall(i in I) {
		relateXtoY: x[i] <= M[i] * y[i]; 	
	}
	
	limitUB: sum(i in I) y[i] <= MaxLocations; 
	limitLB: sum(i in I) y[i] >= MinLocations;
	
	forall(i in I) {
		minOpening: x[i] >= MinOpen * y[i]; 	
	}

}
