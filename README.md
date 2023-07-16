# SimpleMovingAverage
This project includes a program to study the performance of calculating the moving average for the ``float`` and ``double`` types.

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