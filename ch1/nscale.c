/* nScale = Constructs a scale (displays est. frequencies)
   divided into n semitones
   based on user input and starting MIDInote.*/

#include <stdio.h>
#include <math.h>

int main (int argc, char const *argv[])
{
  int i, notes, midinote;
  double frequency, ratio;
  double c0, c5;
  double frequencies[24];
   
  if(argc != 3)
  {
    printf("Usage: %s no_of_notes midinote\n", argv[0]);
    return 1;
  }
  
  //tests on input
  notes = atoi(argv[1]); //the number of notes
  if(notes < 1)
  {
    printf("Error: Notes Must Be Positive! \n");
    return;
  }
  
  if(notes > 24)
  {
    printf("Sorry, maximum number of notes is 24.\n");
    return 1;
  }
  
  midinote = atoi(argv[2]); // the midiNote input
  
  if(midinote < 0 || midinote > 127)  
  {
    printf("MIDI note range is 0 - 127!\n");
    return 1;
  }
    
  ratio = pow(2.0, 1.0/12.0); /* approx 1.0594631 */
  c5 = 220.0 * pow(ratio, 3); // frequency of Middle C
  c0 = c5 * pow(0.5, 5); // frequency of MIDI note 0
  frequency = c0 * pow(ratio, midinote); // starting frequency of user defined scale
  
  //recalculate ratio based on the input
  ratio = pow(2.0, 1.0/notes);
  
  // use ratio to get each frequency in scale
  for(i = 0; i < notes; ++i)
  {
    frequencies[i] = frequency;
    frequency *= ratio;
  }
  
  for(i = 0; i < notes; ++i)
  {
    printf("%f\n", frequencies[i]);
  }
  return 0;
}