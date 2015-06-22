PatternRecognizer 1.0 by
Zakharov Konstantin aka Ralor
<e-mail:zakharov.k.l@yandex.ru>
<skype:ralor-real>

Please don't look at my ugly code. Continuous XP is a bad practice.

![screenshot](https://raw.githubusercontent.com/Ralor/PatternRecognizer/master/screenshot.jpg)

Backlog:
	- User want to recognize contour of circle, rectangle and triangle from loaded jpg, so I'm supposed to design a simple algorithms using appropriate opencv functions.
	- User want a plugin system, so I need to find some kind of architectural pattern and C++ plugins library/mechanism.
	- User want to adjust contour width and color, so there must be some kind of standart dialog window to do that and some standart painting functions.

	- (*) User want to use webcamera, so I need to update QWidget with new image faster.
	- (*) User want to recognize images better, so I need to power up some alogrithms and give user some ability of customizing initial data.
	- (*) User want to know what plugin is better, so I need autotesting utility to know percentage of passed tests.

Waiting:
	- power up recognition algorithms
	-- look at Canny results with/without tresholding
	-- make tresholdind parameters adjustable via GUI (+ autorepaint <<onRelease>>)
	-- adjust color levels for tests with high difficulty
	- transfer projects to git repo
	- (*) set custom library path for app (smth like "../lib/" instead of %PATH%)
	- (*) set custom library path for plugins (instead of placing them into "../lib/")
	- (*) paint plugin tester
	
WIP:
	- compile RectangleRecognizer.dll
	- compile CircleRecognizer.dll
	
DONE:
	- install opencv
	- create makefil/*.pro or smth that compiles helloworld
	-- compile shared opencv libs using cmake and WITH_QT = 1 option (what that means?)
	-- find appropriate "LIBS +=" and line
	- render image on QWidget with QPainter, paint static line on it
	- find library/mechanism for plugin loading
	- find appropriate GoF pattern for plugins (adapter IPlugin)
	- find an algorithm for triangle (works approx ok)
	- find an algorithm for circle (works bad)
	- find an algorithm for rectangle (works bad)
	- create ITestMethod plugin interface (Mat& in, vector<vector<Point>>& out)
	-- create any valid plugin of ITestMethod and use it as template to populate others
	- embed custom QWidget into usual Qt GUI
	-- remember standart qt elements: adjuster, textedit, label, button, openfile dialog, color dialog
	-- QWidget features : set image, paint contour with specified plugin, set line color
	
REFERENCES:

(*) opencv coding style guide: http://code.opencv.org/projects/opencv/wiki/CodingStyleGuide
(*) enable webcamera: http://robocraft.ru/blog/computervision/420.html

OVERVIEW:
    
	
LICENSE:
	This source has been released "As is", you can you use it as you want.
	See LICENSE for details.
    
COMPILING:
	Provided code was compiled with gcc 4.8.1 (tdm-2).
	See BUILDING for details.
    
NOTES:
	Please report bugs to me via email.