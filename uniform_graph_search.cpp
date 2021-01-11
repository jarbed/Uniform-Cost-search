#include <bits/stdc++.h>
using namespace std;
char* infile=NULL;
char* label=NULL;
bool directed=false,weighted=false;
int ind=1;
class node{
    public:
    int cost;
    vector<int> list;
};
struct Comparecost { 
    bool operator()(node const& p1, node const& p2) 
    {
        return p1.cost > p2.cost; 
    } 
};   
priority_queue<node, vector<node>, Comparecost> frontier;
class graph{
    public:
    vector<vector<pair<int,double>>> adj_list; // adjacency list to store graph
    vector<string> labels;  // labels for the vertices
    graph(char* inf,char* lab){ // constructor
        vector<set<pair< int,double>>> link;
        ifstream finput;
        finput.open(inf,fstream::in);
        while(!finput.eof()){
            int src,dest;
            double weight=1;
            if(weighted)    // if the graph is weighted
                finput>>src>>dest>>weight;
            else
                finput>>src>>dest;
            if(finput){
                if (link.size()<=max(src,dest)+1) { //resize the list for storing a vertex with greater id then the adj_list.size() needs to be strored
                    link.resize(max(src,dest)+1);
                }
                link[src].insert(make_pair(dest,weight));
                if (src!=dest && !directed)
                    link[dest].insert(make_pair(src,weight));
            }
        }
        finput.close();
        for(int i=0;i<link.size();i++){
            vector<pair< int,double>> lst;
            for(auto const &x : link[i]){
                lst.push_back(x);
            }
            adj_list.push_back(lst);
        }
        if(label!=NULL){    // if label file is provided
            finput.open(lab,fstream::in);
            string s;
            while(getline(finput,s)){
                if(s.size()>0)
                    labels.push_back(s);
            }
        }
    }
    void show_labels(){ // show the labels of the vertices by there indices
        for(int i=0;i<labels.size();i++){
            cout<<i+ind<<" "<<labels[i]<<endl;
        }
    }
};
void ufc(int src,int goal,graph g)
{    
    int size=g.adj_list.size();
    bool *visited=new bool(size);
    for(int i=0;i<size;i++)
        visited[i]=false;
    node temp;
    temp.cost=0;
    temp.list.push_back(src);
    frontier.push(temp);
    while(!frontier.empty())
    {
        node p=frontier.top();
        int ver=p.list[p.list.size()-1];
        if(ver==goal)   //if the goal is found
        {
            cout<<"goal found"<<endl;
            cout<<"cost = "<<p.cost<<endl;
            cout<<"path : ";
            for(int i=0;i<p.list.size();i++){
                if(label!=NULL)
                    cout<<"->"<<g.labels[p.list[i]-ind]<<endl;
                else
                    cout<<"->"<<p.list[i];
            }
            cout<<endl;    
            return;
        }
        if(!visited[ver]){  //if vertex not visited
            visited[ver]=true;
            for(int i=0;i<g.adj_list[ver].size();i++){
                node newnode;
                newnode.cost=g.adj_list[ver][i].second+p.cost;
                for(int j=0;j<p.list.size();j++)
                    newnode.list.push_back(p.list[j]);
                newnode.list.push_back(g.adj_list[ver][i].first);
                frontier.push(newnode);    //add vertices to frontier    
            }
        }
        frontier.pop();
    }
    cout<<"destination unreachable"<<endl;    
    return;
}
void init(int argc,char **argv){
    for(int i=1;i<argc;i++){
        if(argv[i][0] == '-') {
        switch(argv[i][1]) {
            case 'i':
                if (i==argc-1){
                    cout<<"input file missing"<<endl;
                    exit(0);
                }    
                infile = argv[i+1];
                i++;
                break;
            case 'w' : // set graph as weighted
                weighted = true;
                break;
            case 'd' :  //set graph as directed
                directed = true;
                break;
            case 'z' :  //set the starting index to 0
                ind=0;
                break;
            case 'l' :  //label file provided
                if (i==argc-1){
                    cout<<"label file missing"<<endl;
                    exit(0);
                }    
                label = argv[i+1];
                i++;
                break;
            default:
                exit(0);
        }
      }
    }
}
int main(int argc,char **argv){
    int src,dest;
    init(argc,argv);
    if(infile==NULL){
        cout<<"input file not provided"<<endl;
        exit(0);
    }
    graph g(infile,label);
    g.show_labels();    //shows the label for the vertices if provided
    while(1){
        cout<<"enter source : ";
        cin>>src;
        cout<<"enter destination : ";
        cin>>dest;
        if(src>=ind&&src<g.adj_list.size()&&dest>=ind&&dest<g.adj_list.size()){ // check for source and destination within the bound 
            ufc(src,dest,g);
            break;
        }
        cout<<"wrong value for source or destination try again :"<<endl;
    }        
    return 0;
}
