package hud
{
	import flash.display.Sprite;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.filters.GlowFilter;
	import flash.filters.BlurFilter;
	import flash.geom.ColorTransform;
	import flash.utils.Timer;
	import flash.events.TimerEvent;

	public class cScreenFlash extends Sprite
	{
		public var theStage:Stage;
		public var health:Number = 10;
		public var bg1:cScreenFlash;
		public var myTimer:Timer;

		private var bg:Sprite;
		private var bgW:int,bgH:int;
		private var bgCol:uint;
		private var maxHealth:Number = 10;
		private var curHealth:Number = 10;
		private var lastHealth:Number = 10;
		private var glow:GlowFilter;
		private var glowMax:Number = 8;
		private var glowAmount:Number = 0;
		private var fall:Number = 1;

		public function cScreenFlash(_bgW:int, _bgH:int, _bgCol:uint)
		{
			bgW = _bgW;
			bgH = _bgH;
			bgCol = _bgCol;

			bg = new Sprite();
			bg.graphics.beginFill(0x000000);
			bg.graphics.drawRect(0, 0, bgW, bgH);
			bg.graphics.endFill();

			addChild(bg);

			glow = new GlowFilter(bgCol,1,0,16,1,4,false,false);
			addEventListener(Event.ENTER_FRAME, update);
		}
		
		function runOnce(event:TimerEvent):void
		{
			trace("runOnce() called @ " + myTimer.currentCount + " ms");
		}
		
		public function instantiateTimer():void
		{
			myTimer = new Timer(100, 1); // 100 ms, run one time
			myTimer.addEventListener(TimerEvent.TIMER, runOnce);
			myTimer.start();
		}
		
		public function clearHealthFlash():void
		{
			myTimer.addEventListener(TimerEvent.TIMER, clearHealthFlash);
			removeChild(bg);
		}

		private function drawBar(perc:Number):void
		{
			bg.graphics.clear();
			bg.graphics.beginFill(bgCol);
			bg.graphics.drawRect(0, 0, bgW * perc, bgH);
			bg.graphics.endFill();
		}

		private function glowing():void
		{
			if (glowAmount > 1)
			{
				glowAmount = 8 + Math.cos(fall * glowMax);
				fall +=  0.1;
				glow.blurX = glow.blurY = glowAmount;
				bg.filters = [glow];
			}
			else
			{
				glow.blurX = glow.blurY = 0;
				fall = 0;
			}
		}

		public function update(e:Event):void
		{
			if (health >= maxHealth)
			{
				lastHealth = health = maxHealth;
				drawBar(health / maxHealth);
			}
			else if (health < maxHealth && health > 0)
			{
				if (lastHealth > health)
				{
					if (curHealth != health)
					{
						glowAmount = glowMax;
						curHealth = health;
					}
					lastHealth -=  0.5;
				}
				drawBar(lastHealth / maxHealth);
			}
			else
			{
				health = 0;
				if (lastHealth > 0)
				{
					lastHealth -=  0.5;
					drawBar(lastHealth / maxHealth);
				}
				else
				{
					bg.graphics.clear();
				}
			}
			glowing();
		}
	}
}