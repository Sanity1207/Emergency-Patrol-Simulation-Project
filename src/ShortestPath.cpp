#include "ShortestPath.h"
//SpCOllection 객체
//만들게 되면, startV에서 그래프의 각 노드로 가는 최단 거리, 경로 계산하여 저장.


int SpCollection::row = 0;
int SpCollection::column = 0;
int SpCollection::num_vertice = 0; //number of points in the map;

vector<vector<int>> cost;


SpCollection :: SpCollection(int startV, Department dept){
    this->startV = startV;
    this->department = dept;    
    initVectors();
    shortestPath();
}

//Getter Setter
int SpCollection :: getGraphSize(){
    return num_vertice;
}
int SpCollection :: getRow(){
    return row;
}
int SpCollection :: getColumn(){
    return column;
}
int SpCollection :: getCurLocation(){
    return startV;
}
int SpCollection :: getResponseCost(int eventIdx){ //get the response cost to a particular point
    return distance[eventIdx];
}
void SpCollection :: setGraphSize(int r, int c){
    row = r;
    column = c;
    num_vertice = r*c;
}
Department SpCollection :: getDept(){
    return department;
}


//다익스트라 시작 이전 그래프 (cost[[]]) 완성
void SpCollection::setGraphCost(){

    cost.resize(num_vertice,vector<int>(num_vertice,INF)); //set all costs to infinity

    //cost 그래프 채우기
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dis(1,10);

    for(int i=0;i<row;i++){ //양 옆으로 가는 path 생성
        for(int j=0;j<column-1;j++){
            int curten = column*i;
            cost[curten+j][curten+j+1] = dis(gen);
            cost[curten+j+1][curten+j] = cost[curten+j][curten+j+1]; //대칭 맞춰주기
            printf("cost(%d %d) is %d\n",curten+j, curten+j+1,cost[curten+j][curten+j+1]);
        }
    }

    for(int i=0;i<row-1;i++){//위 아래를 연결하는 path 생성
        for(int j=0;j<column;j++){
            int curten = column*i;
            int nextten = column*(i+1);
            cost[curten+j][nextten+j] = dis(gen);
            cost[nextten+j][curten+j] = cost[curten+j][nextten+j]; //대칭 맞춰주기
        }
    }
    for(int i=0;i<row;i++){ //일치하는 인간들 맞춰주기ㅣ.
        cost[i][i] = 0;
    }

}

//다익스트라 위한 초기화
void SpCollection::initVectors(){

    //assume cost[][] is already setup.g
    found.clear();
    distance.clear();
    parent.clear();
    
    found.resize(num_vertice, false);
    distance.resize(num_vertice,INF); //v 로부터 얼마나 걸리나를 기록
    parent.resize(num_vertice, -1);

    //initial node is set to found
    found[startV] = true;
    distance[startV] = 0;

    //initialize distance array and parent array
    for(int i=0;i<num_vertice;i++){
        distance[i] = cost[startV][i];
        
        if(i != startV && distance[i]<INF){
            parent[i] = startV;
            
        }
        
        printf("initialparent[%d] = %d\n",i,parent[i]);
    }
}


void SpCollection:: shortestPath(){
    int u;
    int w;

    for(int i=0;i<num_vertice-2;i++){
        
        u = choose();
        if(u == -1) break; //every node is found
        found[u] = true; //이 점을 거점으로 하여 거리 계산

        for(w=0;w<num_vertice;w++){
            if(!found[w] && (distance[w] > distance[u] + cost[u][w])){
                distance[w] = distance[u] + cost[u][w];
                parent[w] = u;
            }
        }

    }

}
int SpCollection:: choose(){
    int minIdx = -1;
    int minVal = INF;

    for(int i=0;i<num_vertice;i++){
        if(!found[i] && (distance[i] < minVal)){
            minIdx = i;
            minVal = distance[i];
        }
    }
    return minIdx;

}
void SpCollection::moveResponderAlongPath(int eventIndex){

    while(parent[eventIndex] > -1){
        path.push_back(eventIndex);
        eventIndex = parent[eventIndex];
        
    }
    
    reverse(path.begin(), path.end());
    
    for(int i=0;i<path.size();i++){
        printf("path : %d\n",path[i]);
        startV = path[i];
    }
    path.clear();
    
}

