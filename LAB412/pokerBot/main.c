#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define playsFirst 0
#define playsSecond 1

int findHand(char hand[5],char range[][5]);
void potCalculation(int potAmt);
void goNextHand();
void potOdds(float myCallAmt,float totalWinAmt,float winPC,int button,float potSize);
void impliedOdds(float opponentBetAmt,float winPC, float totalWinAmt);
void foldEquity(float winPC, float foldPC,float potSize);
void totalEquity(float winPC,float foldPC);
int info1();
int info2();
float retWinPC();
float retFoldPC();
float retMyBet(float potSize,int betType);
float retMyRaise(float opponentBetAmt,int raiseType);
float retPotSize();
int retOpponentAction();
float retOpponentBetOrRaise();
void afterflop(int button,float potSize,int passiveOrAggressive);

int main(){

    char allRanges[169][5]={
    "AKs","AQs","AJs","ATs","A9s","A8s","A7s","A6s","A5s","A4s","A3s","A2s","KQs","KJs","KTs","K9s","K8s","K7s",
    "K6s","K5s","K4s","K3s","K2s","QJs","QTs","Q9s","Q8s","Q7s","Q6s","Q5s","Q4s","Q3s","Q2s","JTs","J9s","J8s","J7s","J6s","J5s",
    "J4s","J3s","J2s","T9s","T8s","T7s","T6s","T5s","T4s","T3s","T2s","98s","97s","96s","95s","94s","93s","92s","87s","86s","85s",
    "84s","83s","82s","76s","75s","74s","73s","72s","65s","64s","63s","62s","54s","53s","52s","43s","42s","32s",

    "AKos","AQos","AJos","ATos","A9os","A8os","A7os","A6os","A5os","A4os","A3os","A2os","KQos","KJos","KTos","K9os","K8os","K7os",
    "K6os","K5os","K4os","K3os","K2os","QJos","QTos","Q9os","Q8os","Q7os","Q6os","Q5os","Q4os","Q3os","Q2os","JTos","J9os","J8os","J7os","J6os","J5os",
    "J4os","J3os","J2os","T9os","T8os","T7os","T6os","T5os","T4os","T3os","T2os","98os","97os","96os","95os","94os","93os","92os","87os","86os","85os",
    "84os","83os","82os","76os","75os","74os","73os","72os","65os","64os","63os","62os","54os","53os","52os","43os","42os","32os",

    "AA","KK","QQ","JJ","TT","99","88","77","66","55","44","33","22"};

    char veryGoodHands[6][5]={"AA","KK","QQ","JJ","TT","99"};

    char goodHands[33][5]={"AKs","AKos","AQs","AQos","AJs","AJos","ATs","A9s","A8s","A7s","A6s","A5s","A4s","A3s","KQs","KJs","KTs","K9s","K8s","QJs","QTs",
    "ATos","A9os","A8os","A7os","A5os","KQos","KJos","KTos","88","77","66","55"};

    char averageHands[65][5]={"A2s","K7s","K6s","K5s","K4s","K3s","K2s","Q9s","Q8s","Q7s","Q6s","Q5s","Q4s","Q3s","Q2s",
    "JTs","J9s","J8s","J7s","J6s","J5s","J4s","J3s","J2s","T9s","T8s","T7s","T6s","98s","97s","96s","87s","QJos",
    "QTos","Q9os","Q8os","Q7os","Q6os","Q5os","Q4os","Q3os","K9os","K8os","K7os","K6os","K5os","K4os","K3os","K2os",
    "JTos","J9os","J8os","J7os","J6os","T9os","T8os","T7os","98os","A6os","A4os","A3os","A2os","44","33","22"};

    char badHands[55][5]={"Q2os","J5os","J4os","J3os","J2os","T6os","T5os","T4os","T3os","T2os","97os","96os","95os","94os","93os","92os","87os","86os","85os",
    "84os","83os","82os","76os","75os","74os","65os","64os","54os","T5s","T4s","T3s","T2s","86s","85s","84s","83s","82s",
    "76s","75s","74s","73s","72s","65s","64s","63s","62s","54s","53s","52s","43s","42s","95s","94s","93s","92s"};

    char veryBadHands[10][5]={"32s","73os","72os","63os","62os","53os","52os"};

//preflop
    float myCallAmt,opponentBetAmt,winPC,totalWinAmt,foldPC;
    int betType,raiseType;
    int passiveOrAggressive;
    int button;
    int opponentAction;
    int opponentAction2;
    float betAmt;
    char hand[5];
    printf("Please enter your posision:\n0->You play first\n1->You play second\n");
    scanf("%d",&button);
    printf("Please enter your hand:\n");
    scanf("%s",&hand);
    printf("Please press:\n0->Your opponent is aggressive\n1->Your opponent is passive\n");
    scanf("%d",&passiveOrAggressive);
    int blind=1;
    float potSize=2*blind;

    printf("--------PREFLOP--------\n");
    if(button==playsSecond){
        opponentAction=retOpponentAction();
        if(opponentAction==1){//opponent checks
                if((findHand(hand,badHands)==1)||(findHand(hand,veryBadHands)==1)){
                   printf("\n*You should check back*\n");
                   printf("\nGoing to flop\n");
                   afterflop(button,potSize,passiveOrAggressive);
                }else if((findHand(hand,averageHands)==1)||(findHand(hand,goodHands)==1)||(findHand(hand,veryGoodHands)==1)){
                    printf("*You should bet the pot= %0.2f*\n",potSize);
                    potSize+=potSize;
                    opponentAction2=retOpponentAction();
                            if(opponentAction2==4){//opponent raises
                               betAmt=retOpponentBetOrRaise();
                               potSize+=betAmt;
                               if(findHand(hand,averageHands)==1){
                                   printf("*You should fold*\n");
                                   printf("\nGoing to the next hand\n");
                                   void goNextHand();
                                   //go next
                               }else if((findHand(hand,goodHands)==1)||(findHand(hand,veryGoodHands)==1)){
                                   potSize+=(betAmt-potSize);//raises to total amount
                                   printf("*You should call*\n");
                                   printf("\nGoing to flop\n");
                                   afterflop(button,potSize,passiveOrAggressive);
                               }
                            }else if(opponentAction2==2){//opponent calls
                                potSize+=potSize;
                                printf("\nGoing to flop\n");
                                afterflop(button,potSize,passiveOrAggressive);
                            }else if(opponentAction2==5){//opponent folds
                                printf("\nGoing to the next hand\n");
                                void goNextHand();
                            }
                }
        }else if(opponentAction==3){//opponent bets
                betAmt=retOpponentBetOrRaise();
                potSize+=betAmt;
                if((findHand(hand,badHands)==1)||(findHand(hand,veryBadHands)==1)){
                   printf("*You should fold*\n");
                   printf("\nGoing to the next hand\n");
                   void goNextHand();
                   //go next
                }else if(findHand(hand,averageHands)==1){
                   potSize+=betAmt;
                   printf("*You should call*\n");
                   printf("\nGoing to flop\n");
                   afterflop(button,potSize,passiveOrAggressive);
                }else if((findHand(hand,goodHands)==1)||(findHand(hand,veryGoodHands)==1)){
                   printf("*You should raise the pot=%0.2f*\n",potSize);
                   potSize+=potSize;
                   opponentAction2=retOpponentAction();
                   if(opponentAction2==2){//opponent calls
                        printf("\nGoing to flop\n");
                        potSize+=potSize/2-betAmt;
                        afterflop(button,potSize,passiveOrAggressive);
                   }else if(opponentAction2==5){//opponent folods
                        printf("\nGoing to the next hand\n");
                        void goNextHand();
                        //go next hand
                   }
                }
        }
    }else if(button==playsFirst){
        if((findHand(hand,badHands)==1)||(findHand(hand,veryBadHands)==1)||(findHand(hand,averageHands)==1)){
                printf("*You should check*\n");
                opponentAction=retOpponentAction();
                if(opponentAction==1){//opponent checks
                    printf("\nGoing to flop\n");
                    afterflop(button,potSize,passiveOrAggressive);
                }else if(opponentAction==3){//opponent bets
                    betAmt=retOpponentBetOrRaise();
                    potSize+=betAmt;
                    if(findHand(hand,averageHands)==1){
                        printf("*You should call*\n");
                        printf("\nGoing to flop\n");
                        afterflop(button,potSize,passiveOrAggressive);
                    }else if((findHand(hand,badHands)==1)||(findHand(hand,veryBadHands)==1)){
                        printf("*You should fold*\n");
                        printf("\nGoing to the next hand\n");
                        void goNextHand();
                        //go next
                    }
                }
        }else if((findHand(hand,goodHands)==1)||(findHand(hand,veryGoodHands)==1)){
                printf("*You should bet the pot=%0.2f*\n",potSize);
                potSize+=potSize;
                opponentAction=retOpponentAction();
                if(opponentAction==2){//opponent calls
                    printf("\nGoing to flop\n");
                    potSize+=potSize;
                    afterflop(button,potSize,passiveOrAggressive);
                }else if(opponentAction==5){//opponent folds
                    printf("\nGoing to the next hand\n");
                    void goNextHand();
                    //go next
                }else if(opponentAction==4){//opponent raises
                    betAmt=retOpponentBetOrRaise();
                    potSize+=2*betAmt-potSize;
                    printf("*You should call*\n");
                    printf("\nGoing to flop\n");
                    afterflop(button,potSize,passiveOrAggressive);
                    }
                }
        }

    return 0;

}

int findHand(char hand[5],char range[][5]){
    int result;
    int i=0;
    for(i=0;i<66;i++){
        result=strcmp(hand,range[i]);
        if(result==0){
            return !result;}
    }
    return -1;
}

void goNextHand(){
    return -1;
}

//Pot Odds
//Decision Rule to Call a Bet
void potOdds(float myCallAmt,float totalWinAmt,float winPC,int button,float potSize){
    winPC=winPC/100;
    float limit;
    limit = myCallAmt/totalWinAmt;
    if(winPC>=limit){
        printf("*You should call the bet*\n");
    }else if(winPC<limit){
        printf("*You should not call the bet, you should fold*\n");
        goNextHand();
    }
}

//Implied Odds
//Additional Chips after draw hits needed to call
void impliedOdds(float opponentBetAmt,float winPC, float totalWinAmt){
    float chips;
    chips=opponentBetAmt/winPC-totalWinAmt;
    printf("*You need your opponent to call :%0.2f more chips to breakeven your call*\n",chips);
}

//Fold Equity
//Decision Rule how much to bet when SemiBluff/Bluff
//foldPC decr/incr-> betAmt decr/incr
void foldEquity(float winPC, float foldPC,float potSize){
    float myBetAmt;
    //bluff
    if(winPC==0){
        myBetAmt=(potSize*foldPC)/(1-foldPC);
    }
    //semi bluff
    else if(winPC>0){
        myBetAmt=(potSize*(1.5*winPC+foldPC))/(-1+foldPC+1.5*winPC);
    }
    printf("*For your Bluff/Semi-Bluff , your max bet should be :%0.2f*\n",myBetAmt);
}

//Total Equity
//Decision Rule to see if a Bluff/Semi-Bluff is worth doing
void totalEquity(float winPC,float foldPC){
    float totalEquity;
    totalEquity=foldPC+winPC;
    if(totalEquity>=(100-winPC)){
        printf("*You could Bluff/Semi-Bluff*\n");
    }else {printf("*You should not Bluff/Semi-Bluff, you should fold*\n");
      goNextHand();}
}

//information about what you hit
int info1(){
    int choose;
    int info;
    printf("Did you \n1-> hit something,\n2-> completely missed,\n3-> have a draw\nPress 1,2 or 3 to choose\n");
    scanf("%d",&choose);
    switch(choose){
    case 1: info=1;
            break;
    case 2: info=2;
            break;
    case 3: info=3;
            break;
    }
    return info;
}

//information about if you win or not
int info2(){
    int choose;
    int info;
    printf("Do you believe that your hand wins right now?\n1->YES\n2->MAYBE\n3->NO\nPress 1,2 or 3 to choose\n");
    scanf("%d",&choose);
    switch(choose){
    case 1: info=1;
            break;
    case 2: info=2;
            break;
    case 3: info=3;
            break;
    }
    return info;
}

float retWinPC(){
        float winPC=0.0;
        int NumOfOuts,RiverOrTurn,list,comb;
        printf("******Poker ODDS Calculator******\n");
        printf("Please enter:\n  Number of Cards Remaining 1(river) or 2(turn+river)\n");
        scanf("%d",&RiverOrTurn);

        if(RiverOrTurn==1){

        printf("Choose your outs from the list or press 0 to enter your own\n");
        printf("-----------------------------------------------------------\n");
        printf(" 1->Inside Straight Draw\n 2->Up and Down Straight Draw\n 3->Flush Draw\n 4->2 Overs\n 5->1 Over\n 6->Pair vs Better Pair\n 7->Top Pair vs Two Pair\n 8->Combination\n 0->Else\n");
        scanf("%d",&list);
        switch(list){
        case 1: winPC=8.7;
                break;
        case 2: winPC=17.4;
                break;
        case 3: winPC=19.6;
                break;
        case 4: winPC=13;
                break;
        case 5: winPC=6.5;
                break;
        case 6: winPC=10.9;
                break;
        case 7: winPC=13;
                break;
        case 8:{
            printf("Choose your combinational output\n");
            printf("-----------------------------------------------------------\n");
            printf(" 0->Flush + 2 Overs\n 1->Flush + 1 Over\n 2->Flush + Pair(vs Better Pair)\n 3->Flush + Inside Straight\n 4->Flush + Up and Down Straight\n 5->Up and Down Straight + Pair(vs Better Pair)\n 6->Inside Straight + Pair(vs Better Pair)\n ");
            scanf("%d",&comb);
            switch(comb){
            case 0:winPC=32.6;
                   break;
            case 1:winPC=26.1;
                   break;
            case 2:winPC=32.6;
                   break;
            case 3:winPC=26.1;
                   break;
            case 4:winPC=32.6;
                   break;
            case 5:winPC=30.4;
                   break;
            case 6:winPC=21.7;
                   break;
        }break;}
        case 0:{
            printf("Please enter:\n The Number Of your Outs\n" );
            scanf("%d",&NumOfOuts);

             switch(NumOfOuts){
                case 1:
                    winPC=2.2;
                    break;
                case 2:
                    winPC=4.3;
                    break;
                case 3:
                    winPC=6.5;
                    break;
                case 4:
                    winPC=8.7;
                    break;
                case 5:
                    winPC=10.9;
                    break;
                case 6:
                    winPC=13;
                    break;
                case 7:
                    winPC=15.2;
                    break;
                case 8:
                    winPC=17.4;
                    break;
                case 9:
                    winPC=19.6;
                    break;
                case 10:
                    winPC=21.7;
                    break;
                case 11:
                    winPC=24.0;
                    break;
                case 12:
                    winPC=26.1;
                    break;
                case 13:
                    winPC=28.3;
                    break;
                case 14:
                    winPC=30.4;
                    break;
                case 15:
                    winPC=32.6;
                    break;
                case 16:
                    winPC=34.3;
                    break;
                case 17:
                    winPC=37.0;
                    break;
                case 18:
                    winPC=39.1;
                    break;
                case 19:
                    winPC=41.3;
                    break;
                case 20:
                    winPC=43.5;
                    break;
                }break;
                }}
     printf("Your Win Equity =%0.2f perCent\n",winPC);
     return winPC;
    }else if(RiverOrTurn==2){

        printf("Choose your outs from the list or press 0 to enter your own\n");
        printf("-----------------------------------------------------------\n");
        printf(" 1->Inside Straight Draw\n 2->Up and Down Straight Draw\n 3->Flush Draw\n 4->2 Overs\n 5->1 Over\n 6->Pair vs Better Pair\n 7->Top Pair vs Two Pair\n 8->Combination\n 0->Else\n");
        scanf("%d",&list);
        switch(list){
        case 1: winPC=16.5;
                break;
        case 2: winPC=31.5;
                break;
        case 3: winPC=35;
                break;
        case 4: winPC=24.1;
                break;
        case 5: winPC=12.5;
                break;
        case 6: winPC=20.3;
                break;
        case 7 :winPC=24.1;
                break;
        case 8:{
            printf("Choose your combinational output\n");
            printf("-----------------------------------------------------------\n");
            printf(" 0->Flush + 2 Overs\n 1->Flush + 1 Over\n 2->Flush + Pair(vs Better Pair)\n 3->Flush + Inside Straight\n 4->Flush + Up and Down Straight\n 5->Up and Down Straight + Pair(vs Better Pair)\n 6->Inside Straight + Pair(vs Better Pair)\n ");
            scanf("%d",&comb);
            switch(comb){
            case 0:winPC=54.1;
                   break;
            case 1:winPC=45;
                   break;
            case 2:winPC=54.1;
                   break;
            case 3:winPC=45;
                   break;
            case 4:winPC=54.1;
                   break;
            case 5:winPC=51.2;
                   break;
            case 6:winPC=38.4;
                   break;

            }
            break;
        }

        case 0:{
    printf("Please enter:\n The Number Of your Outs\n" );
            scanf("%d",&NumOfOuts);
     switch(NumOfOuts){
        case 1:
            winPC=4.4;
            break;
        case 2:
            winPC=8.4;
            break;
        case 3:
            winPC=12.5;
            break;
        case 4:
            winPC=16.5;
            break;
        case 5:
            winPC=20.3;
            break;
        case 6:
            winPC=24.1;
            break;
        case 7:
            winPC=27.8;
            break;
        case 8:
            winPC=31.5;
            break;
        case 9:
            winPC=35;
            break;
        case 10:
            winPC=38.4;
            break;
        case 11:
            winPC=41.7;
            break;
        case 12:
            winPC=45.0;
            break;
        case 13:
            winPC=48.1;
            break;
        case 14:
            winPC=51.2;
            break;
        case 15:
            winPC=54.1;
            break;
        case 16:
            winPC=57;
            break;
        case 17:
            winPC=59.8;
            break;
        case 18:
            winPC=62.4;
            break;
        case 19:
            winPC=65;
            break;
            winPC=67.5;
        case 20:
            break;
           }break;}}
        printf("Your Win Equity =%0.2f perCent\n",winPC);
        return winPC;
    }
}

float retFoldPC(){
    float foldEquity;
    int choose,menu;
    printf("What you believe is your Fold Equity?Press\n1-> Enter the probability in Per Cent\n2-> If you don't know enter your opponents tight/loose factor from the menu below:\n");
    scanf("%d",&choose);
    switch(choose){
        case 1:scanf("%f",&foldEquity);
               break;
        case 2:printf("My opponent is(press the number):\n1->Very Tight(very high fold equity)\n2->Tight(high fold equity)\n3->Normal-Tight(average-high fold equity)\n4->Normal(average fold equity)\n5->Normal-Loose(average-low fold equity)\n6->Loose(low fold equity)\n7->Very Loose(very low fold equity)\n");
               scanf("%d",&menu);
               switch(menu){
                    case 1:foldEquity=92.3;
                           break;
                    case 2:foldEquity=78.1;
                           break;
                    case 3:foldEquity=63.9;
                           break;
                    case 4:foldEquity=49.7;
                           break;
                    case 5:foldEquity=35.5;
                           break;
                    case 6:foldEquity=21.3;
                           break;
                    case 7:foldEquity=7.1;
                           break;
                            }
               break;
                  }
    return foldEquity;
}

float retMyBet(float potSize,int betType){
    float bet;
    int drawHeavyBoard;
    printf("Is the board draw heavy (does it have straight or flush draws)?Press:\n1->YES\n2->NO\n");
    scanf("%d",&drawHeavyBoard);

        if(betType==1){
        //value bet
            bet=0.4*potSize;
        }else if(betType==2){
        //information bet
            bet=0.25*potSize;
        }else if(betType==3){
        //semi bluff bet
            bet=0.35*potSize;
        }

        if(drawHeavyBoard==1){
            bet=bet+0.1*potSize;
        }
        return bet;
}

float retMyRaise(float opponentBetAmt,int raiseType){
    float raise;
    int drawHeavyBoard;
    printf("Is the board draw heavy (does it have straight or flush draws)?\nPress: 1->YES\n2->NO\n");
    scanf("%d",&drawHeavyBoard);

    if(raiseType==1){
    //value raise
        raise=opponentBetAmt*3;
    }else if(raiseType==2){
    //semi bluff raise
        raise=opponentBetAmt*2.5;
    }

    if(drawHeavyBoard==1){
        raise=raise+0.3*opponentBetAmt;
    }
    return raise;
}

float retPotSize(){
    float potSize;
    printf("Please enter the Pot Size:\n");
    scanf("%f",&potSize);
    return potSize;
}

int retOpponentAction(){
    int action=0;
    printf("Please enter the opponent's action.Press:\n1->Check\n2->Call\n3->Bet\n4->Raise\n5->Fold\n");
    scanf("%d",&action);
    return action;
}

float retOpponentBetOrRaise(){
    float bet;
    printf("Please enter the opponent's bet amount or raise amount:\n");
    scanf("%f",&bet);
    return bet;
}

void afterflop(int button,float potSize,int passiveOrAggressive){
    int opponentAction,opponentActionSecond,inf1,inf2,inf3;
    float win,opponentBet,myCall,totalWin,fold,myBet;

//PLAYS SECOND
    if(button==playsSecond){
          opponentAction=retOpponentAction();
          if(opponentAction==3){//opponent bets
                opponentBet=retOpponentBetOrRaise();
                myCall=opponentBet;
                totalWin=potSize+myCall+opponentBet;

                inf1=info1();
                if(inf1==1){//hit
                    inf2=info2();
                    if(inf2==1){//yes
                        if(passiveOrAggressive==1){//passive
                            printf("*You should call the bet*\n");
                            potSize=retPotSize();
                            afterflop(button,potSize,passiveOrAggressive);
                        }else if(passiveOrAggressive==0){//aggressive
                            myBet=retMyRaise(opponentBet,1);//value raise
                            printf("*You should raise for value to :%0.2f*\n",myBet);
                            opponentActionSecond=retOpponentAction();
                            if(opponentActionSecond==5){//opponent folds
                                goNextHand();
                            }else if(opponentActionSecond==2){//opponent calls
                                potSize=retPotSize();
                                afterflop(button,potSize,passiveOrAggressive);
                            }
                        }
                    }else if(inf2==2){//maybe
                        if(passiveOrAggressive==1){//passive
                            win=retWinPC();
                            potSize=retPotSize();
                            potOdds(myCall,totalWin,win,button,potSize);
                        }else if(passiveOrAggressive==0){//aggressive
                            printf("*You should call the bet*\n");
                            potSize=retPotSize();
                            afterflop(button,potSize,passiveOrAggressive);
                        }

                    }else if(inf2==3){//no
                        win=retWinPC();
                        potSize=retPotSize();
                        potOdds(myCall,totalWin,win,button,potSize);
                        potSize=retPotSize();
                        afterflop(button,potSize,passiveOrAggressive);
                    }
                }else if(inf1==2){//miss
                    win=retWinPC();
                    potSize=retPotSize();
                    potOdds(myCall,totalWin,win,button,potSize);
                    potSize=retPotSize();
                    afterflop(button,potSize,passiveOrAggressive);
                }else if(inf1==3){//draw
                    if(passiveOrAggressive==1){//opponent is passive
                        win=retWinPC();
                        fold=retFoldPC();
                        totalEquity(win,fold);
                        potSize=retPotSize();
                        foldEquity(win,fold,potSize);
                        opponentActionSecond=retOpponentAction();
                        if(opponentActionSecond==5){//opponent folds
                            goNextHand();
                        }else if(opponentActionSecond==2){//opponent calls
                            potSize=retPotSize();
                            afterflop(button,potSize,passiveOrAggressive);
                        }
                    }else if(passiveOrAggressive==0){//opponent is aggressive
                        win=retWinPC();
                        potSize=retPotSize();
                        potOdds(myCall,totalWin,win,button,potSize);
                        potSize=retPotSize();
                        afterflop(button,potSize,passiveOrAggressive);
                    }
                }

          }else if(opponentAction==1){//opponent checks
              inf1=info1();
              if(inf1==1){//hit
                  inf2=info2();
                  if(inf2==1){//yes
                      potSize=retPotSize();
                      myBet=retMyBet(potSize,1);//value bet
                      printf("*You should bet for value:%0.2f*\n",myBet);
                      opponentActionSecond=retOpponentAction();
                      if(opponentActionSecond==5){//opponent folds
                        goNextHand();
                      }else if(opponentActionSecond==2){//opponent calls
                        potSize=retPotSize();
                        afterflop(button,potSize,passiveOrAggressive);
                      }else if(opponentActionSecond==4){//opponent raises
                        inf3=info2();
                        opponentBet=retOpponentBetOrRaise();
                        myCall=opponentBet;
                        totalWin=potSize+myCall+opponentBet;
                        if(inf3==1){//yes
                            printf("*You should call the raise*\n");
                            potSize=retPotSize();
                            afterflop(button,potSize,passiveOrAggressive);
                        }else if(inf3==2){//maybe
                            if(passiveOrAggressive==1){//passive
                                win=retWinPC();
                                potSize=retPotSize();
                                potOdds(myCall,totalWin,win,button,potSize);
                                potSize=retPotSize();
                                afterflop(button,potSize,passiveOrAggressive);
                            }else if(passiveOrAggressive==0){//aggressive
                                printf("*You should call the raise*\n");
                                potSize=retPotSize();
                                afterflop(button,potSize,passiveOrAggressive);
                            }
                        }else if(inf3==3){//no
                            printf("*You should fold*\n");
                            goNextHand();
                        }
                      }

                  }else if(inf2==2){//maybe
                      if(passiveOrAggressive==1){//passive
                            potSize=retPotSize();
                            myBet=retMyBet(potSize,2);//information bet
                            printf("*You should bet for information:%0.2f*\n",myBet);
                            opponentActionSecond=retOpponentAction();
                            if(opponentActionSecond==5){//opponent folds
                                goNextHand();
                            }else if(opponentActionSecond==2){//opponent calls
                                potSize=retPotSize();
                                afterflop(button,potSize,passiveOrAggressive);
                            }else if(opponentActionSecond==4){//raises
                                opponentBet=retOpponentBetOrRaise();
                                myCall=opponentBet;
                                totalWin=potSize+myCall+opponentBet;
                                win=retWinPC();
                                potSize=retPotSize();
                                potOdds(myCall,totalWin,win,button,potSize);
                                potSize=retPotSize();
                                afterflop(button,potSize,passiveOrAggressive);
                            }
                      }else if(passiveOrAggressive==0){//aggressive
                            printf("*You should check back*\n");
                            potSize=retPotSize();
                            afterflop(button,potSize,passiveOrAggressive);
                      }
                  }else if(inf2==3){//no
                      printf("*You should check back*\n");
                      potSize=retPotSize();
                      afterflop(button,potSize,passiveOrAggressive);
                  }
              }else if(inf1==2){//miss
                  printf("*You should check*\n");
                  potSize=retPotSize();
                  afterflop(button,potSize,passiveOrAggressive);
              }else if(inf1==3){//draw
                  if(passiveOrAggressive==1){//passive
                      win=retWinPC();
                      fold=retFoldPC();
                      totalEquity(win,fold);
                      potSize=retPotSize();
                      foldEquity(win,fold,potSize);
                      opponentActionSecond=retOpponentAction();
                            if(opponentActionSecond==5){//opponent folds
                                goNextHand();
                            }else if(opponentActionSecond==2){//opponent calls
                                potSize=retPotSize();
                                afterflop(button,potSize,passiveOrAggressive);
                            }else if(opponentActionSecond==4){//raises
                                opponentBet=retOpponentBetOrRaise();
                                myCall=opponentBet;
                                totalWin=potSize+myCall+opponentBet;
                                win=retWinPC();
                                potSize=retPotSize();
                                potOdds(myCall,totalWin,win,button,potSize);
                                potSize=retPotSize();
                                afterflop(button,potSize,passiveOrAggressive);
                            }
                  }else if(passiveOrAggressive==0){//aggressive
                      printf("*You should check*\n");
                      potSize=retPotSize();
                      afterflop(button,potSize,passiveOrAggressive);
                  }
              }
          }
//PLAYS FIRST
    }else if(button==playsFirst){
        inf1=info1();
        if(inf1==1){//hit
            inf2=info2();
            if(inf2==1){//yes
                potSize=retPotSize();
                myBet=retMyBet(potSize,1);//value bet
                printf("*You should bet for value:%0.2f*\n",myBet);
                opponentActionSecond=retOpponentAction();
                     if(opponentActionSecond==5){//opponent folds
                           goNextHand();
                     }else if(opponentActionSecond==2){//opponent calls
                            potSize=retPotSize();
                            afterflop(button,potSize,passiveOrAggressive);
                     }else if(opponentActionSecond==4){//raises
                            opponentBet=retOpponentBetOrRaise();
                            myCall=opponentBet;
                            totalWin=potSize+myCall+opponentBet;
                            win=retWinPC();
                            potSize=retPotSize();
                            potOdds(myCall,totalWin,win,button,potSize);
                            potSize=retPotSize();
                            afterflop(button,potSize,passiveOrAggressive);
                     }
            }else if(inf2==2){//maybe
                if(passiveOrAggressive==1){//passive
                     potSize=retPotSize();
                     myBet=retMyBet(potSize,2);//information bet
                     printf("*You should bet for information:%0.2f*\n",myBet);
                     opponentActionSecond=retOpponentAction();
                     if(opponentActionSecond==5){//opponent folds
                           goNextHand();
                     }else if(opponentActionSecond==2){//opponent calls
                            potSize=retPotSize();
                            afterflop(button,potSize,passiveOrAggressive);
                     }else if(opponentActionSecond==4){//raises
                            opponentBet=retOpponentBetOrRaise();
                            myCall=opponentBet;
                            totalWin=potSize+myCall+opponentBet;
                            win=retWinPC();
                            potSize=retPotSize();
                            potOdds(myCall,totalWin,win,button,potSize);
                            potSize=retPotSize();
                            afterflop(button,potSize,passiveOrAggressive);
                     }
                }else if(passiveOrAggressive==0){//aggressive
                    printf("*You should check*\n");
                    opponentAction=retOpponentAction();
                    if(opponentAction==1){//opponent checks
                        potSize=retPotSize();
                        afterflop(button,potSize,passiveOrAggressive);
                    }else if(opponentAction==3){//opponent bets
                        opponentBet=retOpponentBetOrRaise();
                        myCall=opponentBet;
                        totalWin=potSize+myCall+opponentBet;
                        win=retWinPC();
                        potSize=retPotSize();
                        potOdds(myCall,totalWin,win,button,potSize);
                        potSize=retPotSize();
                        afterflop(button,potSize,passiveOrAggressive);
                    }
                }
            }else if(inf2==3){//no
                printf("*You should check*\n");
                opponentAction=retOpponentAction();
                if(opponentAction==1){//opponent checks
                    potSize=retPotSize();
                    afterflop(button,potSize,passiveOrAggressive);
                }else if(opponentAction==3){//opponent bets
                    opponentBet=retOpponentBetOrRaise();
                    myCall=opponentBet;
                    totalWin=potSize+myCall+opponentBet;
                    win=retWinPC();
                    potSize=retPotSize();
                    potOdds(myCall,totalWin,win,button,potSize);
                    potSize=retPotSize();
                    afterflop(button,potSize,passiveOrAggressive);
                }
            }
        }else if(inf1==2){//miss
            printf("*You should check*\n");
            opponentAction=retOpponentAction();
            if(opponentAction==1){//opponent checks
                potSize=retPotSize();
                afterflop(button,potSize,passiveOrAggressive);
            }else if(opponentAction==3){//opponent bets
                opponentBet=retOpponentBetOrRaise();
                myCall=opponentBet;
                totalWin=potSize+myCall+opponentBet;
                win=retWinPC();
                potSize=retPotSize();
                potOdds(myCall,totalWin,win,button,potSize);
                potSize=retPotSize();
                afterflop(button,potSize,passiveOrAggressive);
            }
        }else if(inf1==3){//draw
            if(passiveOrAggressive==0){//aggressive
                printf("*You should check*\n");
                opponentAction=retOpponentAction();
                if(opponentAction==1){//opponent checks
                    potSize=retPotSize();
                    afterflop(button,potSize,passiveOrAggressive);
                }else if(opponentAction==3){//opponent bets
                    opponentBet=retOpponentBetOrRaise();
                    myCall=opponentBet;
                    totalWin=potSize+myCall+opponentBet;
                    win=retWinPC();
                    potSize=retPotSize();
                    potOdds(myCall,totalWin,win,button,potSize);
                    potSize=retPotSize();
                    afterflop(button,potSize,passiveOrAggressive);
                }
            }else if(passiveOrAggressive==1){//passive
                win=retWinPC();
                fold=retFoldPC();
                totalEquity(win,fold);
                potSize=retPotSize();
                foldEquity(win,fold,potSize);
                opponentActionSecond=retOpponentAction();
                    if(opponentActionSecond==5){//opponent folds
                         goNextHand();
                    }else if(opponentActionSecond==2){//opponent calls
                         potSize=retPotSize();
                         afterflop(button,potSize,passiveOrAggressive);
                    }else if(opponentActionSecond==4){//opponent raises
                        opponentBet=retOpponentBetOrRaise();
                        myCall=opponentBet;
                        totalWin=potSize+myCall+opponentBet;
                         win=retWinPC();
                         potSize=retPotSize();
                         potOdds(myCall,totalWin,win,button,potSize);
                         potSize=retPotSize();
                         afterflop(button,potSize,passiveOrAggressive);
                    }
            }
        }

    }
}
