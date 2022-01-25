# Class 3 instances:
#   Small instances (n=10) are available as hole positions in the directory pos10
#   Small instances (n=10) are available as cost matrices in the directory SavedDists/dists10


# Part 1: # ./main filename.dat savedistsfile.dat [readDists] [Nrandom] [class]

make clean
make
./main x New_n10_class2.dat x 10 2  # New random instance of class 
./main SavedDists/n10_class1/0.dat temp.dat x # Read from saved cost matrix
./main pos10/dists10_1.dat SavedDists/dists10/dists10_1.dat # Read from saved positions

# Part 2: # ./main filename.dat tabulength maxiter [init] [readPos] [Nrandom] [class]

make clean
make
./main x 6 20 1 x 10 2 # New random instance: tabulength=6, maxit=20, random initial solution (1), n=10, class=2
./main SavedDists/n10_class1/0.dat 6 20 # Read from saved cost matrix, tabulength=6, maxit=20
./main pos10/dists10_1.dat 6 10 2 1 # Read from saved positions, tabulength=6, maxit=20, heuristic initial solution (2), readPos(1)