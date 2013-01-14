/* Fig. 5.24: main.c Card shuffling dealing program */ 

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <set>
using namespace std;

struct Card{
    int Value;//2345678910JDKA  --> 0-12
    int Color;//HDCS            --> 0-3

};

struct Hand{
    Card Cards[5];//all the cards
    int eval;//evaluate
    int Num_Hi_cards;//Number of High Cards to battle with
    Card Hi_cards[5];//all the High Cards
    char* name;//name of Hand
};



/* prototypes */ 
void shuffle( int wDeck[][13] ); 
void deal( const int wDeck[][13], const char *wFace[], const char *wSuit[], int Deck5[10][5][2],int n, Hand Players[10] ); //A
void check_hands( int Decks[10][5][2],int n, Hand Players[10]); //A
void check_two_pair( int Decks[10][5][2]);//A 

int evaluate(int a[5][2], Hand h);//MINE  A
bool straightflush(int Decks[5][2],Hand Players[10]);
char* names(int a);

int main() { 
    int n=9;//Numbers of Players=2      A
    Hand* Players= new Hand[10];//Scorest for each player  s.end()-wins!! A
    
    /* initialize suit array */ 
    const char *suit[ 4 ] = { "Hearts", "Diamonds", "Clubs", "Spades" }; 
    /* initialize face array */ 
    const char *face[13] = {"Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King",  "Ace"}; 
    /* initialize deck array */ 
    int deck[4][13] = {0}; 
    int Decks[10][5][2]; 
    srand(time(0)); 
    /* seed random-number generator */
    shuffle(deck); 
    deal( deck, face, suit, Decks, n,Players); 
    
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
                /* end do...while */ 
                
                /* place card number in chosen slot of deck */ 
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
                        printf( "%d->%5s of %-8s  ",(card-1)%n, wFace[ column ], wSuit[ row ]);
                         if ((card)%n==0) printf("\n");
                        Deck5[(card-1)%n][(card-1)%5][0]= column; 
                        Deck5[(card-1)%n][(card-1)%5][1]= row ; } /* end if */ 
                    } /* end for */ 
                } /* end for */ 
            } /* end for */ 
        }/* end function deal */ 
        void check_hands( int Decks[10][5][2],int n, Hand Players[10]) {
            set<int> s;
            s.clear();
            for (int p=0;p<n;p++){
                /*//DEBUG
                for (int j=0; j<5;j++)
                    printf("%d, ",Decks[p][j][0]);
                printf("\n");
                */
                Players[p][1]=0;
                Players[p][0]=(long)evaluate(Decks[p], Players[p][1]);
                printf("%d->%s hi->%d\n", p, names(Players[p][0]),Players[p][1]);
            }
            
            int max=0;
            for (int i=0;i<n;i++){
                if (max<Players[i][0]) max=Players[i][0];
            }
            int eq=0;
            for (int i=0;i<n;i++){
                if (max==Players[i][0]) eq++;
            }
            if (eq>1) {
                for (int i=0;i<eq;i++){
                    
                }
            }
                
        } 
        bool straight(int a[5][2]){
            bool map[30]={0};
            for (int i=0;i<5;i++){//Mapping cards
                map[a[i][0]]=true;
                map[a[i][0]+13]=true;
            }
            int m=0;
            for (int i=0;i<13;i++){//2345678910JDKA
                if (map[i])m++;
                else m=0;
                if (m==5) return true;
            }
            for (int i=12;i<12+5;i++){//A2345
                if (map[i])m++;
                else m=0;
                if (m==5) return true;
            }
            return false;
        
        }
        bool flush(int a[5][2]){
            return (a[0][1]==a[1][1]&&a[1][1]==a[2][1]&&a[2][1]==a[3][1]&&a[3][1]==a[4][1]);
        }
        
        
        int evaluate(int a[5][2], Hand h){
            int m=0,n=0,r=0;
            //hi=0;
            //hi=hicard(a);
            //Straight Flush 1hi  
            if(straight(a)&&flush(a)){
                    hi=hicard(a);
                    return 9;
            }
            //Four of a kind 2hi
            for (int i=0; i<5; i++){
                m=0;
                for (int j=0; j<5; j++){
                    if(a[i][0]==a[j][0]) m++;
                    if (m==4) return 8; 
                }
            }
            m=0,n=0,r=0;
            //Full house 2hi
            for (int i=0; i<5; i++){
                m=0;
                for (int j=0; j<5; j++){
                    if(a[i][0]==a[j][0]) {
                        m++;
                        r=a[i][0];
                    }
                    if (m==3) {
                        for (int i1=0; i1<5; i1++){
                            n=0;
                            for (int j1=0; j1<5; j1++){
                                if(a[i1][0]==a[j1][0] && a[i1][0]!=r) {
                                    n++;
                                }
                            if (n==2) return 7; 
                            }
                        }
                    }    
                } 
            }
            m=0,n=0,r=0;
            //Flush 1hi
            if(flush(a)) return 6;
            //Straight 1hi
            if(straight(a)) return 5;
            //1x3 2hi
            m=0,n=0,r=0;
            for (int i=0; i<5; i++){
                m=0;
                for (int j=0; j<5; j++){
                    if(a[i][0]==a[j][0]) m++;
                    if (m==3) return 4; 
                }
            }
            //2x2 3hi
            m=0,n=0,r=0;
            for (int i=0; i<5; i++){
                m=0;
                for (int j=0; j<5; j++){
                    if(a[i][0]==a[j][0]) {
                        m++;
                        r=a[i][0];
                    }
                    if (m==2) {
                        for (int i1=0; i1<5; i1++){
                            n=0;
                            for (int j1=0; j1<5; j1++){
                                if(a[i1][0]==a[j1][0] && a[i1][0]!=r) {
                                    n++;
                                }
                            if (n==2) return 3; 
                            }
                        }
                    }    
                } 
            }
            m=0,n=0,r=0;
            //1x2 4hi
            for (int i=0; i<5; i++){
                m=0;
                for (int j=0; j<5; j++){
                    if(a[i][0]==a[j][0]) m++;
                    if (m==2) return 2; 
                }
            }
            m=0,n=0,r=0;
            //nothing
            return 1;
            
        }
char* names(int a){
    char* c="Nothing";
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
        default: return c;
    
    }
}
/*
long hicard(int a[5][2]){
    bool map[15]={false};
    for (int i=0;i<5;i++){
        map[a[i][0]]=true;
    }
    long d=1;
    long sum=0;
    for (int i=0;i<13;i++){
        if (map[i]){
            sum+=d*i;
            d*=10;
        }
    }
    return sum;
}
*/

/*
                for (int i=0; i<5; i++){
                    s.insert(Decks[p][i][0]);
                }
                s::iterator o= s.begin();
                for(s::iterator i=++o;i!=i.end();i++){
                    if (abs((*o)-(*i))!=1) Player[p]=0;
                    o=i;
                }
                if(Decks[p][0][0])
                //0 1 2 3 4 5 6 7  8 9 10 11 12
                //2 3 4 5 6 7 8 9 10 J  D  K  A
                        */
                 
