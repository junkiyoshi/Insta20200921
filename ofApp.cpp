#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->frame.clear();
	this->start_location_list.clear();
	this->end_location_list.clear();

	int deg_span = 30;
	for (int x = -230; x <= 230; x += 230) {

		for (int y = -230; y <= 230; y += 230) {

			for (int radius = 30; radius <= 90; radius += 15) {

				int deg_start = 0;
				int deg_end = 0;
				int tmp_deg = 0;
				auto noise_seed = ofRandom(1000);
				for (int deg = 0; deg < 360 + tmp_deg; deg += 1) {

					auto noise_value = ofNoise(glm::vec4(noise_seed, cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD), ofGetFrameNum() * 0.01));

					if (noise_value < 0.6) {

						deg_end = deg;

						if (deg == 0) {

							while (true) {

								tmp_deg -= 1;
								auto tmp_noise_value = ofNoise(glm::vec4(noise_seed, cos(tmp_deg * DEG_TO_RAD), sin(tmp_deg * DEG_TO_RAD), ofGetFrameNum() * 0.01));
								if (tmp_noise_value > 0.55 || tmp_deg < -360) { break; }
								deg_start = tmp_deg;
							}
						}
					}
					else {

						if (deg_start < deg_end) {

							this->setRingToMesh(this->frame, glm::vec3(x, y, 0), radius, deg_start, deg_end);
						}

						deg_start = deg;
						deg_end = deg;
					}
				}

				if (deg_start != deg_end) {

					this->setRingToMesh(this->frame, glm::vec3(x, y, 0), radius, deg_start, deg_end);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(39);
	this->frame.drawWireframe();

	for (auto& location : this->end_location_list) {

		ofFill();
		ofSetColor(239);
		ofDrawCircle(location, 3);

		ofNoFill();
		ofSetColor(39);
		ofDrawCircle(location, 3);
	}

	for (auto& location : this->start_location_list) {

		ofFill();
		ofSetColor(39);
		ofDrawCircle(location, 3);
	}

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setRingToMesh(ofMesh& frame_target, glm::vec3 location, float radius, int deg_start, int deg_end) {

	if (deg_start == deg_end) { return; }

	int index = frame_target.getNumVertices();

	for (int deg = deg_start; deg <= deg_end; deg += 1) {

		vector<glm::vec3> vertices;
		vertices.push_back(location + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
		vertices.push_back(location + glm::vec3(radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), 0));
	
		auto frame_index = frame_target.getNumVertices();

		frame_target.addVertices(vertices);
		frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 1);

		if (deg == deg_start) {

			this->start_location_list.push_back(vertices.front());
		}

		if (deg == deg_end) {

			this->end_location_list.push_back(vertices.back());
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}