#include "utils.hpp"
#include <iostream>
#include <math.h>

char phred_symbol(double p) {
    return -10 * log10(p) + 33;
}

double phred_err(char c) {
    double q = c - 33;
    return pow10(-q/10.0);
}

std::string reverse_complement(std::string seq) {      
    std::string res = seq;
    int len = res.length();

    for (int i = 0; i < len; ++i) {
        res[i] = base_complements.find(seq[len-1-i])->second;
    }

    return res;
}

double mean(std::vector<int> s) {
    double res = 0.0;

    for (int n : s) {
        res += double(n);
    }

    return res / double(s.size());
}

double var(std::vector<int> s) {
    // corrected two-pass algorithm (1.7), from "Algorithms for computing
	// the sample variance: Analysis and recommendations" by Chan, Tony F., Gene H. Golub,
    // and Randall J. LeVeque.
    
    double ss = 0.0;
    double compensation = 0.0;

    double m = mean(s);

    for (int n : s) {
        double d = n - m;
        ss += d*d;
        compensation += d;
    }

    return (ss - compensation*compensation/double(s.size())) / double(s.size()-1);
}

std::string random_str(std::default_random_engine eng, int sz) {
    std::string str = std::string(sz, 'z');

    for (int i = 0; i < sz; i++) {
        str[i] = str_chars[std::uniform_int_distribution<>(0, str_chars.size()-1)(eng)];
    }

    return str;
}