#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    


    ofSetWindowTitle("Final Project");
    font.load("D2Coding.ttf", 15); //load font.
    
    ofSetFrameRate(30);
    ofBackground(70, 70, 70);


    /*
        set flag variables
    */
    loadCompleteFlag = false;
    eventGeneratedFlag = false;
    drawNumberFlag = false;
    generateCompleteFlag = false;
    moveOperationCompleteFlag = true;
    
    //setting up graph here. just in case.
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    

    if(eventGeneratedFlag){
        //drawing an event 를 draw 함수 바깥으로 빼야 할 것 같다.
        drawEvent();
    }
    if(loadCompleteFlag){ //can draw the basic map and responders
        drawMap();
        drawResponders();
        
    }
//    if(generateCompleteFlag){
//        ;
//    }
    if(drawNumberFlag){
        drawNumbers();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='l'){ //load files and 변수들 초기화.
    /*
        todo
        1. cost 배열과 그래프의 사이즈(num_vertices)를 설정하는 함수 호출.
        2. responders 배열을 돌면서 각각의 위치를 설정해주며 생성자 호출 (distance 등등 계산)
    */
        if(!loadCompleteFlag){
            initGraph();
            initResponders(4);
            loadCompleteFlag = true;
        }

    }
    if(key=='g'){//generate event
        if(loadCompleteFlag && moveOperationCompleteFlag){
            moveOperationCompleteFlag = false;
            
            generateEvent();
            eventGeneratedFlag = true;
            CurResponder->moveResponderAlongPath(eventIndex);
         
            //path에 도착 이후
            CurResponder->initVectors();
            CurResponder->shortestPath();
            
            moveOperationCompleteFlag = true;
            
        }

    }
    if(key=='s'){//show number
        if(loadCompleteFlag){
            drawNumberFlag = !drawNumberFlag;
        }
        
    }

    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

/*
    Functions Added in 0622
*/

void ofApp:: initGraph(){
    SpCollection::setGraphSize(10,10);
    SpCollection::setGraphCost();
}

void ofApp::initResponders(int num){
    Responders.resize(2*num);
    
    int Vnum = SpCollection::getGraphSize() - 1;

    //police originally in left corner.
    //fire originallly in right corner.
    for(int i=0;i<2*num;i++){

        if(i<num){//make police patrol
            Responders[i] = new SpCollection(i*10,Police);
        }else{//make fire patrol
            Responders[i] = new SpCollection(i*10,Fire);
        }
    }

    
}
coordinate* ofApp::IdxToCoor(int idx){

    coordinate* temp = new coordinate;
    
    temp->i = idx/(SpCollection::getRow());
    temp->j = idx%(SpCollection::getColumn());

    return temp;
}
int ofApp::coorToIdx(int i,int j){
    int idx = i*(SpCollection::getColumn()) + j;

    return idx;
}

SpCollection* ofApp::generateEvent(){
    /*
    todo
        1. 좌표/responder type 를 무작위로 정한다. 거기서 event 가 일어났다고 가정한다.
        2. responders 배열에서 for loop 돌면서 responding cost 을 기준으로 min heap 에 넣어준다.
        3. min heap 의 맨 위를 빼서 curResponder 에 넣어준다.
        4. 그릴 준비를 해준다.
    */

   //setting random
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> disRow(1,(SpCollection::getRow())-2);
    uniform_int_distribution<int> disCol(0,(SpCollection::getColumn())-1);

    //event row and column 하나 선택후 인덱스 변환
    eventRow= disRow(gen);
    eventCol= disCol(gen);
    eventIndex = coorToIdx(eventRow,eventCol);
    printf("eventIndex = %d\n",eventIndex);
    
    
    if(disCol(gen)%2){
        eventType = Fire;
    }else{
        eventType = Police;
    }


    //responders 를 돌면서 거리가 가장 작은 놈을 찾는다 (min heap 생략)
    int min = INF;
    CurResponder = NULL;
    for(int i=0;i<Responders.size();i++){
        //타입에 맞는 responder 이고 cost 가 minimal 하다.
        if( Responders[i]->getDept() == eventType && (Responders[i]->getResponseCost(eventIndex)) < min ){
            min = Responders[i]->getResponseCost(eventIndex);
            CurResponder = Responders[i];
        }
    }
    
    
}


/*
 Draw functions added in 0622
 */
void ofApp::drawMap(){
    
    int row = SpCollection::getRow();
    int col = SpCollection::getColumn();
    int vertice_num = row*col;
    



    //draw the map
    ofSetColor(40, 40, 40);
    for(int i=0;i<row+1;i++){
        for(int j=0;j<col+1;j++){
//            cout<<i<<endl;
//            cout<<j<<endl;
            if(i==0 || i==row){
                ofDrawRectangle((2*j-1)*WIDTH, (2*i)*HEIGHT, WIDTH, HEIGHT);
            }
            ofDrawRectangle(2*j*WIDTH, 2*i*HEIGHT, WIDTH, HEIGHT);
            if(j==0 || j==row){
                ofDrawRectangle((2*j)*WIDTH, (2*i-1)*HEIGHT, WIDTH, HEIGHT);

            }
        }
    }
    
    if(drawNumberFlag){ //숫자를 그리도록 시킨다면
        
        
    }
    
}

void ofApp::drawResponders(){
    for(int i=0;i<Responders.size();i++){
        printResponder(Responders[i], i);
    }
}

void ofApp::printResponder(SpCollection* resp, int i){
    int curRow;
    int curCol;
    string printStr;
    
    coordinate* temp = IdxToCoor(resp->getCurLocation());
    
    curRow = temp->i;
    curCol = temp->j;
    
    delete temp;
    
    //시작 점 y : (curRow+1)*HEIGHT
    //시작 점 x : (curCol+1)*WIDTH
    //xoffset = WIDTH/2
    //yoffset = HEIGHT/2  //이것은 engine 마다 따로.
    
    //시작 좌표임
    int startX = (curCol*2 + 1)*WIDTH;
    int startY = (curRow*2 + 1)*HEIGHT;
    
    //소방차 : 왼쪽 위 occupy, 빨간색
    //경찰차 : 오른쪽 아래 occupy, 파란색
    
    if(resp->getDept() == Fire){ //소방차
        ofSetColor(71, 45, 51); //set to red;
    }else{ //경찰차.
        ofSetColor(79,129,189); //set to blue;
        startX += WIDTH/2;
        startY += HEIGHT/2;
    
    }
//    cout<<"printing from "<<startX<<" "<<startY<<endl;
    ofDrawRectangle(startX, startY, WIDTH/2, HEIGHT/2);
    
    printStr = to_string(i);
    ofSetColor(0, 0, 0);
    font.drawString(printStr.c_str(), startX+4, startY+WIDTH/2);
    
}

void ofApp::drawEvent(){

    int startX = (eventCol*2 + 1)*WIDTH;
    int startY = (eventRow*2 + 1)*HEIGHT;
    
    if(eventType == Fire){
        ofSetColor(153, 153, 0);
    }else{
        ofSetColor(0, 153, 153);
    }
    
    ofDrawRectangle(startX, startY, WIDTH, HEIGHT);

}
void ofApp::drawNumbers(){
    int totalRow = SpCollection::getRow();
    int totalCol = SpCollection::getColumn();

    string printStr;
    ofSetColor(100, 100, 100);
        for(int i=0;i<totalRow;i++){ //양 옆으로 가는거 출력
            for(int j=0;j<totalCol-1;j++){
                int curten = totalCol*i;
                printStr = to_string(cost[curten+j][curten+j+1]);
                font.drawString(printStr.c_str(), WIDTH*(2*j+2)+7, 2*(i+1)*HEIGHT-10);
                
            }
        }

        for(int i=0;i<totalRow-1;i++){//위 아래로 가는거 출력
            for(int j=0;j<totalCol;j++){
                int curten = totalCol*i;
                int nextten = totalCol*(i+1);
                printStr = to_string(cost[curten+j][nextten+j]);
                font.drawString(printStr.c_str(),WIDTH*(2*j+1)+7,HEIGHT*(2*(i+1)+1) - 12);
            }
        }




}
