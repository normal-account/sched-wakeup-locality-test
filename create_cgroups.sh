: "${CLIENTS:?Error: The CLIENTS environment variable is not set.}"

sudo mkdir /sys/fs/cgroup/parent
sudo mkdir /sys/fs/cgroup/parent/lw
sudo mkdir /sys/fs/cgroup/parent/hw

echo +cpu +cpuset | sudo tee /sys/fs/cgroup/cgroup.subtree_control
echo +cpu +cpuset | sudo tee /sys/fs/cgroup/parent/cgroup.subtree_control

echo 1 | sudo tee /sys/fs/cgroup/parent/lw/cpu.weight
echo 10000 | sudo tee /sys/fs/cgroup/parent/hw/cpu.weight

echo 0-$(($CLIENTS-1)) | sudo tee /sys/fs/cgroup/parent/cpuset.cpus
