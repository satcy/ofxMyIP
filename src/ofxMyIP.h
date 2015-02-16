#pragma once

#include "ofMain.h"

#include <arpa/inet.h>
#include <net/if.h>
#include <ifaddrs.h>

struct ofxMyIPAddress {
    string name;
    string address;
    string netmask;
    string broadcast;
};

class ofxMyIP
{
protected:
    vector<ofxMyIPAddress> list;
public:
    
    void setup(){
		struct ifaddrs *myaddrs;
		struct ifaddrs *ifa;
		struct sockaddr_in *s4;
		int status;
		
		char buf[INET_ADDRSTRLEN];
		
		status = getifaddrs(&myaddrs);
		if (status != 0) {
            ofLog(OF_LOG_NOTICE, "getifaddrs");
		}
		
		for (ifa = myaddrs; ifa != NULL; ifa = ifa->ifa_next) {
			if (ifa->ifa_addr == NULL) continue;
			if ((ifa->ifa_flags & IFF_UP) == 0) continue;
			
			if (ifa->ifa_addr->sa_family == AF_INET) {
				s4 = (struct sockaddr_in *)(ifa->ifa_addr);
				if (inet_ntop(ifa->ifa_addr->sa_family, (void *)&(s4->sin_addr), buf, sizeof(buf)) == NULL) {
					printf("%s: inet_ntop failed!\n", ifa->ifa_name);
				} else {
                    ofxMyIPAddress addr;
                    addr.name = ofToString(ifa->ifa_name);
                    addr.address = ofToString(buf);
                    
                    s4 = (struct sockaddr_in *)(ifa->ifa_netmask);
                    if (inet_ntop(ifa->ifa_netmask->sa_family, (void *)&(s4->sin_addr), buf, sizeof(buf)) == NULL) {
                        addr.netmask = "";
                    } else {
                        addr.netmask = ofToString(buf);
                    }
                    
                    s4 = (struct sockaddr_in *)(ifa->ifa_broadaddr);
                    if (inet_ntop(ifa->ifa_broadaddr->sa_family, (void *)&(s4->sin_addr), buf, sizeof(buf)) == NULL) {
                        addr.broadcast = "";
                    } else {
                        addr.broadcast = ofToString(buf);
                    }
                    
                    
                    list.push_back(addr);
				}
			}
		}
		
		freeifaddrs(myaddrs);
    }
    
    const vector<ofxMyIPAddress> getList(){
        return list;
    }
    
    string getIpAddress(){
        return getIpAddress("en0");
    }
    
	string getIpAddress(string interface)
	{
        if ( list.empty() ) return "";
        int find = -1;
        for ( int i=0; i<list.size(); i++ ) {
            if ( list[i].name == interface ) {
                find = i;
                break;
            }
        }
        if ( find != -1 ) {
            return list[find].address;
        } else {
            return "";
        }
	}
};