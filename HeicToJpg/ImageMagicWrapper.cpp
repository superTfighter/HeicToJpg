#include "ImageMagicWrapper.h"


void ImageMagicWrapper::addPath(std::string path)
{
	this->path = path;
}

int ImageMagicWrapper::executeOnDirectory()
{
	if (this->path.empty())
		throw "Path was not set!";


	for (const auto& entry : std::filesystem::directory_iterator(this->path))
	{

		if(!entry.is_directory()){

		std::string file_path = entry.path().string();
		std::string file_name = entry.path().filename().string();

		std::string c1 = "heic";
		std::string c2 = "HEIC";

			if(file_name.find(c1) != std::string::npos || file_name.find(c2) != std::string::npos)
			{
				std::string new_file_path = file_path; 
			
				new_file_path.replace(file_path.length() - 4, 4, "jpg");
				std::string command = "magick " + file_path + " " + new_file_path;
 
				//system(command.c_str());

				WinExec(command.c_str(), SW_HIDE);

				this->currentCount++;

			}

		}
	}	

	return 0;
}

int ImageMagicWrapper::executeOnDirectory(std::string path)
{

	std::string old_path = this->path;
	this->path = path;

	this->executeOnDirectory();

	this->path = old_path;


	return 0;
}

void ImageMagicWrapper::executeOnSubDirectories()
{
	if (this->path.empty())
		throw "Path was not set!";

	this->executeOnDirectory();

	for (const auto& entry : std::filesystem::directory_iterator(this->path))
	{

		if (entry.is_directory()) 
		{
			this->executeOnSubDirectoriesPath(entry.path().string());
		}

	}

	
}

void ImageMagicWrapper::executeOnSubDirectoriesDifferentThread()
{
	if (this->path.empty())
		throw "Path was not set!";

	if (this->threadPool == nullptr)
		throw "No threadpool!";


	this->totalCount = this->getHeicCount(this->path);

	this->threadPool->operator[](0) = this->starThread();

}

int ImageMagicWrapper::executeOnSubDirectoriesPath(std::string path)
{
	std::string old_path = this->path;
	this->path = path;

	this->executeOnSubDirectories();

	this->path = old_path;


	return 0;
}

int ImageMagicWrapper::getHeicCount(std::string path)
{
	int count = 0;

	if (path.empty())
		throw "Path was not set!";

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{

		if (entry.is_directory())
		{
			count += this->getHeicCount(entry.path().string());
		}
		else
		{

			std::string file_path = entry.path().string();
			std::string file_name = entry.path().filename().string();

			std::string c1 = "heic";
			std::string c2 = "HEIC";

			if (file_name.find(c1) != std::string::npos || file_name.find(c2) != std::string::npos)
			{

				count++;
			}
		}

	}	

	return count;
}

std::thread ImageMagicWrapper::starThread()
{
	return std::thread(&ImageMagicWrapper::executeOnSubDirectories,this);
}
