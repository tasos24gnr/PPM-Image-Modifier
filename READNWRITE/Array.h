#include <string>
#include <iostream>

#include "ppm/ppm/ppm.h"
#include <vector>

using namespace std;

namespace math {
	template <class T>
	class Array {
	protected:
		unsigned int width, height;		//width and weight of Array
		vector<T> buffer;				//Array which holds data
	public:
		// metric accessors
		/*! Returns the width of the image
		*/
		const unsigned int getWidth() const { return width; }
		/*! Returns the height of the image
		*/
		const unsigned int getHeight() const { return height; }

		vector<T> & getRawDataPtr()
		{return this->buffer;}
		//! Obtains the value of the vector at location (x,y). Changed Pixel -> Val to achieve abstraction
		T getVal(unsigned int x, unsigned int y) const
		{
			if (x > this->width || y > this->height) {
				cout << "Coordinates out of bounds!-------getVal" << endl;
				return NULL;
			}
			else {
				return this->buffer[y * this->width + x];
			}
		}
		//Sets the color  value at position (x,y) of vector. Changed Pixel -> Val to achieve abstraction
		void setVal(unsigned int x, unsigned int y, T & value)
		{
			if (this->buffer.empty() || x > this->width || y > this->height) {
				cout << "Coordinates out of bounds!--------setVal" << endl;
			}
			else {
				this->buffer[y * this->width + x] = value;
			}
		}
		/*! Copies the image data from an external raw buffer to the internal image buffer.
		*  Image object and that the data buffer has been already allocated. If the image buffer is not allocated or the
		*  width or height of the image are 0, the method should exit immediately.
		*  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
		*/
		void setData(const vector<T> & data_ptr)
		{
			if (this->height == 0 || this->width == 0) {
				cerr << "width or height equals to 0!-------setData" << endl;
			}
			else {
				this->buffer.clear();					//Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
				this->buffer.reserve(data_ptr.size());  //Requests that buffers vector capacity be at least enough to contain data_ptr.size elements.
				for (int i = 0; i < data_ptr.size(); i++) { this->buffer.push_back(data_ptr[i]); }
			}
		}
		// Copy assignment operator.  param right is the source image.
		//T & operator =(const Array<T> & right)
		//{
		//	this->width = right.getWidth();
		//	this->height = right.getHeight();
		//	vector<T> vect = right.buffer;   
		//	this->buffer.clear();
		//	this->buffer.reserve(vect.size());
		//	for (int i = 0; i < vect.size(); i++) { this->buffer.push_back(vect[i]); }
		//	return *this;
		//}
		//Overload the operator() . Returns reference of i-j value
		T & operator ()(size_t j, size_t i)
		{return this-> buffer[this->width * i + j];}
		
		
		//Default constructor.
		Array() : width(0), height(0) {}
		//Constructor with width and height specification.
		Array(unsigned int width, unsigned int height) : width(width), height(height) {}
		//Constructor with data initilization
		Array(unsigned int width, unsigned int height, const vector<T> data_ptr) : width(width), height(height) {
			setData(data_ptr);
		}
		//Copy constructor
		Array(const Array<T> & src)
		{
			this->width = src.getWidth();
			this->height = src.getHeight();
			setData(src.buffer);
		}
		//Destructor
		~Array() {
			width = 0;height = 0;
			this->buffer.clear();
		}
	};
}
