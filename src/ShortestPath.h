#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>

#define INF 999999
#define WIDTH 35
#define HEIGHT 35
using namespace std;

//cost 는 전역변수로 선언한다.
extern vector<vector<int>> cost;

enum Department {
    Fire,
    Police
};


class SpCollection {
public:
    //스태틱 변수 선언

    //생성자 선언
    SpCollection(int startV, Department dept);

    //함수 선언
    void initVectors(); //shortest path 시행 전에 초기화.
    void shortestPath();// 다익스트라의 알고리즘을 활용하여 맵 전체 포인트에 대한 shortest path 계산
    int choose();
    void moveResponderAlongPath(int eventIndex);

    //멤버 변수 Getter Setter
    void changeCurLocation(int locationIDX);
    int getCurLocation();
    int getResponseCost(int eventIdx);
    Department getDept();


    //스태틱용 getter setter
    static void setGraphSize(int r, int c);
    static void setGraphCost();
    static int getGraphSize();
    static int getRow();
    static int getColumn();

    vector<int> path;
    
    
private:
    
    static int row;
    static int column;
    static int num_vertice; //number of points in the map;

    int startV; //current location of the fire engine/ police patrol
    Department department; //fire or police?

    vector<bool> found;
    vector<int> distance;
    vector<int> parent;

    
    


};
