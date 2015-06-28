//
//  ProtoPlasm.h
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/27/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//



#ifndef __PROTO_PLASM_H__
#define __PROTO_PLASM_H__

// setup GL on Win/OSX/Linux
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
#define GLEW_STATIC // link to glew32s instead of including dll
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#else
#define GLFW_INCLUDE_GLCOREARB
#include "GLFW/glfw3.h"
#endif

#include <iostream>
#include "ProtoBaseApp.h"



namespace ijg {
    
	static void error_callback(int error, const char* description)
	{
		fputs(description, stderr);
	}

    class ProtoPlasm {
        
    public:
		// Setup Event callbacks pushed through to user ProtoController class
		friend void mouseBtn_callback(GLFWwindow* window, int button, int action, int mods);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void window_size_callback(GLFWwindow* window, int width, int height);
		
        int frameCount;
        float frameRate;
        
        //cstrs
		explicit ProtoPlasm(ProtoBaseApp* baseApp);
        ProtoPlasm(int appWidth, int appHeight, std::string appTitle, ProtoBaseApp* baseApp);
        
        
    private:
        
		void initGLFW();
        void runGLFW();
        
        // cross-platform SFML Window
        //sf::Window* window;
        GLFWwindow* window;
        
        // Master controller class, manages view, lighting and rendering
        std::unique_ptr<ProtoWorld> world;
        
        // base app class for user defined app classes
        ProtoBaseApp* baseApp;
        
        int appWidth;
        int appHeight;
        std::string appTitle;

		
    };

	

   
}

#endif // __PROTO_PLASM_H__
