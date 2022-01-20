# script to run 30 times and save in results.txt
MAX=30 # number of runs
if [ $1 -gt 70 ]
then
    MAX=10
fi
# mkdir Results$3
echo 'N =' $1 >  Results$3/results$1_class$2.txt  # clean results file
for ((i=0; i<$MAX; i++))
do 
    printf '%d, ' $i;
    ./main SavedDists/n$1_class$2/$i.dat ola.txt x >> Results$3/results$1_class$2.txt
done
printf '\n';

#  usage: ./main filename.dat savedistsfile.dat [readDists] [Nrandom] [class]