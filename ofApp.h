#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	void setRingToMesh(ofMesh& frame_target, glm::vec3 location, float radius, int deg_start, int deg_end);

	ofEasyCam cam;
	ofMesh frame;

	vector<glm::vec3> start_location_list;
	vector<glm::vec3> end_location_list;
};