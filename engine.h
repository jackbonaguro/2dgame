#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>

class controller{
	public:
	bool up;
	bool down;
	bool jump;
	bool left;
	bool right;
	void update();
};

class animation{
	public:
	sf::Vector2f pos;
	float rotation;
    sf::Vector2i bounds;
    float counter;
    float duration;
    int numframes;
    sf::Texture* tex;
    sf::Sprite sprt;

    animation(sf::Texture* itex, sf::Vector2i ibounds, int inumframes, float idur=1){
    	pos = sf::Vector2f(0,0);
    	rotation = 0;
    	tex = itex;
    	sprt.setTexture(*tex);
    	bounds = ibounds;

    	counter = 0;
    	numframes = inumframes;
    	duration = idur;
    }
    animation(sf::Texture* itex, sf::Vector2i ibounds){
    	pos = sf::Vector2f(0,0);
    	rotation = 0;
    	tex = itex;
    	sprt.setTexture(*tex);
    	bounds = ibounds;

    	counter = 0;
    	numframes = 1;
    	duration = 1;
    }
    void update(){
    	counter += 1/duration;
    	if(counter >= (float)numframes){
    		counter -= (float)numframes;
    	}
    	sprt.setTextureRect(sf::IntRect(sf::Vector2i(((int)counter)*bounds.x,0), bounds));
    }
};

class object{
	public:
	std::vector<animation> animations;
	b2Body* bd;
	b2Fixture* fx;
	b2AABB aabb;
	void refresh();
	virtual void render();
	virtual void update();
	object(animation, b2BodyDef*, b2FixtureDef*);
	object();
};

object::object(){
}

void object::update(){	
}

class controlled: public object{
	public:
	controller ctrl;
	void update();
};