#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	for (int i = 0; i < 20; i++) {

		auto radius = i * 30 + 60;
		ofRotateY(ofRandom(360));

		auto theta = (int)(ofGetFrameNum() + ofRandom(360)) % 180;
		vector<glm::vec3> vertices, sub_vertices;
		for (int deg = 0; deg <= 360; deg += 3) {

			auto location = glm::vec3(radius * cos(deg * DEG_TO_RAD) * sin(theta * DEG_TO_RAD),
				radius * sin(deg * DEG_TO_RAD) * sin(theta * DEG_TO_RAD),
				radius * cos(theta * DEG_TO_RAD));
			vertices.push_back(location);

			if (theta + 3 < 180) {

				auto sub_location = glm::vec3(radius * cos(deg * DEG_TO_RAD) * sin((theta + 5) *DEG_TO_RAD),
					radius * sin(deg * DEG_TO_RAD) * sin((theta + 5) * DEG_TO_RAD),
					radius * cos((theta + 5) * DEG_TO_RAD));
				sub_vertices.push_back(sub_location);
			}
		}

		ofFill();
		ofSetColor(255);
		ofBeginShape();
		ofVertices(vertices);
		if (sub_vertices.size() > 0) {

			std::reverse(sub_vertices.begin(), sub_vertices.end());
			ofVertices(sub_vertices);
		}
		ofEndShape();

		ofNoFill();
		ofSetColor(39);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();

		if (sub_vertices.size() > 0) {
		
			ofBeginShape();
			ofVertices(sub_vertices);
			ofEndShape();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}