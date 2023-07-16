# SimpleMovingAverage
This project includes a program to study the performance of calculating the moving average for the ``float`` and ``double`` types.

Results with plots [here](https://docs.google.com/spreadsheets/d/1rhCF5kd6Vws83d08faSGaQZvbi4hk-4W0C9_XEf9idE/edit?usp=sharing).
All results were made on:
```
OS: Linux 5.19.0-46-generic
CPU: Ryzen 5 3600, 3.6 GHz
RAM: 32 Gb

```
## Dependencies
-- [Docker](https://docs.docker.com/engine/install/)
-- cmake
-- g++

## Calculation moving average
To test calculations was written some simple tests in the ``src/main_simple_test.cpp``.

To test performance depending on window size and floating type was written program: ``src/main_perf_test.cpp``

### To run programs locally
Build execution files:
```
./scripts/compile.sh
./SimpleMovingAverageTest
./SimpleMovingAveragePerfTest
```

### To run from Docker container
Just run script:
```
./scripts/build_and_run_container.sh
```
