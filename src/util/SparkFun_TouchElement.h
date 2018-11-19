/*

SparkFun_TouchElement.h

Purpose:

Author: Owen Lyke

*/



#ifndef SF_TOUCH_ELEMENT_H
#define SF_TOUCH_ELEMENT_H


#include "SparkFun_TouchTypes.h"
#include "SparkFun_TouchRecord.h"
#include "SparkFun_2DRayTracing.h"

class sfti_element{
private:
protected:
public:

// Private (one day)


// Protected (one day)
	sfti_element* pprev;	// Pointer to the previous element in a linked list
	sfti_element* pnext;	// Pointer to the next element in a linked list

	bool isFreeElement( void );

// Public
	sfti_element(); 									// Constructor

	virtual void processRecord(sfti_record rec) = 0;	// This is the function that will be called when there is a new touch record. It is up to the derived classes how to handle this

};


////////////////////////////////////////////////
// 											  //
////////////////////////////////////////////////

class sfti_element_button : public sfti_element{
private:
protected:
public:
// Private (one day)
	
// Protected (one day)
	void call(void (*func)( void ));
	void (*pressed)( void );
	void (*released)( void );
// Public
	sf2drt_polygon poly;
	bool isPressed;

	void processRecord(sfti_record rec);	// This is the function that will be called when there is a new touch record. It is up to the derived classes how to handle this
	
	sfti_element_button(sf2drt_polygon& basepoly, void (*func_pressed)( void ) = NULL, void (*func_released)( void ) = NULL);
	setPressedCallback(void (*func)( void ));
	setReleasedCallback(void (*func)( void ));
};

class sfti_element_handle : public sfti_element{
private:
protected:
public:
// Private (one day)
// Protected (one day)
// Public
	sf2drt_polygon poly;	// The area of the handle
	bool isHeld;

	void processRecord(sfti_record rec);	// This is the function that will be called when there is a new touch record. It is up to the derived classes how to handle this
	sfti_element_handle();
};

class sfti_element_slider : public sfti_element{
private:
protected:
public:
// Private (one day)
// Protected (one day)
// Public
	void processRecord(sfti_record rec);	// This is the function that will be called when there is a new touch record. It is up to the derived classes how to handle this
	sfti_element_slider();
};


class sfti_element_debugger : public sfti_element{
private:
protected:
public:
// Private (one day)
// Protected (one day)
	HardwareSerial* _debugPort;
// Public
	void processRecord(sfti_record rec);	// This is the function that will be called when there is a new touch record. It is up to the derived classes how to handle this

	// sfti_element_debugger(HardwareSerial& port = Serial);
	sfti_element_debugger(HardwareSerial* port = NULL);

};




#endif /* SF_TOUCH_ELEMENT_H */