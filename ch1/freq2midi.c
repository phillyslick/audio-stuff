/* 1.2 MOD - Find nearest MIDI note for given frequency in Hz  */

/*
  For more on this check out: http://oakroadsystems.com/math/loglaws.htm  
  LOG RULE:
  log_a(N) = log_b(N) / log_b(a) to find the log of a value to base 'semitone_ratio'.
  
  TODO: Pitchbend INFO!
  "We define pitchbend as a percentage deviation half a semitone above or below a MIDI note."
  "Maximum deviation is therfore + or - 50 percent."
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char const *argv[])
{
  double semitone_ratio =  pow(2, 1/12.0); /* approx 1.0594631 */
  double c5 = 220.0 * pow(semitone_ratio, 3); // frequency of Middle C
  double c0 = c5 * pow(0.5, 5); // frequency of MIDI note 0
  double frequency;
  
  int midinote; //the note we're outputting
  
  if(argc != 2){
    printf("\n %s: Converts a Frequency in hz (440.00) to a corresponding MIDI note. \n",argv[0]);
    printf("If frequency does not correspond exactly with a midi note, pitch bend information is given as well.\n\n");
    printf("Usage: %s FREQUENCY\n\n", argv[0] );
    return 1;
  }
  
  //assign the input to the double frequency
  frequency = atof(argv[1]);
  
  if(frequency < 0){
    printf("Ah, please enter a position frequency!");
  }
  
   /* Calculate a the midi note from the given frequency */
  double frac_midi = log(frequency / c0) / log(semitone_ratio);
  int low_side = (int) floor(frac_midi);
  int high_side = (int) ceil(frac_midi);
  
  
  /*Round frac_midi to the nearest whole number*/
  midinote = (int) (frac_midi + 0.5);
  
  //need to get the low and high side frequency
  
  double low_frequency = c0 * pow(semitone_ratio, low_side);
  double high_frequency = c0 * pow(semitone_ratio, high_side);
  
  //determine pitchbend
  int pitch_bend;
  double difference;
  char* sign;
  
  if(low_side == midinote)
  {
    difference = frequency - low_frequency;
    sign = "+";
  }  
  else
  {
    difference = high_frequency - frequency;
    sign = "-";
  }
  difference = difference / (high_frequency - low_frequency);
  pitch_bend = (int) (difference * 100 + 0.5);
  
  printf("The nearest midinote to the frequency %f is %d\n", frequency, midinote);
  
  printf("The pitch bend = %s%d%%\n", sign,pitch_bend );
  return 0;
}