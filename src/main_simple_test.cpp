#include <type_traits>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "moving_avg.h"
#define EPS 0.01
#define COMPLETE_STRING "===All tests have been passed!===\n"

template <typename T>
bool const isEqual(std::vector<T> const &v1, std::vector<T> const &v2)
{
    return std::equal(v1.begin(), v1.end(), v2.begin(),
                        [](double value1, double value2)
                        {
                            return std::fabs(value1 - value2) < EPS;
                        });
}


template <typename T>
void test_single(){
    const std::vector <T> v1{3};
    assert(isEqual<T>(moving_avg<T, 1>(v1), v1));
    assert(isEqual<T>(moving_avg<T, 2>(v1), v1));
    assert(isEqual<T>(moving_avg<T, 3>(v1), v1));
}

template <typename T>
void test_equal(){
    const std::vector <T> v1{1, 2, 3, 4, 5, 6, 623, -1};
    const std::vector <T> v2{1.5, 2.5, 3.5, 4.5, 5.5, 314.5, 311};
    const std::vector <T> v3{2, 3, 4, 5, 211.3333, 209.3333};

    assert(isEqual<T>(moving_avg<T, 1>(v1), v1));
    assert(isEqual<T>(moving_avg<T, 2>(v1), v2));
    assert(isEqual<T>(moving_avg<T, 3>(v1), v3));
}


template <typename T>
void test_overflow(){
    const std::vector <T> v1{std::numeric_limits<T>::max(), 2, 3, 4, 5, 6, 623, -1};
    const std::vector <T> v2{-std::numeric_limits<T>::max(), -2, -3, -4, -5, -6, 623, -1};
    try
    {
        moving_avg<T, 3>(v1);
        assert(false);
    }
    catch(const std::exception& e)
    {
        assert(typeid(e)==typeid(std::overflow_error("Type overflow!")));
    }
    try
    {
        moving_avg<T, 3>(v2);
        assert(false);
    }
    catch(const std::exception& e)
    {
        assert(typeid(e)==typeid(std::underflow_error("Type underflow!")));
    }
    
}

int main(){
    test_single<float>();
    test_single<double>();
    test_equal<float>();
    test_equal<double>();
    test_overflow<float>();
    std::cout << COMPLETE_STRING;
    return 0;
}
