#pragma once

#include "ofMain.h"
#include "ShortestPath.h"



typedef struct __coordinate{
    int i;
    int j;
}coordinate;


class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
//not used
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
    
//functions for drawing
        void drawMap();
        void drawResponders();
        void printResponder(SpCollection* resp, int i);
        void drawEvent();
        void drawNumbers();

    
//functions for graph
        void initGraph();
        void initResponders(int num);
        coordinate* IdxToCoor(int idx);
        int coorToIdx(int i, int j);

    
//functions for generating event and moving responders
        SpCollection* generateEvent();
        

    
//public variables for the graph (map)
        vector<SpCollection*> Responders;
        SpCollection* CurResponder;


//flag variables for status control
        bool loadCompleteFlag;
        bool eventGeneratedFlag;
        bool drawNumberFlag;
        bool generateCompleteFlag;
        bool moveOperationCompleteFlag;
//font variable
        ofTrueTypeFont font;

//variables for event
        int eventRow;
        int eventCol;
        int eventIndex;
        Department eventType;
};

