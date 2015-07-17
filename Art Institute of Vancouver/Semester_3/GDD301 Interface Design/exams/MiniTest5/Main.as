package
{
	import flash.display.Sprite;
	import flash.events.KeyboardEvent;
	
	public class Main extends Sprite
	{
		public var box:Sprite = new Sprite();
		
		public function Main()
		{
			box.graphics.beginFill(0x00FF00)
			box.graphics.drawRect(0, 0, 100, 100);
			box.graphics.endFill();
			addChild(box);
			
			stage.addEventListener(KeyboardEvent.KEY_DOWN, keyDown);
		}
		
		public function keyDown(k:keyboardEvent):void
		{
			if(k.keyCode == 37)
			{
				box. -= 8;
			}
		}
	}
}