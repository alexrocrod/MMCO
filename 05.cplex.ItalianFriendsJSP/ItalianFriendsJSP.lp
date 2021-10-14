\ENCODING=ISO-8859-1
\Problem name: 

Minimize
 obj: y
Subject To
 c1:   - h_A_G + y >= 5
 c2:   - h_B_G + y >= 10
 c3:   - h_C_G + y >= 30
 c4:   - h_D_M + y >= 1
 c5:   h_A_R >= 0
 c6:   h_B_S >= 15
 c7:   h_C_M >= 15
 c8:   h_D_G >= 60
 c9:   - h_A_R + h_A_S >= 60
 c10:  h_A_M - h_A_S >= 30
 c11:  - h_A_M + h_A_G >= 2
 c12:  h_B_M - h_B_S >= 75
 c13:  h_B_R - h_B_M >= 3
 c14:  - h_B_R + h_B_G >= 25
 c15:  - h_C_M + h_C_S >= 5
 c16:  h_C_R - h_C_S >= 15
 c17:  - h_C_R + h_C_G >= 10
 c18:  h_D_R - h_D_G >= 90
 c19:  - h_D_R + h_D_S >= 1
 c20:  h_D_M - h_D_S >= 1
 c21:  h_A_R - h_B_R + 423 x_A_B_R >= 25
 c22:  - h_A_R + h_B_R - 423 x_A_B_R >= -363
 c23:  h_A_R - h_C_R + 423 x_A_C_R >= 10
 c24:  - h_A_R + h_C_R - 423 x_A_C_R >= -363
 c25:  h_A_R - h_D_R + 423 x_A_D_R >= 1
 c26:  - h_A_R + h_D_R - 423 x_A_D_R >= -363
 c27:  - h_A_R + h_B_R + 423 x_B_A_R >= 60
 c28:  h_A_R - h_B_R - 423 x_B_A_R >= -398
 c29:  h_B_R - h_C_R + 423 x_B_C_R >= 10
 c30:  - h_B_R + h_C_R - 423 x_B_C_R >= -398
 c31:  h_B_R - h_D_R + 423 x_B_D_R >= 1
 c32:  - h_B_R + h_D_R - 423 x_B_D_R >= -398
 c33:  - h_A_R + h_C_R + 423 x_C_A_R >= 60
 c34:  h_A_R - h_C_R - 423 x_C_A_R >= -413
 c35:  - h_B_R + h_C_R + 423 x_C_B_R >= 25
 c36:  h_B_R - h_C_R - 423 x_C_B_R >= -413
 c37:  h_C_R - h_D_R + 423 x_C_D_R >= 1
 c38:  - h_C_R + h_D_R - 423 x_C_D_R >= -413
 c39:  - h_A_R + h_D_R + 423 x_D_A_R >= 60
 c40:  h_A_R - h_D_R - 423 x_D_A_R >= -422
 c41:  - h_B_R + h_D_R + 423 x_D_B_R >= 25
 c42:  h_B_R - h_D_R - 423 x_D_B_R >= -422
 c43:  - h_C_R + h_D_R + 423 x_D_C_R >= 10
 c44:  h_C_R - h_D_R - 423 x_D_C_R >= -422
 c45:  h_A_M - h_B_M + 423 x_A_B_M >= 3
 c46:  - h_A_M + h_B_M - 423 x_A_B_M >= -421
 c47:  h_A_M - h_C_M + 423 x_A_C_M >= 5
 c48:  - h_A_M + h_C_M - 423 x_A_C_M >= -421
 c49:  h_A_M - h_D_M + 423 x_A_D_M >= 1
 c50:  - h_A_M + h_D_M - 423 x_A_D_M >= -421
 c51:  - h_A_M + h_B_M + 423 x_B_A_M >= 2
 c52:  h_A_M - h_B_M - 423 x_B_A_M >= -420
 c53:  h_B_M - h_C_M + 423 x_B_C_M >= 5
 c54:  - h_B_M + h_C_M - 423 x_B_C_M >= -420
 c55:  h_B_M - h_D_M + 423 x_B_D_M >= 1
 c56:  - h_B_M + h_D_M - 423 x_B_D_M >= -420
 c57:  - h_A_M + h_C_M + 423 x_C_A_M >= 2
 c58:  h_A_M - h_C_M - 423 x_C_A_M >= -418
 c59:  - h_B_M + h_C_M + 423 x_C_B_M >= 3
 c60:  h_B_M - h_C_M - 423 x_C_B_M >= -418
 c61:  h_C_M - h_D_M + 423 x_C_D_M >= 1
 c62:  - h_C_M + h_D_M - 423 x_C_D_M >= -418
 c63:  - h_A_M + h_D_M + 423 x_D_A_M >= 2
 c64:  h_A_M - h_D_M - 423 x_D_A_M >= -422
 c65:  - h_B_M + h_D_M + 423 x_D_B_M >= 3
 c66:  h_B_M - h_D_M - 423 x_D_B_M >= -422
 c67:  - h_C_M + h_D_M + 423 x_D_C_M >= 5
 c68:  h_C_M - h_D_M - 423 x_D_C_M >= -422
 c69:  h_A_S - h_B_S + 423 x_A_B_S >= 75
 c70:  - h_A_S + h_B_S - 423 x_A_B_S >= -393
 c71:  h_A_S - h_C_S + 423 x_A_C_S >= 15
 c72:  - h_A_S + h_C_S - 423 x_A_C_S >= -393
 c73:  h_A_S - h_D_S + 423 x_A_D_S >= 1
 c74:  - h_A_S + h_D_S - 423 x_A_D_S >= -393
 c75:  - h_A_S + h_B_S + 423 x_B_A_S >= 30
 c76:  h_A_S - h_B_S - 423 x_B_A_S >= -348
 c77:  h_B_S - h_C_S + 423 x_B_C_S >= 15
 c78:  - h_B_S + h_C_S - 423 x_B_C_S >= -348
 c79:  h_B_S - h_D_S + 423 x_B_D_S >= 1
 c80:  - h_B_S + h_D_S - 423 x_B_D_S >= -348
 c81:  - h_A_S + h_C_S + 423 x_C_A_S >= 30
 c82:  h_A_S - h_C_S - 423 x_C_A_S >= -408
 c83:  - h_B_S + h_C_S + 423 x_C_B_S >= 75
 c84:  h_B_S - h_C_S - 423 x_C_B_S >= -408
 c85:  h_C_S - h_D_S + 423 x_C_D_S >= 1
 c86:  - h_C_S + h_D_S - 423 x_C_D_S >= -408
 c87:  - h_A_S + h_D_S + 423 x_D_A_S >= 30
 c88:  h_A_S - h_D_S - 423 x_D_A_S >= -422
 c89:  - h_B_S + h_D_S + 423 x_D_B_S >= 75
 c90:  h_B_S - h_D_S - 423 x_D_B_S >= -422
 c91:  - h_C_S + h_D_S + 423 x_D_C_S >= 15
 c92:  h_C_S - h_D_S - 423 x_D_C_S >= -422
 c93:  h_A_G - h_B_G + 423 x_A_B_G >= 10
 c94:  - h_A_G + h_B_G - 423 x_A_B_G >= -418
 c95:  h_A_G - h_C_G + 423 x_A_C_G >= 30
 c96:  - h_A_G + h_C_G - 423 x_A_C_G >= -418
 c97:  h_A_G - h_D_G + 423 x_A_D_G >= 90
 c98:  - h_A_G + h_D_G - 423 x_A_D_G >= -418
 c99:  - h_A_G + h_B_G + 423 x_B_A_G >= 5
 c100: h_A_G - h_B_G - 423 x_B_A_G >= -413
 c101: h_B_G - h_C_G + 423 x_B_C_G >= 30
 c102: - h_B_G + h_C_G - 423 x_B_C_G >= -413
 c103: h_B_G - h_D_G + 423 x_B_D_G >= 90
 c104: - h_B_G + h_D_G - 423 x_B_D_G >= -413
 c105: - h_A_G + h_C_G + 423 x_C_A_G >= 5
 c106: h_A_G - h_C_G - 423 x_C_A_G >= -393
 c107: - h_B_G + h_C_G + 423 x_C_B_G >= 10
 c108: h_B_G - h_C_G - 423 x_C_B_G >= -393
 c109: h_C_G - h_D_G + 423 x_C_D_G >= 90
 c110: - h_C_G + h_D_G - 423 x_C_D_G >= -393
 c111: - h_A_G + h_D_G + 423 x_D_A_G >= 5
 c112: h_A_G - h_D_G - 423 x_D_A_G >= -333
 c113: - h_B_G + h_D_G + 423 x_D_B_G >= 10
 c114: h_B_G - h_D_G - 423 x_D_B_G >= -333
 c115: - h_C_G + h_D_G + 423 x_D_C_G >= 30
 c116: h_C_G - h_D_G - 423 x_D_C_G >= -333
Bounds
 0 <= x_A_B_R <= 1
 0 <= x_A_C_R <= 1
 0 <= x_A_D_R <= 1
 0 <= x_B_A_R <= 1
 0 <= x_B_C_R <= 1
 0 <= x_B_D_R <= 1
 0 <= x_C_A_R <= 1
 0 <= x_C_B_R <= 1
 0 <= x_C_D_R <= 1
 0 <= x_D_A_R <= 1
 0 <= x_D_B_R <= 1
 0 <= x_D_C_R <= 1
 0 <= x_A_B_M <= 1
 0 <= x_A_C_M <= 1
 0 <= x_A_D_M <= 1
 0 <= x_B_A_M <= 1
 0 <= x_B_C_M <= 1
 0 <= x_B_D_M <= 1
 0 <= x_C_A_M <= 1
 0 <= x_C_B_M <= 1
 0 <= x_C_D_M <= 1
 0 <= x_D_A_M <= 1
 0 <= x_D_B_M <= 1
 0 <= x_D_C_M <= 1
 0 <= x_A_B_S <= 1
 0 <= x_A_C_S <= 1
 0 <= x_A_D_S <= 1
 0 <= x_B_A_S <= 1
 0 <= x_B_C_S <= 1
 0 <= x_B_D_S <= 1
 0 <= x_C_A_S <= 1
 0 <= x_C_B_S <= 1
 0 <= x_C_D_S <= 1
 0 <= x_D_A_S <= 1
 0 <= x_D_B_S <= 1
 0 <= x_D_C_S <= 1
 0 <= x_A_B_G <= 1
 0 <= x_A_C_G <= 1
 0 <= x_A_D_G <= 1
 0 <= x_B_A_G <= 1
 0 <= x_B_C_G <= 1
 0 <= x_B_D_G <= 1
 0 <= x_C_A_G <= 1
 0 <= x_C_B_G <= 1
 0 <= x_C_D_G <= 1
 0 <= x_D_A_G <= 1
 0 <= x_D_B_G <= 1
 0 <= x_D_C_G <= 1
Binaries
 x_A_B_R  x_A_C_R  x_A_D_R  x_B_A_R  x_B_C_R  x_B_D_R  x_C_A_R  x_C_B_R 
 x_C_D_R  x_D_A_R  x_D_B_R  x_D_C_R  x_A_B_M  x_A_C_M  x_A_D_M  x_B_A_M 
 x_B_C_M  x_B_D_M  x_C_A_M  x_C_B_M  x_C_D_M  x_D_A_M  x_D_B_M  x_D_C_M 
 x_A_B_S  x_A_C_S  x_A_D_S  x_B_A_S  x_B_C_S  x_B_D_S  x_C_A_S  x_C_B_S 
 x_C_D_S  x_D_A_S  x_D_B_S  x_D_C_S  x_A_B_G  x_A_C_G  x_A_D_G  x_B_A_G 
 x_B_C_G  x_B_D_G  x_C_A_G  x_C_B_G  x_C_D_G  x_D_A_G  x_D_B_G  x_D_C_G 
End
