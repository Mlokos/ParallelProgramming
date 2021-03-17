1compile_ex1_standard:
	mpicc -o ex1_standard.out ex1_standard.c

1run_ex1_standard:
	mpiexec -np 2 ./ex1_standard.out

2compile_ex1_sync:
	mpicc -o ex1_sync.out ex1_sync.c

2run_ex1_sync:
	mpiexec -np 2 ./ex1_sync.out

3compile_ex1_buffered:
	mpicc -o ex1_buffered.out ex1_buffered.c

3run_ex1_buffered:
	mpiexec -np 2 ./ex1_buffered.out

4compile_ex1_ready:
	mpicc -o ex1_ready.out ex1_ready.c

4run_ex1_ready:
	mpiexec -np 2 ./ex1_ready.out

5compile_ex1_async:
	mpicc -o ex1_async.out ex1_async.c

5run_ex1_async:
	mpiexec -np 2 ./ex1_async.out

clean:
	rm *.out