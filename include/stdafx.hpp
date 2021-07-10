#pragma once

#include <fstream>
#include <iostream>
#include <stdlib.h>

#include <array>
#include <vector>
#include <list>
#include <map>

#include <string>

#include <algorithm>
#include <exception>
#include <math.h>
#include <random>

#include "typedef.hpp"

#define deg2rad(deg) deg * 4.0 * std::atan (1.0) / 180.0
#define rad2deg(rad) rad / 4.0 / std::atan (1.0) * 180.0