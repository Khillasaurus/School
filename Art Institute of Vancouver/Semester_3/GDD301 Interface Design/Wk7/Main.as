package
{
	import flash.display.Sprite;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import fl.transitions.Tween;
	import fl.transitions.easing.*;
	import fl.transitions.TweenEvent;
	import flash.events.MouseEvent;
	import flash.display.Stage;
	import hud.cHealthBar;
	import hud.cScreenFlash;
	
	public class Main extends Sprite
	{
		public var ball1:cBall;
		public var myTween:Tween;
		public var damageFlash:cScreenFlash;
		public var healthBar:cHealthBar;
		public var theStage:Stage;
		
		public function Main()
		{
			var shouldTween:Boolean = true;
			ball1 = new cBall();
			addChild(ball1);
			
			healthBar = new cHealthBar();
			addChild(healthBar);
			
			addChild(damageFlash);
			
			/*
			myTimer = new Timer(100, 1); // 100 ms, run one time
			myTimer.addEventListener(TimerEvent.TIMER, runOnce);
			*/
			
			//if(shouldTween)
			//{
				//myTween = new Tween(ball1, "x", Elastic.easeOut, 100, 300, 5, true);
				//if(myTween)
				//{
					stage.addEventListener(KeyboardEvent.KEY_DOWN, MoveObject);
				//}
			//}
			ball1.addEventListener(MouseEvent.CLICK, objectClicked);
		}
		
		/*
		function runOnce(event:TimerEvent):void
		{
			trace("runOnce() called @ " + myTimer.currentCount + " ms");
		}
		*/
		
		public function MoveObject(k:KeyboardEvent):void
		{
			theStage = this.stage;
			ball1.x = Math.random() * (theStage.stageWidth - 10) + 10;
			ball1.y = Math.random() * (theStage.stageHeight - 10) - 10;
			//myTween.yoyo();
		}
		
		public function objectClicked(mb:MouseEvent):void
		{
			theStage = this.stage;
			healthBar.health -= 10;
			
			damageFlash = new cScreenFlash(theStage.stageWidth, theStage.stageHeight, 0xFF0000);
			addChild(damageFlash);
			damageFlash.instantiateTimer();
			damageFlash.clearHealthFlash();
		}
	}
}