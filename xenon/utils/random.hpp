#ifndef XENON_RANDOM
    #define XENON_RANDOM
    namespace xenon {
        // Used to generate random numbers
        namespace random {
            // Generate a random float between 0 and 1
            float generate();
            // Generate random numbers
            int generate_num(int min, int max); // Between MIN and MAX
            // Set a seed
            void set_seed(unsigned int seed);
        }
    }
#endif