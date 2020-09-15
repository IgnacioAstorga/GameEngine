fn Clamp val lowerLimit upperLimit =
(
	if classOf val == Point3 then
	(
		local d = length val
		local clamped = Clamp d
		val = clamped * val / d
	)
	else if classOf val == Integer or classOf val == Float then
	(
		if val < lowerLimit then
			val = lowerLimit
		else if val > upperLimit then
			val = upperLimit
	)
	val
)

fn FindQuaternionTwist q axis normal =
(		
	local transformed = normal * q
	local flattened = transformed - axis * dot transformed axis
	flattened = normalize flattened
	local ang = acos (dot normal flattened)
	local sign = dot (cross flattened normal) axis
	if sign < 0 then ang *= -1
	ang
)

fn GetControllerOwner controller =
(
	local dependencies = refs.dependents controller
	for obj in dependencies where isValidNode obj do
		return obj
	undefined
)

plugin PositionController A3PositionControl
name:"A3 Position Control"
classID:#(0x47db1abc, 0x4e9b5000)
(
	parameters subanims 
	(
		ikState type:#boolean default:false animatable:true
		valueController type:#maxobject subAnim:true
	)
	
	parameters references
	(		
		a1RotationController type:#maxobject subAnim:true
		a2RotationController type:#maxobject subAnim:true
	)
	
	local a1 = undefined
	local a2 = undefined
	local a3 = undefined
	
	fn SetUpLocals =
	(
		if a3 == undefined then
		(
			a3 = GetControllerOwner this
			a2 = a3.parent
			a1 = a2.parent
		)
	)
	
	fn GetIKPosition =
	(
		SetUpLocals()
		local master = a1.parent
		
		valueController.value * master.transform
	)
	
	on getValue do
	(
		SetUpLocals()
		
		[0, 0, a2.height]
	)
	
	on setValue val relVal commit do
	(
		SetUpLocals()
		local master = a1.parent
		
		local controllerValue = val * a2.transform * inverse master.transform
		SetControllerValue valueController controllerValue commit #absolute
		
		local a = [0,0,0]
		local b = [0, 0, a1.height]
		local c = b + [0, 0, a2.height] * a2.rotation.controller.GetRotation()
		local t = b + val * a2.rotation.controller.GetRotation()
		
		local eps = 0.0001
		local lab = length (b - a)
		local lcb = length (b - c)
		local lat = Clamp (length (t - a)) eps (lab + lcb - eps)
		
		local ac_ab_0 = acos ( Clamp (dot (normalize (c - a)) (normalize (b - a))) -1 1)
		local ba_bc_0 = acos ( Clamp (dot (normalize (a - b)) (normalize (c - b))) -1 1)
		local ac_at_0 = acos ( Clamp (dot (normalize (c - a)) (normalize (t - a))) -1 1)
		
		local ac_ab_1 = acos (Clamp ((lcb*lcb - lab*lab - lat*lat) / (-2*lab*lat)) -1 1)
		local ba_bc_1 = acos (Clamp ((lat*lat - lab*lab - lcb*lcb) / (-2*lab*lcb)) -1 1)
		
		local axis0 = normalize (cross (c - a) (b - a))
		local axis1 = normalize (cross (c - a) (t - a))
		
		local r0 = (angleAxis (ac_ab_1 - ac_ab_0) axis0) as quat
		local r1 = (angleAxis (ba_bc_1 - ba_bc_0) axis0) as quat
		local r2 = (angleAxis ac_at_0 axis1) as quat
		
		a1RotationController.value = inverse (inverse (a1.rotation.controller.GetRotation()) * (r2 * r0))
		a2RotationController.value = inverse (inverse (a2.rotation.controller.GetRotation()) * r1)
	)
	
	on create do
	(
		valueController = NewDefaultPositionController()
		
		isLeaf = false
	)
)

plugin RotationController A2RotationControl
name:"A2 Rotation Control"
classId:#(0x47db1abc, 0x4e9b5001)
(
	parameters subanims
	(
		valueController type:#maxobject subAnim:true
	)
	
	parameters references
	(
		ikState type:#boolean default:false animatable:true
		a3PositionController type:#maxobject subAnim:true
		a1RotationController type:#maxobject subAnim:true
	)
	
	local a1 = undefined
	local a2 = undefined
	local a3 = undefined
	
	fn SetUpLocals =
	(
		if a2 == undefined then
		(
			a2 = GetControllerOwner this
			a1 = a2.parent
			
			a3 = for child in a2.children where classOf child.position.controller == A3PositionControl do exit with child
		)
	)
	
	fn GetRotation =
	(
		if ikState == false then
			valueController.value
		else
		(
			SetUpLocals()
			
			local ta = length (a3.position.controller.GetIKPosition() - a1.position)
			
			local ang_y = acos (Clamp ((a1.height * a1.height + a2.height * a2.height - ta * ta) / (2 * a1.height * a2.height)) -1 1)
			
			local rot = angleAxis -(180 - ang_y) [0,1,0]
			rot as quat
		)
	)
	
	on getValue do
	(
		GetRotation()
	)
	
	on setValue val relVal commit do
	(
		SetUpLocals()
		
		local ang_y = FindQuaternionTwist val [0,1,0] [0,0,1]
		if ang_y > 90 then ang_y = -178
		ang_y = Clamp ang_y -178 0
		
		SetControllerValue valueController (angleAxis ang_y [0,1,0]) commit #absolute
		
		local a3Position = [0,0,a1.height] + [0,0,a2.height] * valueController.value
		local targetPosition = a3Position * a1.rotation.controller.GetRotation()
		SetControllerValue a3PositionController targetPosition commit #absolute
		
		local localRot = relVal * inverse ((GetRotation()))
		local ang_z = FindQuaternionTwist localRot [0,0,1] [0,1,0]
		local ikDir = normalize (a3Position * a1.rotation.controller.GetRotation())
		local rot = (angleAxis ang_z ikDir) as quat
		a1RotationController.value = a1.rotation.controller.GetRotation() * rot
	)
	
	on create do
	(
		valueController = NewDefaultRotationController()
		
		isLeaf = false
	)
)

plugin RotationController A1RotationControl
name:"A1 Rotation Control"
classId:#(0x47db1abc, 0x4e9b5002)
(
	parameters subanims
	(
		valueController type:#maxobject subAnim:true
	)
	
	parameters references
	(
		ikState type:#boolean default:false animatable:true
		a3PositionController type:#maxobject subAnim:true
		a2RotationController type:#maxobject subAnim:true
	)
	
	local a1 = undefined
	local a2 = undefined
	local a3 = undefined
	
	fn SetUpLocals =
	(
		if a1 == undefined then
		(
			a1 = GetControllerOwner this
			
			a2 = for child in a1.children where classOf child.rotation.controller == A2RotationControl do exit with child
			a3 = for child in a2.children where classOf child.position.controller == A3PositionControl do exit with child
		)
	)
	
	fn GetRotation =
	(
		if ikState == false then
			valueController.value
		else
		(
			SetUpLocals()
			local master = a1.parent
			
			local dir = (a3.position.controller.GetIKPosition() - a1.position) * inverse master.transform
			local ta = length dir
			dir /= ta
			
			local up = [0,1,0] * valueController.value
			local right = cross up dir
			up = cross dir right
			local rot = (matrix3 right up dir [0,0,0]) as quat
			
			local ang_y = acos (Clamp ((ta * ta + a1.height * a1.height - a2.height * a2.height) / (2 * ta * a1.height)) -1 1)
			rot = ((angleAxis ang_y [0,1,0]) as quat) * rot
			
			rot
		)
	)
	
	on getValue do
	(
		GetRotation()
	)
	
	on setValue val relVal commit do
	(		
		SetControllerValue valueController val commit #absolute
		
		local a3Position = ([0,0,a1.height] + [0,0,a2.height] * a2.rotation.controller.GetRotation())
		local targetPosition = a3Position * valueController.value
		SetControllerValue a3PositionController targetPosition commit #absolute
	)
	
	on create do
	(
		valueController = NewDefaultRotationController()
		
		isLeaf = false
	)
)