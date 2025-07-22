for i in $(seq 1 $(($CLIENTS))); do
        ./burn_cpu &
done
