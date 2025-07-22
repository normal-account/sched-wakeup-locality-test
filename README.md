A test case to reproduce a task wakeup and locality performance issue in the Linux kernel scheduler.

More information here: https://lore.kernel.org/lkml/YQXPR01MB511370FEF51299CEFBF7A511C257A@YQXPR01MB5113.CANPRD01.PROD.OUTLOOK.COM/


# Reproducing the test case

1. Create the high-weight and low-weight cgroups:

```
export CLIENTS=4   # Number of concurrent processes and CPUs
./create_cgroups.sh
```

This will create cgroups "hw" (high weight) and "lw" (low weight), with cpu.weight set to 10000 and 1 respectively.

Assuming the CLIENTS environment variable is set to 4, cpuset.cpus will be set to 0-3 for both cgroups. 

In all scripts ran below, "intermittent" processes will be assigned to "hw" and all "burn" processes will be assigned to "lw". 


2. Compile the "intermittent" and "burn cpu" programs

```
make
```


3. Run the following script, which starts 4 unopposed "intermittent" processes and assign them to the "hw" cgroup (assuming $CLIENTS=4):

```
./run_intermittent_standalone_bench.sh
``` 

Note the number of iterations achieved by the intermittent processes, which will be printed after 30 seconds. This will be our baseline.


4. Run the following script, which runs 4 intermittent processes and 4 burn processes and assigns them to their respective cgroups (assuming $CLIENTS=4):

```
./run_intermittent_burn_compare_bench.sh
```

The number of iterations from the intermittent processes should have drastically reduced from the baseline in step 3, despite the "burn cpu" processes having an exceedingly low weight.

On my machine, the number of iterations achieved by the "intermittent" processes drop by ~32% between steps 3 and 4.
