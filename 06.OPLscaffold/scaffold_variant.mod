int Ndest = ...;
setof(string) I = ...;		// closing sites
setof(int) J = asSet(1..Ndest);			// new sites

float	C[I][J] = ...;		// unit transportation cost
int 	D[I] = ...; 		// number of rods available at origin i in I
int 	R[J] = ...; 		// number of rods required at destintion j in J
float 	F = ...;			// fixed cost per available truck
int		N = ...;			// number of available trucks
float 	L = ...;			// fixed cost to rent a truck
int		K = ...;			// truck capacity

//additional constraint: destination j can receive rods from only one 
//	of the origins in a specific subset  
setof(string) UniqueFrom[J] = ...;

float A[I] = ...;			// fixed cost for loading operations in i

dvar int+ x[I][J];			// how may rods to move from i to j ?
dvar int+ w[I][J];		    // number of trucks from i to j ?
dvar int+ z;				// how many trucks to rent?
dvar boolean y[I][J];		// use a truck from i to j ?
dvar boolean v[I];			// loading operations in i?

minimize sum (i in I, j in J) (C[i][j] * x[i][j]) 
	+ F * sum (i in I, j in J) (w[i][j]) + ( L - F ) * z
	+ sum (i in I) A[i] * v[i];

subject to {
forall ( j in J ) {
	request: sum ( i in I ) x[i][j] >= R[j];
}

forall ( i in I ) {
	capacity: sum ( j in J ) x[i][j] <= D[i] * v[i];
}

forall ( i in I, j in J ) {
	capacityTruck: x[i][j] <= K * w[i][j];
}

limitTrucks: sum (i in I, j in J) (w[i][j]) <= N + z;

//reqirement: destination 2 cannot receive from both A and B
canUseTruckA2: x["A"][2] <= D["A"] * y["A"][2];
canUseTruckB2: x["B"][2] <= D["B"] * y["B"][2];
y["A"][2] + y["B"][2] <= 1;
//generalization
forall ( i in I, j in J ) { // D[i] as big-M
	canUseTruck: x[i][j] <= D[i] * y[i][j];
}
forall (j in J) {
	sum(i in UniqueFrom[j]) y[i][j] <= 1;
}

}





 
 
