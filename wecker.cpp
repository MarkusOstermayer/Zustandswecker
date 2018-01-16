#include "mbed.h"
#include "BtnEventM0S.h"

Serial pc(USBTX, USBRX);

BtnEventM0  sw4(P0_15);
BtnEventM0  sw3(P0_23);
BtnEventM0  sw1(P0_10);

class Wecker{
	public:
		void init();
		void clkrunning();
		void switchH();
		void switchM();
	private:
		void Actionclk();
		void ActionH(int increment);
		void ActionM(int increment);
	
	public:
		int state;
	private:
		Timer t1; //10Hz Timer
};

Wecker w1;
int hh=0;
int mm=0;
int main()
{
	pc.baud(500000);
	w1.init();
	sw4.Init(); sw3.Init(); sw1.Init();
	
	
	while(1){
		if(w1.state==1){
			w1.clkrunning();
		}
		if(w1.state==2){
			w1.switchH();
		}
		
		if(w1.state==3){
			w1.switchM();
		}
				
	
	}
  return 1;
}
void Wecker::init(){
	state=1;
	t1.start();
}

void Wecker::clkrunning(){
	pc.printf("1 Clock running\n");
	pc.printf("3 -1\n");
	while(1){
		Actionclk();
		if(sw4.CheckFlag()){
			state=2;
			return;
		}
	}
}
void Wecker::Actionclk(){
	
	if(t1.read_ms()>100){
		t1.reset();
		mm++;
		if(mm>30){
			mm=0;
			hh+=1;
		}
		if(hh>=24){
			hh=0;
			mm=0;
		}
		pc.printf("2 %02d:%02d\n",hh,mm);
	}
	
}
void Wecker::switchH(){
	pc.printf("1 Edit hh\n");
	pc.printf("3 %d\n", 0);
	while(1){
		if(sw1.CheckFlag() or sw1.CheckButton()){
			ActionH(-1);
			wait_ms(100);
			pc.printf("2 %02d:%02d\n",hh,mm);
		}
		if(sw3.CheckFlag() or sw3.CheckButton()){
			ActionH(1);
			wait_ms(100);
			pc.printf("2 %02d:%02d\n",hh,mm);
		}
		if(sw4.CheckFlag()){
			state=3;
			return;
		}
		
	}
}
void Wecker::ActionH(int increment){
		hh+= increment;
		if(hh<0){
			hh=0;
		}
		if(hh>24){
			hh=0;
		}
}
void Wecker::switchM(){
	pc.printf("1 Edit mm\n");
	pc.printf("3 %d\n", 3);
	while(1){
		if(sw1.CheckFlag() or sw1.CheckButton()){
			ActionM(-1);
			wait_ms(100);
			pc.printf("2 %02d:%02d\n",hh,mm);
		}
		if(sw3.CheckFlag() or sw3.CheckButton()){
			ActionM(1);
			wait_ms(100);
			pc.printf("2 %02d:%02d\n",hh,mm);
		}
		if(sw4.CheckFlag()){
			state=1;
			
			return;
		}
	}
}
void Wecker::ActionM(int increment){
		mm+=increment;
		if(mm>30){
			hh+=1;
			mm=0;
			if(hh>24){
				hh=0;
			}
		}
		if(mm<0){
			mm=0;
		}
}
