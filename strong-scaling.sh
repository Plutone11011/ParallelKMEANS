

MAX_POINTS=200000
K=16
CORES=`cat /proc/cpuinfo | grep processor | wc -l`
echo "Strong"
echo "${CORES}"

for p in `seq $CORES`; do
    echo "Cores $p"
    for rep in `seq 5`; do
        EXEC_TIME="$( OMP_NUM_THREADS=$p ./kmeans $MAX_POINTS $K strong | sed 's/Execution time //' )"
        echo "${EXEC_TIME}"
    done
    echo ""
done