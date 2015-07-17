package
{
	import flash.display.*;

	public class ShapeRect extends Sprite
	{
		public function ShapeRect(rx:uint, ry:uint, rw:uint, rh:uint, col:Number)
		{
			graphics.beginFill(col);
			graphics.drawRect(rx,ry,rw,rh);
			graphics.endFill();
		}
	}
}