#include "esp_random.h"
#include "random_number_getter.h"

static inline double linear_interpolate(double unscaled, double min_range, double max_range,
                                        double min_scaled, double max_scaled)
{
    return (max_scaled - min_scaled) * ((unscaled - min_range) / (max_range - min_range)) +
        min_scaled;
}

double get_random_number_between(double a, double b)
{
    return linear_interpolate((double)esp_random(), 0.0, (double)UINT32_MAX, a, b);
}
