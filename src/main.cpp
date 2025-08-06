#include <Arduino.h>
#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

#define CELL 8             // cell size in pixels
#define GRID_W (320 / CELL) //Adjusted grid width and height for the IlI9341 display(320x240)
#define GRID_H (240 / CELL)

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

bool grid[GRID_W][GRID_H];

void randomizeGrid();

void setup() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE);
  randomizeGrid(); // Draw a random grid once
}

int countNeighbours(int x, int y){

 int neighbours = 0;
 for(int i = x-1; i <= x+1; i++){
    for(int j = y-1; j <= y+1; j++){
      if(!(x == i && y == j) && i >= 0 && i < GRID_W && j >= 0 && j < GRID_H && grid[i][j]){
        neighbours++;
      }
    }  
 }  
  return neighbours;
}

void getNextGrid(){
  bool nextGrid[GRID_W][GRID_H];
  for(int x = 0; x < GRID_W; x++){
    for(int y = 0; y < GRID_H; y++){
      int neighbours = countNeighbours(x,y);
      if(neighbours < 2){ // underpopulation
        nextGrid[x][y] = 0;
      }    
      else if(neighbours > 3){ // overpopulation
        nextGrid[x][y] = 0;
      }
      else if(neighbours == 3){ // reproduction
        nextGrid[x][y] = 1;
      }
      else{
        nextGrid[x][y] = grid[x][y];
      }
    }  
 }
  for(int x = 0; x < GRID_W; x++){
    for(int y = 0; y < GRID_H; y++){
      grid[x][y] = nextGrid[x][y];
    }
  }
}

void randomizeGrid(){
  for(int x = 0; x < GRID_W; x++){
    for(int y = 0; y < GRID_H; y++){
      grid[x][y] = random(0,2);
    }
  }
}

void drawGrid() {
  static uint8_t bitmap[320 * 240 / 8];  // 9600 bytes for full 1-bit screen buffer

  // clear bitmap for new frame
  memset(bitmap, 0, sizeof(bitmap));

  // loop through logical cells
  for (int x = 0; x < GRID_W; x++) {
    for (int y = 0; y < GRID_H; y++) {

      bool cell = grid[x][y];   // current Game of Life grid state
      if (!cell) continue;      // only draw ALIVE cells

      // top-left corner of the cell in pixels
      int newX = x * CELL;
      int newY = y * CELL;

      // fill 8×8 pixels in bitmap
      for (int i = 0; i < CELL; i++) {
        for (int j = 0; j < CELL; j++) {
          int px = newX + i;
          int py = newY + j;

          int byteIndex = (py * 320 + px) / 8;   // which byte in array
          int bitIndex  =  7 - (px % 8);          // which bit in the byte (MSB first)

          bitmap[byteIndex] |= (1 << bitIndex);
        }
      }
    }
  }
  tft.drawBitmap(0, 0, bitmap, 320, 240, TFT_BLACK, TFT_WHITE);
}

void loop() {
  getNextGrid();
  drawGrid();
  delay(3000);
}