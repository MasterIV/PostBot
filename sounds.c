void sounds() {
	// do something here
}

void pewpew() {
  NR52_REG = 0x80; //Master control and status flags
  NR51_REG = 0x11; //Sound Output terminal select (1: enabled; 0: disabled)
  NR50_REG = 0x77; //Vin (input line on cart connector) / Main Output Volume 

  NR10_REG = 0x1E; //$FF10 -- $FF14: Channel 1, Referred to as NR10-NR14
  NR11_REG = 0x10;
  NR12_REG = 0xF3;
  NR13_REG = 0x00;
  NR14_REG = 0x87;
}
