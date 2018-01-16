## Projekt Zustandswecker
### Zustandsdiagram
![](https://image.prntscr.com/image/j8oD86g3SAGzI-FvdgFJDA.png)

### Zustandsauflistung
#### State1
In State 1 wird der Wecker angezeigt und zählt hoch, alle 10 Hz wird das Display upgedatet.
Indem SW4 gedrückt wird, wird der State gewechselt

#### State2
Hier werden die Stunden editiert; Indem man SW1 druckt werden die Stunden hochgezählt, indem man sw3 drückt werden sie verringert.
Das Incrementieren und decrementieren soll auch über einen continous press realisiert werden, es wird also verringert, wenn man draufdrückt und, wenn man gedrückt hält
Mit SW4 wird in den nächsten State gewechselt

#### State3
Hier werden die Minuten editiert; Indem man SW1 druckt werden die MInuten hochgezählt, indem man sw3 drückt werden sie verringert.
Das Oncrementieren und decrementieren soll auch über einen continous press realisiert werden, es wird also verringert, wenn man draufdrückt und, wenn man gedrückt hält
Mit SW4 wird in den nächten State gewechselt


### Codesnippets
#### Klasse
``` c
class Wecker{
    //Funktionen
	public:
		void init(); //Initialisierung, legt den Anfangsstatus fest
		void clkrunning();  //Interface für Actioncls-Methode, Abprüfen von T1 und des SW4s
		void switchH();     //Interface für ActionH_Methode, abprüfen der Buttons
		void switchM();     //Interface für ActionH_Methode, abprüfen der Buttons
	private:
		void Actionclk();   //Hier wird die CLock berechnet und
		void ActionH(int increment);    //Stunden anhand des Increments anpassen (1;-1)
		void ActionM(int increment);    //Minuten anhand des Increments anpassen (1;-1)
	//Variablen und Objekte
	public:
		int state;                      //Gibt den aktuellen Sttaus aus
	private:
		Timer t1; //10Hz Timer          //Aktialisierungstimer für clkrunning
};
```
#### Public Variables and Objekts
``` c
Serial pc(USBTX, USBRX);
BtnEventM0  sw4(P0_15);
BtnEventM0  sw3(P0_23);
BtnEventM0  sw1(P0_10);
Wecker w1;
int hh=0;
int mm=0;
```
#### Main
``` c
int main(){
	pc.baud(500000);
	w1.init(); sw4.Init(); sw3.Init(); sw1.Init(); //Initialisierungen
	
	while(1){
		if(w1.state==1){ //Abprüfen, ob man sich im ersten State befindet
			w1.clkrunning();
		}
		if(w1.state==2){ //Abprüfen, ob man sich im zweiten State befindet
			w1.switchH();
		}
		if(w1.state==3){//Abprüfen, ob man sich im dritten State befindet
			w1.switchM();
		}
	}
  return 1;
}
```