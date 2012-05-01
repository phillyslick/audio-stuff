#include <stdio.h>
#include <stdlib.h>

class Dodecaphonic {
  protected:
    int series[12]; // the tone row, hidden from outside
    
    // modulus as in internal method
    int mod12(int note){
      while (note >= 12) note -= 12;
      while (note < 0) note += 12;
      return note;
    }
  
  public:
    Dodecaphonic() { // default constructor
      for(int i = 0; i < 12; ++i) series[i] = 0;
    }
    
    Dodecaphonic(int *notes) { // constuctor from an array
      for(int i = 0; i < 12; ++i) series[i] = mod12(notes[i]);
    }
    
    // get and set notes
    int get(int index){
      return series[mod12(index)];
    }
    
    void set(int note, int index){
      series[mod12(index)] = mod12(note);
    }
    
    // three base operations
    Dodecaphonic transpose(int interval);
    Dodecaphonic invert();
    Dodecaphonic retrograde();
};

/*So Now, We can define the above base operations from outside the class (we could have done it inside as well)
  All of them return a Dodecaphonic */

Dodecaphonic Dodecaphonic::transpose(int interval){
  Dodecaphonic transp;
  for(int i=0; i < 12; ++i) transp.set(mod12(series[i] + interval), i);
  return transp;
}

Dodecaphonic Dodecaphonic::invert(){
  Dodecaphonic inv;
  inv.set(series[0],0);
  for(int i=1; i < 12; ++i) inv.set(mod12(inv.get(i-1) + series[i-1] - series[i]), i);
  return inv;
}

Dodecaphonic Dodecaphonic::retrograde(){
  Dodecaphonic retr;
  for(int i=0; i < 12; ++i) retr.set(series[i], 11-i);
  return retr;
}

int main (int argc, char const *argv[])
{
  Dodecaphonic row, res;
  int interval, n;
  
  if(argc != 14 || argv[1][0] != '-')
  {
    printf("usage: %s [-oN | -rN | -iN | -irN] " "note1 note2 ... note12\n", argv[0]);
    return -1;
  }
  
  /* Initialize the row object */
  for(n = 0; n < 12; ++n)
  {
    row.set(atoi(argv[n+2]), n);
  }
  
  switch(argv[1][1]){
     // original transposed
    case 'o':
      interval = atoi(argv[1]+2);
      res = row.transpose(interval);
      break;
      
      // retrograde
    case 'r': 
      interval = atoi(argv[1]+2);
      res = row.retrograde().transpose(interval);
      break;
      
      // inverted
    case 'i': 
      if(argv[1][2] != 'r')
      {
        interval = atoi(argv[1] + 2);
        res = row.invert().retrograde().transpose(interval);
      }
      // inverted retrograde
      else{ 
        interval = atoi(argv[1] + 3);
        res = row.invert().retrograde().transpose(interval);
      }
      break;
    
    default:
      printf("unrecognized option \n");
      return -1;
  }
  for(n=0; n<12; ++n) printf("%d ", res.get(n));
  printf("\n");
  return 0;

}