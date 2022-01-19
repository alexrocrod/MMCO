# script to run 30 times and save in results.txt
MAX=30 # number of runs
if [ $1 -gt 70 ]
then
    MAX=10
fi
echo 'N =' $1 >  Results/results$1.txt  # clean results file
mkdir SavedDists/$1
for ((i=0; i<$MAX; i++))
do 
    ./main SavedDists/$1/$i.dat SavedDists/$1/$i.dat x >> Results/results$1.txt
done
#  usage: ./main filename.dat savedistsfile.dat [readDists] [Nrandom] [class]