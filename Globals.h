#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

//Yes, I know... but they are const and clearly labeled. So, please bear with me...
const unsigned char OPTION1_FLAG = 0b0000'0001; // holidays
const unsigned char OPTION2_FLAG = 0b0000'0010; // days off
const unsigned char OPTION3_FLAG = 0b0000'0100; // potential forces
const unsigned char OPTION4_FLAG = 0b0000'1000; // long weeks
const unsigned char OPTION5_FLAG = 0b0001'0000; // saved day1
const unsigned char OPTION6_FLAG = 0b0010'0000; // saved day2
const unsigned char OPTION7_FLAG = 0b0100'0000; // tbd
const unsigned char OPTION8_FLAG = 0b1000'0000; // tbd


#endif