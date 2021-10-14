/*********************************************
 * OPL Model
 * Perfumes: simple model
 *********************************************/

 dvar float+ x_one;
 dvar float+ x_two;
  
 maximize 130 * x_one + 100 * x_two;
 subject to {
   rose:	1.5 * x_one +       x_two <= 27;
   lily:	      x_one +       x_two <= 21;
   violet:	0.3 * x_one + 0.5 * x_two <= 9;
 }