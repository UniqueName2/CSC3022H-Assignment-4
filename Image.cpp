//PTLSAH004

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

#include "Image.h"

namespace ptlsah004
{
	using namespace std;

	Image::Image():width(0), height(0), data(nullptr), imgName(""), hdr(""){}

	Image::Image(u_char** bfr,int w, int h)
	{
        data = unique_ptr<u_char[]>(*bfr);
        width = w;
        height = h;
        imgName = "";
        hdr = "";
    }

    Image::Image(const Image& other)
    {
        width = other.width;
        height = other.height;
        imgName = other.imgName;
        hdr = other.hdr;
        data = unique_ptr<u_char[]>(new u_char[other.height * other.width]);

        for(Image::iterator itrThis = begin(), itrOther = other.begin(); itrOther != other.end(); ++itrThis, ++itrOther)
        {
            *itrThis = *itrOther;
    	}
    }

  	Image& Image::operator=(const Image& other)
  	{
        width = other.width;
        height = other.height;
        imgName = other.imgName;
        hdr = other.hdr;
        data = unique_ptr<u_char[]>(new u_char[other.height * other.width]);

        for(Image::iterator itrThis = begin() , itrOther = other.begin(); itrOther != other.end(); ++itrThis, ++itrOther)
        {
            *itrThis = *itrOther;
        }
        
        return *this;
    }
    
    //move constructor
    Image::Image(Image&& other)
    {
        width = other.width;
        height = other.height;
        imgName = other.imgName;
        hdr = other.hdr;
        data = unique_ptr<u_char[]>(new u_char[other.height * other.width]);

        for(Image::iterator itrThis = begin() , itrOther = other.begin(); itrOther != other.end(); ++itrThis, ++itrOther)
        {
            *itrThis = *itrOther;
        }
        
        other.width = 0;
        other.height = 0;
        other.data = nullptr;
        other.imgName = "";
        other.hdr = "";
    }               		
    
    Image& Image::operator=(Image&& other)
    {
        width = other.width;
        height = other.height;
        imgName = other.imgName;
        hdr = other.hdr;
        data = unique_ptr<u_char[]>(new u_char[other.height * other.width]);
        
        for(Image::iterator itrOther = other.begin(), itrThis = begin(); itrOther != other.end(); ++itrOther, ++itrThis)
        {
            *itrThis = *itrOther;
        }
        
        other.width = 0;
        other.height = 0;
        other.data = nullptr;
        other.imgName = "";
        other.hdr = "";
        
        return *this;
    }
    
   
    Image::~Image(){}

    Image Image::operator!() const
    {
        Image x(*this);
        for(Image::iterator itrThis = begin(), lImg = x.begin(); itrThis != end(); ++itrThis, ++lImg)
        {
            int num = 255 - (int)(*itrThis);
            *lImg = (u_char)bounded(num);
        }
        
        return x;
    }

    Image Image::operator/(const Image& rhs) const
    {
        if(height == rhs.height && width == rhs.width)
        {
            Image x(rhs);
            for(Image::iterator lImg = x.begin(), itrThis = begin(); itrThis != end(); ++lImg, ++itrThis)
            {
                if((int)(*lImg) == 255)
                {
                	int z = bounded((int)(*itrThis));
                    *lImg = (u_char)z;
                }
            }
            
            return x;
        }
        else{exit(1);}
    }

    Image Image::operator-(const Image& rhs) const
    {
        if(height == rhs.height && width == rhs.width)
        {
            Image x(*this);
            for(Image::iterator lImg = x.begin(), rImg = rhs.begin(); rImg != rhs.end(); ++lImg, ++rImg)
            {
                int num = (int)(*lImg) - (int)(*rImg);
                *lImg = (u_char)bounded(num);
        	}

            return x;
        }
        else{exit(1);}
    }

    Image Image::operator+(const Image& rhs) const
    {
        if(height == rhs.height && width == rhs.width)
        {
            Image x(*this);
            for(Image::iterator rImg = rhs.begin(), lImg = x.begin(); rImg != rhs.end(); ++lImg, ++rImg)
            {
                int num = (int)(*lImg) + (int)(*rImg);
                *lImg = (u_char)bounded(num);
            }
            
            return x;
        }
        else{exit(1);}
    }
    
    Image Image::operator*(const int thrsh) const
    {
        Image x(*this);
        for(Image::iterator itrThis = begin(), lImg = x.begin(); itrThis != end(); ++itrThis, ++lImg)
        {
            if((int)(*lImg) <= thrsh)
            {
                *lImg = (u_char)0;
            }
            else
            {
                *lImg = (u_char)255;
            }
        }
        
        return x;
    }
    
    void Image::save(string oFname)
    {       
        ofstream saveFile(oFname, ios::out|ios::binary);
        saveFile << hdr;
        saveFile << width << " " << height << '\n' << 255 << endl;
        int dmn = height * width;
        saveFile.write((char*)data.get(), dmn);
        saveFile.close();
    }

    void Image::load(string fName)
    {
        ifstream ifsFileIn(fName, ios::in|ios::binary);
        imgName = fName;
        string ln;
        getline(ifsFileIn, ln);
        hdr = hdr + ln + "\n";
        getline(ifsFileIn, ln);
        while(ln[0] == '#')
        {
            hdr = hdr + ln + "\n";   
            getline(ifsFileIn, ln);
        }
        istringstream w_and_h(ln);
        w_and_h >> width >> height;
        int numbers;
        ifsFileIn >> numbers >> ws;
        int dmn = height * width;
        data = unique_ptr<u_char[]>(new u_char[dmn]);
        ifsFileIn.read((char*)data.get(), dmn);
        ifsFileIn.close();
    }

    int bounded(int num)
    {
        if(num > 255){num = 255;}
        else if(num < 0){num = 0;}

        return num;
    }

    /*
    	Iterator functions
	*/

    u_char& Image::iterator::operator*(){return *ptr;}

    const Image::iterator& Image::iterator::operator++()
    {
        ptr ++;
        return *this;
    }
    
    const Image::iterator& Image::iterator::operator--()
    {
        ptr --;
        return *this;
    }
    
    Image::iterator& Image::iterator::operator=(const Image::iterator& rhs)
    {
       ptr = rhs.ptr;
       return *this;
    }
    
    Image::iterator& Image::iterator::operator=(Image::iterator&& rhs)
    {
        ptr = rhs.ptr;
        rhs.ptr = nullptr;    
        return *this;
    }

    bool Image::iterator::operator==(const Image::iterator& rhs){return (ptr == rhs.ptr);}

    bool Image::iterator::operator!=(const Image::iterator& rhs){return (ptr != rhs.ptr);}

    Image::iterator Image::begin(void) const{return iterator(data.get());}
    
    Image::iterator Image::end() const{return iterator(&data[height * width]);}

    ostream& operator<<(ostream& os,const Image& img)
    {
        os << img.hdr << img.width << " " << img.height << '\n' << 255 << endl;
        int dmn = img.height * img.width;
        os.write((char*)img.data.get(), dmn);
        
        return os;
    }

    istream& operator>>(istream& is, Image& img)
    {
        string ln;
        getline(is, ln);
        img.hdr = img.hdr + ln + "\n";
        getline(is, ln);
        while(ln[0] == '#')
        {            
            img.hdr = img.hdr + ln + "\n";
            getline(is, ln);
        }
        istringstream w_and_h(ln);
        w_and_h >> img.width >> img.height;
        int xy;
        is >> xy >> ws;
        int dmn = img.height * img.width;
        img.data = unique_ptr<u_char[]>(new u_char[dmn]);
        is.read((char*)img.data.get(), dmn);
        return is;
    }
}