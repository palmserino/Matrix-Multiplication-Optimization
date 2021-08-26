# Matrix-Multiplication-Optimization

This project aims to optimize matrix-matrix multiplication via 
  1. Sequential optimization
  2. Parallelization
  3. Vectorization
  4. Distrbution across compute nodes

The main implementations for each of these optimizations are in the files
  1. eigenfaces_opt.cpp
  2. eigenfaces_par.cpp
  3. eigenfaces_dgemm.cpp
  4. eigenfaces_mpi.cpp

The matrix-matrix multiplication done in this project computes a covariance matrix used to compute the singular value decomposition across images of human faces. This results in an 'eigenface' or set of eigenvectors that allows a computer to recognize a human face. 
