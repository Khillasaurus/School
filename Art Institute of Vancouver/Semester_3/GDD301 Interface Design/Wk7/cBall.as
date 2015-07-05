package
{
	import flash.display.Sprite;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.filters.GlowFilter;
	import flash.filters.BlurFilter;
	import Math;
	
	public class cBall extends Sprite
	{
		public var theStage:Stage;
		public var angle:Number = 0;
		public var glow:GlowFilter;
		public var blur:BlurFilter;
		public var startX:Number;
		public var startY:Number;
		
		public function cBall()
		{
			graphics.beginFill(0xFF0000);
			graphics.drawCircle(0, 0, 25);
			graphics.endFill();
			
			glow = new GlowFilter(0xFFFFFF, 1, 0, 16, 1, 4, false, false);
			blur = new BlurFilter(24, 24, 3);
			//this.filters = [glow, blur];
			
			addEventListener(Event.ADDED_TO_STAGE, Added)
			addEventListener(Event.ENTER_FRAME, Update)
		}
		
		public function Added(e:Event):void
		{
			theStage = this.stage;
			startX = theStage.stageWidth/2;
			startY = theStage.stageHeight/2;
			this.x = startX;
			this.y = startY;
		}
		
		public function abs( value:Number ):Number
		{
			//return (value ^ (value >> 31)) – (value >> 31);
			//return (Math.pow( value, (value >> 31) )) – (value >> 31);
			return value < 0 ? -value : value;
		}
		
		public function Update(e:Event):void
		{
			var xChange:Number = 7.5;
			var yChange:Number = 10;
			var distance:Number = 30;
			this.x += Math.sin(angle) * xChange;
			this.y += Math.cos(angle) * (-yChange);
			angle += 0.1;
			if((this.x > (theStage.stageWidth - distance)) || (this.x < distance))
			{
				blur = new BlurFilter(24, 24, distance/( abs( (theStage.stageWidth/2)-this.x ) ));
				this.filters = [glow, blur];
			}
			else if((this.x < (theStage.stageWidth - distance)) || (this.x > distance))
			{
				blur = new BlurFilter(0, 0, 0);
				this.filters = [glow, blur];
			}
			if( (this.y < (-(theStage.stageHeight - distance))) || (this.y > (-distance)) )
			{
				blur = new BlurFilter(24, 24, distance/( abs( (theStage.stageHeight/2)-this.y ) ));
				this.filters = [glow, blur];
			}
			else if((this.y > (-(theStage.stageHeight - distance))) || (this.y < (-distance)))
			{
				blur = new BlurFilter(0, 0, 0);
				this.filters = [glow, blur];
			}
		}
	}
}



//In Class Notes
//Tween(Object, "String", EasingFunction, start, end, time, SecsBoolean);
	//SecsBoolean determines whether you want to work in seconds(true) or frames(false)
