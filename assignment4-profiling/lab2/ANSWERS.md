### Performance improvements

Three flamegraphs are present in the analysis section, along with old data. Newer data is present in the main memory and has also been cited here. The thoughts.md cites my real time thoughts employing quite a lot of brevity


Looking at the original flamegraph (flamgegraph.svg in analysis), I noticed that chase dependency had a significant self time, a overall 56% according to sampled profiling (check analysis.txt) and a self percentage of 50. I also noticed significant L1 cache loads using perf stat (old_perf.txt). 
The total time of execution was 0.433ms

There were no memory leaks according to valgrind. 

I decided to first optimize chase_dependency. Using the hint, I first explored constant expressions, but that led to nowhere. Then, I unrolled the loop, using 7 instructions instead and that bought out noticeable changes. Sampling percentage of the function decreased to 37% while execution time of the program decreased to 0.347. 


The old flame graph also indicated that branchy_score also took some significant self time. As it was due to prediction misses, (multiple if misses), I used a bitwise masking approach and improved. The new flame graph is flame_graph2. The overall percentage of branchy_score went to 6% while the self reported percentage went down to 0.45%. There was a small decrease in execution time.


Branch misses decreased from 3.33% to 0.07%.


One other optimization I did, especially to reduce the L1 cache misses was to change the order of access in cold_probe to row major. This decreased branch misses from 39% to 25%.


After these optimizations, my code runs at an overall 0.189s

