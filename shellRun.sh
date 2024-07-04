gcc main.c -Ofast -march=native -flto -fno-signed-zeros -fno-trapping-math  -o run.out
time ./run.out