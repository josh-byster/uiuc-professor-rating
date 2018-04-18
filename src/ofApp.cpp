#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    searchGui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    searchInput = searchGui->addTextInput("Last Name:", "Fagen-Ulmschneider");
    searchInput->onTextInputEvent(this, &ofApp::onTextInputEvent);
    searchResults = nullptr;

    dataframe = DataFrame(FILE_PATH);

}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    cout << "the input field changed to: " << e.text << endl;
    std::vector<std::string> matches = dataframe.getProfessorMatchesByName(e.text, 5);
    
    // cannot delete or change dropdown object options in ofxDatGui, so we 
    // must instead hide the layer
    if(searchResults != nullptr){
        searchResults->setVisible(false);
    }
    searchResults = searchGui->addDropdown("Results",matches);
    searchResults->setVisible(true);
    searchResults->onDropdownEvent(this, &ofApp::onDropdownEvent);

}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout << "the option at index # " << e.child << " was selected " << endl;
    ofxDatGuiDropdownOption* selectedOption = searchResults->getChildAt(e.child);
    //layoutGui();
    std::cout<<selectedOption->getLabel()<<std::endl;

    for(const Course& c : dataframe.getCoursesByInstructor(selectedOption->getLabel())){
        std::cout<<c.courseTitle<<std::endl;
    }
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
