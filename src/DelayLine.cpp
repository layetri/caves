//
// Created by Daniël Kamp on 25/02/2021.
//

#include "Header/DelayLine.h"
#include <iostream>

DelayLine::DelayLine(int delayTime, float feedback, Buffer *input) {
  this->delayTime = delayTime;
  this->feedback = feedback;
  position = 0;

  x = input;
  y = new Buffer(input->getSize(), "DelayLine");
}

DelayLine::~DelayLine() {
  delete y;
}

// Increment the buffer position
void DelayLine::tick() {
  if(position < x->getSize()) {
    position++;
  } else {
    //std::cout << x->getSize() << "," << position << ": Delay line buffer wrap @ " << delayTime << std::endl;
    position -= x->getSize();
  }
}

int16_t DelayLine::process() {
  int16_t sample;
  // Run the delay line
  sample = 0.3 * x->getSample(position - delayTime) + 0.7 * x->getSample(position - delayTime - 1) + ((y->getSample(position - delayTime - 1) + y->getSample(position - delayTime)) * 0.5 * feedback);

  // Store the sample in the output buffer
  y->write(sample);
  y->tick();

  // Return the sample
  return sample;
}

void DelayLine::setDelayTime(int delayTime) {
  this->delayTime = delayTime;
}

void DelayLine::setdf(int delayTime, float feedback) {
  this->delayTime = delayTime;
  this->feedback = feedback;
}

int DelayLine::getDelayTime() {
  return delayTime;
}
