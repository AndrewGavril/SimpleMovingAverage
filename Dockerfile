FROM gcc:10.5
RUN apt-get update && apt-get install -y cmake
WORKDIR /project_src/
COPY ./src ./src
COPY ./CMakeLists.txt ./CMakeLists.txt
COPY ./scripts ./scripts
RUN ./scripts/compile.sh
WORKDIR /project_src/output/
CMD ../SimpleMovingAverageTest && ../SimpleMovingAveragePerfTest