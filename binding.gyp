{
	"targets": [{
		"target_name": "index",
		"sources": ["index.cpp"],
		"include_dirs" : ["<!(node -e \"require('nan')\")"]
	}]
}
