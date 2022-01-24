# script to run the 30 saved instances and save results in results.txt
# usage: ./runOldRandom.sh N class ResIdx

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
#   ./main filename.dat savedistsfile.dat [readDists] [Nrandom] [class]
done

printf '\n';
