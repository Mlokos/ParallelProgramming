compile_homework_std:
	mpicc -o homework_std.out homework_std.c

run_homework_std:
	mpiexec -np 2 ./homework_std.out 2000000 20000

run_homework_std_no_shared_mem:
	MPIR_CVAR_NOLOCAL=1 mpiexec -np 2 ./homework_std.out 2000000 20000

compile_homework_async:
	mpicc -o homework_async.out homework_async.c

run_homework_async:
	mpiexec -np 2 ./homework_async.out 2000000 20000

run_homework_async_no_shared_mem:
	MPIR_CVAR_NOLOCAL=1 mpiexec -np 2 ./homework_async.out 2000000 20000

clean:
	rm *.out