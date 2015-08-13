# Quirky_Challenge_Question

The final challenge question asked in the interview process for EE
Summer Firmware Engineer Intern position. The prompt is as follows:

/*
Function should parse a hex string, and turn it into an array
of 8-bit integers.
In: a null-terminated string of valid hex digits, that will be up
to 64 hex characters long.
out: an array of 8-bit integers, each representing 2 characters of hex
data. Should be at least half the length of the incoming
string.
*/
void hex_to_bytearray(const char* hex_in, uint8_t* int_out);
/*
Function should return a pointer to an array of 4, 8-bit integers
corresponding to the values contained in the incoming 32-bit int.
example: input is 0x12345678, output should be a pointer to {0x12,
0x34, 0x56, 0x78}
If possible, a typedef or a #define should be used instead of a
function call.
*/
uint8_t* int_to_array(uint32_t big_int);
