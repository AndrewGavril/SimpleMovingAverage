#ifndef SIMPLEMOVINGAVERAGE_SRC_MOVINGAVG_H_
#define SIMPLEMOVINGAVERAGE_SRC_MOVINGAVG_H_
#define FLOAT_TYPE_ERR_MSG "Wrong template type, type should be float or double!"
#define TYPE_OVEFLOW_STR "Type overflow!"
#define TYPE_UNDERLOW_STR "Type underflow!"
#define INVALID_WINDOW_LENGRH_ERR_STR "Invalid window_length argument: window_length should be > 0!"
#define INVALID_VECTOR_LENGRH_ERR_STR "Invalid source_data argument: source_data size should be > 0!"
#include <vector>
#include <stdexcept>
#include <type_traits>
#include <limits>
#include <memory>



template <typename T>
std::shared_ptr<std::vector <T>> const moving_avg(const std::shared_ptr<std::vector <T>> &souce_data, const unsigned window_length){
    static_assert(std::is_floating_point<T>::value, FLOAT_TYPE_ERR_MSG);
    if (window_length == 0) throw std::invalid_argument(INVALID_WINDOW_LENGRH_ERR_STR);
    if (souce_data->size() == 0) throw std::invalid_argument(INVALID_WINDOW_LENGRH_ERR_STR);
    

    auto length = souce_data->size() > window_length? souce_data->size() - window_length + 1: 1;
    auto result = std::make_shared<std::vector <T>>(length);
    
    long double cur_sum = 0.0;
    auto mv_avg_iter = result->begin();
    for(auto it = souce_data->cbegin(); it < souce_data->cend(); it++){

        if ( (cur_sum < 0.0) == (*it < 0.0)
            && std::abs( *it ) > std::numeric_limits<T>::max() - std::abs( cur_sum ) ) {
            if (cur_sum > 0) throw std::overflow_error(TYPE_OVEFLOW_STR);
            if (cur_sum < 0) throw std::underflow_error(TYPE_UNDERLOW_STR);

        }
        cur_sum += *it;


        if (std::distance(souce_data->cbegin(), it) >= window_length - 1){
            cur_sum -= *(it - window_length);
            *mv_avg_iter = cur_sum / window_length;
            mv_avg_iter++;

        }
        
    }
    
    if (result->size() == 1) (*result)[0] = cur_sum / souce_data->size();
    return result;
}

#endif 