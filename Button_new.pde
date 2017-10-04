  class Button{
    int x,y,w,h;  
    String l;    
    Button(int x1,int y1,int w1,int h1,String l1){  x=x1;  y=y1;  w=w1;  h=h1;  l=l1; 
        fill(255);
        rect(x,y,w,h);    
        fill(0);
        //textSize(h-20);
        text(" "+l,x,y+15);  
    }
    void checkarea(){    
      if(mouseX>=x&&mouseX<=(x+w))      
        if(mouseY>=y&&mouseY<=(y+h))
         {       move();  }    
        else return;
      else return ;   
    }    
    void move(){
      if((cbx-pbx)==50){
        if((st.equals("l")||st.equals("T")||st.equals("f"))&&l.equals("Forward")){   s.write('f');  xc+=50; line(xc-50,yc,xc,yc); }
        else if((st.equals("l")||st.equals("T"))&&l.equals("Left")){    yc-=50; s.write('l');  line(xc,yc+50,xc,yc);     }
        else if((st.equals("r")||st.equals("T"))&&l.equals("Right")){   yc+=50; s.write('r');  line(xc,yc-50,xc,yc);     }
        else if(l.equals("Backward")){  s.write('b');  xc-=50;    }
      }
      
      else if((cbx-pbx)==-50){
        if((st.equals("l")||st.equals("T")||st.equals("f"))&&l.equals("Forward")){   s.write('f');  xc-=50; line(xc+50,yc,xc,yc); }
        else if((st.equals("l")||st.equals("T"))&&l.equals("Left")){    yc+=50; s.write('l');  line(xc,yc-50,xc,yc);     }
        else if((st.equals("r")||st.equals("T"))&&l.equals("Right")){   yc-=50; s.write('r');  line(xc,yc+50,xc,yc);     }
        if(l.equals("Backward")){  s.write('b');  xc+=50;    }
      }
      else if((cby-pby)==50){
        if((st.equals("l")||st.equals("T")||st.equals("f"))&&l.equals("Forward")){   s.write('f');  yc+=50; line(xc,yc-50,xc,yc); }
        else if((st.equals("l")||st.equals("T"))&&l.equals("Left")){    xc+=50; s.write('l');  line(xc-50,yc,xc,yc);     }
        else if((st.equals("r")||st.equals("T"))&&l.equals("Right")){   xc-=50; s.write('r');  line(xc+50,yc,xc,yc);     }
        if(l.equals("Backward")){  s.write('b');   yc-=50;    }
      }
      else if((cby-pby)==-50||(cby-pby)==0){
        if((st.equals("l")||st.equals("T")||st.equals("f"))&&l.equals("Forward")){   s.write('f');  yc-=50; line(xc,yc+50,xc,yc); }
        else if((st.equals("l")||st.equals("T"))&&l.equals("Left")){    xc-=50; s.write('l');  line(xc+50,yc,xc,yc);     }
        else if((st.equals("r")||st.equals("T"))&&l.equals("Right")){   xc+=50; s.write('r');  line(xc-50,yc,xc,yc);     }
        if(l.equals("Backward")){  s.write('b');  yc+=50;    }
      }
     
     
      pbx=cbx;  cbx=xc;
      pby=cby;  cby=yc;
      if(l.equals("Stop"))
          s.write('s');
    }
}