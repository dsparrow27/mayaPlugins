#ifndef VERTSNAPCOMMAND_H
#define VERTSNAPCOMMAND_H


#include <maya/MFnMesh.h>
#include <maya/MGlobal.h>
#include <maya/MIntArray.h>
#include <maya/MItDependencyGraph.h>
#include <maya/MMeshIntersector.h>
#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MPointArray.h>
#include <maya/MPxCommand.h>
#include <maya/MSelectionList.h>
#include <maya/MSyntax.h>
#include <maya/MArgDatabase.h>
#include <maya/MDagPath.h>

class VertSnapCommand : MPxCommand
{
public:	VertSnapCommand();
		//command excution order
		//doit : read/ store all flag arguments and return redoIt()
		//redoIt : main functionality , gets called in doit
		//undoIt : Restores the initial state with maya undo
		virtual MStatus	doIt(const MArgList& argList);
		virtual	MStatus	redoIt();
		virtual MStatus	undoIt();
		virtual	bool isUndoable() const;
		static void* creator();
		static MSyntax	newSyntax();
		

private:
	//gets the shape node from a transform
	MStatus	getShapeNode(MDagPath& path);
	MStatus calculateVertexMapping();
	//stores the meshes from the scene selection
	//MObject 
	MDagPath mPathBaseMesh;
	MDagPath mPathSnapMesh;

};

#endif