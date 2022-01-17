# script to run 30 times and save in results.txt
# $1 -> tabu length
# $2 -> maxiter
# $3 -> nodes N


MAX=30 # number of runs
if [ $3 -gt 70 ]
then
    MAX=10
fi
echo 'tabu = ' $1 ', maxiter = ' $2 ', N =' $3 >  Results/results$3.txt  # clean results file
for ((i=0; i<$MAX; i++))
do 
    ./main rand $1 $2 x $3 >> Results/results$3.txt
done