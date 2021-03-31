parallel_compile:
	mpicc -o homework_pi_parallel.out homework_pi_parallel.c

parallel_run:
	mpiexec -np 4 ./homework_pi_parallel.out 10000000

x_clean:
	rm *.out