# script to run 30 times and save in results.txt
# $1 -> tabu length
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

for ((j=0; j<5; j++))
do
    # mkdir Results$j
    echo 'N =' $1 >  Results$j/results$1_class1_init1.txt  # clean results file
    for ((i=0; i<$MAX; i++))
    do 
        printf '%d, ' $i;
        ./main SavedDists/n$1_class1/$i.dat $TABU $MAXIT 0 >> Results$j/results$1_class1_init1.txt
    done
    printf '\n';

    echo 'N =' $1 >  Results$j/results$1_class2_init1.txt  # clean results file
    for ((i=0; i<$MAX; i++))
    do 
        printf '%d, ' $i;
        ./main SavedDists/n$1_class2/$i.dat $TABU $MAXIT 0 >> Results$j/results$1_class2_init1.txt
    done
    printf '\n';

    # echo 'N =' $1 >  Results$j/results$1_class1_init2.txt  # clean results file
    # for ((i=0; i<$MAX; i++))
    # do 
    #     printf '%d, ' $i;
    #     ./main SavedDists/n$1_class1/$i.dat $TABU $MAXIT 2 >> Results$j/results$1_class1_init2.txt
    # done
    # printf '\n';

    # echo 'N =' $1 >  Results$j/results$1_class2_init2.txt  # clean results file
    # for ((i=0; i<$MAX; i++))
    # do 
    #     printf '%d, ' $i;
    #     ./main SavedDists/n$1_class2/$i.dat $TABU $MAXIT 2 >> Results$j/results$1_class2_init2.txt
    # done
    # printf '\n';
done

#  usage: ./main filename.dat tabulength maxiter [init] [readPos] [Nrandom] [class] 