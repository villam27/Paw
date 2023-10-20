--	Lua config file for Minou

application = {
	fps = 30,
	scale = 3,
}

sheets = {
	{
		file = "Minouanim.png",
		sprites = {
			--	first line
			{0, 0, 24, 24},
			{24, 0, 24, 24},
			{48, 0, 24, 24},
			{72, 0, 24, 24},
			--	second line
			{0, 24, 24, 24},
			{24, 24, 24, 24},
			{48, 24, 24, 24},
			{72, 24, 24, 24},
			--	third line
			{0, 48, 24, 24},
			{24, 48, 24, 24},
			{48, 48, 24, 24},
			{72, 48, 24, 24},
			--	fourth line
			{0, 72, 24, 24},
			{24, 72, 24, 24},
			{48, 72, 24, 24},
			{72, 72, 24, 24},

			{0, 0, 48, 48},
			{48, 0, 48, 48},
			{0, 48, 48, 48},
			{48, 48, 48, 48},
		},
	},
}

animations = {
	{
		name = "Idle",
		sheet = "Minouanim.png",
		frames = {0},
		duration = 100, --	in ms
	},
	{
		name = "Sleep",
		sheet = "Minouanim.png",
		frames = {3, 7},
		duration = 1000,
	},
	{
		name = "Lick",
		sheet = "Minouanim.png",
		frames = {11, 15},
		duration = 700,
	},
	{
		name = "Test",
		sheet = "Minouanim.png",
		frames = {16, 17, 18, 1},
		duration = 500,
	},
}