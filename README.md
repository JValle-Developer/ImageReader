# ImageReader
An image reader program for non indexed BMP files of 24 bits per pixel in C++

Download winbgim from here: http://www.mediafire.com/file/z9wnl0c70tiacqn/winbgim_DevCpp.zip/file, is in dev-c++, you probably have to load a couple of parameters for the linker, the path is: project, project options, parameters, and write: -lbgi -lgdi32 -luser32 -lcomdlg32 -luuid -loleaut32 -lole32 -mwindows -lwinmm, one thing more, after installing winbgim, go to dev c and create new project as console graphics application, this item must be in the project list if winbgim is properly installed, I wrote "write to shared memory", because I wrote the file also in memory although I did not access the file this way, but from the same file

Regards
