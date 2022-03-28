echo "p\tt1\tt2\tt3\tt4\tt5"

MAX_POINTS=50000
K=10
CORES=`cat /proc/cpuinfo | grep processor | wc -l`
echo "${CORES}"

for p in `seq $CORES`; do
    echo "$p\t\c"
    for rep in `seq 5`; do
        EXEC_TIME="$( OMP_NUM_THREADS=$p ./kmeans $MAX_POINTS $K | sed 's/Execution time //' )"
        echo "${EXEC_TIME}\t\c"
    done
    echo ""
done