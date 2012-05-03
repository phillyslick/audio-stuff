/* iscale = Constructs a scale from user specifed options:
   a starting note based on a frequency or a MIDI note,
   the definition of each scale: how many semitones make up the scale.
   Outputs either frequencies (default), or the interval ration as well as the frequencies*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char const *argv[])
{
  int i, notes, midinote;
  int is_midi = 0;
  int write_interval = 0;
  int err = 0;
  double start_value, base_frequency, ratio;
  double c0, c5;
  double frequencies[25];
  FILE* fp;
     
  /*To Parse the Input We Need 3 Steps:
    1.  Handle Flag Arguments 
    2.  Check that we have at least two remaining arguments
    3.  If we have a fourth argument (the output file), process that as well.
  */
  
  //handle flag arguments
  while(argc > 1){
    if(argv[1][0] == '-')
    {
      if(argv[1][1] == 'm')
      {
        is_midi = 1;
      }
      else if(argv[1][1] == 'i')
      {
        write_interval = 1;
      }
      else{
        printf("Unrecognized option: %s\n", argv[1]);
        return 1;
      }
      //since argc and argv are pointers, we can increment the position in the char array
      argc--;
      argv++;
      
    }
    else{
      break;
    }
  }
  
  //if there aren't three arguments left
  if(argc < 3)
  {
    printf("Usage: %s [-m] [-i] no_of_notes start_value [outfile.txt]\n\n", argv[0]);
    printf("-m: interprets starting_point as a MIDI note\n");
    printf("(default is a frequency in hz)\n\n");
    printf("-i: prints interval ratios in addtion to frequencies.\n");
    printf("(default is just the frequency values.)\n");
    printf("outfile.txt: name of (optional) file to write output to. \n\n");
    return 1;
  }
  
  //now let's actually process the arguments and make sure they're valid

  
  notes = atoi(argv[1]); //the number of notes
  if(notes < 1 || notes > 24)
  {
    printf("%d",notes);
    printf("Error: Number of Notes must be between 1-24 \n");
    return 1;
  }
  
 
  start_value = atof(argv[2]); // the start_value input
  printf("start_value: %f\n", start_value);
  if (is_midi == 1){
    printf("start_value: %f\n", start_value);
    //process start value as midi
    if(start_value < 0 || start_value > 127)  
    {
      printf("MIDI note range is 0 - 127!\n");
      return 1;
    }
    
  }
  else{
    //process start value as frequency
    if(start_value <= 0.00){
      printf("Error, frequency start value must be greater than 0.0 hz!\n");
      return 1;
    }
  }
  
  /*Now, let's check for the optional filename*/
  fp = NULL;
  if(argc == 4)
  {
    //this means we've got a filename!
    fp = fopen(argv[3], "w");
    if(fp == NULL)
    {
      printf("WARNING: unable to create file %s\n", argv[3]);
      perror(""); //a C function that deals with file errors.
    }
  }
  
  /*Okay!  All params ready, let's fill the array and write to the screen/file*/
  
  //calculate base_frequency based on MIDI
  if(is_midi == 1)
  {
    ratio = pow(2.0, 1.0/12.0); /* approx 1.0594631 */
    c5 = 220.0 * pow(ratio, 3); // frequency of Middle C
    c0 = c5 * pow(0.5, 5); // frequency of MIDI note 0
    base_frequency = c0 * pow(ratio, start_value); // starting frequency of user defined scale
  }
  else{
  //the frequency is just the input
    base_frequency = start_value;
  }

  
  //recalculate ratio based on the input
  ratio = pow(2.0, 1.0/notes);
  
  // use ratio to get each frequency in scale
  for(i = 0; i < notes; ++i)
  {
    frequencies[i] = base_frequency;
    base_frequency *= ratio;
  }
  
  //finally - ready array, write to screen, and optionally to file
  
  for(i = 0; i < notes; ++i)
  {
    if(write_interval == 1)
    {
      //then we need to print the interval as well
      printf("%d:\t%f\t%f\n",i, pow(ratio,i), frequencies[i]);
    }
    else
    {
      printf("%d:\t%f\n",i, frequencies[i]);
    }
    //now if we need to print to a file, do it
    if(fp)
    {
      //if we're writing the interval..
      if(write_interval == 1)
      {
        //then we need to print the interval as well
         err = fprintf(fp,"%d:\t%f\t%f\n",i, pow(ratio,i), frequencies[i]);
      }
      else{
        err = fprintf(fp,"%d:\t%f\n",i, frequencies[i]);
      }
      if (err < 0){
        break;
      }
    }
  }
  
  if(err < 0)
  {
    perror("There was an error writing the file.\n");
  }
  if(fp){
    fclose(fp);
  }
  
  return 0;
}