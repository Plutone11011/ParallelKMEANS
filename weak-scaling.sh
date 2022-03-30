echo "p\tt1\tt2\tt3\tt4\tt5"

MAX_POINTS=(5000 10000 20000 50000 100000)
K=10
CORES=`cat /proc/cpuinfo | grep processor | wc -l`
echo "${CORES}"

for p in `seq $CORES`; do
    echo "$p\t\c"
    for i in "${MAX_POINTS[@]}"; do
    echo "$i\t\c"
        for rep in `seq 5`; do
            EXEC_TIME="$( OMP_NUM_THREADS=$p ./kmeans $i $K | sed 's/Execution time //' )"
            echo "${EXEC_TIME}\t\c"
        done
    echo ""
    done
done