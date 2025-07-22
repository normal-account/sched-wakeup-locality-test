for i in $(seq 1 $CLIENTS); do
        ./intermittent $i &
done
