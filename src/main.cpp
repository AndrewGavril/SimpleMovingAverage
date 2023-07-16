#include <type_traits>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <cassert>
#define FLOAT_TYPE_ERR_MSG "Wrong template type, type should be float or double!"
#define EPS 0.01
template <typename T>
bool const isEqual(std::vector<T> const &v1, std::vector<T> const &v2)
{
    return std::equal(v1.begin(), v1.end(), v2.begin(),
                        [](double value1, double value2)
                        {
                            return std::fabs(value1 - value2) < EPS;
                        });
}


template <typename T, int window_length>
std::vector <T> const moving_avg(const std::vector <T> &souce_data){
    static_assert(std::is_floating_point<T>::value, FLOAT_TYPE_ERR_MSG);
    auto length = souce_data.size() > window_length? souce_data.size() - window_length + 1: 1;
    std::vector <T> result(length);
    
    double cur_sum = 0.0;
    auto mv_avg_iter = result.begin();
    for(auto it = souce_data.cbegin(); it < souce_data.cend(); it++){
        cur_sum += *it;
        if (std::distance(souce_data.cbegin(), it) >= window_length - 1){
            cur_sum -= *(it - window_length);
            *mv_avg_iter = cur_sum / window_length;
            mv_avg_iter++;

        }
    }
    if (result.size() == 1) result[0] = cur_sum / souce_data.size();
    return result;
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

    auto result = moving_avg<T, 3>(v1);
    for(const auto& el: result){
        std::cout << el << ' ';
    }
    std::cout << std::endl;
    assert(isEqual<T>(moving_avg<T, 1>(v1), v1));
    assert(isEqual<T>(moving_avg<T, 2>(v1), v2));
    assert(isEqual<T>(moving_avg<T, 3>(v1), v3));
}

int main(){
    test_single<float>();
    test_single<double>();
    test_equal<float>();
    test_equal<double>();

    return 0;
}