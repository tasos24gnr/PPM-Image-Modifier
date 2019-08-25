#include <iostream>
#include <cmath>
#include "Image.h"

using namespace std;

namespace imaging {
	
	/*	This method acts on an image and alters it, producing 
	 *	a new one and it should be able to be called (polymorphic), from the offspring of the Filter class.The
	 *	descendants of this class will each implement differently this method, depending on
	 *	the type of filter.
	 */
	class Filter {
		public:
			//Constructors Destructor
			Filter() { cout << "Filters Default constructor" << endl; }
			~Filter() { cout << "Filters Default destructor" << endl; }
			//Pure Virtual Function 
			virtual Image operator << (const Image & image) = 0;  // is a pure virtual function that is required to be implemented by a derived class
	};
	//Formula of FilterLinear: p'(x,y) = a . p(x,y) + c
	class FilterLinear:Filter {
		protected:
			Color a, c;						// def math::Vec3<float> Color
		public:
			//Constructors Destructor
			FilterLinear(Color colA, Color colC) : a(colA), c(colC)
			{ cout << "FilterLinear's Default Constructor" << endl; }
			FilterLinear(const FilterLinear & FL)
			{
				this -> a = FL.a;
				this -> c = FL.c;
				cout << "FilterLinear's Copy Constructor" << endl;
			}
			~FilterLinear() { cout << "FilterLinear's Destructor" << endl; }
			//Implementation of Filter's pure virtual func
			Image operator << (const Image & image) {
				Image new_image = image;
				for (int i = 0; i < new_image.getHeight(); i++) {
					for (int j = 0; j < new_image.getWidth(); j++) {
						new_image.setVal(j, i, Presult(j, i, new_image, a, c));		//setVal(width,height,value)
					}
				}
				return new_image;
			}
		private:				//Here, i will calculate the specific formulas functions
			//P(x,y,) pixel's cordinates of the input image.
			Color P(unsigned int x, unsigned int y, const Image & image) { return image.getVal(x, y); }
			//Presult(...) calculates FilterLinear's formula equation.
			Color Presult ( unsigned int x , unsigned int y , const Image & image , Color a , Color c){
				Color result = P(x, y, image)*a + c;
				result = result.clampToUpperBound(1.0);
				result = result.clampToLowerBound(0.0);
				return result;
			}
	};

	//Formula of FilterGamma: p'(x,y) =  p(x,y) ^ g
	class FilterGamma :Filter {
	protected:
		float g;
	public:
		FilterGamma(float gama) {
			while (gama > 2.0 || gama < 0.5) {
				cout << "'g' value is not accepted. Please enter a new value, in range [0.5 , 2]: ";
				cin >> gama;
				cout << "     " << endl;
			}
			g = gama;
		}
		//Copy Constructor
		FilterGamma(const FilterGamma & i) {
			this->g = i.g;
		}
		//Destructor
		~FilterGamma() {}
		//Implementation of Filter's pure virtual func
		Image operator << (const Image & image) {
			Image new_image = image;
			for (int i = 0; i < new_image.getHeight(); i++) {
				for (int j = 0; j < new_image.getWidth(); j++) {
					new_image.setVal(j, i, Presult(j, i, new_image, g));
				}
			}
			return new_image;
		}
	
	private:				//Here, i will calculate the specific formulas functions
		//P(x,y,) pixel's cordinates of the input image.
		Color P(unsigned int x, unsigned int y, const Image & image) { return image.getVal(x, y); }
		//Presult(...) calculates FilterGamma's formula equation.
		Color Presult(unsigned int x, unsigned int y, const Image & image,float g) {
			Color result = P(x, y, image) * pow(1, g);
			return result;
		}
	};
}