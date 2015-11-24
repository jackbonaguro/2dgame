#include <stdlib.h>
#include <stdio.h>
#include "engine.h"


int winw = 600;
int winh = 400;
const float SCALE = 30.f;

//////////////////////////////////////////////////////////////////////////////////
sf::RenderWindow win(sf::VideoMode(winw,winh,32), "Test", sf::Style::Default);
sf::Event event;
sf::Clock gameclock;
controller mainctrl;

b2Vec2 gravity(0.0f/SCALE, 150.f/SCALE);
b2World world(gravity);
b2Body* playerBody;
object* o1;

sf::Texture BoxTexture;
sf::Texture GroundTexture;
sf::Texture BallTexture;
sf::Texture EdgeTexture;
//////////////////////////////////////////////////////////////////////////////////

object::object(sf::Sprite isprt){//, b2BodyDef* ibd, b2FixtureDef* ifx){
	sprt = isprt;
	//bd = world.CreateBody(ibd);
	//fx = bd->CreateFixture(ifx);
	//refresh();
}

//object::object(){

//}

void object::refresh(){
		fx = bd->GetFixtureList();

		b2Transform trans = bd->GetTransform();
		trans.q = b2Rot(0);
		fx->GetShape()->ComputeAABB(&aabb,trans,0);
	}

void object::render(){
	//if(bd->GetType() == b2_dynamicBody){
		//sprt.setTexture(BoxTexture);
	//}else{
		//sprt.setTexture(GroundTexture);
	//}
	//sf::Sprite sp(BoxTexture);
		//b2Transform trans = bd->GetTransform();
		//trans.q = b2Rot(0);
		//fx->GetShape()->ComputeAABB(&aabb,trans,0);
	//sprt.setOrigin(sprt.getLocalBounds().width / 2, sprt.getLocalBounds().height / 2);
	//sprt.setPosition(SCALE * bd->GetPosition().x, SCALE * bd->GetPosition().y);
	//sprt.setScale(1,1);//(aabb.lowerBound.x - aabb.upperBound.x) * SCALE / sprt.getTexture()->getSize().x,
				//	(aabb.lowerBound.y - aabb.upperBound.y) * SCALE / sprt.getTexture()->getSize().y);
	//sprt.setRotation((bd->GetAngle()+b2_pi) * 180/b2_pi);
	win.draw(sprt);
}

/*void controller::update(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		up = true;
	}else if(up){
			jump = true;
			up = false;
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

void pupd(float dt){
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world.Step(1/60.f, velocityIterations, positionIterations);

	if(mainctrl.up){
		float impulse = o1->bd->GetMass()*.2f;
		o1->bd->ApplyLinearImpulse( b2Vec2(0,-impulse), o1->bd->GetWorldCenter(), true);
	}
	if(mainctrl.left){
		float impulse = o1->bd->GetMass() * .1;
		o1->bd->ApplyLinearImpulse( b2Vec2(-impulse,0), o1->bd->GetWorldCenter(), true);
	}
	if(mainctrl.right){
		float impulse = o1->bd->GetMass() * .1;
		o1->bd->ApplyLinearImpulse( b2Vec2(impulse,0), o1->bd->GetWorldCenter(), true);
	}
}*/

void oupd(){
	/*for(b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext()){
		for(b2Fixture* f = BodyIterator->GetFixtureList(); f; f = f->GetNext()){
			b2AABB aabb;
			b2Transform trans = BodyIterator->GetTransform();
			trans.q = b2Rot(0);
			f->GetShape()->ComputeAABB(&aabb,trans,0);

			if(f->GetType() == b2Shape::e_circle){
				sf::Sprite Sprite;
				Sprite.setTexture(BallTexture);
				Sprite.setOrigin(BallTexture.getSize().x / 2, BallTexture.getSize().y / 2);
				Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				Sprite.setScale(f->GetShape()->m_radius * 2 * SCALE / BallTexture.getSize().x, f->GetShape()->m_radius * 2 * SCALE / BallTexture.getSize().y);
				Sprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
				win.draw(Sprite);
			}else if(f->GetType() == b2Shape::e_polygon){
				
				sf::Sprite Sprite;
				if(BodyIterator->GetType() == b2_dynamicBody){
					Sprite.setTexture(BoxTexture);
				}else{
					Sprite.setTexture(GroundTexture);
				}
				Sprite.setOrigin(Sprite.getTexture()->getSize().x / 2, Sprite.getTexture()->getSize().y / 2);
				Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				Sprite.setScale((aabb.lowerBound.x - aabb.upperBound.x) * SCALE / Sprite.getTexture()->getSize().x,
								(aabb.lowerBound.y - aabb.upperBound.y) * SCALE / Sprite.getTexture()->getSize().y);
				Sprite.setRotation((BodyIterator->GetAngle()+b2_pi) * 180/b2_pi);
				win.draw(Sprite);
			}else if(f->GetType() == b2Shape::e_edge){

				sf::VertexArray line(sf::TrianglesStrip);
				line.append(sf::Vertex(sf::Vector2f(aabb.lowerBound.x * SCALE, aabb.lowerBound.y * SCALE),sf::Color::Green));
				line.append(sf::Vertex(sf::Vector2f(aabb.upperBound.x * SCALE, aabb.upperBound.y * SCALE),sf::Color::Green));
				line.append(sf::Vertex(sf::Vector2f(aabb.lowerBound.x * SCALE+1, aabb.lowerBound.y * SCALE+1),sf::Color::Green));
				line.append(sf::Vertex(sf::Vector2f(aabb.upperBound.x * SCALE+1, aabb.upperBound.y * SCALE+1),sf::Color::Green));
				
				win.draw(line);
			}
		}
	}*/
	win.display();
	win.clear(sf::Color(50,100,255));
}

int main(){

/*	bool doSleep = true;
	world.SetAllowSleeping(doSleep);

	b2BodyDef bodyDef;
	//bodyDef.fixedRotation = true;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(300.0f/SCALE, 15.f/SCALE);
	playerBody = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((40.f/2)/SCALE, (40.f/2)/SCALE);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.4f;
	playerBody->CreateFixture(&fixtureDef);
*/
	//********
	bodyDef.position.Set(350.f/SCALE, 15.f/SCALE);
	sf::Sprite sprt1(BoxTexture);
	object obj1(sprt1);//, &bodyDef, &fixtureDef);
	o1 = &obj1;
//	o1.sprt = &sprt1;
//	o1.bd = world.CreateBody(&bodyDef);
//	o1.fx = o1.bd->CreateFixture(&fixtureDef);
	//o1.refresh();
	o1->sprt = sf::Sprite(BoxTexture);

	/*b2Body* ground;{

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
*/
	/////////////////////////////////////////////

	BoxTexture.loadFromFile("box.png");
	GroundTexture.loadFromFile("ground.png");
	BallTexture.loadFromFile("ball.png");
	EdgeTexture.loadFromFile("edge.png");

	while (win.isOpen()){
		while (win.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				win.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				win.close();
			}
		//mainctrl.update();
		//pupd(gameclock.getElapsedTime().asSeconds());
		oupd();

		o1->render();
	}
	return 0;
}