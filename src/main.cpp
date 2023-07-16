#include <type_traits>
#include <iostream>
#include <vector>
#include <cerrno>

#define FLOAT_TYPE_ERR_MSG "Wrong template type, type should be float or double!"

template <typename T, int window_length>
std::vector <long double> const moving_avg(const std::vector <T> souce_data){
    static_assert(std::is_floating_point<T>::value, FLOAT_TYPE_ERR_MSG);
    std::vector <long double> result(souce_data.size() - window_length + 1);
    long double cur_sum = 0.0;
    auto mv_avg_iter = result.begin();
    for(auto it = souce_data.cbegin(); it < souce_data.cend(); it++){
        cur_sum += *it;
        if (std::distance(souce_data.cbegin(), it) >= window_length - 1){
            *mv_avg_iter = cur_sum / window_length;
            mv_avg_iter++;
            cur_sum -= *(it - window_length);
        }
    }
    return result;
}

int main(){
    std::vector<float> data{1, -2, -3, 4, 5};
    auto result = moving_avg<float, 3>(data);
    for(const auto& el: result){
        std::cout << el << ' ';
    }
    std::cout << std::endl;
    return 0;
}