#include <vector>
#include <string.h>
//#include <mxml.h>
#include "engine.h"

class resourceManager{
	public:
	std::vector<sf::Texture> textures;
	void loadTexture(std::string s){
		sf::Texture tex;
		tex.loadFromFile(s);
		textures.push_back(tex);
	}
};

class worldManager{
	public:
	resourceManager res;
	controlled playerObj;
	std::vector<object> objects;
	std::vector<object*> renderList;

	void addObject(object o){
		objects.push_back(o);
	}
	void initialize(){
		renderList.push_back(&playerObj);
		for(std::vector<object>::size_type i = 0; i<objects.size(); i++){
			renderList.push_back(&(objects[i]));
		}
	}
};
	