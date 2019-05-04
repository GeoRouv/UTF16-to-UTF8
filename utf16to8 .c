#include <stdio.h>

int main(void){
	int x,y,h,j,z,flag;
				//z=Unicode,h=pair to 2-byte encoding or 1st pair to 4byte-encoding,j=2nd pair to a 4byte-encoding,

	x=getchar();				
	y=getchar();
	while(x!=EOF){		//Don't stop until the end of the file
		flag=0;		//Indication if character is encoded in UTF-16
		h=(x<<=8)|y;	
		if((h<=0xD7FF)||(h>=0xE000 && h<=0xFFFF)){//2-byte encoded,h exists in [0x0000,0xD7FF] or [0xE000,0xFFFF].
			flag=1;
			z=h;    						
		}						
		if(h>=0xD800 && h<=0xDBFF){		//4-byte encoded,h exists in [0xD800,0xDBFF].
			x=getchar();	
			y=getchar();
			j=(x<<8)|y;				
			if(j>=0xDC00 && j<=0xDFFF){	//j exists in [0xDC00,0xDFFF].
				flag=1;
				h-=0xD800;
				j-=0xDC00;
				z=(h<<10)|j;
				z+=0x10000;		//Unicode=[(1stpair-0xD800)o(2ndpair-0xDC00)]+0x10000  , where o stands for composition
						
			}
		
		}
		if(!flag){				//Error:false input text file
			printf("\nTEXT NOT IN UTF-16");
			break;
		}

	//////////////////////////////////////////////////Start Of UTF-8 encoding///////////////////////////////////////////////

		
		
  		if (z < 0x80) {				//Encoding using 1 byte , 0xxxxxxx
  			putchar (z);
  		}
  		else if (z < 0x800) {			//Encoding using 2 bytes , 110xxxxx 10xxxxxx
  	  		putchar (192 | z>>6);
   			putchar (128 | z & 63);
			
  		}
  		else if (z <= 0xFFFF) {			//Encoding using 3 bytes , 1110xxxx 10xxxxxx 10xxxxxx
			if(z<0xD800 || z>0xDFFF){
  				putchar (224| z>>12);
  				putchar (128 | z>>6 & 63);
  				putchar (128 | z & 63);
			}
			
 		}
 		else if (z<=0x10FFFF) {			//Encoding using 4 bytes , 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
  			putchar (240 | z>>18);
  			putchar (128 | z>>12 & 63);
  			putchar (128 | z>>6 & 63);
  			putchar (128 | z & 63);
 		}
		
			

	x=getchar();					//Moving to next characters	
	y=getchar();
	}

return 0;	
}
