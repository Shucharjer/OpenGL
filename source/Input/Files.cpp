#include "Input/Files.h"
#include <fstream>
#include <io.h>

void Files::GetAllFiles(const std::string folder_path, std::vector<std::string>& files)
{
    long   hFile   =   0;  
	//文件信息  
	struct _finddata_t fileinfo;  
	std::string p;  
	if((hFile = _findfirst(p.assign(folder_path).append("\\*").c_str(),&fileinfo)) !=  -1)  
	{  
		do  
		{   
			if((fileinfo.attrib &  _A_SUBDIR))  
			{  
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
				{
					files.push_back(p.assign(folder_path).append("\\").append(fileinfo.name) );
					GetAllFiles(p.assign(folder_path).append("\\").append(fileinfo.name), files); 
				}
			}  
			else  
			{  
				files.push_back(p.assign(folder_path).append("\\").append(fileinfo.name) );  
			} 
 
		}while(_findnext(hFile, &fileinfo)  == 0);  
 
		_findclose(hFile); 
	}
}

void Files::GetAllFormatFiles(std::string folder_path, std::vector<std::string>& files, const char* format)
{
    //文件句柄  
	long   hFile   =   0;  
	//文件信息  
	struct _finddata_t fileinfo;  
	std::string p;  
	if((hFile = _findfirst(p.assign(folder_path).append("\\*" + std::string(format)).c_str(),&fileinfo)) !=  -1)  
	{  
		do  
		{    
			if((fileinfo.attrib &  _A_SUBDIR))  
			{  
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
				{
					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
					GetAllFormatFiles( p.assign(std::string(folder_path)).append("\\").append(std::string(fileinfo.name)), files,format); 
				}
			}  
			else  
			{  
				files.push_back(p.assign(folder_path).append("\\").append(fileinfo.name) );  
			}  
		}while(_findnext(hFile, &fileinfo)  == 0);  
 
		_findclose(hFile); 
	}
}