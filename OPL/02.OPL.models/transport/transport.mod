/*********************************************
 * OPL Model
 * Transportation problem with additional constraints (mininum quantity on low cost links)
 *********************************************/

int Ndest = ...;
setof(string) I = ...;		// origins
setof(int) J = asSet(1..Ndest);			// destinations

int 	O[I] = ...; 		// capacity of origin i in I
int 	D[J] = ...; 		// request of destintion j in J
float	C[I][J] = ...;		// unit transportation cost

//additional parameters for requirement 1:
//	if the cost of link from i to j is at most LowCost,
//	then the flow on this link should be at least LowCostMinOnLink
float 	LowCost = ...;
int 	LowCostMinOnLink = ...;

//additional parameters for requirement 2:
//	destination SpecialDestination should receive at least MinToSpecialDest units
//	from each origin, but for origin SpecialOrigin
int SpecialDestination = ...;
string SpecialOrigin = ...;
float MinToSpecialDest = ...;

dvar int+ x[I][J];	// how much to move from i to j ?

minimize sum (i in I, j in J) (C[i][j] * x[i][j]);

subject to {
forall ( j in J ) {
	request: sum ( i in I ) x[i][j] >= D[j];
}

forall ( i in I ) {
	capacity: sum ( j in J ) x[i][j] <= O[i];
}

//additional constraints 1
forall ( i in I, j in J : C[i][j] <= LowCost ) {
	lowerboundCost: x[i][j] >= LowCostMinOnLink;
}

//additional constraints 2
forall ( i in I : i != SpecialOrigin) {
	lowerboundSpecial: x[i][SpecialDestination] >= MinToSpecialDest;
}

}





 
 
