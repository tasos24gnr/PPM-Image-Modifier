// BENOS ANASTASIOS 3130141

#include <iostream>
#include <cstdlib>
#include <string>
#include "ppm/ppm/ppm.h"
#include <vector>
#include "Image.h"
#include "Filter.h"

using namespace std;

int main(int argc, char *argv[]) {
	imaging::Image myimage;
	const char *fileName;
	int count = 0;

	if (argc == 1) {
		printf("\nPlease, pass your IMAGE FILTER COMMAND in Debugging -> Command Arguments and try again! \n");
	}
	else {
		cout << "CMD Line Arguments are:     ";
		for (int i = 1; i<argc; ++i) {
			cout << argv[i] << " ";
		}
		cout << endl << endl;
		cout << "File name of the image to load: ";
		cout << argv[argc - 1] << endl;
		
		string s = argv[argc - 1];
		fileName = (s).c_str();

		string fend = "";
		string filteredfilename = "";
		const char * fname = fileName;
		do {
			if (*fname == '.') {
				while (*fname != '\0') {
					fend += *fname;
					*fname++;
				}break;
			}
			else {
				filteredfilename += *fname;
			}
		} while (*fname++);
		filteredfilename = "filtered_" + s;
		cout << "File name of the filtered image to save: "<<filteredfilename << endl;

		bool e= myimage.load(fileName, fend);

		while (count < argc - 2) {
			if (strcmp(argv[count], "-f") == 0) {
				count++;

				if (strcmp(argv[count], "gamma") == 0) {
					float gamma = atof(argv[++count]);		//atof : to change a string variable into integer
					imaging::FilterGamma filter(gamma);
					myimage = filter.operator<<(myimage);
				}
				else if (strcmp(argv[count], "linear") == 0) {
					float a1 = atof(argv[++count]);
					float a2 = atof(argv[++count]);
					float a3 = atof(argv[++count]);
					float c1 = atof(argv[++count]);
					float c2 = atof(argv[++count]);
					float c3 = atof(argv[++count]);
					imaging::Color a(a1, a2, a3);
					imaging::Color c(c1, c2, c3);

					imaging::FilterLinear filter(a, c);
					myimage = filter.operator<<(myimage);
				}
			}
			else {
				count++;
			}
		}
		if (e) myimage.save(filteredfilename, fend);	//This if statement protects me from the special case: Header on ppm file contains accaiptable format,height and width but wrong color number. Image::save should not run in this case , otherwise we will get an error.
	}
	system("PAUSE");
}




