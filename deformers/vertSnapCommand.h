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

class VertSnapCommand : MPxCommand
{
public:	VertSnapCommand();
		virtual MStatus	doIt(const MArgList& argList);
		virtual	MStatus	redoIt();
		virtual MStatus	undoIt();
		virtual	bool isUndoable() const;
		static void* creator();
		static MSyntax	newSyntax();
};

#endif