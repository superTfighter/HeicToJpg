#pragma once
#include <stdlib.h>
#include <iostream>
#include <filesystem>
#include <thread>
#include <windows.h>


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


	ImageMagicWrapper(std::vector<std::thread>* threadPool)
	{
		int statusCode = system("magick -version");

		if (statusCode != 0)
			throw "Imagemagic not found...";

		path = "";

		this->threadPool = threadPool;
	}


	void addPath(std::string path);

	int executeOnDirectory();

	int executeOnDirectory(std::string path);

	void executeOnSubDirectories();

	void executeOnSubDirectoriesDifferentThread();

	int executeOnSubDirectoriesPath(std::string path);

	std::string path;

	int totalCount;


	int currentCount;


private:
	int getHeicCount(std::string path);
	std::vector<std::thread>* threadPool;


	std::thread starThread();




};





