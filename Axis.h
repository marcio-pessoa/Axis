/* Axis.h - Robot Axis Management Library
 * 
 * Author: Márcio Pessoa <marcio.pessoa@sciemon.com>
 * Contributors: none
 * 
 * Change log
 * 2017-05-11
 *         * New feature: Added this aboluteRead() method.
 * 
 * 2016-05-07
 *         * New feature: Added this abolute() method.
 * 
 * 2014-11-18
 *         * Axis
 *         Changed unsigned int _pin to byte _pin. To reduce memory consumption.
 * 
 * 2014-11-16
 *         * Axis
 *         changed name String type to char. To reduce memory consumption.
 * 
 * 2014-09-06
 *         Experimental version.
 */

#ifndef Axis_h
#define Axis_h

#include "Arduino.h"

class Axis
{
  public:
    Axis(char *name, byte pin, 
         int position_minimal_hard, int position_maximum_hard, 
         int position_minimal_soft, int position_maximum_soft,
         int position_park,
         unsigned long delay);
    String nameRead();
    byte pinRead();
    bool run();
    bool positionReset();
    int positionRead();
    int positionReadRelative();
    bool positionWrite(int position);
    int hardMinimumRead();
    bool hardMinimumWrite(int position);
    int hardMaxiumRead();
    bool hardMaximumWrite(int position);
    int softMinimumRead();
    bool softMinimumWrite(int position);
    int softMaxiumRead();
    bool softMaximumWrite(int position);
    int parkRead();
    bool parkWrite(int position);
    int delayRead();
    bool delayWrite(int delay);
    bool isDone();
    String status();
    bool absolute(bool enable=true);
    bool absoluteRead();
  private:
    char *_name;
    byte _pin;
    int _position_minimum_hard;
    int _position_minimum_soft;
    int _position_maximum_hard;
    int _position_maximum_soft;
    int _position_park;
    int _position_current;
    int _position_relative;
    int _position_destination;
    unsigned long _delay;
    unsigned long _timer;
    bool _absolute;
};

#endif
