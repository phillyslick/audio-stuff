#include <stdio.h>

int name_to_pitch_class(char name){
  switch(name){ //translating from note name to pitch class
    case 'C': case 'c':
    return 0;
    
    case 'D': case 'd':
    return 2;
    
    case 'E': case 'e':
    return 4;
    
    case 'F': case 'f':
    return 5;
    
    case 'G': case 'g':
    return 7;
    
    case 'A': case 'a':
    return 9;
    
    case 'B': case 'b':
    return 11;
    
    default:
    return 100; //error code
  }
}

int main (int argc, char const *argv[])
{
  char note1,note2, dummy;
  int interval; 
  
  printf("Please enter two natural notes.\nfirst note: ");
  scanf("%c%c", &note1, &dummy);
  printf("second note: ");
  scanf("%c", &note2);
  
  // we'll call name_to_pitch_class() to calculate the intervals and translate
  interval = name_to_pitch_class(note2) - name_to_pitch_class(note1);
  if(interval > 20 || interval < -11)
  {
    printf("Either %c or %c are invalid notes\n", note1, note2);
    return 1;
  }
  if (interval < 0) interval += 12;
  else if (interval > 11) interval -= 12;
  
  /*Print the number of semitones.  We've got to
  handle the special case of unison (0) as well! */
  
    printf("%d semitones up or %d semitones down\n", interval, interval ? 12-interval : 0);
    
    switch(interval){
      case 1:
      printf("minor 2nd up or major 7th down\n");
      break;
      
      case 2:
      printf("major 2nd up or minor 7th down\n");
      break;
      
      case 3:
      printf("minor 3rd up or major 6th down\n");
      break;
      
      case 4:
      printf("major 3rd up or minor 6th down\n");
      break;
      
      case 5:
      printf("perfect 4th up or perfect 5th down\n");
      break;
      
      case 6:
      printf("augmented 4th \n");
      break;
      
      case 7:
      printf("perfect 5th up or perfect 4th down\n");
      break;
      
      case 8:
      printf("minor 6th up or major 3rd down\n");
      break;
      
      case 9:
      printf("major 6th up or minor 3rd down\n");
      break;
      
      case 10:
      printf("minor 7th up or major 2nd down\n");
      break;
      
      case 11:
      printf("major 7th up or minor 2nd down\n");
      break;
      
      default:
      printf("unison \n");
    }

  return 0;
}