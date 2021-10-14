/*********************************************
 * OPL Model
 * Diet: simple model
 *********************************************/

 dvar float+ xV;
 dvar float+ xM;
 dvar float+ xF;
 
 minimize 4 * xV + 10 * xM + 7 * xF;
 subject to {
   proteins:	5 * xV + 15 * xM +  4 * xF >= 20;
   iron:		6 * xV + 10 * xM +  5 * xF >= 30;
   calcium:		5 * xV +  3 * xM + 12 * xF >= 10;
 }
 