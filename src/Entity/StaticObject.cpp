#include "StaticObject.h"


Object::Object(sf::Vector2f position, textureID texture_id, bool isCollision, bool isAnimate) : 
	m_IsAnimate(isAnimate), m_IsCollision(isCollision)
{
	m_position = position;
	m_textureID = texture_id;
}

sf::Vector2f Object::getPosition() {

	return m_position;

}


void Object::setPosition(const sf::Vector2f& pos) {

	m_position = pos;

}

textureID Object::getTextureID(){
	return m_textureID;
}


void Object::setTexture(textureID texture_id) {
	m_textureID = texture_id;
}


bool Object::isAnimate() {
	return m_IsAnimate;
}

void Object::setAnimate(bool isAnimate) {
	m_IsAnimate = isAnimate;
}

bool Object::getCollisionIndicate() {
	return m_IsCollision;
}

void Object::setCollision(bool collision) {
	m_IsCollision = collision;
}