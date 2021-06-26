//
// Created by Daniël Kamp on 17/02/2021.
//

#include "Header/Buffer.h"

Buffer::Buffer(int length, std::string name) {
  data = new int16_t [length];
  size = length;
  position = 0;
  full_cycle_flag = false;

  this->name = name;
}

Buffer::~Buffer() {
  delete[] data;
}

int Buffer::getSize() {
  return size;
}

int Buffer::getPosition() {
  return position;
}

std::string Buffer::getName() {
  return name;
}

int16_t Buffer::getSample(int sample_position) {
//  int pos = ((sample_position > size || (sample_position * -1) > size) * sample_position % size) +
//      ((sample_position < size && (sample_position * -1) < size) * sample_position);

  if(sample_position < 0) {
    return this->operator[](size + sample_position);
  } else {
    return this->operator[](sample_position);
  }
}

int16_t Buffer::getCurrentSample() {
  return this->operator[](position);
}

void Buffer::tick() {
  if(position < size) {
    position++;
  } else {
    if(!full_cycle_flag) full_cycle_flag = true;
    position -= size;
  }
}

void Buffer::write(int16_t sample) {
  data[position] = sample;
}

void Buffer::writeAddition(int16_t sample) {
  data[position] += sample;
}

void Buffer::writeAhead(int16_t sample, int places) {
  data[position + places] = sample;
}

int16_t Buffer::readAhead(int places) {
  return data[position + places];
}

int16_t Buffer::readBack(int places) {
  int pos = position - places;
//  std::cout << name << ": " << pos << " " << data[pos] << std::endl;
  if(pos < 0) {
    if(full_cycle_flag) {
      pos = size + pos;
    } else {
      return 0;
    }
  }

  return data[pos];
}

void Buffer::flush() {
  data[position] = 0;
}


