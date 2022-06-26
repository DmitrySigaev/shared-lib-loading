#pragma once

/*
** This is the base class for libraries
*/
class ishared
{
	
public:
	virtual ~ishared() = default;

	/*
	** Pure method which will be overrided.
	*/
	virtual void ShowStats() = 0;

};