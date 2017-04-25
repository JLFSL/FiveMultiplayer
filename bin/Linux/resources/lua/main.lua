vehicles = {
	veh1 = Vehicle(),
	veh2 = Vehicle(),
	veh3 = Vehicle(),
	veh4 = Vehicle()
}


function OnInit() 
	server.PrintMessage("Starting Gamemode...")
	
	vehicles.veh1:Create("elegy", {x = -3.0, y = 6.0, z = 73.0}, 10.0)
	vehicles.veh2:Create("comet3", {x = -6.0, y = 8.0, z = 71.0}, 10.0)
	vehicles.veh3:Create("blazer5", {x = -9.0, y = 10.0, z = 73.0}, {x = 0.0, y = 0.0, z = 10.0})
	vehicles.veh4:Create("voltic2", {x = -12.0, y = 12.0, z = 73.0}, 10.0)
	
	distance = vehA:GetViewDistance()
	print("Default View Distance: " .. tostring(distance))
	vehA:SetViewDistance(1573)
	distance = vehA:GetViewDistance()
	print("New View Distance: " .. tostring(distance))
	
	cp = Checkpoint()
	cp:Create({x = -12.0, y = 12.0, z = 71.0}, {x = -12.0, y = 12.0, z = 71.0}, 1, 10.0, {r = 255, g = 0, b = 0, a = 150}, 0)
	height = cp:GetNearHeight()
	print("Near Height: " .. tostring(height))
	cp:SetNearHeight(120)
	height = cp:GetNearHeight()
	print("Near Height: " .. tostring(height))
	
	visual.ShowMessageAboveMap("this is a message", "CHAR_CREATOR_PORTRAITS", 1, "Server", "Message")
end

function OnPlayerConnecting(guid)
	return 1
end

function OnPlayerConnected(entity)
	user = Player()
	user:SetUID(entity)
	
	return 1
end

function OnEntityEnterCheckpoint(checkpointent, entity)

end

function OnEntityExitCheckpoint(checkpointent, entity)

end

function OnPlayerCommand(entity, message)

end

function OnPlayerMessage(entity, message)

end


