#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>
#include "moving_avg.h"
#define TESTS_PER_WINDOW_LEN 1000
#define VECTOR_GEN_LEN 1000000
#define RESULT_FILENAME "result.csv"
#define CSV_HEADER_STRING "WindowSize;FloatMeasurement;DoubleMeasurement;\n"
#define MIN_VAL -500.0
#define MAX_VAL 500.0

template <typename T>
std::shared_ptr<std::vector <T>> generate_vector(){
    static_assert(std::is_floating_point<T>::value, FLOAT_TYPE_ERR_MSG);
    std::srand(std::time(nullptr));
    auto vector = std::make_shared<std::vector<T>>(VECTOR_GEN_LEN);
    for(auto i=0; i < VECTOR_GEN_LEN; i++)
        vector->at(i) = MIN_VAL + static_cast <T> (rand()) /( static_cast <T> (RAND_MAX/(MAX_VAL-MIN_VAL)));
        
    return vector;
}

template <typename T>
long double test_one(std::shared_ptr<std::vector <T>> &vector, const int window_size){
    std::clock_t c_start = std::clock();
    
    try
    {
        moving_avg<T>(vector, window_size);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    std::clock_t c_end = std::clock();
    long double time_elapsed_ms = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
    return time_elapsed_ms;
}


void test(){
    const std::array window_sizes = {4, 8, 16, 32, 64, 128};
    std::ofstream result_file;
    result_file.open(RESULT_FILENAME);
    if(result_file.is_open()){
        result_file << CSV_HEADER_STRING;
        for(int j = 0; j < window_sizes.size(); j++){
            long double float_measures = 0.0;
            long double double_measures = 0.0;
            for(int i=0; i < TESTS_PER_WINDOW_LEN; i++){
                auto float_vector = generate_vector<float>();
                auto float_time = test_one<float>(float_vector, window_sizes[j]);
                float_measures += float_time;
                auto double_vector = generate_vector<double>();
                auto double_time = test_one<double>(double_vector, window_sizes[j]);
                double_measures += double_time;
            }
            float_measures /= TESTS_PER_WINDOW_LEN;
            double_measures /= TESTS_PER_WINDOW_LEN;
            result_file << window_sizes[j] << ";" << float_measures << ";" << double_measures << std::endl;

        }
        result_file.close();
    }
    else{
        std::cout << "Cannot open file: "<< RESULT_FILENAME << std::endl;
    }
}

int main(){
    auto vector = generate_vector<float>();
    test();
    return 0;
}