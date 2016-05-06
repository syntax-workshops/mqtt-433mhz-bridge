{
	"targets": [
	{
		"target_name": "node-kaku",
		"sources": [ "node-kaku.cc" ],
		"libraries": [
			"-lwiringPi", "-L/usr/local/lib"
		],
		"include_dirs": [
			"/usr/local/include"
		]
	}
	]
}
