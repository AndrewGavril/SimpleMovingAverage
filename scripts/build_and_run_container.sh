#!/bin/bash

docker build . -t moving_avg
docker run --rm -v ./output:/project_src/output moving_avg
