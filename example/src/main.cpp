#include "ofMain.h"
#include "ofxMyIP.h"

class ofApp : public ofBaseApp{
private:
    ofxMyIP myip;
    string result;
public:
    void setup(){
        ofBackground(0);
        ofSetFrameRate(30);
        myip.setup();
        
        vector<ofxMyIPAddress> list = myip.getList();
        stringstream s;
        for (vector<ofxMyIPAddress>::iterator o = list.begin(); o != list.end(); o++) {
            s << "interface: " << o->name << ", ip: " << o->address << ", netmask: " << (!o->netmask.empty() ? o->netmask : "null") << ", broadcast address: " << (!o->broadcast.empty() ? o->broadcast : "null") << endl;
        }
        result = s.str();
    }
    void update(){
        
    }
    void draw(){
        ofDrawBitmapString(result, 0, 10);
    }
    
};

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);
	ofRunApp(new ofApp());
    
}
