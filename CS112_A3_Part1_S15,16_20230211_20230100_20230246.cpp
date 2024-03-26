#include "Image_Class.h"
#include <iostream>

using namespace std;

void gray_scale() {
  string filename;

  cout << "Pls enter colored image name to turn to gray scale: ";
  cin >> filename;

  Image image(filename);
  for (int i = 0; i < image.width; i++) {
    for (int j = 0; j < image.height; j++) {
      unsigned int avg = 0;
      for (int k = 0; k < image.channels; k++) {
        avg += image(i, j, k);
      }
      avg /= 3;
      image(i, j, 0) = avg;
      image(i, j, 1) = avg;
      image(i, j, 2) = avg;
    }
  }
  cout << "Pls enter image name to store new image\n";
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";

  cin >> filename;
  image.saveImage(filename);
}

void black_and_white() {
  string photoName;
  cout << "Pls enter colored image name to turn to gray scale: ";
  cin >> photoName;

  Image image(photoName);

  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      unsigned int avg = 0;

      for (int k = 0; k < 3; k++) {
        avg += image(i, j, k);
      }

      avg /= 3;

      for (int k = 0; k < 3; k++) {
        if (avg > 128) {
          image(i, j, k) = 255;
        } else if (avg < 128) {
          image(i, j, k) = 0;
        }
      }
    }
  }
}

void darken_lighten() {
  string photo;
  cout << "please inter your coloured photo\n";
  cin >> photo;
  Image Photo(photo);
  string choice;
  cout << "please inter what do you want \n";
  cout << "[A] to Lighten your image\n";
  cout << "[B] to Darken your image\n";
  cin >> choice;
  if (choice == "A" || choice == "a") {
    for (int i = 0; i < Photo.width; i++) {
      for (int j = 0; j < Photo.height; j++) {
        int red = Photo(i, j, 0) * 2;
        int green = Photo(i, j, 1) * 2;
        int blue = Photo(i, j, 2) * 2;
        if (red > 255) {
          red = 255;
        }
        if (green > 255) {
          green = 255;
        }
        if (blue > 255) {
          blue = 255;
        }
        Photo(i, j, 0) = red;
        Photo(i, j, 1) = green;
        Photo(i, j, 2) = blue;
      }
    }
  } else if (choice == "B" || choice == "b") {
    for (int i = 0; i < Photo.width; i++) {
      for (int j = 0; j < Photo.height; j++) {
        Photo(i, j, 0) /= 2;
        Photo(i, j, 1) /= 2;
        Photo(i, j, 2) /= 2;
      }
    }
  }
  string photoname;
  cout << "Pls enter image name to store new image and specify extension .jpg, "
          ".bmp, .png, .tga: \n";
  cin >> photoname;
  Photo.saveImage(photoname);
  system(photoname.c_str());
}

void invert_image() {
  string filename;
  cout << "Pls enter colored image name to turn to gray scale: ";
  cin >> filename;

  Image image(filename);

  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      for (int k = 0; k < 3; ++k) {
        image(i, j, k) = 255 - image(i, j, k);
      }
    }
  }

  cout << "Pls enter image name to store new image\n";
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";

  cin >> filename;
  image.saveImage(filename);
}
