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
	return true;
}

MSyntax VertSnapCommand::newSyntax()
{
	MSyntax syntax;

	return syntax;
}

MStatus	VertSnapCommand::doIt(const MArgList& argList)
{
	MStatus status;
	return	MS::kSuccess;
}

MStatus	VertSnapCommand::undoIt()
{
	MStatus status;
	return	MS::kSuccess;
}

MStatus VertSnapCommand::redoIt()
{
	MStatus status;
	return	MS::kSuccess;
}
