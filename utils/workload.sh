#!/bin/sh

mkdir out-figures
mkdir out-csvs
parallel -j $1 "./bin/sat-simulated-annealing -n 250000 --samax 5 --tn 0.001 --t0 500 --cooling-schedule-i 1 < examples/{1} > out-csvs/out-{1}-{2}.csv && python3 utils/plot.py out-csvs/out-{1}-{2}.csv out-figures/out-{1}-{2}.png" ::: uf20-01.cnf uf100-01.cnf uf250-01.cnf ::: 1 2 3 4 5 6 7 8 9 10
parallel -j $1 "./bin/sat-simulated-annealing -n 250000 --samax 5 --tn 0.001 --t0 500 --cooling-schedule-i {2} < examples/{1} > out-csvs/test-out-{1}-{2}.csv && python3 utils/plot.py out-csvs/test-out-{1}-{2}.csv out-figures/test-out-{1}-{2}.png" ::: uf20-01.cnf uf100-01.cnf uf250-01.cnf ::: 0 1 2 3 4 5 6 7 8 9