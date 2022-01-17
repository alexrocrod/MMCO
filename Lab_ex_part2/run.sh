# script to run 30 times and save in results.txt
# $1 -> tabu length
# $2 -> maxiter
# $3 -> nodes N
TABU=6
if [ $1 -gt 49 ]
then
    TABU=8
fi
MAXIT=$((2*$1))

MAX=30 # number of runs
if [ $1 -gt 70 ]
then
    MAX=10
fi
echo 'tabu = ' $TABU ', maxiter = ' $MAXIT ', N =' $1 >  Results/results$1.txt  # clean results file
for ((i=0; i<$MAX; i++))
do 
    ./main rand $TABU $MAXIT x $1 >> Results/results$1.txt
done