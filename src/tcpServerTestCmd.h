//
//  tcpServerTestCmd.h
//  cameraTraceBuilder
//
//  Created by rainbo on 4/15/15.
//
//

#ifndef __cameraTraceBuilder__tcpServerTestCmd__
#define __cameraTraceBuilder__tcpServerTestCmd__

#include <iostream>

#include <maya/MPxCommand.h>
#include <maya/MDGModifier.h>

#include "dlib/sockets.h"
#include "dlib/server.h"

using namespace dlib;
using namespace std;

class serv : public server
{
public:
    //this function is override from server, and when a new connection is build,
    //create a new thread to invoke this function.
    void on_connect(connection& new_connection){
        char buffer;
        while(new_connection.read(&buffer, 1) > 0)
        {
            
            if(new_connection.write(&buffer,1) != 1)
                break;
        }
    }
};


class tcpServerTestCmd : public MPxCommand
{
public:
	virtual MStatus	doIt ( const MArgList& );
	virtual MStatus undoIt();
	virtual MStatus redoIt();
	virtual bool isUndoable() const { return true; }
    
	static void *creator() { return new tcpServerTestCmd; }
	static MSyntax newSyntax();
    
    //	MStatus setCameraPos(MPoint &cameraPos, MVector &cameraDir,
    //                         MVector &wsUpDir, double horizFieldOfView, double aspectRatio);
    
    //	MStatus getCameraParameters();
    
private:
    
    serv mayaTcpServer;
    
};


#endif /* defined(__cameraTraceBuilder__tcpServerTestCmd__) */
