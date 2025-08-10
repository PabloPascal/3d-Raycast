#include "StaticObject.h"


StaticObject::StaticObject(sf::Vector2f position, textureID texture_id, bool isCollision, bool isAnimate) : 
	m_IsAnimate(isAnimate), m_IsCollision(isCollision)
{
	m_position = position;
	m_textureID = texture_id;
}

sf::Vector2f StaticObject::getPosition() const {

	return m_position;

}


void StaticObject::setPosition(const sf::Vector2f& pos) {

	m_position = pos;

}

textureID StaticObject::getTextureID() const{
	return m_textureID;
}


void StaticObject::setTexture(textureID texture_id) {
	m_textureID = texture_id;
}


bool StaticObject::isAnimate() {
	return m_IsAnimate;
}

void StaticObject::setAnimate(bool isAnimate) {
	m_IsAnimate = isAnimate;
}

bool StaticObject::getCollisionIndicate() {
	return m_IsCollision;
}

void StaticObject::setCollision(bool collision) {
	m_IsCollision = collision;
}