#include "shop_text.h"

unsigned char bottom_text[5][51] = 
{
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0",
"|                                                |\0",
"| MONEY:                                         |\0",
"|                                                |\0",
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\0",
};
unsigned char menu_text[30][31] =
{"'~~~~~~~~~~~~~~~~~~~~~~~~~~~~`\0",
 "|          - MENU -          |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "|                            |\0",
 "'~~~~~~~~~~~~~~~~~~~~~~~~~~~~'\0"};

 unsigned char controls_text[30][31] =
{"'~~~~~~~~~~~~~~~~~~~~~~~~~~~~`\0",
"|        - CONTROLS -        |\0",
"|                            |\0",
"| - ENTER  - Select component|\0",
"|    or option from the menu |\0",
"|                            |\0",
"| - ARROWS - Navigate menus  |\0",
"|                            |\0",
"| - ESCAPE - Go back         |\0",
"|     (use to exit this menu)|\0",
"|                            |\0",
"| - WASD   - Move Cursor     |\0",
"|                            |\0",
"| - DELETE - Delete selected |\0",
"|    component               |\0",
"|                            |\0",
"|                            |\0",
"| - SPACE  - Place selected  |\0",
"|    component               |\0",
"|                            |\0",
"| - R      - Rotate selected |\0",
"|    component               |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"'~~~~~~~~~~~~~~~~~~~~~~~~~~~~'\0"};

unsigned char shop_menu_text[30][31] =
{"'~~~~~~~~~~~~~~~~~~~~~~~~~~~~`\0",
"|    - SHOP CATEGORIES -     |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"|                            |\0",
"'~~~~~~~~~~~~~~~~~~~~~~~~~~~~'\0"};

  unsigned char shop_text[30][31] =
  {"'~~~~~~~~~~~~~~~~~~~~~~~~~~~~`\0",
  "|          - SHOP -          |\0",
  "|                            |\0",
  "|   (ABSOLUTELY NO REFUNDS)  |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "|                            |\0",
  "'~~~~~~~~~~~~~~~~~~~~~~~~~~~~'\0"};


  unsigned char menu_items [2][31] = 
  {
    "|  -    Shop                 |\0",
    "|  -  Controls               |\0"
  };

  unsigned char shop_menu_items[4][31] =
{"|  - CONVEYORS              |\0",
 "|  - UPGRADERS              |\0",
 "|  - FURNACES               |\0",
 "|  - MINES                  |\0"};


unsigned char shop_items [4][8][31] =
{
    {"|1 - Basic Conveyor       $10|\0",
     "|2 - Basic Corner         $20|\0",
     "|3 - Fast Conveyor       $200|\0",
     "|4 - Fast Corner          $1K|\0",
     "|5 - Ore Launcher        $10K|\0",
     "|6 - Walled Conveyor     $15K|\0",
     "|7 - Fast Mini Conveyor  $25K|\0",
     "|8 - Mini Launcher      $100K|\0"},
    {"|1 - Basic Upgrader       $50|\0",
     "|2 - Improved Upgrader   $500|\0",
     "|3 - Multi Upgrader       $2K|\0",
     "|4 - Expo Upgrader        $5K|\0",
     "|5 - LOCKED                  |\0",
     "|6 - LOCKED                  |\0",
     "|7 - LOCKED                  |\0",
     "|8 - LOCKED                  |\0"},
    {"|1 - Basic Furnace        $10|\0",
     "|2 - Improved Furnace    $500|\0",
     "|3 - Excellent Furnace    $2K|\0",
     "|4 - Cell Furnace         $5K|\0",
     "|5 - LOCKED                  |\0",
     "|6 - LOCKED                  |\0",
     "|7 - LOCKED                  |\0",
     "|8 - LOCKED                  |\0"},
    {"|1 - Unlock Mine 1       FREE|\0",
     "|2 - Speed up Mine 1      $10|\0",
     "|3 - Unlock Mine 2       $100|\0",
     "|4 - Speed up Mine 2     $500|\0",
     "|5 - Unlock Mine 3        $1K|\0",
     "|6 - Speed up Mine 3      $5K|\0",
     "|7 - Unlock Mine 4       $10K|\0",
     "|8 - Speed up Mine 4     $20K|\0"}
};

int shop_prices[4][8] = {
  {10,20,200,1000,10000,15000,25000,100000},//conveyors
  {50,500,2000,5000,1000000000,1000000000,1000000000,1000000000},//upgraders
  {10,500,5000,10000,1000000000,1000000000,1000000000,1000000000},//furnaces
  {0,10,100,500,1000,5000,10000,20000}//mines
};

