//
// 7-segment digit data
//
//  +---a---+
//  |       |
//  f       b
//  |       |
//  +---g---+
//  |       |
//  e       c
//  |       |
//  +---d---+
//

// 7-bit binary values for segments abcdefg (a=bit 7, g=bit 0)
// values 0-f encoded for completeness
static unsigned char sec7dat[] = {
  0b1111110,			/* digit 0 */
  0b0110000,			/* digit 1 */
  0b1101101,			/* digit 2 */
  0b1111001,			/* digit 3 */
  0b0110011,			/* digit 4 */
  0b1011011,			/* digit 5 */
  0b1011111,			/* digit 6 */
  0b1110000,			/* digit 7 */
  0b1111111,			/* digit 8 */
  0b1111011,			/* digit 9 */
  0b1110111,			/* digit A */
  0b0011111,			/* digit b */
  0b1001110,			/* digit C */
  0b0111101,			/* digit d */
  0b1001111,			/* digit E */
  0b1000111			/* digit F*/
};
