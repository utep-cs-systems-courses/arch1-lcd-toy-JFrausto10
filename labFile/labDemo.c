#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "led.h"

#define LED_RED BIT6             // P1.6


short redrawScreen = 1;
u_int backroundColor = COLOR_BLACK;

void auto_backround_color(char posTracker)
{
  switch(posTracker){
    case 0:
      backroundColor = COLOR_BLACK;
      break;
    case 5:
      backroundColor = COLOR_RAZZLE_DAZZLE;
      break;
    case 10:
      backroundColor = COLOR_GOLD;
      break;
    case 15:
      backroundColor = COLOR_AQUAMARINE;
      break;
    default:
      break;
  }
}

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount == 100) {
    secCount = 0;
    //backroundColor = (backroundColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
    clearScreen(backroundColor);
  }
}

void main()
{
  P1DIR |= LED_RED;/**< red led on when CPU on */
  P1OUT |= LED_RED;
  configureClocks();
  lcd_init();
  led_init();
  switch_init();

  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);                 /**< GIE (enable interrupts) */

  static char posTracker = 0;

  clearScreen(COLOR_BLACK);
  while (1) {
    if (redrawScreen) {
      redrawScreen = 0;
      drawString11x16(20,20,"Lab 3",COLOR_GREEN, backroundColor);
      if(switch_state_down1){
	if(posTracker<20){
	  fillFlagPole(20+posTracker,45);
	  posTracker++;
	}
	else{
	  fillFlagPole(20,45);
	  posTracker = 0;
	}
      }
    }
    auto_backround_color(posTracker);
    P1OUT &= ~LED_RED;/* green off */
    or_sr(0x10);/**< CPU OFF */
    P1OUT |= LED_RED;/* green on */
  }
}
