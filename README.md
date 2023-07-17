
# Project Title

This is an implementation SSSP using openMP. The goal is to parallelize SSSP algorithm so that it can be computationally faster and can be used to get the shortest path in large graphs with more than million or so nodes.

 
- Note :- The start node is 0 in most of the graphs.


## Googlesheet

 - The time is added for each graph in the Googlesheet that uses this link.      [click here](https://docs.google.com/spreadsheets/d/1y5K034SQDRGhh9Xp47HXxsQ0ctHYJzlUCKpwlYbiI9g/edit?usp=sharing)
 - [Large graphs link](https://snap.stanford.edu/data/)


## Related

OpenMP documentation [click here](https://www.openmp.org/resources/tutorials-articles/)




## Run Locally

Clone the project

```bash
  git clone https://github.com/anubhavkhajuria/OpenMP-problems/blob/6b813e52f59770c08113629204c48f670886c89c/Single_source_shortest_path.c
```

Go to the project directory

```bash
  cd my-project
```

Install dependencies

```bash
  sudo apt-get install libomp-dev

```


To run program, run the following command:-

```bash
  gcc -fopenmp Single_source_shortest_path.c -o SSSp
  
  ./SSSp
```

