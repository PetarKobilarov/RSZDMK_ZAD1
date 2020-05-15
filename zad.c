#include <LiquidCrystal.h>
#include <util/delay.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

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

void kontrola_kursora(char pov_Simb[4])
{
	lcd.cursor();
	lcd.setCursor(0, 0);
	//char taster = 0;
	int h = 0, v = 0, i;//horizontalno, vrednost
	char simbol[4] = {'P', 'K', 'H', 'T'}, pom[4];
	
	do
	{
		switch (ocitaj_taster())
		{
			case '2':
				if (v == 3)
				{
					v = 0;
					lcd.setCursor(h, 0);
					lcd.write(simbol[v]);
					lcd.setCursor(h, 0);
                  	pom[h] = simbol[v];
					_delay_ms(100);
					//lcd.setCursor(h, v);
				}else
				{
					v++;
					lcd.setCursor(h, 0);
					lcd.write(simbol[v]);
					lcd.setCursor(h, 0);
                 	pom[h] = simbol[v];
					_delay_ms(100);
				}
				break;
				
			case '8':
				if (v == 0)
				{
					v = 3;
					lcd.setCursor(h, 0);
					lcd.write(simbol[v]);
					lcd.setCursor(h, 0);
                  	pom[h] = simbol[v];
					_delay_ms(100);
				}else
				{
					v--;
					lcd.setCursor(h, 0);
					lcd.write(simbol[v]);
					lcd.setCursor(h, 0);
                  	pom[h] = simbol[v];
					_delay_ms(100);
				}
				break;
				
			case '4':
				if (h == 0)
				{
					h = 3;
					lcd.setCursor(h, 0);
					_delay_ms(100);
				}else
				{
					h--;
					lcd.setCursor(h, 0);
					_delay_ms(100);
				}
				break;
				
			case '6':
				if (h == 3)
				{
					h = 0;
					lcd.setCursor(h, 0);
					_delay_ms(100);
				}else
				{
					h++;
					lcd.setCursor(h, 0);
					_delay_ms(100);
				}
				break;
		}
	}while (ocitaj_taster() != '5');
	
	for(i = 0; i < 4; i++)
		pov_Simb[i] = pom[i];
	
}

int main()
{
	lcd.begin(16, 2);
	
	char taster = 0, rez;
	char poc_Simb[4], pov_Simb[4];
	int i, pom;
	uint32_t seed = 0;
	
	while (1)
	{
		
		while (ocitaj_taster() != '*')
		{
			seed++; 
			randomSeed(seed);
		}
		
		for (i = 0; i < 4; i++)
		{
			pom = rand() % 4;
			switch (pom)
			{
				case 0:
					poc_Simb[i] = 'P';	break;
				
				case 1:
					poc_Simb[i] = 'K';	break;
					
				case 2:
					poc_Simb[i] = 'H';	break;
					
				case 3:
					poc_Simb[i] = 'T';	break;
			}
		}
		
		lcd.clear();
		rez = 'D';
		
		lcd.noCursor();
		lcd.setCursor(0, 0);
		lcd.write('P');
		lcd.setCursor(1, 0);
		lcd.write('K');
		lcd.setCursor(2, 0);
		lcd.write('H');
		lcd.setCursor(3, 0);
		lcd.write('T');
		_delay_ms(2000);
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.write('-');
		lcd.setCursor(1, 0);
		lcd.write('-');
		lcd.setCursor(2, 0);
		lcd.write('-');
		lcd.setCursor(3, 0);
		lcd.write('-');
		
		kontrola_kursora(pov_Simb);
		
		for (i = 0; i < 4; i++)
		{
			if (poc_Simb[i] != 	pov_Simb[i])
				rez = 'N';
		}
		
		for (i = 0; i < 4; i++)
		{
			lcd.setCursor(i, 1);
			lcd.write(poc_Simb[i]);
		}
		
		lcd.setCursor(15, 1);
		lcd.write(rez);
	}
	
	return 0;
}