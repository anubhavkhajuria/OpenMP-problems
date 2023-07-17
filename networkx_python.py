import networkx as nx  
import time
def dijkstra(graph, start):
    distances = nx.single_source_dijkstra_path_length(graph, start)
    return distances

def read_graph_from_file(file_name):
    graph = nx.Graph()
    with open(file_name, 'r') as file:
        for line in file:
            node, neighbor = line.split()
            graph.add_edge(node, neighbor)
    return graph

#function to write the output in a file
def write_output_to_file(output_file, shortest_distances,time_taken):
    with open(output_file, 'w') as file:   
        file.write(f"Time taken to complete the computation:- {time_taken}\n")                 
        file.write(f"Shortest distances from node {start_node}:\n")
        for node, distance in shortest_distances.items():
            file.write(f"Node {node}: {distance}\n")


input_file = 'Slash.txt'  # Input file which contains source and destination
output_file = 'output1.txt'  # output file in which the result will be stored
graph = read_graph_from_file(input_file)

start_node = '0'
start_time = time.time()
shortest_distances = dijkstra(graph, start_node)
end_time = time.time()
time_taken = end_time-start_time
print(time_taken)

write_output_to_file(output_file, shortest_distances,time_taken)
