Prerequisites:
	graph must be stored in a space separated file.containt of the file looks like
1. if the graph is unweighted
	source1 destination1
	source2 destination2
	.
	.
2. if the graph is weighted 
	source1 destination1 weight1
	source2 destination2 weight1
	.
	.
Labels may be given to vertices by a file where the labels are written according to there id in ascending order.Eg,
	label1
	label2
	.
	.
	.
Compile Instruction : 
	g++ uniform_graph_search.cpp
Execute Instruction :
	./a.out -i example_graph.txt
Execute Options:
-i : Must be provied for input graph file
-w : To use weighted graph(by default the graph is unweighted)
-d : To use directed graph(by default the graph is undirected)
-l : To provide a label for the vertices
-z : if the index start from 0 (by default the index starts from zero)