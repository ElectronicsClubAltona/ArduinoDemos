// Chessboard adding Queens or at least castles
// 17/11/11
//
// Mike Hewitt    VK3KMJ
//  a revision exercise for my aging C++

#define nQ 8

int i = 0;
int j = 0;
int b = 1; // board display count
// for AddQueen
int x;
int y;

const int maxx = nQ;   // was 8
const int maxy = nQ;   // tried series linking but failed

int board [maxx][maxy];  // rows by columns
void AddQueen(int x, int y) ;     //prototype
void RemoveQueen(int x, int y) ;  //prototype
void BoardPrint();    // prototype

void setup() {

  Serial.begin(9600);
  Serial.println("Chess Board with 8 Queens 17 November 2011");
}

void RemoveQueen(int x, int y) {
  // x:y      i:j
  // first do horizontal
  // if we treat as castle then can do horizontal & vertial as a single for
  // loop
  /*
  so y stays same    ; see k for x
   */


  int p = x; // save parameters
  int q = y;

  for (int k = 0; k < maxx; k++) {
    board[k][y] =  board[k][y] - 1;
  }

  //  now the vertical cmpnt
  for (int l = 0; l < maxy; l++) {
    board[x][l] = board[x][l] - 1;
  }

  while ((x < maxx + 1) && (y < maxy + 1)) { // North East
    board[x][y] = board[x][y] - 1;
    x++;
    y++;
  }
  x = p;
  y = q;
  // restore originals after last loop
  // check scope and make copies of input parameters
  while ((x < maxx + 1) && (y > -1)) { //   South East
    board[x][y] = board[x][y] - 1;
    x++;
    y--;
  }
  //  new 17/11/11
  x = p;
  y = q;
  // restore originals after last loop
  // check scope and make copies of input parameters
  while ((x > -1) && (y > -1)) { //  South West
    board[x][y] = board[x][y] - 1;
    x--;
    y--;
  }



  x = p;
  y = q;
  // restore originals after last loop
  // check scope and make copies of input parameters
  while ((x > -1) && (y < maxy + 1)) {  //  North West
    board[x][y] = board[x][y] - 1;
    x--;
    y++;
  }

  /*
   while (x < i) {   // go East
   board[x][y]  = board[x][y] + 1;
   x++;
   // board[x][y]++;
   }
   */

  /* while (x != -1) {     // West        sus !=> fudge to reach edge of board
   board[x][y] = board[x][y] + 1;
   x--;
   }
   */

  // board[x][y] = 1;   // included in earlier loop
  Serial.println(" ");
  BoardPrint();
  // end RemoveQueen
}



void loop() {
  Serial.println("Inside 'loop'");

  // initialise board to have no pieces on it
  //for  (i=0; i<=8; i++ ) {
  // board [0][i] = 0;
  // }
  // Serial.println("test mjh 2");

  for  (i = 0; i < maxx; i++ ) { // init a row at a time
    for ( j = 0; j < maxy; j++ ) {
      board [i][j] = 0;
      //    Serial.print(board[i][j]);
      //    Serial.print(" ");
      /*     Serial.print(i);
       Serial.print(" ");
       Serial.print(j);
       Serial.print(" ");
       */
    }
    //  Serial.println("x");
  }


  // AddQueen(3,4);
  AddQueen(0, 0);
  RemoveQueen(0, 0);
  AddQueen(1, 2);
  AddQueen(2, 4);
  AddQueen(3, 1);
  //  RemoveQueen(3,1);
  //  RemoveQueen(1,2);
  //  RemoveQueen(2,4);
  // AddQueen(4,3);

  // BoardPrint();
  /*
   AddQueen(3,4);   //calling Q on existing co-ords works
   //BoardPrint();

   AddQueen(5,2);
   // BoardPrint();


   AddQueen(7,7);
   //BoardPrint();
   AddQueen(0,0);
   */
  /*
  AddQueen(0,7);
   // BoardPrint();

   AddQueen(0,0);
   // BoardPrint();
   */


  // now to print the board
  //Serial.println("Board");

  // BoardPrint();

  // while(true) ;  // hold execution here

  delay(8000);

}
void AddQueen(int x, int y) {
  // x:y      i:j
  // first do horizontal
  // if we treat as castle then can do horizontal & vertial as a single for
  // loop
  /*
  so y stays same    ; see k for x
   */


  int p = x; // save parameters
  int q = y;

  for (int k = 0; k < maxx; k++) {
    board[k][y] =  board[k][y] + 1;
  }

  //  now the vertical cmpnt
  for (int l = 0; l < maxy; l++) {
    board[x][l] = board[x][l] + 1;
  }

  while ((x < maxx + 1) && (y < maxy + 1)) { // North East
    board[x][y] = board[x][y] + 1;
    x++;
    y++;
  }
  x = p;
  y = q;
  // restore originals after last loop
  // check scope and make copies of input parameters
  while ((x < maxx + 1) && (y > -1)) { //   South East
    board[x][y] = board[x][y] + 1;
    x++;
    y--;
  }
  //  new 17/11/11
  x = p;
  y = q;
  // restore originals after last loop
  // check scope and make copies of input parameters
  while ((x > -1) && (y > -1)) { //  South West
    board[x][y] = board[x][y] + 1;
    x--;
    y--;
  }



  x = p;
  y = q;
  // restore originals after last loop
  // check scope and make copies of input parameters
  while ((x > -1) && (y < maxy + 1)) {  //  North West
    board[x][y] = board[x][y] + 1;
    x--;
    y++;
  }

  /*
   while (x < i) {   // go East
   board[x][y]  = board[x][y] + 1;
   x++;
   // board[x][y]++;
   }
   */

  /* while (x != -1) {     // West        sus !=> fudge to reach edge of board
   board[x][y] = board[x][y] + 1;
   x--;
   }
   */

  // board[x][y] = 1;   // included in earlier loop
  Serial.println(" ");
  BoardPrint();
}


void BoardPrint() {
  // now to print the board
  Serial.print("Board ");
  Serial.println(b);
  b++;
  for ( j = 0; j < maxy; j++ ) {
    for  (i = 0; i < maxx; i++ ) { // init a row at a time
      Serial.print(board[i][j]);
      Serial.print(" ");
    }
    Serial.println(); // start a new line
  }
}











































