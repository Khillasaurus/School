package 
{
	import flash.display.*;
	import flash.events.*;
	import flash.text.*;

	public class Main extends MovieClip
	{

		public function Main()
		{
			addEventListener(Event.ENTER_FRAME, objMove);
			addEventListener(Event.ENTER_FRAME, checkCollision);
		}

		private function objMove(event:Event):void
		{
			//move star with mouse
			star.x = mouseX;
			star.y = mouseY;
		}
		
		private function checkCollision(event:Event):void
		{
			if(moon.hitTestPoint(mouseX, mouseY, true))
			{
				messageText1.text = "hitTextPoint: YES";
			}
			else
			{
				messageText1.text = "hitTextPoint: NO";
			}
			
			if(star.hitTestObject(moon))
			{
				messageText2.text = "hitTestObject: YES";
			}
			else
			{
				messageText2.text = "hitTestObject: NO";
			}
		}
		
	}
}
import flash.events.KeyboardEvent;



/*



//Constructor Function
stage.addEventListener(KeyboardEvent.KEY_DOWN, keyPressed);

//Keyboard Functions
public function keyPressed(k:KeyboardEvent):void
{
	if( k.keykode == 32 )
	{
		
	}
}

//REMOVING OBJECTS
//Object is called Target

public function killTarget(toDie:MouseEvent):void
{
	var deadTarget:Target = ( toDie.target as Target );
	removeChild(deadTarget);
}

*/




//Text Book on Safari Books Online That I Should use: Animation for Action Script 3 Making Things Move