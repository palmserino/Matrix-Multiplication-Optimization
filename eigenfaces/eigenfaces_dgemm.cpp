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
#include "mkl_cblas.h"

auto gen_covariance(const std::vector<Vector>& z) {
  size_t sz = z[0].num_rows();
  Matrix C(sz, sz);
  
  // Declare variables per intel's source code
  double *A = new double[sz*z.size()];
  double *B = new double[z.size()*sz];
  double *P = new double[sz*sz];

  // Dimensions
  int m = sz;
  int n = sz; 
  int k = z.size();
  // F needs to be 2475 * num images, which is sz * z.size()
  // F^T needs to be num_images * 2475, which is z.size() * transpose 

  // Alpha and beta values
  double alpha = 1.0;
  double beta = 0.0; 

  // Matrices
    for (size_t i = 0; i < m; i++) {
      for (size_t k = 0; k < z.size(); ++k) {
        A[(i*z.size())+k] = 1.0*(z[k](i));
      }
    }
   

    for (size_t i = 0; i < n; i++) {
      for (size_t k = 0; k < z.size(); ++k) {
        B[(i*z.size())+k] = 1.0*(z[k](i));
      }
    }

    // Init P as a placeholder
    for (size_t i = 0; i < (m*n); i++) {
        P[i] = 0.0;
    }
  
  // call to cblas_dgemm
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, m, n, k, alpha, A, k, B, z.size(), beta, P, n);

  // convert placeholder array to C matrix
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      C(i,j) = P[(i*m) + j];
    }
  }

  // data cleanup
  delete [] A;
  delete [] B;
  delete [] P;

  // normalize 
  for (size_t i = 0; i < C.num_rows(); ++i) {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      C(i,j) = C(i,j) / z.size();
    }
  }

  return C;
}

const char* tag = "dgemm";

#include "main.hpp"
