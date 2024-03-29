Procedual Terrain Generator (version 1.0) 06/04/2019


DEVELOPER TEAM
----------------------------------------------------------------

M.B.C.
	E-mail: mchavez 0612 (at) ucla (dot) edu

T.A.
	E-mail: timandersen 32 (at) gmail (dot) com



PROGRAM NOTES
----------------------------------------------------------------

- Program as built with Qt (C++) Community Creator 5.12.2. 

- Program was part of final project submission. 

- Project was created for the UCLA PIC 10C Advanced Programming course.




INSTRUCTIONS
---------------------------------------------------

Installation: Using Qt Community Creator 5.12.2, the application can be built with either Desktop Qt 5.12.2 GCC 64-bit or MSV 2017 64-bit. The program will not run correctly otherwise. Older versions of Qt Creator will not build the applicaiton at all due to the need of newest
libraries. 

Device Requirements: A decent computer is sufficient. Older computers will low CPU power may experience longer run-times due to the intense computational process of this application. 

Notes: The files cannot be re-ordered in another fashion as it is currently. The program algorithms are local path specific. Furthermore, the png files cannot be re-named for the same reason. 

Suggestions: Run the application in full window for best user experience. 


DESCRIPTION
---------------------------------------------------
This is a Procedual Terrain Generator (PTG) implemented with the Qt Framework. This is actually a fork of [T.A](https://github.com/timand32)'s repo, but that repo was in a messy state. This repo is like a re-organized version. This application was intended to be submitted as part of a class project. 

The following figures explains the program. There is also a video in the README folder that has a live demonstration of the application.
![](instruction_image_page1.png)
![](instruction_image_page2.png)

The class hierarchy is briefly described by the following figure. 
![](figure_class_hierarchy_diagram.png)


LICENSING AND ACKNOWLEDGEMENTS 
---------------------------------------------------
Big thanks for [T.A](https://github.com/timand32) for managing the github repo during development.

This is project built for an educational purpose. We do NOT condone plagaraism, but this program is free to use for other PERSONAL purposes.

A special thanks to open source code used for generating procedural noise:
	
	1. For the Perlin Noise Generator,
	
	//	siv::PerlinNoise
	
	//	Perlin noise library for modern C++
	
	//	Copyright (C) 2013-2018 Ryo Suzuki <reputeless@gmail.com>

	
	2. For the Diamond Square implementation,
	
	//	Copyright (c) 2018 Martyn Afford
	
	//	Licensed under the MIT licence
