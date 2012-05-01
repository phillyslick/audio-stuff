/* 1.2 - Caluclate frequency of a MIDI note number 
   Takes command line input!
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char const *argv[])
{
  double semitone_ratio =  pow(2, 1.0/12); /* approx 1.0594631 */
  double c5 = 220.0 * pow(semitone_ratio, 3); // frequency of Middle C
  double c0 = c5 * pow(0.5, 5); // frequency of MIDI note 0

  double frequency = 440.0; //what we want to find
  int midinote; //the note we're given
  
  char message[256]; //char array for input
  
  if(argc != 2)
  {
    printf("%s : converts MIDI note to frequency. \n", argv[0]);
    printf("Usage: %s MIDInote\n", argv[0]);
    printf("Range: 0 <= MIDInote <= 127 \n");
    return 1;
  }  
  

  
  //convert char array to interger
  midinote = atoi(argv[1]);
  if(midinote < 0)
  {
    printf("Sorry - %s is a bad MIDI note number\n",message );
  }
  
  if(midinote > 127)
  {
    printf("Sorry - %s is a out of the MIDI range!\n",message );
  }
  
  
  /* Calculate a frequency for a given note number */
  frequency = c0 * pow(semitone_ratio, midinote);
  printf("frequency of MIDI note %d = %f\n",midinote, frequency);
  return 0;
}