#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    searchGui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    searchInput = searchGui->addTextInput("Last Name:", "Fagen-Ulmschneider");
    searchInput->onTextInputEvent(this, &ofApp::onTextInputEvent);

    vector<string> options = {"ONE", "TWO", "THREE", "FOUR"};
    searchResults = searchGui->addDropdown("Hi",options);  
    searchResults->setVisible(false);
    searchResults->onDropdownEvent(this, &ofApp::onDropdownEvent);
}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    cout << "the input field changed to: " << e.text << endl;
    searchResults->setVisible(true);
    

}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout << "the option at index # " << e.child << " was selected " << endl;
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
