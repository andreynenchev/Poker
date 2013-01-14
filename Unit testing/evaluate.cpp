/* Fig. 5.24: main.c Card shuffling dealing program */ 
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <cstring>
using namespace std;
/* prototypes */ 
void shuffle( int wDeck[][13] ); 
void deal( const int wDeck[][13], const char *wFace[], const char *wSuit[], int Deck5[10][5][2],int n ); //A
void check_hands( int Decks[10][5][2],int n, int Players[10][6]); //A
void check_two_pair( int Decks[10][5][2]);//A 

//MINE  A
bool straightflush(int Decks[5][2],int Players[10]);
int evaluate(int a[5][2], int h[5]);
int hicard(int a[5][2]);
char* names(int a);
void print(int Decks[10][5][2],int n);
bool order (int i,int j) { return (i>j); }//for the sort function


/* initialize suit array */ 
const char *suit[ 4 ] = { "Hearts", "Diamonds", "Clubs", "Spades" }; 
/* initialize face array */ 
const char *face[13] = {"Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};


int main() { 
    int n=8;//Numbers of Players=2      A
    int Players[10][6];//Scorest for each player//a
     
    /* initialize deck array */ 
    int deck[4][13] = {0}; 
    int Decks[10][5][2]; 
    srand(time(0)); 
    
    shuffle(deck); 
    deal( deck, face, suit, Decks, n); 
    
    
    /*DEBUGING::
    Decks[0][4][0]=12;
    Decks[0][1][0]=11;
    Decks[0][2][0]=4;
    Decks[0][3][0]=9;
    Decks[0][0][0]=8;
    Decks[0][0][1]=0;
    Decks[0][1][1]=1;
    Decks[0][2][1]=0;
    Decks[0][3][1]=0;
    Decks[0][4][1]=0;
    
    Decks[1][4][0]=12;
    Decks[1][1][0]=11;
    Decks[1][2][0]=4;
    Decks[1][3][0]=9;
    Decks[1][0][0]=8;
    Decks[1][0][1]=0;
    Decks[1][1][1]=1;
    Decks[1][2][1]=0;
    Decks[1][3][1]=0;
    Decks[1][4][1]=0;
    
    Decks[2][4][0]=6;
    Decks[2][1][0]=6;
    Decks[2][2][0]=6;
    Decks[2][3][0]=3;
    Decks[2][0][0]=2;
    Decks[2][0][1]=0;
    Decks[2][1][1]=1;
    Decks[2][2][1]=2;
    Decks[2][3][1]=3;
    Decks[2][4][1]=2;
    
    Decks[3][0][0]=6;
    Decks[3][1][0]=6;
    Decks[3][2][0]=6;
    Decks[3][3][0]=3;
    Decks[3][4][0]=2;
    Decks[3][0][1]=0;
    Decks[3][1][1]=1;
    Decks[3][2][1]=2;
    Decks[3][3][1]=3;
    Decks[3][4][1]=2;

    */
    print(Decks,n);
    check_hands(Decks,n,Players);
    //getchar();
    return 0; 
    /* indicates successful termination */ 
    }
     /* end main */ 
     
     /* shuffle cards in deck */ 
    void shuffle( int wDeck[][13] ) { 
        int row; /* row number */ 
        int column; /* column number */ 
        int card; /* counter */ 
        /* for each of the 52 cards, choose slot of deck randomly */ 
        for ( card = 1; card <= 52; card++ ) { 
            /* choose new random location until unoccupied slot found */ 
            do { 
                row = rand() % 4; 
                column = rand() % 13; 
                } while( wDeck[row][column] != 0 ); 
                wDeck[ row ][ column ] = card; 
                } /* end for */ 
            } /* end function shuffle */ /* deal cards in deck */ 
    void deal( const int wDeck[][13], const char *wFace[], const char *wSuit[], int Deck5[10][5][2], int n ) { 
        int card; /* card counter */ int row; /* row counter */ 
        int column; /* column counter */ /* deal each of the 52 cards */ 
        for ( card = 1; card <= 5*n; card++ ) { /* loop through rows of wDeck */ ///First REDACTION
            for ( row = 0; row < 4; row++ ) { /* loop through columns of wDeck for current row */ 
                for ( column = 0; column < 13; column++ ) { /* if slot contains current card, display card */ 
                    if ( wDeck[ row ][ column ] == card ) {
                        //printf( "%d->%5s of %-8s  ",(card-1)%n, wFace[ column ], wSuit[ row ]);
                        //if ((card)%n==0) printf("\n");
                        Deck5[(card-1)%n][(card-1)%5][0]= column; 
                        Deck5[(card-1)%n][(card-1)%5][1]= row ; } /* end if */ 
                    } /* end for */ 
                } /* end for */ 
            } /* end for */ 
        }/* end function deal */ 
        void check_hands( int Decks[10][5][2],int n, int Players[10][6]) {
            /**Evaluating all the hands*/
            for (int p=0;p<n;p++){
                Players[p][5]=evaluate(Decks[p], Players[p]);
            }
            
            // Writing __Winner at the winner
            bool winner[10]={true, true, true, true, true, true, true, true, true, true};
            for (int p=0;p<n;p++){
                for (int i=p+1; i<n; i++){
                    if (Players[p][5]<Players[i][5]) {
                        winner[p]=false;
                    }
                    else if (Players[p][5]==Players[i][5]) {
                        int j=0;
                        while (j<5 && Players[p][j]==Players[i][j]) j++;
                        if ( j<5 ){
                            if (Players[p][j]<Players[i][j]) winner[p]=false;
                            else winner[i]=false;
                        }
                    }
                    else if(Players[p][5]>Players[i][5]) {winner[i]=false;
                    }
                }
            }
            
            for (int p=0;p<n;p++){
                    switch (Players[p][5]){
                        case 1: 
                            printf("Player %d-> %s", p ,face[Players[p][0]]);
                            break;
                        case 2: 
                            printf("Player %d-> %s: %s with %s high", p, names(Players[p][5]), face[Players[p][0]], face[Players[p][2]]);
                            break;
                        case 3: 
                            printf("Player %d-> %s: %s over %s", p, names(Players[p][5]), face[Players[p][0]], face[Players[p][2]]);
                            break;
                        case 4: 
                            printf("Player %d-> %s: %s with %s high", p, names(Players[p][5]), face[Players[p][0]], face[Players[p][3]]);
                            break;
                        case 5: 
                            printf("Player %d-> %s: %s - high", p , names(Players[p][5]),face[Players[p][0]]);
                            break;
                        case 6: 
                            printf("Player %d-> %s: %s - high", p , names(Players[p][5]),face[Players[p][0]]);
                            break;
                        case 7: 
                            printf("Player %d-> %s: %s over %s", p, names(Players[p][5]), face[Players[p][0]], face[Players[p][3]]);
                            break;
                        case 8: 
                            printf("Player %d-> %s: %s with %s high", p, names(Players[p][5]), face[Players[p][0]], face[Players[p][4]]);
                            break;
                        case 9: 
                            printf("Player %d-> %s: %s - high", p , names(Players[p][5]),face[Players[p][0]]);
                            break;
                    }
                if (winner[p]) printf(" __WINNER!!!");
                printf("\n");
            }
        } 
        /**To evaluate if straight*/
        bool straight(int a[5][2]){
            bool map[26]={0};
            for (int i=0;i<5;i++){
                map[a[i][0]]=true;
                map[a[i][0]+13]=true;
            }
            int m=0;
            for (int i=0;i<13;i++){//2345678910J D K A     
                if (map[i])m++;
                else m=0;
                if (m==5) return true;
            }
            m=0;
            for (int i=12;i<18;i++){
                if (map[i])m++;
                else m=0;
                if (m==5) return true;
            }
            return false;
        
        }
        
        /**To evaluate if flush*/
        bool flush(int a[5][2]){
            return (a[0][1]==a[1][1]&&a[1][1]==a[2][1]&&a[2][1]==a[3][1]&&a[3][1]==a[4][1]);
        }
        
        /**Evaluating of a hand:
            starts with the hightest possible evaluation : Straight-Flush and goes down to High card
            modifies Players array:keeps the cards sorted and returns form 1-9 combination(name of the hand)
        */
        int evaluate(int a[5][2], int h[5]){
            int m=0,n=0,r=0;
            //Straight Flush 1hi(One High card)
            memset(h,0,sizeof(h));  
            if(flush(a)&&straight(a)){
                    for (int i=0; i<5; i++){
                        h[i]=a[i][0];
                    }
                    sort(h,h+5,order);
                    if(h[0]-h[1]>1) h[0]=h[1];//if A5432 - make it 55432 //we only care about h[0]!!!!
                    return 9;
            }
            //Four of a kind 2hi
            memset(h,0,sizeof(h));
            for (int i=0; i<5; i++){
                m=0;
                for (int j=0; j<5; j++){
                    if(a[i][0]==a[j][0]){
                        m++;
                        h[0]=a[i][0];
                    }
                    if (m==4){
                        //fill up the rest of the high cards, so it will work on Texas Holdem' :)
                        h[1]=h[2]=h[3]=h[0];
                        int k=1;
                        for (int i=0; i<5; i++){
                            if (h[0]!=a[i][0]){
                                h[4]=a[i][0];
                            }
                        }
                        return 8; 
                    }
                }
            }
            m=0,n=0,r=0;
            memset(h,0,sizeof(h));
            //Full house 2hi
            for (int i=0; i<5; i++){
                m=0;
                for (int j=0; j<5; j++){
                    if(a[i][0]==a[j][0]) {
                        m++;
                        r=a[i][0];
                        h[0]=a[i][0];
                    }
                    if (m==3) {
                        for (int i1=0; i1<5; i1++){
                            n=0;
                            for (int j1=0; j1<5; j1++){
                                if(a[i1][0]==a[j1][0] && a[i1][0]!=r) {
                                    n++;
                                    h[1]=a[i1][0];
                                }
                                if (n==2){
                                    int k=2;
                                    for (int i2=0; i2<5; i2++){
                                        if (h[0]!=a[i2][0]&&h[1]!=a[i2][0]){
                                            h[k++]=a[i2][0];
                                        }
                                    }
                                    //fill up the rest of the high cards, so it will work on Texas Holdem' :)
                                    h[3]=h[4]=h[1];
                                    h[0]=h[1]=h[2]=h[0];
                                    return 7; 
                                }
                            }
                        }
                    }    
                } 
            }
            m=0,n=0,r=0;
            //Flush 1hi
            memset(h,0,sizeof(h));
            if(flush(a)){
                for (int i=0; i<5; i++){
                    h[i]=a[i][0];
                }
                sort(h,h+5,order);
                return 6;
            }
            //Straight 1hi
            memset(h,0,sizeof(h));
            if(straight(a)){
                for (int i=0; i<5; i++){
                    h[i]=a[i][0];
                }
                sort(h,h+5,order);
                if(h[0]-h[1]>1) h[0]=h[1];//if A5432 - make it 55432 //we only care about h[0]!!!!
                return 5;
            }
            //1x3 2hi
            m=0,n=0,r=0;
            memset(h,0,sizeof(h));
            for (int i=0; i<5; i++){
                m=0;
                for (int j=0; j<5; j++){
                    if(a[i][0]==a[j][0]){
                        m++;
                        h[0]=a[i][0];   
                    }
                    if (m==3){
                        int k=1;
                        for (int i=0; i<5; i++){
                            if (h[0]!=a[i][0]){
                                h[k++]=a[i][0];
                            }
                        }
                        if(h[1]<h[2]){
                            int sw=h[1];
                            h[1]=h[2];
                            h[2]=sw;
                        }
                        h[3]=h[1];
                        h[4]=h[2];
                        h[0]=h[1]=h[2]=h[0];
                        return 4; 
                    }
                }
            }
            //2x2 3hi
            m=0,n=0,r=0;
            memset(h,0,sizeof(h));
            for (int i=0; i<5; i++){
                m=0;
                for (int j=0; j<5; j++){
                    if(a[i][0]==a[j][0]) {
                        m++;
                        h[0]=a[i][0];
                        r=a[i][0];
                    }
                    if (m==2) {
                        for (int i1=0; i1<5; i1++){
                            n=0;
                            for (int j1=0; j1<5; j1++){
                                if(a[i1][0]==a[j1][0] && a[i1][0]!=r) {
                                    h[1]=a[i1][0];
                                    n++;
                                }
                                if (n==2){
                                    int k=2;
                                    for (int i2=0; i2<5; i2++){
                                        if (h[0]!=a[i2][0]&&h[1]!=a[i2][0]){
                                            h[k++]=a[i2][0];
                                        }
                                    }
                                    //swap
                                    if(h[0]<h[1]){
                                        int sw=h[0];
                                        h[0]=h[1];
                                        h[1]=sw;
                                    }
                                    h[4]=h[2];
                                    h[2]=h[3]=h[1];
                                    h[0]=h[1]=h[0];
                                    return 3; 
                                }
                            }
                        }
                    }    
                } 
            }
            m=0,n=0,r=0;
            memset(h,0,sizeof(h));
            //1x2 4hi
            for (int i=0; i<5; i++){
                m=0;
                for (int j=0; j<5; j++){
                    if(a[i][0]==a[j][0]) {
                        m++;
                        h[0]=a[i][0];
                    }
                    if (m==2) {
                        int k=2;
                        h[1]=h[0];
                        for (int i=0; i<5; i++){
                            if (h[0]!=a[i][0]){
                                h[k++]=a[i][0];
                            }
                        }
                        sort(h+2,h+4,order);
                        return 2; 
                        
                    }
                }
            }
            m=0,n=0,r=0;
            memset(h,0,sizeof(h));
            for (int i=0; i<5; i++){
                h[i]=a[i][0];
            }
            sort(h,h+5,order);
            //nothing
            return 1;
        }
    //**In case of the number returns the name of the hand*/
    char* names(int a){
        switch (a){
            case 1: return "Nothing";
            case 2: return "Pair";
            case 3: return "Two Pairs";
            case 4: return "Three of a kind";
            case 5: return "Straight";
            case 6: return "Flush";
            case 7: return "Full House"; 
            case 8: return "Four of a kind";
            case 9: return "Straight Flush";
            default: return "Nothing";
        }
}

/*Printing function of Players cards   for DEBUGGING to work**/
void print(int Decks[10][5][2],int n){
    for ( int card = 1; card <= 5*n; card++ ) {
        printf( "%d->%5s of %-8s  ",(card-1)%n, face[ Decks[(card-1)%n][(card-1)%5][0] ], suit[ Decks[(card-1)%n][(card-1)%5][1] ]);
            if ((card)%n==0) 
                printf("\n");
        }
}
