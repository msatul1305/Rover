import processing.serial.*;
Serial s;
Button b[]=new Button[6];  
String st=null;
int xc=100,yc=450;;
int pbx=100,cbx=100;
int pby=450,cby=450;
int r=0,g=0,bl=0,i=0,j=0;
void setup(){
  size(500,500);
  //frameRate(2000);
  background(255);  
  s = new Serial(this, "COM8", 115200);
  b[0]=new Button(50,20,50,20,"Forward");   
  b[1]=new Button(45,80,59,20,"Backward");    
  b[2]=new Button(10,50,50,20,"Left");
  b[3]=new Button(80,50,50,20,"Right");
  b[4]=new Button(20,120,50,20,"Start");
  b[5]=new Button(20,150,50,20,"Stop");
}
void draw(){
         if(st!=null)
          if(st.equals("q")&&(r!=10&&g!=10&&bl!=10)){
          fill(r,g,bl);
          rect(xc-7.5,yc-7.5,15,15);
        }
}

void serialEvent(Serial se){
   
   if(se.available()>0){
      if(i==0&&j==0){
        st=se.readString(); 
        println(st);      
        }
      if(st.equals("q")){
          if(i==0){    r=se.read();i++; }
              
          else if(i==1){    g=se.read();i++;}
              
          else if(i==2){     bl=se.read(); i=0;  }
          
          if(r==-1||g==-1||bl==-1){   j=1; i=0; if(r==10||g==10||bl==10)  j=0; return;  }
          if(r==10||g==10||bl==10){ j=0; return;  }
          println(r+" "+g+" "+bl);

    }
  }
  
}
void mousePressed(){
  for(int x=0;x<6;x++){    
     b[x].checkarea();     
  }
}