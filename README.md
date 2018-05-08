# Matrix calculator
author: Tomáš Vopat

## Program commands
HELP    show help page
EXIT    terminates program
LIST    print all variables and definitions

## Matrix Definition
<matrix name> = MATRIX <matrix type> [<row count>,<column count>]
#### matrix type:
-F  full matrix
-S  sparse matrix

### SCAN <matrix name>
<val[0,0]> <val[0,1]> <val[0,2]> ... <val[1,0]> <val[1,1]> ...
#### description:
scan elements of the matrices
#### example:
A = MATRIX -F [2,3]
SCAN A
1 2 3 4 5 6
PRINT A
#### result:
A: 1   2   3
   4   5   6
### Show value in matrix
<matrix name> (<row>,<column>)
#### description:
show element on <row>.row <column>.column in matrix <matrix name>
### Set value in MATRIX
<matrix name> (<row>,<column>) = <value>
#### description:
set element on <row>.row <column>.column in matrix <matrix name> to value <value>

## Binary operators
### 1. option:
<matrix name A> <operator> <matrix name B>
#### description:
print result of binary operation
### 2. option:
<matrix name C> = <matrix name A> <operator> <matrix name B>
#### description:
store result of binary operation to variable <matrix name C>

### Binary operators
+   addition
-   subtraction
*   multiplication
#### addition
sizes of both matrices must be equal
##### example:
A + B
C = A + B
#### subtraction
sizes of both matrices must be equal
##### example:
A - B
C = A - B
#### multiplication:
width of first matrix must be equal to the height of the second matrix
#### example:
A * B
C = A * B

------------------------------
------------------------------

## Operations with MATRIX
### MERGE
MERGE <merge type> <matrix name A> <matrix name B>
<matrix name C> = MERGE <merge type> <matrix name A> <matrix name B>
#### marge type:
-H  merge matrices horizontally
-V  merge matrices vertically
#### example:
MERGE -H A B
C = MERGE -V A B

### CUT
CUT <matrix name> <top-left position> <bottom-right position>
#### description:
Operation to crop the matrix within specified positions top-left and bottom-right element included.
#### example:
CUT A (1,0) (2,1)
C = CUT A (1,0) (2,1)

### TRANS
TRANS <matrix name>
#### description:
Operation to transpose the matrix.
#### example:
TRANS A
C = TRANS A

### INV
INV <matrix name>
#### description:
Operation to count inverted matrix. ONLY for square matrices.
#### example:
INV A
C = INV A

### GEM
GEM <matrix name>
#### description:
Operation to perform Gaussian elimination.
#### example:
GEM A
C = GEM A

### GEM
 <matrix name>
#### description:
Count determinant of the matrix. ONLY for square matrices.
#### example:
DET A

### GEM
RANK <matrix name>
#### description:
Count rank of the matrix.
#### example:
RANK A
