#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    ofxDatGuiTextInput* myInput = gui->addTextInput("Name:", "Stephen");
    vector<string> options = {"ONE", "TWO", "THREE", "FOUR"};
    
    gui->addDropdown("Hi",options);  
    myInput->onTextInputEvent(this, &ofApp::onTextInputEvent);
}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    cout << "the input field changed to: " << e.text << endl;
}
//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
