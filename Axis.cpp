/* Axis.cpp - Robot Axis Management Library
 * 
 */

#include "Arduino.h"
#include "Axis.h"

/* Axis::Axis
 * 
 * Description
 *   Define a robot axis.
 * 
 *   Axis (char name, unsigned int pin,
 *         int position_minimal_hard, int position_maximum_hard,
 *         int position_minimal_soft, int position_maximum_soft,
 *         int position_park,
 *         unsigned long delay)
 * 
 * Parameters
 *   String name
 *   unsigned int pin
 *   int position_minimal_hard
 *   int position_maximum_hard
 *   int position_minimal_soft
 *   int position_maximum_soft
 *   int position_park
 *   unsigned long delay
 * 
 * Returns
 *   void
 */
Axis::Axis(char *name, byte pin, 
           int position_minimal_hard, int position_maximum_hard, 
           int position_minimal_soft, int position_maximum_soft,
           int position_park,
           unsigned long delay) {
  _name = name;
  _pin = pin;
  _position_minimum_hard = position_minimal_hard;
  _position_maximum_hard = position_maximum_hard;
  _position_minimum_soft = position_minimal_soft;
  _position_maximum_soft = position_maximum_soft;
  _position_park = position_park;
  _position_current = _position_park;
  _position_relative = 0;
  _position_destination = _position_park;
  _delay = delay;
  _timer = millis();
  _absolute = true;
}

/* nameRead
 * 
 * Description
 *   Read axis name.
 * 
 *   axis.nameRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   String: Name of axis
 */
String Axis::nameRead() {
  return _name;
}

/* pinRead
 * 
 * Description
 *   Read electronic pin of axis.
 * 
 *   axis.pinRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   byte: axis pin
 */
byte Axis::pinRead() {
  return _pin;
}

/* run
 * 
 * Description
 *   Do axis move based on time.
 * 
 *   axis.run()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   true: If axis do a step to move
 *   false: If axis don't move
 */
bool Axis::run() {
  _position_relative = 0;
  if (millis() - _timer < _delay) {
    return false;
  }
  if (_position_destination > _position_current) {
    _position_relative = 1;
    _position_current++;
  }
  if (_position_destination < _position_current) {
    _position_relative = -1;
    _position_current--;
  }
  _timer = millis();
  return true;
}

/* positionReset
 * 
 * Description
 *   Define curret axis position as zero position.
 * 
 *   axis.positionReset()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool Axis::positionReset() {
  _position_current = 0;
  _position_destination = 0;
}

/* positionRead
 * 
 * Description
 *   Read current axis position.
 * 
 *   axis.positionRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: Curret axis position
 */
int Axis::positionRead() {
  return _position_current;
}

/* positionReadRelative
 * 
 * Description
 *   Read axis direction to move.
 * 
 *   axis.positionReadRelative()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: Axis relative position
 *         1: increase position
 *         0: not to do
 *        -1: decrease position
 */
int Axis::positionReadRelative() {
  return _position_relative;
}

/* positionWrite
 * 
 * Description
 *   Define axis position to move.
 * 
 *   axis.positionWrite()
 * 
 * Parameters
 *   position: Position to move
 * 
 * Returns
 *   void
 */
bool Axis::positionWrite(int position) {
  if (_absolute) {
    if ((position > _position_maximum_soft) or 
        (position < _position_minimum_soft)) {
      return true;
    }
    _position_destination = position;
  }
  else {
    if ((position + _position_destination > _position_maximum_soft) or 
        (position + _position_destination < _position_minimum_soft)) {
      return true;
    }
    _position_destination += position;
  }
  return false;
}

/* hardMinimumRead
 * 
 * Description
 *   Read axis hard minimum position.
 * 
 *   axis.hardMinimumRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: A hard minimum position
 */
int Axis::hardMinimumRead() {
  return _position_minimum_hard;
}

/* hardMinimumWrite
 * 
 * Description
 *   Define axis hard minimum position.
 * 
 *   axis.hardMinimumWrite()
 * 
 * Parameters
 *   position: A hard minimum position
 * 
 * Returns
 *   void
 */
bool Axis::hardMinimumWrite(int position) {
  _position_minimum_hard = position;
}

/* hardMaxiumRead
 * 
 * Description
 *   Read axis hard maximum position.
 * 
 *   axis.hardMaxiumRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   position: A hard maximum position
 */
int Axis::hardMaxiumRead() {
  return _position_maximum_hard;
}

/* hardMaximumWrite
 * 
 * Description
 *   Define axis hard maximum position.
 * 
 *   axis.hardMaximumWrite()
 * 
 * Parameters
 *   position: A hard maximum position
 * 
 * Returns
 *   void
 */
bool Axis::hardMaximumWrite(int position) {
  _position_maximum_hard = position;
}

/* softMinimumRead
 * 
 * Description
 *   Read axis soft minimum position.
 * 
 *   axis.softMinimumRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   position: A soft minumum position
 */
int Axis::softMinimumRead() {
  return _position_minimum_soft;
}

/* softMinimumWrite
 * 
 * Description
 *   Define axis soft minimum position.
 * 
 *   axis.softMinimumWrite()
 * 
 * Parameters
 *   position: A soft minimum position
 * 
 * Returns
 *   void
 */
bool Axis::softMinimumWrite(int position) {
  _position_minimum_soft = position;
}

/* softMaxiumRead
 * 
 * Description
 *   Read axis soft maximum position.
 * 
 *   axis.softMaxiumRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: A soft maximum position
 */
int Axis::softMaxiumRead() {
  return _position_maximum_soft;
}

/* softMaximumWrite
 * 
 * Description
 *   Define axis soft maximum position.
 * 
 *   axis.softMaximumWrite()
 * 
 * Parameters
 *   position: A soft maximum position
 * 
 * Returns
 *   void
 */
bool Axis::softMaximumWrite(int position) {
  _position_maximum_soft = position;
}

/* parkRead
 * 
 * Description
 *   Read axis park position.
 * 
 *   axis.parkRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: An axis position used to park
 */
int Axis::parkRead() {
  return _position_park;
}

/* parkWrite
 * 
 * Description
 *   Define axis park position.
 * 
 *   axis.parkWrite()
 * 
 * Parameters
 *   position: An axis position used to park
 * 
 * Returns
 *   void
 */
bool Axis::parkWrite(int position) {
  _position_park = position;
}

/* delayRead
 * 
 * Description
 *   Read axis delay time.
 * 
 *   axis.delayRead()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   int: A delay to axis wait between steps
 */
int Axis::delayRead() {
  return _delay;
}

/* delayWrite
 * 
 * Description
 *   Define a delay time to axis wait between steps.
 * 
 *   axis.delayWrite()
 * 
 * Parameters
 *   delay: delay axis time
 * 
 * Returns
 *   void
 */
bool Axis::delayWrite(int delay) {
  _delay = delay;
}

/* isDone
 * 
 * Description
 *   Check if axis is moving.
 * 
 *   axis.isDone()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   bool: true if axis is stop, false if axis is moving
 */
bool Axis::isDone() {
  if (_position_current == _position_destination) {
    return true;
  }
  else {
    return false;
  }
}

/* status
 * 
 * Description
 *   Detailed axis information.
 * 
 *   axis.status()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   String: axis information
 */
String Axis::status() {
  return ("Axis: " + String(_name) + "\n" +
          "  Electronic pin: " + String(_pin) + "\n" +
          "  Timer: " + String(_timer) + "\n" +
          "  Move delay: " + String(_delay) + "\n" +
          "  Positions:\n" +
          "    Current: " + String(_position_current) + "\n" +
          "    Destination: " + String(_position_destination) + "\n" +
          "    Percent: " + String(100 - (_position_maximum_hard - _position_minimum_hard - _position_current) * 100 / (_position_maximum_hard - _position_minimum_hard)) + "%\n" +
          "    Park: " + String(_position_park) + "\n" +
          "    Hard minimum: " + String(_position_minimum_hard) + "\n" +
          "    Soft minimum: " + String(_position_minimum_soft) + "\n" +
          "    Hard maximum: " + String(_position_maximum_hard) + "\n" +
          "    Soft maximum: " + String(_position_maximum_soft));
}

/* absolute
 * 
 * Description
 *   Changes axis mode to absolute or relative.
 * 
 *   axis.absolute(false)
 * 
 * Parameters
 *   enable: Boolean to define axis mode, absolute or relative.
 * 
 * Returns
 *   boolean: False when absolute mode is disable, True when enable.
 */
bool Axis::absolute(bool enable) {
  return _absolute = enable;
}

/* absoluteRead
 * 
 * Description
 *   Return absolute status.
 * 
 *   axis.absoluteRead()
 * 
 * Parameters
 *   void
 * 
 * Returns
 *   boolean: _abolute variable
 */
bool Axis::absoluteRead() {
  return _absolute;
}
