
static MMatrix gToMMatrix(MVector x, MVector y, MVector z)
{
	// MMatrix builder from 3 vectors
	MMatrix o = MMatrix::identity;
	o(0, 0) = x[0]; o(0, 1) = x[1]; o(0, 2) = x[2];
	o(1, 0) = y[0]; o(1, 1) = y[1]; o(1, 2) = y[2];
	o(2, 0) = z[0]; o(2, 1) = z[1]; o(2, 2) = z[2];
	return o;
}

MStatus basicNode::compute(const MPlug& plug, MDataBlock& dataBlock){
	if (plug == outputPosition || plug == outputRotation || plug == outputTransform){
		int inVal = dataBlock.inputValue(inputVal).asInt();
		MObject crvV = dataBlock.inputValue(inputCurve).asNurbsCurve();

		MArrayDataHandle outputTransforms = dataBlock.outputArrayValue(outputTransform);
		MFnNurbsCurve crvFn(crvV);
		// get lenght of the current curve with a precision of 0.01
		double curveLen = crvFn.length(0.01);
		// make the transform attribute a builder to hold multiple instances with data
		MArrayDataBuilder builder = outputTransforms.builder();
		// calculate if we have too many output values in the node
		int remainderPos = builder.elementCount() - inVal;

		if (remainderPos > 0){
			// cleanup builder to contain the given amount of ouputs
			for (int index = 0; index < remainderPos; index++){
				int currentCount = builder.elementCount();
				builder.removeElement(currentCount - 1);
			}
		}
		for (int i = 0; i < inVal; i++){
			// build multiple outputs from the given inputvalue
			MDataHandle outHandle = builder.addElement(i);
			double outVal = crvFn.findParamFromLength((curveLen / ((float)inVal - 1.0f))*i);

			// calculate position and rotation
			MPoint ParamPos;
			crvFn.getPointAtParam(outVal, ParamPos, MSpace::kWorld);
			MVector ParamNormal = crvFn.normal(outVal, MSpace::kWorld).normal();
			MVector ParamTangent = crvFn.tangent(outVal, MSpace::kWorld).normal();
			MVector ParamCross = (ParamNormal ^ ParamTangent).normal();

			// build rotational matrix from normal up and cross
			MMatrix rotMatrix = gToMMatrix(ParamNormal, ParamTangent, ParamCross);
			MEulerRotation rotation;
			rotation = rotMatrix;
			// convert radians to degrees
			rotation *= 360 / (2 * PI);

			// set the data for each child attribute
			outHandle.child(outputPosition).set(MVector(ParamPos));
			outHandle.child(outputRotation).set(rotation.asVector());
		}
		// set output data of entire node to clean
		outputTransforms.setAllClean();
	}