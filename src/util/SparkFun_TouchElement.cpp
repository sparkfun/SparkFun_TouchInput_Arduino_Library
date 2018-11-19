/*

SparkFun_TouchElement.cpp
Header: SparkFun_TouchElement.h

Purpose:

Author: Owen Lyke

*/

#include "SparkFun_TouchElement.h"


sfti_element::sfti_element( void )
{
	pprev = NULL;
	pnext = NULL;
}

bool sfti_element::isFreeElement( void )
{
	if((pnext == NULL) && (pprev == NULL))	// If we mess with an element that has a valid pnext value then it could break whatever list it is currently in
	{
		return true;
		// if(pelem->pprev != NULL)	// It is, however, POSSIBLE to take the very last element of a list and switch it over. However let's not do that cause it's weird
		// {
		// 	pelem->pprev->pnext = NULL;
		// }
	}
	return false;
}






// Button
sfti_element_button::sfti_element_button(sf2drt_polygon& basepoly, void (*func_pressed)( void ), void (*func_released)( void )) : sfti_element()
{
	pressed = func_pressed;
	released = func_released;

	isPressed = false;
	poly = basepoly;
}

sfti_element_button::setPressedCallback(void (*func)( void ))
{
	pressed = func;
}

sfti_element_button::setReleasedCallback(void (*func)( void ))
{
	released = func;
}

void sfti_element_button::call(void (*func)( void ))
{
	if(func != NULL)	// Safely call the function
	{
		(*func)();
	}
}

void sfti_element_button::processRecord(sfti_record rec)
{
	bool pressedNow = false;
	for(sfti_mxtouch_t indi = 0; indi < rec.numTouches; indi++)
	{
		sf2drt_coordinate_t ctemp;
		ctemp.x = (sf2drt_extent_t)((rec.pcoords + indi)->x);
		ctemp.y = (sf2drt_extent_t)((rec.pcoords + indi)->y);

		if(poly.contains(ctemp))
		{
			pressedNow = true;
		}
	}

	if((!isPressed) && (pressedNow))
	{
		call(pressed);
	}

	if((isPressed) && (!pressedNow))
	{
		call(released);
	}

	isPressed = pressedNow;
}



// Handle
sfti_element_handle::sfti_element_handle( void ) : sfti_element()
{

}

void sfti_element_handle::processRecord(sfti_record rec)
{

}



// Slider
sfti_element_slider::sfti_element_slider( void ) : sfti_element()
{

}

void sfti_element_slider::processRecord(sfti_record rec)
{
	// Serial.println("Itsa me, a slider");
	// Serial.println("Record information printed through the slider:");
	// rec.printInfo();
}








// Debugger (prints info for touch records)
sfti_element_debugger::sfti_element_debugger(HardwareSerial* port) : sfti_element()
// sfti_element_debugger::sfti_element_debugger(HardwareSerial& port) : sfti_element()
{
	_debugPort = port;
	// _debugPort = &port;
}

void sfti_element_debugger::processRecord(sfti_record rec)
{
	if(_debugPort != NULL)
	{
		Serial.print("Debugger output: ");
		// _debugPort->print("valid = "); _debugPort->print(valid); // _debugPort->println();
		// _debugPort->print("dynamic = "); _debugPort->print(dynamic); // _debugPort->println();
		// _debugPort->print("maxTouches = "); _debugPort->print(maxTouches); // _debugPort->println();
		// _debugPort->print("numTouches = "); _debugPort->print(numTouches); // _debugPort->println();
		// _debugPort->print("value of pcoords = 0x"); _debugPort->print((uint32_t)pcoords, HEX); // _debugPort->println();
		_debugPort->print("timestamp = "); _debugPort->print(rec.timestamp); _debugPort->print(" "); // _debugPort->println();
		if(rec.numTouches)
		{
			_debugPort->print("Coordinate info: ");
			_debugPort->print("Touch");
			for(sfti_mxtouch_t indi = 0; indi < rec.numTouches; indi++)
			{
				_debugPort->print(" #");
				_debugPort->print(indi);
				_debugPort->print(", {");
				_debugPort->print((rec.pcoords+indi)->x);
				_debugPort->print(", ");
				_debugPort->print((rec.pcoords+indi)->y);
				_debugPort->print("}, ");
			}
		}
		_debugPort->println();
	}
}
	