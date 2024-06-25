# PDC_A1
Speeding Up the Matrix Multiplication
# Performance Comparison and Optimization

## Processor Details
We started with an Intel Core i5-7300U CPU @ 2.60GHz, equipped with 2 physical and 4 logical cores. The system had 7.6 GiB of RAM and utilized an NVMe SSD for storage. The processor supported several vector capabilities, including SSE, AVX, AVX2, and FMA.

## Execution Times for Python, Java, and C
We executed a test case on a 1024x1024 matrix using Python, Java, and C to compare their performance:

### Python
Test case-1: real 11m57.786s, user 11m16.473s, sys 0m2.370s  
Test case-2: real 9m55.511s, user 9m31.469s, sys 0m0.804s  
Test case-3: real 12m35.401s, user 12m05.326s, sys 0m0.901s  

### Java
Test case-1: real 0m57.010s, user 0m21.119s, sys 0m15.204s  
Test case-2: real 0m47.743s, user 0m16.464s, sys 0m11.671s  
Test case-3: real 0m46.353s, user 0m15.902s, sys 0m10.836s  

### C
Test case-1: real 0m28.898s, user 0m6.516s, sys 0m0.244s  
Test case-2: real 0m28.989s, user 0m6.487s, sys 0m0.256s  
Test case-3: real 0m31.123s, user 0m6.774s, sys 0m0.310s  

## Optimizations with Vector Instructions and Multi-threading
Next, we implemented vector instructions and multi-threading in our C code to further optimize performance:

### Vector Instructions
Test case-1: real 0m56.667s, user 0m18.380s, sys 0m0.489s  
Test case-2: real 0m51.336s, user 0m18.584s, sys 0m0.505s  
Test case-3: real 0m27.126s, user 0m11.694s, sys 0m0.340s  

### Multi-threading
Test case-1: real 0m26.450s, user 0m11.713s, sys 0m0.340s  
Test case-2: real 0m26.980s, user 0m11.791s, sys 0m0.372s  
Test case-3: real 0m27.126s, user 0m11.694s, sys 0m0.340s  

### Vector Instructions + Multi-threading
Test case-1: real 0m27.861s, user 0m10.805s, sys 0m0.476s  
Test case-2: real 0m27.417s, user 0m10.588s, sys 0m0.580s  
Test case-3: real 0m28.166s, user 0m10.064s, sys 0m0.650s  

## Insights and Learnings
Through this assignment, we gained valuable insights into the performance differences between serial and parallel computation. The exercise involved implementing the same algorithm across high-level and low-level languages and comparing their execution times. As expected, lower-level languages demonstrated a clear advantage in terms of execution speed.

We observed that transitioning from Python to C provided the most significant speed-up. Additionally, incorporating multi-threading and vector instructions in C further enhanced performance, although the improvements were less pronounced than the initial language shift. Overall, optimizing code to leverage lower-level languages and parallel processing techniques can significantly reduce execution times.

## Documentation
For detailed documentation, including screenshots, refer to the [full report](./Pdc_A1_Document.odt).

## Screenshots

![image](https://github.com/Hamadshk/PDC_A1/assets/137650797/517d7940-68d2-42f7-a5ac-0a27c28a0437)

![image](https://github.com/Hamadshk/PDC_A1/assets/137650797/caa133fc-ecc7-4c0a-8d02-8dc15abe918c)

