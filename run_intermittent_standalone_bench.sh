: "${CLIENTS:?Error: The CLIENTS environment variable is not set.}"

echo "Number of clients : $CLIENTS"

./kill_burns.sh

echo Adding intermittent procs to cgroup hw...
./run_intermittent_procs.sh
./add_intermittent_cgroup.sh

# Wait for "intermittent" procs to be done
res=0
while [ $res -eq 0 ]; do
    pgrep -f intermittent &> /dev/null
    res=$?
    sleep 1
done

echo Done!
