//set a certain bit to one
#define Set_bit(Reg,bit) {Reg|=(1<<bit);}

//set a certain bit to zero
#define Clear_bit(Reg,bit) {Reg &= ~(1<<bit);}

//retrieve bit
#define Get_Bit(Reg,bit) ((Reg >> bit) & 1)

//toggle a certain bit
#define Toggle_Bit(Reg,bit) {Reg^= (1<<bit);}