function OnGameModeInit() 
	PrintMessage("Starting Gamemode...")
	
	vehAPos = Vector3(-3.0, 6.0, 71.0)
	vehA = Vehicle()
	--vehA:Create("elegy", Vector3(-3.0, 6.0, 71.0), 360.0) --Sadly Vector3's aren't passing correctly at the moment
	vehA:Create("elegy", -3.0, 6.0, 71.0, 360.0)
	
	vehB = Vehicle()
	vehB:Create("comet3", {x = -6.0, y = 8.0, z = 71.0}, 360.0)
	
	vehC = Vehicle()
	vehC:Create("blazer5", -9.0, 10.0, 71.0, 360.0)
	
	Vehicle():Create("voltic2", {x = -12.0, y = 12.0, z = 71.0}, 360.0)
	
	vehA:SetPosition(Vector3(-92.0, 100.0, 71.0))
	vehB:SetPosition(-92.0, 100.0, 71.0)
	vehC:SetPosition({x = -92.0, y = 100.0, z = 71.0})
	
	vehE = Vehicle()
	vehE:Create("blazer5", -19.0, 16.0, 71.0, 360.0)
	vehE:Destroy(); --How you destroy a vehicle
	
	posB = vehB:GetPosition() -- For now returns a table
	print(tostring(posB.x))
	
	pos = Vector3(1.4, 12.5, 24.8)
	pos.x = 25.4
	print(tostring(pos.x))
end
