#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(600, 300);
    
    searchGui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    infoGui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT);
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
    searchResults->expand();
}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout << "the option at index # " << e.child << " was selected " << endl;
    ofxDatGuiDropdownOption* selectedOption = searchResults->getChildAt(e.child);
    //layoutGui();
    std::cout<<"The full name of the instructor is: "<<selectedOption->getLabel()<<std::endl;
    std::map<SemesterClass,std::vector<Course>> courseMap = dataframe.getSemesterClassMapByInstructor(selectedOption->getLabel());
    clearLabels();
    int labelNumber = 0;
    for(auto it = courseMap.begin(); it != courseMap.end(); ++it){
        SemesterClass semesterClass = it->first;
        std::vector<Course> courseList = it->second;
        std::cout<<"SEMESTER CLASS: "<<semesterClass.subject<<semesterClass.courseNumber<<" "<< semesterClass.term<< " "<<semesterClass.year<<std::endl;
        std::cout<<"COURSE COUNT: "<<courseList.size()<<std::endl;
        std::cout<<"PROF GPA: "<<dataframe.getGPAByCourseVector(courseList)<<std::endl;
        std::cout<<"OTHER: "<<dataframe.getGPAExcludingInstructor(semesterClass,selectedOption->getLabel())<<std::endl;
        
        std::vector<std::pair<std::string,double>> instructorRankByGPA = dataframe.getInstructorRanksForSemesterClass(semesterClass);
        std::cout<<"OTHER PROFESSORS THIS SEMESTER: "<<std::endl;
        for(std::pair<std::string,double> instructorGPAPair : instructorRankByGPA){
            std::cout<<instructorGPAPair.first<<": "<<instructorGPAPair.second<<std::endl;
        }
        addCourseLabel(semesterClass,courseList);
    }
}

void ofApp::addCourseLabel(SemesterClass semesterClass, std::vector<Course> courseList){
    std::string description;
    double courseGPA = dataframe.getGPAByCourseVector(courseList);
    std::string professorName = courseList[0].instructorName;
    double nonInstructorGPA = dataframe.getGPAExcludingInstructor(semesterClass,professorName);

    description+= semesterClass.subject 
               + std::to_string(semesterClass.courseNumber) + " "
               + termArray[semesterClass.term] + " "
               + std::to_string(semesterClass.year) + "    "
               + std::to_string(round(1000*courseGPA)/1000).substr(0,5);
    
    std::pair<int,int> instructorRelativeRank = dataframe.getInstructorRankForSemesterClass(semesterClass,professorName);
    description+="("+std::to_string(instructorRelativeRank.first) +" / "+std::to_string(instructorRelativeRank.second) + ")";
    //if(instructorRelativeRank.first == 1) { 
    //    description+=" WORST GPA ";
    //}
    //if(instructorRankByGPA[instructorRankByGPA.size()-1].first == professorName) { // vector is sorted ascending, so being the first entry means worst GPA
    //    description+=" BEST GPA ";
    //}
    ofxDatGuiLabel* label = infoGui->addLabel(description);
    infoLabels.push_back(label);

    
    if(nonInstructorGPA == 0){
       label->setStripeColor(ofColor::orange);
    } else if(courseGPA < nonInstructorGPA){ // it's lower than average, so mark red
        label->setStripeColor(ofColor::red);
    } else {
        label->setStripeColor(ofColor::green);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofColor colorOne(0, 0, 1);
    ofColor colorTwo(255, 255, 255);

    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_CIRCULAR);
    ofDrawBitmapString("Josh's Professor Rating App", ofGetWidth()/2-120, ofGetHeight()-50);
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

void ofApp::clearLabels(){
    for(ofxDatGuiLabel* label : infoLabels){
        label->setVisible(false);
    }
    infoLabels.clear();
}
