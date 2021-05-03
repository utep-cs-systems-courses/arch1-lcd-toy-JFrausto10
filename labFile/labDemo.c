#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount == 25) {
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
    clearScreen(COLOR_BLACK);
  }
}

void main()
{
  P1DIR |= LED_GREEN;/**< Green led on when CPU on */
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();

  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);                 /**< GIE (enable interrupts) */

  static char posTracker = 0;

  clearScreen(COLOR_BLACK);
  while (1) {/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      drawString11x16(20,20,"hello",COLOR_GREEN,COLOR_RED);
      if(posTracker<=20){
	fillFlagPole(20+posTracker,45);
	posTracker++;
      }
      else{
	fillFlagPole(20,45);
	posTracker = 0;
      }
    }
    P1OUT &= ~LED_GREEN;/* green off */
    or_sr(0x10);/**< CPU OFF */
    P1OUT |= LED_GREEN;/* green on */
  }
}
