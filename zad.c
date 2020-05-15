#include <LiquidCrystal.h>
#include <util/delay.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

//char pik[3] = {0x6, 0x16, 0x6};


char ocitaj_taster()
{
  char taster = 0;
  unsigned char row;
  
  MCUCR &= ~0x10;
  PORTD = 0x0f; 
  
  for(row = 0x80; row != 0x08; row >>= 1)
  {
    DDRD = row;
	_delay_ms(2);
    
    switch(row | ((~PIND) & 0x0f))
    {
      case 0x88:
      	taster = '1'; break;
      case 0x84:
      	taster = '2'; break;
      case 0x82:
      	taster = '3'; break;
      case 0x81:
      	taster = 'A'; break;
		
	  case 0x48:
      	taster = '4'; break;
      case 0x44:
      	taster = '5'; break;
      case 0x42:
      	taster = '6'; break;
      case 0x41:
      	taster = 'B'; break;
		
	  case 0x28:
      	taster = '7'; break;
      case 0x24:
      	taster = '8'; break;
      case 0x22:
      	taster = '9'; break;
      case 0x21:
      	taster = 'C'; break;
		
	  case 0x18:
      	taster = '*'; break;
      case 0x14:
      	taster = '0'; break;
      case 0x12:
      	taster = '#'; break;
      case 0x11:
      	taster = 'D'; break;
    }
  }
  
  return taster;
}

void kontrola_kursora()
{
	lcd.cursor();
	lcd.setCursor(0, 0);
	//char taster = 0;
	int h = 0, v = 0;//horizontalno, vrednost
	char simbol[4] = {'P', 'K', 'H', 'T'};
	
	do
	{
		
	}while (ocitaj_taster() != '5');
	
}

int main()
{
	lcd.begin(16, 2);
	//srand(time(NULL));
	
	char taster = 0;
	
	while (1)
	{
		lcd.noCursor();
		//lcd.createChar(0, pik);
		while (ocitaj_taster() != '*');
		
		lcd.setCursor(0, 0);//skroz levo
		//lcd.write(rand(3));
		lcd.write('P');
		lcd.setCursor(1, 0);
		lcd.write('K');
		lcd.setCursor(2, 0);
		lcd.write('H');
		lcd.setCursor(3, 0);
		lcd.write('T');
		//_delay_ms(2000);
		_delay_ms(500);
		lcd.clear();
		lcd.setCursor(0, 0);//skroz levo
		lcd.write('-');
		lcd.setCursor(1, 0);
		lcd.write('-');
		lcd.setCursor(2, 0);
		lcd.write('-');
		lcd.setCursor(3, 0);
		lcd.write('-');
		
		kontrola_kursora();
		
		lcd.clear();
		lcd.print("ok");
		
		
	}
	
	return 0;
}