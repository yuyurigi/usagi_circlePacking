#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false); //フレーム更新時に塗りつぶしを無効
    ofBackground(241, 240, 238);
    
    ofSetCircleResolution(50);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    myPhoto.load("u1.jpg"); //シルエット取得用の画像
    //myPhoto.load("u2.jpg");
    myPhoto.resize(400, 400);
    myPhoto.setImageType(OF_IMAGE_GRAYSCALE);
    width = myPhoto.getWidth();
    height = myPhoto.getHeight();
    
    pixelsOrigin = myPhoto.getPixels().getData();
    pixels = new unsigned char [width * height];
    
    myPhoto2.load("back1.jpg"); //色取得用の画像
    //myPhoto2.load("back2.jpg");
    
    //画像を白黒変換
    int threshold = 100;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(pixelsOrigin[i*width+j]>=threshold){
                pixels[i*width+j] = 255;
            }else{
                pixels[i*width+j] = 0;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    int currentFrame = ofGetFrameNum();
    if (currentFrame >= 3) { //３フレーム後から描き始める
        
    if(!onePixelLeft){
        maxWidth = 0;
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                if(pixels[i*width+j]==0){
                    // --> algorithm for finding the largest one
                    int range = 1;
                    bool dtct = 0;
                    
                    for(int k = 1; k<width+1; k+=2){
                            range = k;
                        if(((j-range/2)<0)||((j+range/2)>width)) dtct = 1;
                        if(((i-range/2)<0)||((i+range/2)>height)) dtct = 1;
                        if(dtct) {
                            range -= 2;
                            break;
                        }
                        dtct = 0;
                        for(int l=j-range/2; l<=j+range/2; l++){
                            for(int m=i-range/2; m<=i+range/2; m++){ // think about the case of l or m elss than 0
                                dist = sqrt((l-j)*(l-j)+(m-i)*(m-i));
                                if((dist<=(float)range/2)&&(pixels[m*width+l] == 255)) dtct = 1;
                            }
                        }
                    }
                    if(maxWidth<range){
                        maxWidth = range;
                        centerX = j;
                        centerY = i;
                    }
                }
            }
        }
        
        
        for(int i=centerY-maxWidth/2; i<=centerY+maxWidth/2; i++){
            for(int j=centerX-maxWidth/2; j<=centerX+maxWidth/2; j++){
                dist = sqrt((j-centerX)*(j-centerX)+(i-centerY)*(i-centerY));
                if(dist<=maxWidth/2) {
                    pixels[i*width+j] = 255;
                }
            }
        }
        if(maxWidth <4) onePixelLeft = 1; //円の直径の最小値　4未満は描かれない
    }
     
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofScale(2);
    myc = readBackground(centerX*2, centerY*2);
    ofSetColor(myc);
    ofDrawCircle(centerX, centerY, maxWidth/2);
    
    myImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
 
    if (key == 'S' || key == 's') {
            myImage.save(ofGetTimestampString("%Y%m%d%H%M%S")+"##.jpg");
    }
}

//--------------------------------------------------------------
ofColor ofApp::readBackground(float x, float y){
    ofPixels colorPixels = myPhoto2.getPixels();
    ofColor c = colorPixels.getColor(x, y);
    return c;
    
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
