# script to run 30 times and save in results.txt
MAX=30 # number of runs
if [ $1 -gt 70 ]
then
    MAX=10
fi
echo 'N =' $1 >  Results/results$1_class$2.txt  # clean results file
mkdir SavedDists/n$1_class$2
for ((i=0; i<$MAX; i++))
do 
    printf '%d, ' $i;
    ./main rand SavedDists/n$1_class$2/$i.dat x $1 $2 >> Results/results$1_class$2.txt
done
printf '\n';
#  usage: ./main filename.dat savedistsfile.dat [readDists] [Nrandom] [class]
