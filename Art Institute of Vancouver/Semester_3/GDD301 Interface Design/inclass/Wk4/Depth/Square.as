package
{
	import flash.display.Sprite;
	
	public class Square extends Sprite
	{
		public function Square( )
		{
			graphics.beginFill( 0x000000);
			graphics.drawRect( -10, -10, 20, 20 );
			graphics.endFill();
		}
	}
}