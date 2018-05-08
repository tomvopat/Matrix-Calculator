# Matrix calculator
author: Tomáš Vopat

## Program commands
HELP\tshow help page\n
EXIT\tterminate program\n
LIST\tshow all variables and their values\n

## Matrix Definition
\<matrix name\> = MATRIX \<matrix type\> [\<row count\>,\<column count\>]\n
#### matrix type:
-F\tfull matrix\n
-S\tsparse matrix\n

### SCAN <matrix name>
\<val[0,0]\> \<val[0,1]\> \<val[0,2]\> ... \<val[1,0]\> \<val[1,1]\> ...\n
#### description:
scan elements of the matrices\n
#### example:
A = MATRIX -F [2,3]\n
SCAN A\n
1 2 3 4 5 6\n
PRINT A\n
#### result:
A:\n
\t1   2   3\n
\t4   5   6\n
### Show value in matrix
\<matrix name\> (\<row\>,\<column\>)\n
#### description:
show element on \<row\>.row \<column\>.column in matrix \<matrix name\>\n
### Set value in MATRIX
\<matrix name\> (\<row\>,\<column\>) = \<value\>\n
#### description:
set element on \<row\>.row \<column\>.column in matrix \<matrix name\> to value \<value\>\n

## Binary operators
### 1. option:
\<matrix name A\> \<operator\> \<matrix name B\>\n
#### description:
print result of binary operation\n
### 2. option:
\<matrix name C\> = \<matrix name A\> \<operator\> \<matrix name B\>\n
#### description:
store result of binary operation to variable \<matrix name C\>\n

### Binary operators
+\taddition\n
-\tsubtraction\n
\*\tmultiplication\n
#### addition
sizes of both matrices must be equal\n
##### example:
A + B\n
C = A + B\n
#### subtraction
sizes of both matrices must be equal\n
##### example:
A - B\n
C = A - B\n
#### multiplication:
width of first matrix must be equal to the height of the second matrix\n
#### example:
A * B\n
C = A * B\n
## Operations with MATRIX
### MERGE
MERGE \<merge type\> \<matrix name A\> \<matrix name B\>\n
\<matrix name C\> = MERGE \<merge type\> \<matrix name A\> \<matrix name B\>\n
#### marge type:
-H\tmerge matrices horizontally\n
-V\tmerge matrices vertically\n
#### example:
MERGE -H A B\n
C = MERGE -V A B\n
### CUT
CUT \<matrix name\> \<top-left position\> \<bottom-right position\>\n
#### description:
Operation to crop the matrix within specified positions top-left and bottom-right element included.\n
#### example:
CUT A (1,0) (2,1)\n
C = CUT A (1,0) (2,1)\n
### TRANS
TRANS \<matrix name\>\n
#### description:
Operation to transpose the matrix.\n
#### example:
TRANS A\n
C = TRANS A\n
### INV
INV \<matrix name\>\n
#### description:
Operation to count inverted matrix. ONLY for square matrices.\n
#### example:
INV A\n
C = INV A\n

### GEM
GEM \<matrix name\>\n
#### description:
Operation to perform Gaussian elimination.\n
#### example:
GEM A\n
C = GEM A\n

### DEM
DET \<matrix name\>\n
#### description:
Count determinant of the matrix. ONLY for square matrices.\n
#### example:
DET A\n

### RANK
RANK <matrix name>\n
#### description:
Count rank of the matrix.\n
#### example:
RANK A\n
