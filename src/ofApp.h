#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    ofColor readBackground(float x, float y);
    
    ofImage myPhoto;
    ofImage myPhoto2;
    ofImage myImage;
    unsigned char * pixelsOrigin;
    unsigned char * pixels;
    int width;
    int height;
    int maxWidth;
    int centerX;
    int centerY;
    float dist;
    bool onePixelLeft;
    
    ofColor myc;
};
