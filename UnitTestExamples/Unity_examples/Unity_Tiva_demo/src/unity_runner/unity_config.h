#pragma once

/**
 * Prototype is defined for being used in subsequent #define
 */
void SendChar(char a);

/**
 * Define the function which outputs a character
 */
#define UNITY_OUTPUT_CHAR(a) (void)SendChar(a)
