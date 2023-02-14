#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 45 < 5) {

		this->random_seed = ofRandom(1000);
	}

	ofSeedRandom(this->random_seed);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto number_of_sphere = 150;
	vector<glm::vec2> location_list;
	vector<float> radius_list;

	while (location_list.size() < number_of_sphere) {

		auto location = glm::vec2(ofRandom(-300, 300), ofRandom(-300, 300));
		auto radius = ofRandom(8, 70);
		bool flag = true;
		for (int i = 0; i < location_list.size(); i++) {

			if (glm::distance(location, location_list[i]) < (radius + radius_list[i])) {

				flag = false;
				break;
			}
		}

		if (flag) {

			location_list.push_back(location);
			radius_list.push_back(radius);
		}
	}

	int count = 0;
	while (true) {

		auto all = true;

		for (int i = 0; i < location_list.size(); i++) {

			auto flag = true;
			for (int k = 0; k < location_list.size(); k++) {

				if (i == k) { continue; }

				if (glm::distance(location_list[i], location_list[k]) < (radius_list[i] + radius_list[k])) {

					flag = false;
				}
			}

			if (flag) {

				radius_list[i] += 1;
				all = false;
				break;
			}
		}

		if (all) {

			break;
		}

		count++;
	}

	ofColor color;
	auto param = ofGetFrameNum() % 45 < 5 ? 0.2 : ofGetFrameNum() % 45 < 15 ? ofMap(ofGetFrameNum() % 45, 5, 15, 0.2, 1) : 1;
	for (int i = 0; i < location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(location_list[i]);
		ofRotate(ofRandom(360));

		color.setHsb(ofRandom(0, 10), ofRandom(0, 255), 255);
		
		vector<glm::vec2> vertices;
		for (int deg = 0; deg < 360; deg += 1) {

			vertices.push_back(this->make_point(deg * DEG_TO_RAD) * 1.1);
		}

		for (auto& vertex : vertices) {

			vertex = vertex / 20 * radius_list[i];
		}

		ofFill();
		ofSetColor(color, 170);

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();

		ofNoFill();
		ofSetColor(color);

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
//Reference by https://twitter.com/shiffman/status/1095764239665512453
glm::vec2 ofApp::make_point(float theta) {

	float x = 16 * (pow(sin(theta), 3));
	float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	return glm::vec2(x, -y);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}