pgrep -f "intermittent" | while read pid; do echo $pid | sudo tee /sys/fs/cgroup/parent/hw/cgroup.procs; done
