#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Engine
{
	class Animation
	{
	public:
		Animation( std::string animName, double interval, int firstFrame, int lastFrame )
		:
		name( animName ),
		timeInterval( interval ),
		firstFrame( firstFrame ),
		lastFrame( lastFrame ),
		currFrame( firstFrame ),
		lastTime( -1 )
		{}

		std::string getName()
		{
			return name;
		}

        double getInterval()
        {
            return timeInterval;
        }

        int getFrame()
        {
	    double currTime = glfwGetTime(); // TODO: engine get time...

	    if( lastTime == -1)
		    lastTime = currTime;

		// TODO: CHECK IF MULTIPLE MOVES NEEDED? (currTime - lastTime > 2*timeInterval)
	    // if it's time to switch frames
	    if( currTime - lastTime > timeInterval )
	    {
		if( currFrame == lastFrame )
		    currFrame = firstFrame;
		else
		    currFrame++;
	    }

	    lastTime = currTime;

	    return currFrame;
        }

        void setInactive()
        {
        	currFrame = lastFrame;
        }

	private:
	    // name of the animation
	    std::string name;

	    // how long to wait before swapping frames, time of last swap
	    double timeInterval, lastTime;

	    // what frame we're at, frame of start, frame to end with.
		int currFrame, firstFrame, lastFrame;
	};
}

#endif
