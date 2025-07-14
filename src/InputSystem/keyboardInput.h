#pragma once 
#include "defines.h"
#include <functional>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp> 



namespace INPUT {
	
	
	void isKeyPressedW(std::function<void()>& action);
	
	void isKeyPressedA(std::function<void()>& action);
	
	void isKeyPressedS(std::function<void()>& action);
	
	void isKeyPressedD(std::function<void()>& action);



}