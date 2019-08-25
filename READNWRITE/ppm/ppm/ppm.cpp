#include <iostream>
#include <string>
#include <fstream>
#include "ppm.h"

using namespace std;

bool isDigit(string &word) {
	bool retVal = true;
	for (std::string::const_iterator k = word.begin(); k != word.end(); ++k)
		retVal = retVal && isdigit(*k);
	return retVal;
}

float * imaging::ReadPPM(const char * fName, int * w, int * h){

	fstream iFile(fName, ios::out | ios::in | ios::binary);
	string text1, text2, text3, text4;
	int v;
	bool panic = false;
	
	if (iFile.is_open()) {

		v = iFile.peek();
		while (v == 10 || v == 32 || v == 35) {
			if (v == 10 || v == 32) {
				//cout << " Space or Enter" << endl;
				v = iFile.get();
				v = iFile.peek();
			}
			else if (v == 35) {
				//cout << " Comment " << endl;
				iFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				v = iFile.peek();
			}
		}

		iFile >> text1;
		

		if (text1.compare("P6") == 0 && panic == false) {
			cout << "\n- Correct format -" << endl;


			v = iFile.peek();
			while ((v < 48 || v>57) && (panic == false)) {
				if (v == 10 || v == 32) {
					//cout << " Space or Enter" << endl;
					v = iFile.get();
					v = iFile.peek();
				}
				else if (v == 35) {
					//cout << " Comment " << endl;
					iFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					v = iFile.peek();
				}
				else { panic = true; }
			}

			iFile >> text2;

			if (panic == false && isDigit(text2) && stoi(text2) > 0) {
				cout << "- Acceptable Width -" << endl;


				*w = stoi(text2);	//Pass Width value

				v = iFile.peek();
				while ((v < 48 || v>57) && (panic == false)) {
					if (v == 10 || v == 32) {
						//cout << " Space or Enter" << endl;
						v = iFile.get();
						v = iFile.peek();
					}
					else if (v == 35) {
						//cout << " Comment " << endl;
						iFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						v = iFile.peek();
					}
					else { panic = true; }

				}

				iFile >> text3;

				if (panic == false && isDigit(text3) && stoi(text3) > 0) {
					cout << "- Acceptable Height -" << endl;

					*h = stoi(text3);	//Pass Height value

					v = iFile.peek();
					while ((v < 48 || v>57) && (panic == false)) {
						if (v == 10 || v == 32) {
							//cout << " Space or Enter" << endl;
							v = iFile.get();
							v = iFile.peek();
						}
						else if (v == 35) {
							//cout << " Comment " << endl;
							iFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							v = iFile.peek();
						}
						else { panic = true; }

					}

					iFile >> text4;

					if (panic == false && isDigit(text4) && stoi(text4) > 0 && stoi(text4) <= 255) {
						cout << "- Acceptable  maximum value of the colour components -" << endl;

						v = iFile.peek();

						while ((v < 48 || v>57) && (panic == false)) {
							if (v == 10 || v == 32) {
								//cout << " Space or Enter" << endl;
								v = iFile.get();
								v = iFile.peek();
							}
							else if (v == 35) {
								//cout << " Comment " << endl;
								iFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								v = iFile.peek();

							}
							else {
								//cout << "Image data found!" << endl;
								break;
							}
						}

						unsigned char * pixelArray = new unsigned char[stoi(text2) * stoi(text3) * 3];
						iFile.read((char *)pixelArray, stoi(text2) * stoi(text3) * 3);
							//cout << iFile.gcount() << endl;
							//cout << iFile.good() << endl;
							//cout << iFile.eof() << endl;
							//cout << iFile.peek() << endl;
							//cout << iFile.good() << endl;
							//cout << iFile.eof() << endl;
						float * fArray = new float[stoi(text2) * stoi(text3) * 3];

						for (int z = 0; z < (stoi(text2) * stoi(text3) * 3);z++) {
							fArray[z] = (float)pixelArray[z] / 255.f;
						}

						delete[]pixelArray;

						return &fArray[0];


					}
					else {
						if (panic == true) {
							cout << "Error: Missing Color number from the given file!" << endl;
						}else { cerr << "Error: Unacceptable  maximum value of the colour components " << endl; }return nullptr;}
				}
				else
				{
					if (panic == true) {
						cout << "Error: Missing Height and Color number from the given file!" << endl;
					}else { cerr << "Error: Unacceptable Height" << endl; }return nullptr;}
			}
			else
			{
				if (panic == true) {
					cout << "Error: Missing Width, Height and Color number from the given file!" << endl;
				}else { cerr << "Error: Unacceptable Width" << endl; }return nullptr;}
		}
		else
		{cerr << "Error: The format of the image data is not P6!" << endl;return nullptr;}

		iFile.close();
	
	}else { cout << "Error: Cannot open the input file. Probably, this image file does not exists!" << endl;return nullptr; }
}


bool imaging::WritePPM(const float * data, int w, int h, const char * filename) {
	
	ofstream outputFile;
	outputFile.open(filename, ios::out | ios::binary);
	
	if (outputFile.is_open()) {
		outputFile << "P6" << " " << w << " " << h << " " << "255" << "\n";
		unsigned char * negar = new unsigned char[h * w * 3];

		for (int z = 0; z < (w * h * 3);z++) {
			negar[z] = (float)data[z] * 255.f;
		}

		outputFile.write((char *)negar, h * w * 3);
		outputFile.flush();
		outputFile.close();

		return true;

	}else { cout << "Error: Cannot open/create the output file" << endl;return false; }
}
