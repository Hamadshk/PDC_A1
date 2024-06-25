# PDC_A1: Speeding Up Matrix Multiplication

## Performance Comparison and Optimization 🚀

### Processor Details
We utilized an Intel Core i5-7300U CPU @ 2.60GHz with 2 physical and 4 logical cores, 7.6 GiB of RAM, and an NVMe SSD. The processor supports SSE, AVX, AVX2, and FMA vector capabilities.

## Execution Times for Python, Java, and C
We tested a 1024x1024 matrix multiplication using Python, Java, and C:

### Python 🐍
- **Test case-1**: real 11m57.786s, user 11m16.473s, sys 0m2.370s
- **Test case-2**: real 9m55.511s, user 9m31.469s, sys 0m0.804s
- **Test case-3**: real 12m35.401s, user 12m05.326s, sys 0m0.901s

### Java ☕
- **Test case-1**: real 0m57.010s, user 0m21.119s, sys 0m15.204s
- **Test case-2**: real 0m47.743s, user 0m16.464s, sys 0m11.671s
- **Test case-3**: real 0m46.353s, user 0m15.902s, sys 0m10.836s

### C 🅲
- **Test case-1**: real 0m28.898s, user 0m6.516s, sys 0m0.244s
- **Test case-2**: real 0m28.989s, user 0m6.487s, sys 0m0.256s
- **Test case-3**: real 0m31.123s, user 0m6.774s, sys 0m0.310s

## Optimizations with Vector Instructions and Multi-threading
We implemented vector instructions and multi-threading in our C code to optimize performance:

### Vector Instructions
- **Test case-1**: real 0m56.667s, user 0m18.380s, sys 0m0.489s
- **Test case-2**: real 0m51.336s, user 0m18.584s, sys 0m0.505s
- **Test case-3**: real 0m27.126s, user 0m11.694s, sys 0m0.340s

### Multi-threading
- **Test case-1**: real 0m26.450s, user 0m11.713s, sys 0m0.340s
- **Test case-2**: real 0m26.980s, user 0m11.791s, sys 0m0.372s
- **Test case-3**: real 0m27.126s, user 0m11.694s, sys 0m0.340s

### Vector Instructions + Multi-threading
- **Test case-1**: real 0m27.861s, user 0m10.805s, sys 0m0.476s
- **Test case-2**: real 0m27.417s, user 0m10.588s, sys 0m0.580s
- **Test case-3**: real 0m28.166s, user 0m10.064s, sys 0m0.650s

## Insights and Learnings
This assignment provided valuable insights into the performance differences between serial and parallel computation using Python, Java, and C. Transitioning from Python to C resulted in significant speed-ups, further enhanced by multi-threading and vector instructions in C. Optimizing code with lower-level languages and parallel processing techniques can dramatically reduce execution times.

## Documentation
For detailed documentation and screenshots, refer to the [full report](./Pdc_A1_Document.odt).

## Screenshots
![Matrix Multiplication Screenshot 1](https://github.com/Hamadshk/PDC_A1/assets/137650797/517d7940-68d2-42f7-a5ac-0a27c28a0437)
![Matrix Multiplication Screenshot 2](https://github.com/Hamadshk/PDC_A1/assets/137650797/caa133fc-ecc7-4c0a-8d02-8dc15abe918c)

## How to Run
To execute the matrix multiplication:
- Python: `python3 runPythonBased.py`
- Java: `javac runJavaBased.java` followed by `java runJavaBased`
- C: Compile with `gcc -o a runCbased.c` and execute with `./a`
- C with multi-threading: Compile with `gcc -o a runCbased.c -pthread` and execute with `./a`
- C with vector instructions and multi-threading: Compile with `gcc -o a runVectorAndMultiCore.c -mavx -pthread` and execute with `./a`

🔍 Explore, optimize, and enjoy faster matrix multiplication!
