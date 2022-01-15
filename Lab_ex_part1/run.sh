# script to run 30 times and save in results.txt
MAX=30 # number of runs
if [ $1 -gt 70 ]
then
    MAX=10
fi
echo '' >  Results/results$1.txt  # clean results file
for ((i=0; i<$MAX; i++))
do 
    ./main rand $1 >> Results/results$1.txt
done