-- Template script for Minou

-- Custom lua function
function FromLua()
	MyCppFunction("Im a from lua 1")
end

function Updating()
	print("Updating")
end

-- Module
local Module = {
	{
		name = "My Module",
		author = "Villam",
		version = "1.0.0",
	}
}

-- Module functions
-- For now only one function is supported
-- Event supported: ON_UPDATE
function Module.OnProgramStart()
	HookEvent("ON_UPDATE", "FromLua")
	HookEvent("ON_UPDATE", "Updating")
end

return Module