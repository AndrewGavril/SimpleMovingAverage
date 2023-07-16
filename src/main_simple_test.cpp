#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "moving_avg.h"
#define EPS 0.01
#define COMPLETE_STRING "===All tests have been passed!===\n"

template <typename T>
bool const isEqual(std::shared_ptr<std::vector <T>> const &v1, std::shared_ptr<std::vector <T>> const &v2)
{
    return std::equal(v1->begin(), v1->end(), v2->begin(),
                        [](double value1, double value2)
                        {
                            return std::fabs(value1 - value2) < EPS;
                        });
}


template <typename T>
void test_single(){
    auto v1 = std::make_shared<std::vector <T>>(std::vector<T>{3});
    assert(isEqual<T>(moving_avg<T>(v1, 1), v1));
    assert(isEqual<T>(moving_avg<T>(v1, 2), v1));
    assert(isEqual<T>(moving_avg<T>(v1, 3), v1));
}

template <typename T>
void test_equal(){
    auto v1 = std::make_shared<std::vector <T>>(std::vector<T>{1, 2, 3, 4, 5, 6, 623, -1});
    auto v2 = std::make_shared<std::vector <T>>(std::vector<T>{1.5, 2.5, 3.5, 4.5, 5.5, 314.5, 311});
    auto v3 = std::make_shared<std::vector <T>>(std::vector<T>{2, 3, 4, 5, 211.3333, 209.3333});

    assert(isEqual<T>(moving_avg<T>(v1, 1), v1));
    assert(isEqual<T>(moving_avg<T>(v1, 2), v2));
    assert(isEqual<T>(moving_avg<T>(v1, 3), v3));
}


template <typename T>
void test_overflow(){
    auto v1 = std::make_shared<std::vector <T>>(std::vector<T>{std::numeric_limits<T>::max(), 2, 3, 4, 5, 6, 623, -1});
    auto v2 = std::make_shared<std::vector <T>>(std::vector<T>{-std::numeric_limits<T>::max(), -2, -3, -4, -5, -6, 623, -1});
    try
    {
        moving_avg<T>(v1, 3);
        assert(false);
    }
    catch(const std::exception& e)
    {
        assert(typeid(e)==typeid(std::overflow_error(TYPE_OVEFLOW_STR)));
    }
    try
    {
        moving_avg<T>(v2, 3);
        assert(false);
    }
    catch(const std::exception& e)
    {
        assert(typeid(e)==typeid(std::underflow_error(TYPE_UNDERLOW_STR)));
    }
    
}

void test_arguments(){
    auto v1 = std::make_shared<std::vector <float>>(std::vector<float>());
    try
    {   

        moving_avg<float>(v1, 3);
        assert(false);
    }
    catch(const std::exception& e)
    {
        assert(typeid(e)==typeid(std::invalid_argument(INVALID_VECTOR_LENGRH_ERR_STR)));
    }
    try
    {
        moving_avg<float>(v1, 0);
        assert(false);
    }
    catch(const std::exception& e)
    {
        assert(typeid(e)==typeid(std::invalid_argument(INVALID_WINDOW_LENGRH_ERR_STR)));
    }
}

int main(){
    test_single<float>();
    test_single<double>();
    test_equal<float>();
    test_equal<double>();
    test_overflow<float>();
    test_overflow<double>();
    test_arguments();
    std::cout << COMPLETE_STRING;
    return 0;
}
