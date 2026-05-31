Current time: 0.433

1) Chase dependency is a hotspot
    -optimized it by unrolling the loop as steps is compile time. Went from 50% to 37% overall. 
Now time is 0.347

2) Branchy is as well
Went from 9.92% overall to 6% and self decreased from 9.14 to 0.45;

flame graph two representing the change after these 2 were added

Cold column probe went from 10.5% of running time to 9.6 and a reduction in self time from 7 to 0.5 when I changed the order. This should also help with the high l1-cache misses I had seen

Current l1 load cache misses - 17/65

old - 20/44;


Refresh history is the only other function for me to address



