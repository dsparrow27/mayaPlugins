#include "vertSnapCommand.h"
#include "vertSnapDeformer.h"

VertSnapCommand::VertSnapCommand()
{

}
void* VertSnapCommand::creator()
{
	return new VertSnapCommand();
}



bool VertSnapCommand::isUndoable() const
{
	//allow the command to support undo
	return true;
}

MSyntax VertSnapCommand::newSyntax()
{
	//designs the mel command flags for creation
	MSyntax syntax;

	//add naming to flag args
	syntax.addFlag("-n", "-name", MSyntax::kString);
	//get the current scene selection 
	syntax.setObjectType(MSyntax::kSelectionList, 2, 2);
	syntax.useSelectionAsDefault(true);
	syntax.enableEdit(false);
	syntax.enableQuery(false);

	return syntax;
}

MStatus	VertSnapCommand::doIt(const MArgList& argList)
{
	//read all flag arguments 
	MStatus status;

	MArgDatabase argData(syntax(), argList, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	//get the objects from selectionList
	MSelectionList selection;
	status = argData.getObjects(selection);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	//store the dagPath of selection in class variables
	status = selection.getDagPath(0, mPathSnapMesh);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	status = selection.getDagPath(0, mPathBaseMesh);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	//retrieve the first valid shapeNode from the dagPaths
	status = getShapeNode(mPathBaseMesh);//if passed this is now the shapeNode
	CHECK_MSTATUS_AND_RETURN_IT(status);
	status = getShapeNode(mPathSnapMesh);//if passed this is now the shapeNode
	CHECK_MSTATUS_AND_RETURN_IT(status);

	status = calculateVertexMapping();
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return redoIt();
}

MStatus VertSnapCommand::redoIt()
{
	//main functionality for a command
	MStatus status;
	return	MS::kSuccess;
}

MStatus	VertSnapCommand::undoIt()
{
	//Restores the initial state
	MStatus status;
	return	MS::kSuccess;
}


MStatus VertSnapCommand::getShapeNode(MDagPath& path)
{
	//find's the first shapeNode that is a kMesh and not the intermediate shapeNode

	MStatus status;


	if (path.apiType() == MFn::kMesh)
	{
		return MS::kSuccess;
	}

	unsigned int numOfShapes;
	//get all the shapes 
	status = path.numberOfShapesDirectlyBelow(numOfShapes);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	//get the correct shape node 
	for (unsigned int i = 0; i < numOfShapes; ++i)
	{
		status = path.extendToShapeDirectlyBelow(i);
		CHECK_MSTATUS_AND_RETURN_IT(status);
		//check if not mesh
		if (!path.hasFn(MFn::kMesh))
		{
			//remove the mesh from path
			path.pop();
			continue;
		}
		MFnDagNode fnNode(path, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);
		//return success if not intermediateObject()
		if (!fnNode.isIntermediateObject())
		{
			return MS::kSuccess;
		}
		//intermediateObject so remove and continue
		path.pop();
	}
	//return  fail because we didnt find a shapeNode
	return MS::kFailure;

}


MStatus VertSnapCommand::calculateVertexMapping()
{
	MStatus status;

	return MS::kSuccess;
}