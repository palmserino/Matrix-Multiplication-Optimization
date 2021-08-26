
Final Questions
===============

Eigenfaces
----------

* Given that forming the covariance matrix with 500 images takes approximately 10 seconds, how long (approximately) would forming the covariance matrix take if we used
all 262,781 images in the data file?

The time to compute the covariance is proportional to the square of the size of the vectors and to the number of those vectors. Each vector is of length 55*45 = 2475, and if we have 500
of those vectors we can write an equation in order to find the proportionality constant: t = k*n*l^2 -> 10 = k*(500)*(2475)^2 -> k = 3.26*10^-9. Using this proportionality constant
with 262,781 vectors (images) of the same length, we get the resulting time as t = (3.26*10^-9)(262,781)(2475)^2 = 5250 seconds. This means that computing the covariance matrix 
with 262,781 images takes around 5000 seconds. 


Sequential Optimization
-----------------------

* What optimizations did you apply to improve eigenfaces_opt? Explain why these optimizations would result in better performance.

I changed the loop ordering when computing the covariance matrix in the outer function. Moreover, I hoisted out the x element that remains constant. The change in loop ordering makes 
us access adjacent elements in memory, and hoisting the constant value of x prevents us from going out of place in memory. Together these improve performance.


Parallelization
---------------

* How did you parallelize your code? On 5000 faces, how much speedup were you able to get on 2, 4, 10, and 20 cores (cpus-per-task)?
Does the speedup improve if you load 15000 faces rather than 5000 faces?

I used openMP to parallelize my code and also used a SIMD directive to change my covariance matrix computation loop into a SIMD loop. For 2, 4, 10, and 20 cores 
I got speedups of 2.8x, 4.4x, 6.8x, and 14x respectively. Yes, the speedup improves (using 20 cores) from 14x to 17x when using 15000 faces. 


Blocking (AMATH 583)
--------------------

* Explain your blocking approach.
On 5000 faces and 10 (or 20) cores (say), 
how much speedup were you able to get over the non-blocked case?
How much speedup were you able to get over the non-blocked case for 50000 face?


DGEMM (Extra Credit)
--------------------

* What single core performance do you get with eigenfaces_dgemm? How does your performance scale for 2, 5, 10, 20 cores?  
How does your performance scale with number of faces (500, 5k, 50k)? (You may even try 40 cores and 50k or more faces.)

I achieved single core performane of 75 Gflops with eigenfaces_dgemm. I achieved speedups for 2, 5, 10, and 20 cores of 1.5x, 2.2x, 2.6x, and 2.1x respectively. 
Using 10 cores, I achieved performance scaling of 2.5x and 2.3x for 5k and 50k faces relative to 500 faces. 



MPI
---

* How does the performance of your eigenfaces_mpi.exe scale for 1, 2, 4, 8 nodes?  (With 10 cores.)

The nodes result in a linear performance increase between them (i.e 2 nodes is twice as fast as 1 node and 8 nodes is 8 times as fast as 1 node). 1 node performance is on par 
with the dgemm performance. For reference, the highest Gflops I saw with a call to mpi was around 900!


Max
---

* What configuration of nodes and cores per node gives you the very best performance?
(And what was your best performance?)

Using eigenfaces_mpi with the call to cblas dgemm with 16 nodes with 16 cores each gave me a peak performance of 1636.7 Gflops!

