#include "Random.h"
#include <time.h>

std::random_device Random::s_Device;
std::mt19937 Random::s_Engine(Random::s_Device());