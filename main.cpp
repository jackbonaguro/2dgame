#include <stdlib.h>
#include <stdio.h>
#include "manager.h"
#include <string>

const int winw = 600;
const int winh = 400;
const float SCALE = 30.f;

//////////////////////////////////////////////////////////////////////////////////
sf::RenderWindow win(sf::VideoMode(winw,winh,32), "Test", sf::Style::Default);
sf::Event event;
sf::Clock gameclock;
sf::Font font;
std::vector<sf::Text> text;

controller mainctrl;

b2Vec2 gravity(0.f/SCALE, 0.f/SCALE);
b2World world(gravity);

worldManager wrldmgr;
//////////////////////////////////////////////////////////////////////////////////

object::object(animation ianm, b2BodyDef* ibd, b2FixtureDef* ifx){
	animations.push_back(ianm);
	bd = world.CreateBody(ibd);
	fx = bd->CreateFixture(ifx);
	refresh();
}

void object::refresh(){
	fx = bd->GetFixtureList();

	b2Transform trans = bd->GetTransform();
	trans.q = b2Rot(0);
	fx->GetShape()->ComputeAABB(&aabb,trans,0);
}

void controller::update(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		up = true;
	}else{
		up = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		down = true;
	}else{
		down = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		left = true;
	}else{
		left = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		right = true;
	}else{
		right = false;
	}
}

void controlled::update(){
	ctrl.update();
	if(ctrl.up){
		float impulse = bd->GetMass()*.1f;
		float angle = (bd->GetAngle()+(b2_pi/2));
		bd->ApplyLinearImpulse( b2Vec2(-impulse*cos(angle),-impulse*sin(angle)), bd->GetWorldCenter(), true);
	}
	if(ctrl.down){
		bd->SetLinearVelocity(b2Vec2(bd->GetLinearVelocity().x*.99f, bd->GetLinearVelocity().y*.99f));
		//wrldmgr.playerObj.bd->SetAngularVelocity(wrldmgr.playerObj.bd->GetAngularVelocity()*.99f);
	}
	if(ctrl.left){
		float impulse = bd->GetMass() * .05;
		bd->ApplyAngularImpulse(-impulse, true);
	}
	if(ctrl.right){
		float impulse = bd->GetMass() * .05;
		bd->ApplyAngularImpulse(impulse, true);
	}
}

void pupd(float dt){
	wrldmgr.playerObj.update();
	for(std::vector<object>::size_type i = 0; i<wrldmgr.objects.size(); i++){
		wrldmgr.objects[i].update();
	}
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world.Step(1/600.f, velocityIterations, positionIterations);
}

void object::render(){
	for(std::vector<animation>::size_type i = 0; i<animations.size(); i++){
		animations[i].update();
		animations[i].sprt.setPosition(SCALE * bd->GetPosition().x + animations[i].pos.x*cos(animations[i].rotation),
									   SCALE * bd->GetPosition().y - animations[i].pos.y*sin(animations[i].rotation));
		animations[i].sprt.setOrigin(animations[i].sprt.getLocalBounds().width / 2, animations[i].sprt.getLocalBounds().height / 2);
		animations[i].sprt.setScale((aabb.lowerBound.x - aabb.upperBound.x) * SCALE / animations[i].bounds.y,
									(aabb.lowerBound.y - aabb.upperBound.y) * SCALE / animations[i].bounds.y);
		animations[i].sprt.setRotation((bd->GetAngle() + animations[i].rotation) * 180/b2_pi);
		win.draw(animations[i].sprt);
	}
}

void renderEdge(b2Body* eb){
	for(b2Fixture* f = eb->GetFixtureList(); f; f = f->GetNext()){
		b2AABB aabb;
		b2Transform trans = eb->GetTransform();
		trans.q = b2Rot(0);
		f->GetShape()->ComputeAABB(&aabb,trans,0);

		sf::VertexArray line(sf::TrianglesStrip);
		line.append(sf::Vertex(sf::Vector2f(aabb.lowerBound.x * SCALE, aabb.lowerBound.y * SCALE),sf::Color::Green));
		line.append(sf::Vertex(sf::Vector2f(aabb.upperBound.x * SCALE, aabb.upperBound.y * SCALE),sf::Color::Green));
		line.append(sf::Vertex(sf::Vector2f(aabb.lowerBound.x * SCALE+1, aabb.lowerBound.y * SCALE+1),sf::Color::Green));
		line.append(sf::Vertex(sf::Vector2f(aabb.upperBound.x * SCALE+1, aabb.upperBound.y * SCALE+1),sf::Color::Green));
		
		win.draw(line);
	}
}

void oupd(){
	for(std::vector<object*>::size_type i = 0; i<wrldmgr.renderList.size(); i++){
		(wrldmgr.renderList[i])->render();
	}
	for(std::vector<sf::Text>::size_type j = 0; j<text.size(); j++){
		text[j].setPosition(12,10+text[j].getCharacterSize()*1.5*j);
		//text[j].setColor(sf::Color::Red);
		win.draw(text[j]);
	}
	win.display();
	win.clear(sf::Color(50,100,255));
}

int main(){

	wrldmgr.res.loadTexture("art/ChestBlue.png");
	wrldmgr.res.loadTexture("art/Coin.png");
	wrldmgr.res.loadTexture("art/Gem.png");

	/////////////////////////////////////////////////////////////////////

	bool doSleep = true;
	world.SetAllowSleeping(doSleep);

	controlled obj1;{
		b2BodyDef bodyDef;
		//bodyDef.fixedRotation = true;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(300.0f/SCALE, 15.f/SCALE);

		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox((40.f/2)/SCALE, (40.f/2)/SCALE);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 0.4f;

		obj1.animations.push_back(animation(&wrldmgr.res.textures[0], sf::Vector2i(100,100), 2, 300));//wrldmgr.res.textures[0].getSize().x, wrldmgr.res.textures[0].getSize().y)));
		obj1.animations.push_back(animation(&wrldmgr.res.textures[2], sf::Vector2i(50,50)));
		obj1.animations[1].pos = sf::Vector2f(0,400);

		obj1.bd = world.CreateBody(&bodyDef);
		obj1.fx = obj1.bd->CreateFixture(&fixtureDef);
		obj1.refresh();
	}
	wrldmgr.playerObj = obj1;

	object obj2;{
		b2BodyDef bbd;
		bbd.position.Set(400.f/SCALE,30.f/SCALE);
		bbd.type = b2_dynamicBody;

		b2CircleShape ballshape;
		ballshape.m_radius = 50.f/SCALE;
		b2FixtureDef ballFixtureDef;
		ballFixtureDef.shape = &ballshape;
		ballFixtureDef.density = 1.0f;
		ballFixtureDef.friction = 0.3f;
		ballFixtureDef.restitution = 0.4f;

		obj2.animations.push_back(animation(&wrldmgr.res.textures[1], sf::Vector2i(100,100)));//wrldmgr.res.textures[1].getSize().x, wrldmgr.res.textures[1].getSize().y)));
		obj2.bd = world.CreateBody(&bbd);
		obj2.fx = obj2.bd->CreateFixture(&ballFixtureDef);
		obj2.refresh();
	}
	wrldmgr.addObject(obj2);

	b2Body* ground;{

			b2BodyDef bd;
			bd.position.Set(0.0f/SCALE, 0.0f/SCALE);
			ground = world.CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef sd;
			sd.shape = &shape;
			sd.density = 0.0f;
			sd.restitution = 0.4f;

			// Left vertical
			shape.Set(b2Vec2(10.0f/SCALE, 10.0f/SCALE), b2Vec2(10.0f/SCALE, (winh - 10.0f)/SCALE));
			ground->CreateFixture(&sd);

			// Right vertical
			shape.Set(b2Vec2((winw - 10.0f)/SCALE, 10.0f/SCALE), b2Vec2((winw - 10.0f)/SCALE, (winh - 10.0f)/SCALE));
			ground->CreateFixture(&sd);

			// Top horizontal
			shape.Set(b2Vec2(10.0f/SCALE, (winh - 10.0f)/SCALE), b2Vec2((winw - 10.0f)/SCALE, (winh - 10.0f)/SCALE));
			ground->CreateFixture(&sd);

			// Bottom horizontal
			shape.Set(b2Vec2(10.0f/SCALE, 10.0f/SCALE), b2Vec2((winw - 10.0f)/SCALE, 10.0f/SCALE));
			ground->CreateFixture(&sd);
	}
	/////////////////////////////////////////////

	wrldmgr.initialize();

	font.loadFromFile("art/Grundschrift-Normal.otf");
	text.push_back(sf::Text("Hello!",font,20));
	text.push_back(sf::Text("",font,15));
	text.push_back(sf::Text("",font,15));
	text.push_back(sf::Text("",font,15));

	while (win.isOpen()){
		while (win.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				win.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				win.close();
			}
		float dt = gameclock.getElapsedTime().asSeconds();
		gameclock.restart();
		pupd(dt);

		text[1].setString("UPS: ");// + std::to_string(int(1/dt)));
		text[2].setString("Player Speed: ");// + std::to_string(wrldmgr.playerObj.bd->GetLinearVelocity().Length()));
		text[3].setString("Player Angular Speed: ");// + std::to_string(wrldmgr.playerObj.bd->GetAngularVelocity()));
		renderEdge(ground);
		oupd();
	}
	return 0;
}