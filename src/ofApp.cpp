#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    // Create the GUI sections
    searchGui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    infoGui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    legendGui = new ofxDatGui(ofxDatGuiAnchor::BOTTOM_RIGHT);

    // Create the search GUI
    searchInput = searchGui->addTextInput("Last Name:", "");
    searchInput->onTextInputEvent(this, &ofApp::onTextInputEvent);
    searchResults = nullptr;

    // Load the DataFrame
    dataframe = DataFrame(FILE_PATH);

    // Add a legend
    legendGui->addLabel("Legend:");
    legendGui->addLabel("(1/n) is easiest of n, (n/n) is hardest")->setStripeColor(ofColor::white);
    legendGui->addLabel("Green - Above Average GPA")->setStripeColor(ofColor::green);
    legendGui->addLabel("Red - Below Average GPA")->setStripeColor(ofColor::red);
    legendGui->addLabel("Orange - Only Instructor")->setStripeColor(ofColor::orange);


}

//--------------------------------------------------------------
void ofApp::update() {

}

/**
 * Handles getting and displaying the search query for instructors
 * 
 * @param event the ofxDatGui event representing what's in the textbox currently
 */
void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent event) {

    std::vector<std::string> matches = dataframe.getInstructorMatchesByName(event.text, 5);

    // cannot delete or change dropdown object options in ofxDatGui, so we 
    // must instead hide the layer
    if (searchResults != nullptr) {
        searchResults->setVisible(false);
    }
    searchResults = searchGui->addDropdown("Results", matches);
    searchResults->setVisible(true);
    searchResults->onDropdownEvent(this, &ofApp::onDropdownEvent);
    searchResults->expand();
}

/**
 * Handles when the user selects an instructor from the dropdown
 * 
 * @param event the event representing the index in the dropdown selected
 */
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent event) {
    // Get the specific dropdown that was selected, containing the instructor label
    ofxDatGuiDropdownOption *selectedOption = searchResults->getChildAt(event.child);
    std::map<SemesterClass, std::vector<Course>> courseMap = dataframe.getSemesterClassMapByInstructor(
            selectedOption->getLabel());

    // Remove any current labels
    clearLabels();
    int labelNumber = 0;
    for (auto it = courseMap.begin(); it != courseMap.end(); ++it) {
        // Display each label
        addCourseLabel(it->first, it->second);
    }

}

/**
 * Add the label to the GUI with all the information for that SemesterClass
 * @param semesterClass to compute statistics for
 * @param courseList courses taught that SemesterClass by the instructor that's being queried 
 */
void ofApp::addCourseLabel(SemesterClass semesterClass, std::vector<Course> courseList) {
    std::string description;
    double courseGPA = dataframe.getGPAByCourseVector(courseList);
    std::string instructorName = courseList[0].instructorName;
    double nonInstructorGPA = dataframe.getGPAExcludingInstructor(semesterClass, instructorName);

    description += semesterClass.subject
                   + std::to_string(semesterClass.courseNumber) + " "
                   + termArray[semesterClass.term] + " "
                   + std::to_string(semesterClass.year) + "    "
                   + std::to_string(round(1000 * courseGPA) / 1000).substr(0, 5);

    std::pair<int, int> instructorRelativeRank = dataframe.getInstructorRankForSemesterClass(
            semesterClass, instructorName);
    description += "("
                   + std::to_string(instructorRelativeRank.first)
                   + " / "
                   + std::to_string(instructorRelativeRank.second)
                   + ")";

    ofxDatGuiLabel *label = infoGui->addLabel(description);
    infoLabels.push_back(label);


    if (nonInstructorGPA == 0) {
        label->setStripeColor(ofColor::orange); // No GPA to compare with, so mark orange
    } else if (courseGPA < nonInstructorGPA) { // GPA lower than average, so mark red
        label->setStripeColor(ofColor::red);
    } else {
        label->setStripeColor(ofColor::green); // GPA higher than average, so mark green
    }

}

/**
 * Hide all the info labels in order to display info labels for a new instructor.
 */
void ofApp::clearLabels() {
    for (ofxDatGuiLabel *label : infoLabels) {
        label->setVisible(false);
    }
    infoLabels.clear();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofColor colorOne(0, 0, 1);
    ofColor colorTwo(255, 255, 255);

    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_CIRCULAR);
    ofDrawBitmapString("Josh's Instructor Rating App", ofGetWidth() / 2 - 120, ofGetHeight() - 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

