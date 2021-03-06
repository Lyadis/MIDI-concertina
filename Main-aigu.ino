
/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Tone

 */
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
// notes in the melody:

void setup() {
      // Configuration de la broche 12 en tant qu'entree numerique.
    MIDI.begin(1);
    
    Serial.begin(115200);
    
    pinMode(2,INPUT);
    digitalWrite(2,HIGH);
    pinMode(3,INPUT);
    digitalWrite(3,HIGH);
    pinMode(4,INPUT);
    digitalWrite(4,HIGH);
    pinMode(5,INPUT);
    digitalWrite(5,HIGH);
    pinMode(6,INPUT);
    digitalWrite(6,HIGH);
    pinMode(7,INPUT);
    digitalWrite(7,HIGH);
    pinMode(8,INPUT);
    digitalWrite(8,HIGH);
    pinMode(9,INPUT);
    digitalWrite(9,HIGH);
    pinMode(10,INPUT);
    digitalWrite(10,HIGH);
    pinMode(13,INPUT);
    digitalWrite(13,HIGH);
    pinMode(11,INPUT);
    digitalWrite(11,HIGH);
    pinMode(12,INPUT);
    digitalWrite(12,HIGH);
    pinMode(A0,INPUT);
    digitalWrite(A0,HIGH);
    pinMode(A1,INPUT);
    digitalWrite(A1,HIGH);
    pinMode(A2,INPUT);
    digitalWrite(A2,HIGH);
    pinMode(A3,INPUT);
    digitalWrite(A3,HIGH);
    pinMode(A4,INPUT);
    digitalWrite(A4,HIGH);
    pinMode(A5,INPUT);
    digitalWrite(A5,HIGH);
    //  Set MIDI baud rate:

}
int oldStatePousser[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int oldStateTirer[] =   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void note(int bouton, int sens_soufflet, int noteA, int noteB, int index, int octave){//, int oldStatePousser, int oldStateTirer
    int velocity = 100;//velocity of MIDI notes, must be between 0 and 127
    //higher velocity usually makes MIDI instruments louder
    if ( bouton == LOW ) {
      if(sens_soufflet == LOW ){
        // on pousse sur le bouton et sur le soufflet
        if(oldStatePousser[index] == 0){
          MIDI.sendNoteOn(noteA + octave ,velocity,1);
          oldStatePousser[index] = 1;
           if( oldStateTirer[index] == 1){
           MIDI.sendNoteOff(noteB + octave ,0,1);
           oldStateTirer[index] = 0;
        }
          
        }
      }else{
        // on tire sur le soufflet et on appuie sur le bouton
        if(oldStateTirer[index] == 0){
          MIDI.sendNoteOn(noteB + octave,velocity,1);
          oldStateTirer[index] = 1;
          if(oldStatePousser[index] == 1){
            MIDI.sendNoteOff(noteA + octave,0,1);   
            oldStatePousser[index] = 0;
         }
        }
      }
    }else{
        if(oldStatePousser[index] == 1){
            MIDI.sendNoteOff(noteA + octave,0,1);   
            oldStatePousser[index] = 0;
         }
         if( oldStateTirer[index] == 1){
        // on appuie pas sur le bouton ma
           MIDI.sendNoteOff( noteB + octave,0,1);
           oldStateTirer[index] = 0;
        }
  }
} 

//main droite
//
// {23,26,31,25,38,12,19,24,28,31,16,21,25,33,32}
// {26,30,33,36,40,19,23,26,29,33,17,22,27,31,34}
//
// main gauche
//
// {43, 47, 50, 55, 59,  36, 40, 43, 48, 52, 37, 45, 44, 49, 53 }
// {42, 45, 48, 52, 54,  35, 38, 41, 45, 47, 39, 43, 46, 51, 57 }     

void loop() {
        int etatButton[]= {digitalRead(2),digitalRead(3), digitalRead(4),digitalRead(5),digitalRead(6), digitalRead(7),digitalRead(8), digitalRead(9), digitalRead(10), digitalRead(11), digitalRead(12), digitalRead(A0), digitalRead(A1), digitalRead(A2), digitalRead(A3)};

        int pousser[] ={43, 47, 50, 55, 59,  36, 40, 43, 48, 52, 37, 45, 44, 49, 53 };
        int tirer[]   = {42, 45, 48, 52, 54,  35, 38, 41, 45, 47, 39, 43, 46, 51, 57 };
        
        int poussertirer = digitalRead(A4);
        int pushed = 0;
        
        //velocity of MIDI notes, must be between 0 and 127
        //higher velocity usually makes MIDI instruments louder
        for (int i=0; i < 15; i++){
          note( etatButton[i],poussertirer, pousser[i], tirer[i],i,2*12);//,oldStatePousser[i],oldStateTirer[i]
        } // fin de la boucle for
}
