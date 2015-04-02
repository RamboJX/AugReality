//-
// ==========================================================================
// Copyright pku&itu . All rights reserved.
// ==========================================================================
//+
//
// File: recordCameraTrace.cpp
//
//
// Author: Lingbo Wang
//

#include "recordCameraTrace.h"

MDagPath recordCameraTrace::testTrans;

MStatus recordCameraTrace::doIt ( const MArgList &args )
{ 	
	
	MStatus status = MS::kSuccess;

//1. new a camera, and set the animation fn bind to this camera
	MString camera_name = "test";
	MFnCamera cameraFn;
	MObject camera = cameraFn.create(&status);
	if (status == MS::kFailure)
        printf("Error creating the camera.\n");
	MFnDagNode fnSet( camera, &status);
    
    MDagPath dp;
	if (cameraFn.getPath(dp) != MS::kSuccess)
        printf("Failure creating dag path\n");
	if (camera_name.length() > 0) {
		fnSet.setName(camera_name, &status);
		if (status == MS::kFailure)
            printf("Error setting the camera name.\n");
	}

    MGlobal::displayInfo( MString( "=====Camera is already create, now to key the trace!=====\n" ) );

//2. bind
	// init translateX animation curve fn
	MString attrName( "translateX");
	const MObject attrtx = fnSet.attribute (attrName, &status);
	if ( MS::kSuccess != status ) printf( "Failure to find attribute translateX\n");	
	activeCameraACFn.acFnSetTx.create ( dp.transform(), attrtx, NULL, &status);
	if ( MS::kSuccess != status ) printf("Failure creating MFnAnimCurve function set (translateX)\n");

	//init translateY animation curve fn
	attrName.set( "translateY");
	const MObject attrty = fnSet.attribute (attrName, &status);
	if ( MS::kSuccess != status ) printf( "Failure to find attribute translateY\n");
	activeCameraACFn.acFnSetTy.create ( dp.transform(), attrty, NULL, &status);
	if ( MS::kSuccess != status ) printf("Failure creating MFnAnimCurve function set (translateX)\n");

	//init translateZ animation curve fn
	attrName.set( "translateZ");
	const MObject attrtz = fnSet.attribute (attrName, &status);
	if ( MS::kSuccess != status ) printf( "Failure to find attribute translateZ\n");
	activeCameraACFn.acFnSetTz.create ( dp.transform(), attrtz, NULL, &status);
	if ( MS::kSuccess != status ) printf("Failure creating MFnAnimCurve function set (translateY)\n");

	//init rotateX animation curve fn
	attrName.set( "rotateX");
	const MObject attrrx = fnSet.attribute (attrName, &status);
	if ( MS::kSuccess != status ) printf( "Failure to find attribute rotateX\n");
	activeCameraACFn.acFnSetRx.create ( dp.transform(), attrrx, NULL, &status);
	if ( MS::kSuccess != status ) printf("Failure creating MFnAnimCurve function set (translateZ)\n");

	//init rotateY animation curve fn
	attrName.set( "rotateY");
	const MObject attrry = fnSet.attribute (attrName, &status);
	if ( MS::kSuccess != status ) printf( "Failure to find attribute rotateY\n");
	activeCameraACFn.acFnSetRy.create ( dp.transform(), attrry, NULL, &status);
	if ( MS::kSuccess != status ) printf("Failure creating MFnAnimCurve function set (rotateY)\n");

	//init rotateZ animation curve fn
	attrName.set( "rotateZ");
	const MObject attrrz = fnSet.attribute (attrName, &status);
	if ( MS::kSuccess != status ) printf( "Failure to find attribute rotateZ\n");
	activeCameraACFn.acFnSetRz.create ( dp.transform(), attrrz, NULL, &status);
	if ( MS::kSuccess != status ) printf("Failure creating MFnAnimCurve function set (rotateZ)\n");

	//init horizontal film aperture fn
	attrName.set( "horizontalFilmAperture" );
	const MObject attrhfa = fnSet.attribute( attrName, &status);
	if ( MS::kSuccess != status ) printf( "Failure to find attribute hfa\n");
	activeCameraACFn.acFnSetHfa.create ( dp.node(), attrhfa, NULL, &status);
	if ( MS::kSuccess != status ) printf("Failure creating MFnAnimCurve function set hfa\n");

	//init vertical film aperture fn
	attrName.set( "verticalFilmAperture" );
	const MObject attrvfa = fnSet.attribute( attrName, &status);
	if ( MS::kSuccess != status ) printf( "Failure to find attribute vfa\n");
	activeCameraACFn.acFnSetVfa.create ( dp.node(), attrvfa, NULL, &status);
	if ( MS::kSuccess != status ) printf("Failure creating MFnAnimCurve function set vfa\n");

	//init focal length fn
	attrName.set( "focalLength" );
	const MObject attrfl = fnSet.attribute( attrName, &status);
	if ( MS::kSuccess != status ) printf( "Failure to find attribute fl\n");
	activeCameraACFn.acFnSetFl.create ( dp.node(), attrfl, NULL, &status);
	if ( MS::kSuccess != status ) printf("Failure creating MFnAnimCurve function set focal length\n");

	//init fstop fn
	attrName.set( "fStop" );
	const MObject attrfs = fnSet.attribute( attrName, &status);
	if ( MS::kSuccess != status ) printf( "Failure to find attribute fstop\n");
	activeCameraACFn.acFnSetFs.create ( dp.node(), attrfs, NULL, &status);
	if ( MS::kSuccess != status ) printf("Failure creating MFnAnimCurve function set fstop\n");

	//init focus distance fn
	attrName.set( "focusDistance" );
	const MObject attrfd = fnSet.attribute( attrName, &status);
	if ( MS::kSuccess != status ) printf( "Failure to find attribute fd\n");
	activeCameraACFn.acFnSetFd.create ( dp.node(), attrfd, NULL, &status);
	if ( MS::kSuccess != status ) printf("Failure creating MFnAnimCurve function set fd\n");

    
    MGlobal::displayInfo( MString( "now we already get the camera's attribute\n" ) );

    
    ifstream cameraTraceFp("/Users/rainbo/Documents/SaveData_xincoder.xml");
    
    if(cameraTraceFp.is_open()){
        MGlobal::displayInfo( MString( "Reading camera trace!\n" ) );
    }
    else{
        MGlobal::displayInfo( MString( "camera trace file can't open!\n" ) );
        return MS::kFailure;
        
    }
        
    string dataLine;
    while(getline(cameraTraceFp, dataLine)){
        
        MGlobal::displayInfo( MString( "Get the new line:\n" ) );

        MString cmdLine(dataLine.c_str());
        MStringArray cmdWords;
        cmdLine.split(';',cmdWords);
        cout<<"this is the received command line:"<<cmdLine<<endl;
    
        MGlobal::displayInfo( cmdLine );
        
        // step 1. get camera attribute
        cameraParam cameraPara;
        double timeFrame  = cmdWords[TIME_FRAME].asDouble();
        cameraPara.translateX = cmdWords[TRANS_X].asFloat();
        cameraPara.translateY = cmdWords[TRANS_Y].asFloat();
        cameraPara.translateZ = cmdWords[TRANS_Z].asFloat();   //chose negative because the right-hand coordinate
        
        //from quaternion to Euler
        double quat_x = cmdWords[QUATERNION_X].asFloat();
        double quat_y = cmdWords[QUATERNION_Y].asFloat();
        double quat_z = cmdWords[QUATERNION_Z].asFloat();
        double quat_w = cmdWords[QUATERNION_W].asFloat();
        
        MQuaternion quater(quat_x, quat_y, quat_z, quat_w);
        MEulerRotation euler = quater.asEulerRotation();
        
        cameraPara.rotateX = euler.x;
        cameraPara.rotateY = euler.y;
        cameraPara.rotateZ = euler.z;
        
        
        //setp 3. key the camera
        
        activeCameraACFn.acFnSetTx.addKeyframe(MTime(timeFrame,MTime::uiUnit()),cameraPara.translateX);
        activeCameraACFn.acFnSetTy.addKeyframe(MTime(timeFrame,MTime::uiUnit()),cameraPara.translateY);
        activeCameraACFn.acFnSetTz.addKeyframe(MTime(timeFrame,MTime::uiUnit()),cameraPara.translateZ);
        
        activeCameraACFn.acFnSetRx.addKeyframe(MTime(timeFrame,MTime::uiUnit()),cameraPara.rotateX);
        activeCameraACFn.acFnSetRy.addKeyframe(MTime(timeFrame,MTime::uiUnit()),cameraPara.rotateY);
        activeCameraACFn.acFnSetRz.addKeyframe(MTime(timeFrame,MTime::uiUnit()),cameraPara.rotateZ);
        
    }//end while
    
    //close file pointer
    cameraTraceFp.close();
    
	return MStatus::kSuccess;
}


MSyntax recordCameraTrace::newSyntax()
{
	MStatus status;
	MSyntax syntax;
	syntax.addFlag( kDoNotClearBackground, kDoNotClearBackgroundLong );
	CHECK_MSTATUS_AND_RETURN(status, syntax);
	return syntax;
}


MStatus recordCameraTrace::parseSyntax(MArgDatabase &argData)
{
	doNotClearBackgroud = argData.isFlagSet(kDoNotClearBackground);
	return MS::kSuccess;
}


bool recordCameraTrace::recFindTransformDAGNodes( MString& nodeName, MString& transformNodeName)
{
	// To handle Maya groups we traverse the hierarchy starting at
	// each objectNames[i] going towards the root collecting transform
	// nodes as we go.
	MStringArray result;
	MString cmdStr = "listRelatives -ap " + nodeName;

	cout << cmdStr.asChar()<<endl;

	MGlobal::executeCommand( cmdStr, result );

	if( result.length() == 0 )
		// nodeName must be at the root of the DAG.  Stop recursing
		return false;

	for( unsigned int j=0; j<result.length(); j++ ) {
		// check if the node result[i] is of type transform
		MStringArray result2;
		MGlobal::executeCommand( "nodeType " + result[j], result2 );

		if( result2.length() == 1 && result2[0] == "transform" ) {
			// check if result[j] is already in result[j]
			transformNodeName = result[j];
			return true;
		}
	}
	return false;
}