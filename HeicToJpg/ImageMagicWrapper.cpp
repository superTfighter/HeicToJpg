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
 
				system(command.c_str());

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

int ImageMagicWrapper::executeOnSubDirectories()
{
	if (this->path.empty())
		throw "Path was not set!";

	for (const auto& entry : std::filesystem::directory_iterator(this->path))
	{

		if (entry.is_directory()) 
		{
			this->executeOnSubDirectories(entry.path().string());
		}

	}

	this->executeOnDirectory();

	return 0;

}

int ImageMagicWrapper::executeOnSubDirectories(std::string path)
{
	std::string old_path = this->path;
	this->path = path;

	this->executeOnSubDirectories();

	this->path = old_path;


	return 0;
}
