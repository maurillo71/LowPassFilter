/* Lowpass filter using integer calculation (FAST) */

int * LPfilter(int iInput)
{
  /* K_FACTOR is a division shift right instead of a regular division for highspeed */
  /*
  If iFilterReg is a 15 bit integer,the input can max be iInput / (K_FACTOR * 2).
  Example: K_FACTOR = 2. +/-32767 / (2 * 2) = +/-8191.
  */

  static int iaFilterData[4]; // Static filter Data
  static int iaFilterReg[4]; // Static filter Register
  static unsigned char ucOrder; // Order of Filter

  iaFilterData[0] = iInput;

  /* Make order of filters */
  for (ucOrder = 1; ucOrder <= 3; ucOrder++) {
    iaFilterReg[ucOrder] = iaFilterReg[ucOrder] - (iaFilterReg[ucOrder] >> K_FACTOR) + iaFilterData[ucOrder - 1];
    iaFilterData[ucOrder] = (iaFilterReg[ucOrder] >> K_FACTOR);
  }

  /* Highpass filter calculated on lowpass 3th order filter data */
  iaFilterData[0] = iInput - iaFilterData[3];

  /* Return pointer to filter data array */
  return iaFilterData;
} 
