
#define done (((frog[2]==0)||(frog[2]==1)|| (frog[2]==2)) && ((frog[3]==0)||(frog[3]==1)||(frog[3]==2)) && ((frog[4]==0)||(frog[4]==1)||(frog[4]==2)) && (frog[0]==3) && (frog[1]==4))

byte frog [5]; //4 frog and empty 

proctype jumpyfrog(int i; int direction){
int temp;
atomic{if 
::(frog[i] == frog[0] + direction || frog[i] == frog[0] + direction + direction)
   printf( "\n%d:MOVE FROG%d FROM %d TO %d\n"
      , _pid 
      , i
      , frog[i]
      , frog[0]
      );
      //swap empty position and frog position
   temp = frog[i];
   frog[i] = frog[0];
   frog[0] = temp;
   
   printf( "\n%d: EMPTY %d, FROG1@%d, FROG2@%d, FROG3@%d, FROG4@%d\n"
      , _pid
      , frog[0]
      , frog[1]
      , frog[2]
      , frog[3]
      , frog[4]
      );
:: else printf( "\n%d: FROG[%d] CAN'T JUMP\n", _pid , i); 
fi
}
}

init {
frog[0] = 1; //empty
frog[1] = 0; //frog 1
frog[2] = 2; //frog 2
frog[3] = 3; //frog 3
frog[4] = 4; //frog 4

printf( "EMPTY %d, FROG1@%d, FROG2@%d, FROG3@%d, FROG4@%d\n"
      , frog[0]
      , frog[1]
      , frog[2]
      , frog[3]
      , frog[4]
      );
    
do
::      
atomic{
if //if empty is within 1 or 2 space in respective directions of frog run jumpyfrog allowing the frog to jump
::(frog[1] == frog[0] - 1  || frog[1] == frog[0] - 2) ->
  run jumpyfrog(1, -1); 
  
::(frog[2] == frog[0] + 1  || frog[2] == frog[0] + 2) ->
  run jumpyfrog(2, 1); 

::(frog[3] == frog[0] + 1  || frog[3] == frog[0] + 2) ->
  run jumpyfrog(3, 1); 
  
::(frog[4] == frog[0] + 1  || frog[4] == frog[0] + 2) ->
  run jumpyfrog(4, 1); 
  
::else -> break;
fi
}
od

   printf( "\n%d: EMPTY %d, FROG1@%d, FROG2@%d, FROG3@%d, FROG4@%d, DONE\n"
      , _pid
      , frog[0]
      , frog[1]
      , frog[2]
      , frog[3]
      , frog[4]
      );
      
      assert(!done);
}
