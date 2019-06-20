#!/bin/bash
for i in {1000001..5000000..1000000}
do
   gcc ExactMedian.c -lm -o ExactMedian && ./ExactMedian i
done
