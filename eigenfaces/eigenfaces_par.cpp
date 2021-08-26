//
// This file is part of the course materials for AMATH 483/583 at the University of Washington
// Spring 2021
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Carter Peyton
//

#include "amath583.hpp"
#include <future>
#include "omp.h"

void outer(Matrix& A, const Vector& x) {
  #pragma omp parallel // use openMP to parallelize 
    {
      size_t tid       = omp_get_thread_num();
      size_t parts     = omp_get_num_threads();
      size_t blocksize = x.num_rows() / parts;
      size_t begin     = tid * blocksize;
      size_t end       = (tid + 1) * blocksize;
      if (tid == parts - 1) {
        end = x.num_rows();
      }
    // Change loop ordering so that we are accessing adjacent parts of memory
    for (size_t i = begin; i < end; ++i) {
      double row_val = x(i);
      //#pragma omp simd //simd for even further optimization
      #pragma omp simd
      for (size_t j = 0; j < A.num_cols(); ++j) { 
        A(i,j) += row_val * x(j); 
      } 
    }
    }
}


auto gen_covariance(const std::vector<Vector>& z) {
  size_t sz = z[0].num_rows();
  Matrix C(sz, sz);

  for (size_t k = 0; k < z.size(); ++k) {
    outer(C, z[k]);
  }

  // Normalize
  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      C(i,j) = C(i,j) / z.size();
    }
  }

  return C;
}

const char* tag = "par";

#include "main.hpp"
