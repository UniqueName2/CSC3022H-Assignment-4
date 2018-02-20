//PTLSAH004

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <memory>

namespace ptlsah004
{
	class Image
	{
		//friended functions to allow for stream operator overloading
        friend std::ostream& operator<<(std::ostream& os,const Image& img);
        friend std::istream& operator>>(std::istream& is, Image& img);

		private:
			int width, height;
			std::unique_ptr<u_char[]> data;
			std::string imgName, hdr;
		
		public:
			Image();                            		//default constructor
			Image( u_char** bfr,int w, int h); 			//constructor for testing
            Image(const Image& other);          		//copy constructor
          	Image& operator= (const Image& rhs);		//copy assignment
            Image(Image&& other);               		//move constructor
            Image& operator= (Image&& rhs);     		//move assignment
            ~Image();                           		//destructor
            
            Image operator+(const Image& rhs) const; 	//add two images
            Image operator-(const Image& rhs) const; 	//subtract images
            Image operator!() const;	 				//invert an image
            Image operator/(const Image& rhs) const; 	//mask an image with another
            Image operator*(const int thrsh) const; //threshold an image by given int
            
            void load(std::string fName); 			//load image with the given fName
            void save(std::string oFname); 		//save image data to file with given name
            
            int getWidth(){return width;}
    		int getHeight(){return height;}
    		

			class iterator
			{
				friend class Image;

				private:
					u_char *ptr; 				//ptr to current pixel									
					iterator(u_char *p) : ptr(p) {}		// constructor (only called by Image::begin())
				public:
					//copy construct is public
					iterator( const iterator & rhs) : ptr(rhs.ptr) {}

					// define overloaded ops: *, ++, --, =
					iterator& operator=(const iterator& rhs); //copy assignment
                    iterator& operator=(iterator&& rhs); // move assignment
                    u_char& operator*();             //dereference
                    const iterator& operator++();   //prefix ++
                    const iterator& operator--();   //prefix --
                    
                    bool operator==(const iterator& rhs); //equality
                    bool operator!=(const iterator& rhs); //inequality
		
			};

			iterator begin(void) const; 
			iterator end() const;
		

	};

	int bounded(int num); 

	//overloaded stream operators
    std::ostream& operator<<(std::ostream& os, const Image& img);
    std::istream& operator>>(std::istream& is, Image& img);
}
#endif