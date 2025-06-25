#include "../headers/StaticObject.h"


Object::Object(sf::Vector2f position, sf::Texture& texture, bool isCollision, bool isAnimate) : 
	m_IsAnimate(isAnimate), m_IsCollision(isCollision)
{
	m_position = position;
	m_texture = texture;
}

sf::Vector2f Object::getPosition() {

	return m_position;

}


void Object::setPosition(const sf::Vector2f& pos) {

	m_position = pos;

}

sf::Texture& Object::getTexture() {

	return m_texture;

}

void Object::setTexture(sf::Texture& texture) {
	m_texture = texture;

}


sf::Image& Object::getImage() {
	return m_image;
}


void Object::setImage(sf::Image& image) {
	m_image = image;
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