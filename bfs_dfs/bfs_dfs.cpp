#include<iostream>
#include<string>
#include<fstream>
#include<new>
#include<vector>
#include<algorithm>

//Global Variables
struct Node_Details
{
    int cost;
    int depth;
    int act_cost;
    std::string parent;
    std::string name;
};
std::vector<Node_Details> Visited_Nodes;
std::vector<Node_Details> Root_Array;
std::vector<Node_Details> Searched_Array;

bool node_compare(const Node_Details& lhs, const Node_Details& rhs)                //Comparing for sorting in Accending Order
{
    if(lhs.depth == rhs.depth)
        return lhs.name < rhs.name;
    else
        return lhs.depth < rhs.depth;
}

bool node_compareD(const Node_Details& lhs, const Node_Details& rhs)                //Comparing for sorting in Decending Order
{
    if(lhs.depth == rhs.depth)
        return lhs.name > rhs.name;
    else
        return lhs.depth < rhs.depth;
}
bool node_compareUCS(const Node_Details& lhs, const Node_Details& rhs)               //Comparing for sorting for UCS
{
    if(lhs.act_cost == rhs.act_cost)
        return lhs.name < rhs.name;
    else
        return lhs.act_cost < rhs.act_cost;
}

//Calculate depth
int cal_depth(std::string super_node)
{
    int d;
    
    for(int i=0;i<Searched_Array.size();i++)
    {
        if(super_node == Searched_Array[i].name)
        {
            d = (Searched_Array[i].depth)+1;
            break;
        }
        else if(super_node == "Main Root")
                d = 999;
    }
    return d;
}

//To Calculate the cumulative cost of path for UCS
int cal_cost(std::string nds, int cur_cos)
{
    int d;
    for(int i=0;i<Searched_Array.size();i++)
    {
        if(nds == Searched_Array[i].name)
        {
            d = (Searched_Array[i].act_cost)+cur_cos;
            break;
        }
    }
    return d;
}

//To calculate teh cost of Visited node.
int Visited_Cost(std::string vis_name)
{
    int d;
    for(int i=0;i<Root_Array.size();i++)
    {
        if(vis_name == Root_Array[i].name)
        {
            d = Root_Array[i].act_cost;
            break;
        }
    }
    return d;
}
//from root array to serached array
int Visited_Depth(std::string vis_name)
{
    int d;
    for(int i=0;i<Root_Array.size();i++)
    {
        if(vis_name == Root_Array[i].name)
        {
            d = Root_Array[i].depth;
            break;
        }
    }
    return d;
}
//To Remove the visited node having higher cost in UCS
void remv_node(std::string rmv_nd)
{
    for(int i=0;i<Root_Array.size();i++)
    {
        if(rmv_nd == Root_Array[i].name)
        Root_Array.erase(Root_Array.begin()+i);
    }
}

void BFS_search(int BRCost,std::string BRName,std:: string *BNodes,int Bnode_count,int **Bgraph,int Bbegin,int BRDepth,int BRact_cost,int Rs_code,std::string BRParn)
{
    std::cout<<"\n\n ****** EXPLORING POPED NODE:     "<<BRName<<"**********************\n\n";
    Node_Details dummy;
    int curr_node_cost,curr_node_act_cost;
    std::vector<Node_Details> temp_arr;
    dummy.cost = BRCost;
    dummy.act_cost = BRact_cost;
    dummy.name = BRName;
    dummy.depth = BRDepth;
    dummy.parent = BRParn;
    Searched_Array.push_back(dummy);                            //Push to BFS Graph
    int VNSize = Visited_Nodes.size(); std::cout<<"\n Visitied Node Size     :\t"<<VNSize<<"\n";
    for(int m = 0 ; m < VNSize ; m++)
    {
        std::cout<<"\n Visited Node Name and depth\t"<<Visited_Nodes[m].name<<"\t"<<Visited_Nodes[m].depth<<"\n";
    }
    for(int j=0; j<Bnode_count; j++)                       //Navigate all elements
    {
        bool flag = false;
        if(Bgraph[Bbegin][j] != 0)                       //Check if connectivity availableĵ
        {
            std::cout<<"\nPresent Node  \t"<<BNodes[j]<<"\n";
            curr_node_cost = Bgraph[Bbegin][j];
            curr_node_act_cost = cal_cost(BRName,curr_node_cost);
            bool flag = false;
            for(int k=0; k<VNSize; k++)  //check if node visited
            {
                int t_c_depth = cal_depth(BRName);
                if(BNodes[j] == Visited_Nodes[k].name && Visited_Nodes[k].depth <= t_c_depth)
                {
                    flag = true;
                    std::cout<<"Node already visited \t"<<Visited_Nodes[k].name<<"\tat depth\t"<<Visited_Nodes[k].depth<<"\tcurrent depth\t"<<t_c_depth<<"\n";                //Move to next element if node is visited
                    break;
                }
                else if (BNodes[j] == Visited_Nodes[k].name && Visited_Nodes[k].depth > t_c_depth)
                {
                    remv_node(Visited_Nodes[k].name);
                }
            }
            if(flag == false)
            {
                std::cout<<"\nPresent Node Inserting to Root and Visited \t"<<BNodes[j]<<"\n";
                //Update the visited vector
                dummy.cost = Bgraph[Bbegin][j];
                dummy.name = BNodes[j];
                dummy.parent = BRName;
                dummy.depth = cal_depth(BRName);
                dummy.act_cost = curr_node_act_cost;
                Root_Array.push_back(dummy);
                Visited_Nodes.push_back(dummy);
                for (int it=0;it<Root_Array.size();it++)
                    std::cout<<"\n Valur IN Root AARAY root & name\t"<<Root_Array[it].depth<<"\t"<<Root_Array[it].name<<"\n";
                
            }
            
        }
    }
    
    if(Rs_code == 1)                                               //Sorting
    std::sort(Root_Array.begin(), Root_Array.end(), node_compare);
    else if(Rs_code == 2)
    std::sort(Root_Array.begin(), Root_Array.end(), node_compareD);
    
}

void UCS_search(int BRCost,std::string BRName,std:: string *BNodes,int Bnode_count,int **Bgraph,int Bbegin,int BRDepth,int BRact_cost,std::string BRparn)
{
    int curr_node_cost,curr_node_act_cost;
    Node_Details dummy;
    dummy.cost = BRCost;
    dummy.act_cost = BRact_cost;
    dummy.name = BRName;
    dummy.depth = BRDepth;
    dummy.parent = BRparn;
    Searched_Array.push_back(dummy);                                                                        //Push to BFS Graph
    int VNSize = Visited_Nodes.size();
    for(int j=0; j<Bnode_count; j++)                                                                       //Navigate all elements
    {
        if(Bgraph[Bbegin][j] != 0)                                                                         //Check if connectivity available
        {
            curr_node_cost = Bgraph[Bbegin][j];
            curr_node_act_cost = cal_cost(BRName,curr_node_cost);
            bool flag = false;
            for(int k=0; k<VNSize; k++)                                                                   //check if node visited
            {
                int t_cost = Visited_Cost(Visited_Nodes[k].name);
                if(BNodes[j] == Visited_Nodes[k].name && t_cost <= curr_node_act_cost)
                {
                    flag = true;
                    //Move to next element if node is visited
                    std::cout<<"Node already visited with lower cost\t"<<Visited_Nodes[k].name<<"\n"; 
                    break;
                }
                else if (BNodes[j] == Visited_Nodes[k].name && t_cost > curr_node_act_cost)
                {
                    remv_node(Visited_Nodes[k].name);
                }
                
                
            }
            if(flag == false)
            {
                
                //Update the visited vector
                dummy.cost = Bgraph[Bbegin][j];
                dummy.name = BNodes[j];
                dummy.parent = BRName;
                dummy.depth = cal_depth(BRName);
                dummy.act_cost = curr_node_act_cost;
                Root_Array.push_back(dummy);
                Visited_Nodes.push_back(dummy);                                  //Update the temp vector
                std::sort(Root_Array.begin(), Root_Array.end(), node_compareUCS);
                
                
            }
            
        }
    }
    
    
}



void Print_BFS(std::string goal, int code)
{
    //std::vector<Node_Details> Path_Aarray;
    int x = 0;
    std::vector<std::string> t_name;
    bool itis = true;
    std::string go = goal;
    std::ofstream output;
    output.open("output.txt");
    //output<<"Tree:\t\t";
    for(int i=0;i<Searched_Array.size();i++)
    {
        
        if(Searched_Array[i].name == goal)
        {
            x = i+1;
            break;
        }
        //std::cout<<"\nVAlue of XXXXX\t"<<x;
        
    }
    
    if(x == 0 )
    {
        //CHANGED
        for(int i=0;i<Searched_Array.size();i++)
        {
            std::cout<<"\nParent of node  "<<i<<Searched_Array[i].name<<"at depth\t"<<Searched_Array[i].depth<<"   is \t "<<Searched_Array[i].parent;
            if(i == 0)
                output<<Searched_Array[i].name;
            else
                output<<"-"<<Searched_Array[i].name;
        }
        std::cout<<"\nNoPathAvailable";
        output<<"\nNoPathAvailable";
        output.close();
        exit(0);
    }
    
    for(int i=0;i<x;i++)
    {
        std::cout<<"\nParent of node  "<<i<<Searched_Array[i].name<<"   is \t "<<Searched_Array[i].parent;
        if(i == 0)
            output<<Searched_Array[i].name;
        else
            output<<"-"<<Searched_Array[i].name;
        
    }
    output<<"\n";
    while(go != "Main Root")
    {
        t_name.push_back(go);
        for (int k=0;k<Searched_Array.size();k++)
        {
            if(go == Searched_Array[k].name)
            {
                go = Searched_Array[k].parent;
                break;
            }
        }
        
    }
    
    
    for(int k = t_name.size()-1; k>=0;k--)
    {
        if(k == t_name.size()-1)
            output<<t_name[k];
        else
            output<<"-"<<t_name[k];
    }
    
    for(int j=0;j<Searched_Array.size();j++)
    {
        if(Searched_Array[j].name == goal)
        {
            output<<"\n"<<Searched_Array[j].act_cost;
            break;
        }
        
    }
    output.close();
    
}

//Checking for presence of Root and Goal node
void node_search(std:: string nds[],std::string str,int count)
{
    int x = 0,i;
    for(i=0;i<count;i++)
    {
        if(nds[i] == str)
        {
            x++;
            std::cout<<str<<" is present \n";
            break;
        }
    }
    if(x==0)
    {
        std::cout<<str<<" not available \n";
        std::ofstream output;
        output.open("output.txt");
        output<<str<<"  Node is not available in the given nodes.";
        output.close();
        exit(0);
    }
}
int main()
{
    //Variables
    int s_code,node_count,i,j,k,begin,RCost,Rdepth,Ract_cost;
    int **graph;
    std::string Root;
    std::string Goal;
    std::string *Nodes;
    std::string RName;
    std::string RParn;
    Node_Details dummy;
    // File Object
    std::ifstream input;
    input.open("input.txt");
    // Reading Type,Root, Goal and No. of nodes from file
    input>>s_code>>Root>>Goal>>node_count;
    std::cout<<s_code<<'\n'<<Root<<'\n'<<Goal<<'\n'<<node_count<<'\n';
    //Reading Nodes Names
    Nodes = new(std::nothrow) std::string[node_count];
    if (Nodes == NULL)
        std::cout<<"Error memory cannot be allocated";
    else
    {
        for(i=0;i<node_count;i++)
        input>>Nodes[i];
    }
    for(i=0;i<node_count;i++)
    std::cout<<Nodes[i]<<'\n';
    node_search(Nodes,Root,node_count);
    node_search(Nodes,Goal,node_count);
    //Rerading Graph
    graph = new(std::nothrow) int*[node_count];
    if (graph == NULL)
        std::cout<<"Error memmory cannot be allocated";
    else
    {
        for(j=0;j<node_count;j++)
        {
            graph[j] = new int[node_count];
        }
    }
    for(j=0;j<node_count;j++)
    {
        for(k=0;k<node_count;k++)
        {
            input>> graph[j][k];
        }
    }
    
    for(j=0;j<node_count;j++)
    {
        for(k=0;k<node_count;k++)
        std::cout<<graph[j][k]<<" ";
        std::cout<<'\n';
    }
    //Search Selection
    switch(s_code)
    {
        case 1:
        for(i=0; i<node_count; i++)
        {
            if(Nodes[i] == Root)
            {
                //Inserting the root to the root array
                begin = i;
                dummy.cost = graph[begin][begin];
                dummy.name = Nodes[begin];
                dummy.depth = 0;
                dummy.act_cost = 0;
                dummy.parent = "Main Root";
                Root_Array.push_back(dummy);
                Visited_Nodes.push_back(dummy);
                std::cout<<"\n Root is at \t"<<begin<<"\n";
                break;
            }
            
            else
            {
                std::cout<<"Root Not Present aaa  \n";
            }
        }
        
        while (Root_Array.size() != 0)
        {
            RCost = Root_Array[0].cost;
            Ract_cost = Root_Array[0].act_cost;
            RName = Root_Array[0].name;
            Rdepth = Root_Array[0].depth;
            RParn = Root_Array[0].parent;
            for(int i=0; i<node_count; i++)
            {
                if(Nodes[i] == RName)
                {
                    begin = i;
                    break;
                }
            }
            Root_Array.erase (Root_Array.begin());
            BFS_search(RCost,RName,Nodes,node_count,graph,begin,Rdepth,Ract_cost,s_code,RParn);
        }
        
        Print_BFS(Goal,s_code);
        for (int p=0;p<Searched_Array.size();p++)
            std::cout<<"\n BFS: at Node\t"<<p<<"\t"<<Searched_Array[p].name<<"   DEPTH   "<<Searched_Array[p].depth;
        for( int q=0;q<Visited_Nodes.size();q++)
        std::cout<<"\n VISITED NODES LIST:\t"<<q<<"  element \t"<<Visited_Nodes[q].name;
        break;
        
        
        case 2:
        for(i=0; i<node_count; i++)
        {
            if(Nodes[i] == Root)
            {
                begin = i;
                dummy.cost = graph[begin][begin];
                dummy.act_cost = 0;
                dummy.name = Nodes[begin];
                dummy.depth = 0;
                dummy.parent = "Main Root";
                Root_Array.push_back(dummy);
                Visited_Nodes.push_back(dummy);
                std::cout<<"\n Root is at \t"<<begin<<"\n";
                break;
            }
            
            else
                std::cout<<"Root Not Present \n";
        }
        while (Root_Array.size() != 0)
        {
            int RASize = Root_Array.size();
            RCost = Root_Array[RASize-1].cost;
            Ract_cost = Root_Array[RASize-1].act_cost;
            RName = Root_Array[RASize-1].name;
            Rdepth = Root_Array[RASize-1].depth;
            RParn = Root_Array[RASize-1].parent;
            for(int i=0; i<node_count; i++)
            {
                if(Nodes[i] == RName)
                {
                    begin = i;
                    break;
                }
            }
            Root_Array.pop_back();
            BFS_search(RCost,RName,Nodes,node_count,graph,begin,Rdepth,Ract_cost,s_code,RParn);
        }
        
        Print_BFS(Goal,s_code);
        for (int p=0;p<Searched_Array.size();p++)
            std::cout<<"\n DFS: at Node\t"<<p<<"\t"<<Searched_Array[p].name<<"   DEPTH   "<<Searched_Array[p].depth;
        for( int q=0;q<Visited_Nodes.size();q++)
        std::cout<<"\n VISITED NODES LIST:\t"<<q<<"  element \t"<<Visited_Nodes[q].name;
        break;
        
        case 3:  for(i=0; i<node_count; i++)
        {
            if(Nodes[i] == Root)
            {
                begin = i;
                dummy.cost = graph[begin][begin];
                dummy.act_cost = 0;
                dummy.name = Nodes[begin];
                dummy.depth = 0;
                dummy.parent = "Main Root";
                Root_Array.push_back(dummy);
                Visited_Nodes.push_back(dummy);
                std::cout<<"\n Root is at \t"<<begin<<"\n";
                break;
            }
            
            else
                std::cout<<"Root Not Present \n";
        }
        while (Root_Array.size() != 0)
        {
            RCost = Root_Array[0].cost;
            RName = Root_Array[0].name;
            Rdepth = Root_Array[0].depth;
            Ract_cost = Root_Array[0].act_cost;
            RParn = Root_Array[0].parent;
            for(int i=0; i<node_count; i++)
            {
                if(Nodes[i] == RName)
                {
                    begin = i;
                    break;
                }
            }
            Root_Array.erase (Root_Array.begin());
            UCS_search(RCost,RName,Nodes,node_count,graph,begin,Rdepth,Ract_cost,RParn);
        }
        
        Print_BFS(Goal,s_code);
        for (int p=0;p<Searched_Array.size();p++)
            std::cout<<"\n BFS: at Node\t"<<p<<"\t"<<Searched_Array[p].name<<"   COST   "<<Searched_Array[p].act_cost;
        for( int q=0;q<Visited_Nodes.size();q++)
            std::cout<<"\n VISITED NODES LIST:\t"<<q<<"  element \t"<<Visited_Nodes[q].name;
        break;
        default:
        std::cout<<"Please Enter a correct serach type number"<<'\n';
    }
    return 0;
}

