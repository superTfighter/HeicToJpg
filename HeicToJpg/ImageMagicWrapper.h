#pragma once
#include <stdlib.h>
#include <iostream>
#include <filesystem>


//TODO:Error handling
class ImageMagicWrapper
{
public:
	ImageMagicWrapper()
	{
		int statusCode = system("magick -version");

		if (statusCode != 0)
			throw "Imagemagic not found...";

		path = "";
	}

	void addPath(std::string path);

	int executeOnDirectory();

	int executeOnDirectory(std::string path);

	int executeOnSubDirectories();

	int executeOnSubDirectories(std::string path);

	std::string path;


private:

	

};

