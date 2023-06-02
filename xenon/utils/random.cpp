#include <cstdlib>
#include <cmath>
#include "utils/random.hpp"

namespace xenon {
    namespace random {
        float generate() {
            return (float)rand()/(float)RAND_MAX;
        }

        int generate_num(int min, int max) {
            // Make sure that max is greater than min. Else swap them around
            int nMax, nMin;
            if (min > max) {
                nMax = min;
                nMin = max;
            }
            else {
                nMax = max;
                nMin = min;
            }
            // Then generate the number
            float randValue = generate();
            return (int)round(randValue * (max - min) + min);
        }

        void set_seed(unsigned int seed) {
            srand(seed);
        }
    }
}