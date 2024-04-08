/**
 * Author: NA
 * Date: ??
 * License: NA
 * Description: For rng
 */
#pragma once

void RNG(){
  seed_seq seq{
    (uint64_t)chrono::duration_cast<chrono::nanoseconds>(
            chrono::high_resolution_clock::now()
            .time_since_epoch()).count(),
    (uint64_t)__builtin_ia32_rdtsc(),
    (uint64_t)(uintptr_t) make_unique<char>().get()};
  mt19927 rng(seq);//mt19937_64 lrng(seq); num=rng(); 
  num=uniform_int_distribution<int>(a,b)(rng);//[a,b]
  uniform_int_distribution<int>thing(a,b); num=thing();
}
