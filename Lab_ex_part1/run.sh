# script to run 30 times and save in results.txt
# for i in {1..30}; do 
for i in {1..10}; do 
    ./main rand $1 >> Results/results$1.txt
done