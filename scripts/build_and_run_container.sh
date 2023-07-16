#!/bin/bash

docker build . -t moving_avg
docker run --rm -v ./output:/project/output moving_avg
