//
//  tcpServerTestCmd.cpp
//  cameraTraceBuilder
//
//  Created by rainbo on 4/15/15.
//
//

#include "tcpServerTestCmd.h"

MStatus tcpServerTestCmd::doIt(const MArgList &)
{
    try
    {
        mayaTcpServer.set_listening_port(3000);
        mayaTcpServer.start_async();
    }
    catch(exception& e){
        cout << e.what();
    }
    
    return MStatus::kSuccess;
}