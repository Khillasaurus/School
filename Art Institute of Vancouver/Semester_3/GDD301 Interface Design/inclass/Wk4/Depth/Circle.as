package
{
	import flash.display.Sprite;
	
	public class Circle extends Sprite
	{
		public function Circle( col:uint )
		{
			graphics.beginFill( col );
			graphics.drawCircle( 0, 0, 50 );
			graphics.endFill();
		}
	}
}