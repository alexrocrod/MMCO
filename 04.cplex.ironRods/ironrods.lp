\ENCODING=ISO-8859-1
\Problem name: 

Minimize
 obj: 9 x_A_1 + 6 x_A_2 + 5 x_A_3 + 7 x_B_1 + 4 x_B_2 + 9 x_B_3 + 4 x_C_1
      + 6 x_C_2 + 3 x_C_3 + 50 y_A_1 + 50 y_A_2 + 50 y_A_3 + 50 y_B_1
      + 50 y_B_2 + 50 y_B_3 + 50 y_C_1 + 50 y_C_2 + 50 y_C_3 + 15 z
Subject To
 c1:  x_A_1 + x_B_1 + x_C_1 >= 8000
 c2:  x_A_2 + x_B_2 + x_C_2 >= 5000
 c3:  x_A_3 + x_B_3 + x_C_3 >= 4000
 c4:  x_A_1 + x_A_2 + x_A_3 <= 7000
 c5:  x_B_1 + x_B_2 + x_B_3 <= 6000
 c6:  x_C_1 + x_C_2 + x_C_3 <= 4000
 c7:  x_A_1 - 10000 y_A_1 <= 0
 c8:  x_A_2 - 10000 y_A_2 <= 0
 c9:  x_A_3 - 10000 y_A_3 <= 0
 c10: x_B_1 - 10000 y_B_1 <= 0
 c11: x_B_2 - 10000 y_B_2 <= 0
 c12: x_B_3 - 10000 y_B_3 <= 0
 c13: x_C_1 - 10000 y_C_1 <= 0
 c14: x_C_2 - 10000 y_C_2 <= 0
 c15: x_C_3 - 10000 y_C_3 <= 0
 c16: y_A_1 + y_A_2 + y_A_3 + y_B_1 + y_B_2 + y_B_3 + y_C_1 + y_C_2 + y_C_3 - z
      <= 4
Bounds
      x_A_1 >= 0
      x_A_2 >= 0
      x_A_3 >= 0
      x_B_1 >= 0
      x_B_2 >= 0
      x_B_3 >= 0
      x_C_1 >= 0
      x_C_2 >= 0
      x_C_3 >= 0
 0 <= y_A_1 <= 1
 0 <= y_A_2 <= 1
 0 <= y_A_3 <= 1
 0 <= y_B_1 <= 1
 0 <= y_B_2 <= 1
 0 <= y_B_3 <= 1
 0 <= y_C_1 <= 1
 0 <= y_C_2 <= 1
 0 <= y_C_3 <= 1
 0 <= z <= 1
Binaries
 y_A_1  y_A_2  y_A_3  y_B_1  y_B_2  y_B_3  y_C_1  y_C_2  y_C_3  z 
Generals
 x_A_1  x_A_2  x_A_3  x_B_1  x_B_2  x_B_3  x_C_1  x_C_2  x_C_3 
End
