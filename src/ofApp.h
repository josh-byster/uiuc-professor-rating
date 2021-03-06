#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "CSVReader.h"
#include "Constants.h"
#include "DataFrame.h"
#include <vector>

class ofApp : public ofBaseApp {

public:
    void setup();

    void update();

    void draw();

    void keyPressed(int key);

    void keyReleased(int key);

    void mouseMoved(int x, int y);

    void mouseDragged(int x, int y, int button);

    void mousePressed(int x, int y, int button);

    void mouseReleased(int x, int y, int button);

    void mouseEntered(int x, int y);

    void mouseExited(int x, int y);

    void windowResized(int w, int h);

    void dragEvent(ofDragInfo dragInfo);

    void gotMessage(ofMessage msg);

private:
    ofxDatGui *searchGui;
    ofxDatGui *infoGui;
    ofxDatGui *legendGui;
    std::vector<ofxDatGuiLabel *> infoLabels;
    ofxDatGuiTextInput *searchInput;
    ofxDatGuiDropdown *searchResults;
    DataFrame dataframe;

    void onTextInputEvent(ofxDatGuiTextInputEvent event);

    void onDropdownEvent(ofxDatGuiDropdownEvent event);

    void clearLabels();

    void addCourseLabel(SemesterClass semesterClass, std::vector<Course> courseList);
};
