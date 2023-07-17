
# Project Title

This is a repo on SSSP using openMP. The goal is to parallelize SSSP algorithm so that it can be computationally faster and can be used to get the shortest path in large graphs with more than million or so nodes.

 
- Note :- The start node is 0 in most of the graphs.


## Googlesheet

 - The time is added for each graph in the Googlesheet that uses this link.      [click here](https://docs.google.com/spreadsheets/d/1y5K034SQDRGhh9Xp47HXxsQ0ctHYJzlUCKpwlYbiI9g/edit?usp=sharing)
 - [Large graphs link](https://snap.stanford.edu/data/)


## Related

OpenMP documentation [click here](https://www.openmp.org/resources/tutorials-articles/)




## Run

To run program, run the following command:-

```bash
  gcc -fopenmp SSSp.c -o SSSp
  
  ./SSSp
```

