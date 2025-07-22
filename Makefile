all: burn_cpu intermittent

burn_cpu:
	gcc -O0 -o burn_cpu burn_cpu.c

intermittent_burn_cpu:
	gcc -O3 -o intermittent intermittent.c