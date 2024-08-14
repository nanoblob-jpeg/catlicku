/**
 * Author: NA
 * Date: ??
 * License: NA
 * Description: For rng
 */
#pragma once

mt19937_64 rng();
int a_to_b = uniform_int_distribution<int>(a, b)(rng);