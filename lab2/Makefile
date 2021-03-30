seq_compile:
	gcc -o homework_pi_sequential.out homework_pi_sequential.c

seq_run:
	./homework_pi_sequential.out 1000000

parallel_compile:
	mpicc -o homework_pi_parallel.out homework_pi_parallel.c

parallel_run:
	mpiexec -np 4 ./homework_pi_parallel.out 10000000

x_clean:
	rm *.out