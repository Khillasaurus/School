package
{
	import flash.display.Sprite;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.ui.Keyboard;
	
	public class DepthChange extends Sprite
	{
		public var circle1, circle2, circle3 :Circle;
		public var childs:uint;
		public var bob:Sprite;
		
		public function DepthChange()
		{
			circle1 = new Circle( 0xFF0000 );
			circle1.x = 100;
			circle1.y = 100;
			addChild( circle1 );
			circle1.addEventListener( MouseEvent.CLICK, swap );
			
			circle2 = new Circle( 0x00FF00 );
			circle2.x = 125;
			circle2.y = 125;
			addChild( circle2 );
			circle2.addEventListener( MouseEvent.CLICK, swap );
			
			circle3 = new Circle( 0x0000FF );
			circle3.x = 75;
			circle3.y = 125;
			addChild( circle3 );
			circle3.addEventListener( MouseEvent.CLICK, swap );
			
			bob = circle3;
			stage.addEventListener( KeyboardEvent.KEY_DOWN, tap );
		}
		
		public function swap( e:MouseEvent )
		{
			childs = this.numChildren-1;
			bob = getChildByName( e.target.name ) as Sprite;
			setChildIndex(bob, childs);
		}
		
		public function tap( k:KeyboardEvent ):void
		{
			var key:uint = k.keyCode;
			var square:Square = new Square();
			
			switch( key )
			{
				case Keyboard.SPACE:
					bob.addChild( square );
					break;
				case Keyboard.CONTROL:
					addChild( square );
					break;
			}
		}
			
		
	}
}