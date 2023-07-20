import time

import heapq


def Single_source_shortest_path(graph, source):             #takes graph and source ass an input and returns the shortest distance from source to every node
    distances = {node: float('inf') for node in graph}         #initializing distance to every node to inf
    distances[source] = 0                   
    visited = set()
    fringe = [(0, source)]                                      # will Store all possibe node that can be visited from current node

    while fringe:
        current_distance, current_node = heapq.heappop(fringe)      #returns the shortest distance present in the fringe

        if current_node in visited:
            continue

        visited.add(current_node)
        for neighbor in graph[current_node]:                        
            new_distance = current_distance + 1
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance               
                heapq.heappush(fringe, (new_distance, neighbor))

    return distances


start_node = 0





def write_output_to_file(output_file, shortest_distances,time_taken):           #function to write output to the file 
    with open(output_file, 'w') as file:   
        file.write(f"Time taken to complete the computation:- {time_taken}\n")                 
        file.write(f"Shortest distances from node {start_node}:\n")
        for node, distance in shortest_distances.items():
            if(distance != float('inf') ):
                file.write(f"Node {node}: {distance}\n")



def read_graph(file):

    if file is None:
        exit(1)         #Some error in opening the file
    d = {}
    while True:
        line = file.readline()
        if not line:
            break
        node, neighbor = map(int,line.split())
        if(node in d):
            x = d[node]
            x.append(neighbor)
            if(neighbor in d):
                y = d[neighbor]
                y.append(node)
            else:
                d[neighbor] = [node]

        else:
            d[node] = [neighbor]
            if(neighbor in d):
                y = d[neighbor]
                y.append(node)
            else:
                d[neighbor] = [node]
    return d



file = open("facebook_combined.txt",'r')            #Graph input file 
d = read_graph(file)

file.close()
output_file = "output_google.txt"                   #File in which the output will be stored

start_time = time.time()
ds = Single_source_shortest_path(d,start_node)      #Function call
ds = dict(sorted(ds.items(), key=lambda x:x[1]))    #Sorting the result in according to the node distance from the source nodes

end_time = time.time()
time_taken = end_time-start_time

write_output_to_file(output_file,ds,time_taken)
print("Execution time: {} seconds".format(end_time - start_time))
