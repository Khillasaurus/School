package hud
{
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.filters.GlowFilter;
	import flash.geom.ColorTransform;

	public class cHealthBar extends Sprite
	{
		public var health:Number = 100;

		private var bg:Sprite;
		private var bar:Sprite;
		private var barW:int,barH:int;
		private var col:uint;
		private var maxHealth:Number = 100;
		private var curHealth:Number = 100;
		private var lastHealth:Number = 100;
		private var glow:GlowFilter;
		private var glowMax:Number = 8;
		private var glowAmount:Number = 0;
		private var fall:Number = 1;

		public function cHealthBar(hbW:int = 100, hbH:int = 20, hbCol:uint = 0x00FF00)
		{
			barW = hbW;
			barH = hbH;
			col = hbCol;

			bg = new Sprite();
			bg.graphics.beginFill(0x000000);
			bg.graphics.drawRect(0, 0, barW, barH);
			bg.graphics.endFill();
			addChild(bg);

			bar = new Sprite();
			addChild(bar);

			glow = new GlowFilter(col,1,0,16,1,4,false,false);
			addEventListener(Event.ENTER_FRAME, update);
		}

		private function drawBar(perc:Number):void
		{
			bar.graphics.clear();
			bar.graphics.beginFill(col);
			bar.graphics.drawRect(0, 0, barW * perc, barH);
			bar.graphics.endFill();
		}

		private function glowing():void
		{
			if (glowAmount > 1)
			{
				glowAmount = 8 + Math.cos(fall * glowMax);
				fall +=  0.1;
				glow.blurX = glow.blurY = glowAmount;
				bar.filters = [glow];
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
					bar.graphics.clear();
				}
			}
			glowing();
		}
	}
}