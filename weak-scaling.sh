MAX_POINTS=50000
K=8
CORES=`cat /proc/cpuinfo | grep processor | wc -l`
echo "Weak"
echo "${CORES}"

for p in `seq $CORES`; do
    echo "Cores $p"
    for rep in `seq 5`; do
        EXEC_TIME="$( OMP_NUM_THREADS=$p ./kmeans $MAX_POINTS $K weak $p | sed 's/Execution time //' )"
        echo "${EXEC_TIME}"
    done
    echo ""
done