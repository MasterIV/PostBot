#include "music.c"

int exit_music;

void setNote(Note *n){
    switch((*n).i){
            case MELODY:
                    NR10_REG = 0x00U; //pitch sweep
                    NR11_REG = 0x84U; //wave duty
                    NR12_REG = (*n).env; //envelope
                    NR13_REG = (UBYTE)frequencies[(*n).p]; //low bits of frequency
                    NR14_REG = 0x80U | ((UWORD)frequencies[(*n).p]>>8); //high bits of frequency (and sound reset)
            break;
            case HARMONY:
                    NR10_REG = 0x00U;
                    NR11_REG = 0x00U; //wave duty for harmony is different
                    NR12_REG = (*n).env;
                    NR13_REG = (UBYTE)frequencies[(*n).p];
                    NR14_REG = 0x80U | ((UWORD)frequencies[(*n).p]>>8);
            break;
            case SNARE:
                    NR21_REG = 0x00U;
                    NR22_REG = (*n).env;
                    NR23_REG = (UBYTE)frequencies[(*n).p];
                    NR24_REG = 0x80U | ((UWORD)frequencies[(*n).p]>>8);
                    NR51_REG |= 0x22;
            break;
            case WAVE:

            break;
            case CYMBAL:
                NR41_REG = 30;
                NR42_REG = 55;     
                NR43_REG = 50;         
                NR44_REG = 0xC0U;
                NR51_REG |= 0x88;
            break;
    }
}

void init_sounds() {
  //NR52_REG = 0x80; //Master control and status flags
  //NR51_REG = 0x11; //Sound Output terminal select (1: enabled; 0: disabled)
  //NR50_REG = 0x77; //Vin (input line on cart connector) / Main Output Volume 
  
    NR52_REG = 0xFFU;
    NR51_REG = 0x00U;
    NR50_REG = 0x77U;
}

void play_gameplay_music(){
    //if (muteChannel1 == 0)
    //    setNote(&song_gameplay_ch1[currentBeat]);
  
    //setNote(&song_gameplay_ch2[currentBeat]);
  
    //if (muteChannel4 == 0)
    //    setNote(&song_gameplay_ch4[currentBeat]);
  
  setNote(&game_ch1[currentBeat]);
  setNote(&game_ch2[currentBeat]);
  
  NR51_REG |= 0x11U;
}

void play_jingle() {
  setNote(&jingle[0]);
  NR51_REG |= 0x11U;
  delay(400);
  setNote(&jingle[1]);
  NR51_REG |= 0x11U;
  delay(400);
  setNote(&jingle[2]);
  NR51_REG |= 0x11U;
}

void update_music(){
    if (timerCounter >= 14){
            timerCounter = 0;
	  
            if (currentBeat < 15) //song length - 1
            {
                currentBeat++;
            }
            else
            {
                currentBeat = 0;
            }
	  
            play_gameplay_music();
    }
  
    timerCounter++;
  
    /*if (muteChannel1 != 0)
    {
        muteChannel1++;
	  
        if (muteChannel1 > 10)
            muteChannel1 = 0;
    }
    if (muteChannel4 != 0)
    {
        muteChannel4++;
        if (muteChannel4 > 10)
            muteChannel4 = 0;
    }*/
}

///

void pewpew() {
  NR10_REG = 0x1E; //$FF10 -- $FF14: Channel 1, Referred to as NR10-NR14
  NR11_REG = 0x10;
  NR12_REG = 0xF3;
  NR13_REG = 0x00;
  NR14_REG = 0x87;
}

void walk_sound() {
 int length;
int envinit;
int envmode;
int envsteps;
int polyfreq;
int polystep;
int polydiv;
int consecutive;
int initialflag;

length = 2; /* 0 - 63 */
envinit = 15; /* 0 - 15 */
envsteps = 1; /* 0 - 7 */
envmode = 0; /* 0 = decrease 1 = increase */
polyfreq = 4; /* 0 - 7 */
polystep = 0; /* 0 - 1 */
polydiv = 5; /* 0 - 7 */
consecutive = 0; /* 0 - 1 */
initialflag = 1; /* 0 - 1 */

  NR41_REG = length;
  NR42_REG = (envsteps + (envmode * 8) + (envinit * 16));
  NR43_REG = (polydiv + (polystep * 8) + (polyfreq * 16));
  NR44_REG = (consecutive * 64) + 128;
}

void error_sound()
{
	int sweeptime;
	int sweepmode;
	int sweepshifts;
	int patternduty;
	int soundlength;
	int envinit;
	int envmode;
	int envsteps;
	unsigned int freql;
	int freqh;
	int consecutive;
	int initialflag;

	sweeptime = 7; /* 0-7 */
	sweepmode = 1; /* 0-1 */
	sweepshifts = 1; /* 0 - 7 */
	patternduty = 1; /* 0-3 */
	soundlength = 0; /* 0 - 63 */
	envinit = 15; /* 0 - 15 */
	envmode = 0; /* 0-1 */
	envsteps = 2; /* 0 - 7 */
  
	freql = 000;
	freqh = 5;
	consecutive = 0;
	initialflag = 1;

	NR10_REG = (sweepshifts + (sweepmode * 8) + (sweeptime * 16));
	NR11_REG = (soundlength + (patternduty * 32));
	NR12_REG = (envsteps + (envmode * 8) + (envinit * 16));
	NR13_REG = freql;
	NR14_REG = (freqh + (consecutive * 64) + (initialflag * 128));

	delay(100);

	sweeptime = 7; /* 0-7 */
	sweepmode = 1; /* 0-1 */
	sweepshifts = 2; /* 0 - 7 */
	patternduty = 3; /* 0-3 */
	soundlength = 0; /* 0 - 63 */
	envinit = 15; /* 0 - 15 */
	envmode = 0; /* 0-1 */
	envsteps = 2; /* 0 - 7 */

	freql = 000;
	freqh = 4;
	consecutive = 0;
	initialflag = 1;

	NR10_REG = (sweepshifts + (sweepmode * 8) + (sweeptime * 16));
	NR11_REG = (soundlength + (patternduty * 32));
	NR12_REG = (envsteps + (envmode * 8) + (envinit * 16));
	NR13_REG = freql;
	NR14_REG = (freqh + (consecutive * 64) + (initialflag * 128));
}
