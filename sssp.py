#implementing the algorithm
import time
def dijkstra(graph, start):
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    visited = set()
    
    while len(visited) < len(graph):
        current_node = None
        min_distance = float('inf')
        
        # find the unvisited node with the minimum distance
        for node in graph:
            if node not in visited and distances[node] < min_distance:
                current_node = node
                min_distance = distances[node]
        
        visited.add(current_node)
        
        #updating the distance for neighboring nodes
        if current_node in graph:
            for neighbor in graph[current_node]:
                distance = distances[current_node] + 1  #considering the weights of all edges is 1
                
                if distance < distances[neighbor]:
                    distances[neighbor] = distance
    
    return distances

def read_graph_from_file(file_name):  # function to read the input from a file
    graph = {}
    with open(file_name, 'r') as file:
        for line in file:
            node, neighbor = line.split()
            
            if node not in graph:       #incase the data is missing from the file
                graph[node] = []
            
            if neighbor not in graph:      #incase the data is missing from the file
                graph[neighbor] = []
                
            
            graph[node].append(neighbor)
            graph[neighbor].append(node)  #as it is an undirected graph
            
    return graph



def sortt(shortest_distances):        #sorting the nodes according to the distance from the start node
    return dict(sorted(shortest_distances.items(), key=lambda x:x[1]))
#function to write the output in a file



def write_output_to_file(output_file, shortest_distances,time_taken):
    with open(output_file, 'w') as file: 
        file.write(f"Time taken to complete the computation :- {time_taken}\n")                   
        file.write(f"Shortest distances from node {start_node}:\n")
        for node, distance in shortest_distances.items():
            file.write(f"Node {node}: {distance}\n")


input_file = 'Slash.txt'  # Input file which contains source and destination
output_file = 'output.txt'  # output file in which the result will be stored
graph = read_graph_from_file(input_file)
start_node = '0'
start_time = time.time()
shortest_distances = dijkstra(graph, start_node)
end_time = time.time()
shortest_distances = sortt(shortest_distances)
time_taken = end_time-start_time
print(time_taken)
write_output_to_file(output_file, shortest_distances,time_taken)
