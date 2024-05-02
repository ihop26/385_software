#include "shop_text.h"

unsigned char bottom_text[5][51] = 
{
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0",
"|                                                |\0",
"|                                                |\0",
"|                                                |\0",
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0"
};
unsigned char menu_text[30][31] =
{"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0",
 "           - MENU -           \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0"};

 unsigned char controls_text[30][31] =
{"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0",
 "         - CONTROLS -         \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0"};

 unsigned char shop_menu_text[30][31] =
{"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0",
 "     -  SHOP CATEGORIES  -    \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0"};

  unsigned char shop_text[30][31] =
{"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0",
 "           - SHOP -           \0",
 "                              \0",
 "    (ABSOLUTELY NO REFUNDS)   \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "                              \0",
 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0"};


  unsigned char menu_items [2][31] = 
  {
    "        Shop                  \0",
    "      Controls                \0"
  };

  unsigned char shop_menu_items[4][31] =
{"   CONVEYORS                 \0",
 "   UPGRADERS                 \0",
 "   FURNACES                  \0",
 "   MINES                     \0"};


unsigned char shop_items [4][8][31] =
{
    {"1SS                           \0",
     "2CS                           \0",
     "3CF                           \0",
     "4SF                           \0",
     "5LA                           \0",
     "6WM                           \0",
     "7FM                           \0",
     "8FLA                          \0"},
    {"1u                            \0",
     "2u                            \0",
     "3u                            \0",
     "4u                            \0",
     "5u                            \0",
     "6u                            \0",
     "7u                            \0",
     "8u                            \0"},
    {"1f                            \0",
     "2f                            \0",
     "3f                            \0",
     "4f                            \0",
     "5f                            \0",
     "6f                            \0",
     "7f                            \0",
     "8f                            \0"},
    {"1m                            \0",
     "2m                            \0",
     "3m                            \0",
     "4m                            \0",
     "5m                            \0",
     "6m                            \0",
     "7m                            \0",
     "8m                            \0"}
};

shop_prices[4][8] = {
  {10,20,200,1000,10000,15000,25000,100000},//conveyors
  {50,500,2000,5000,1000000000,1000000000,1000000000,1000000000},//upgraders
  {10,500,5000,10000,1000000000,1000000000,1000000000,1000000000},//furnaces
  {0,0,0,0,0,0,0,0}//mines
};

