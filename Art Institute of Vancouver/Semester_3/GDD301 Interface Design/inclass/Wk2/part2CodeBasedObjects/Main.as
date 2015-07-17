package
{
	import flash.display.*;
	
	public class Main extends MovieClip
	{
		
		public function Main()
		{
			var rectangleR = new ShapeRect(150,100,100,50,0xFF0000);
			var rectangleG = new ShapeRect(250,100,100,75,0x00FF00);
			var rectangleB = new ShapeRect(350,100,100,100,0x0000FF);
			addChild(rectangleR);
			addChild(rectangleG);
			addChild(rectangleB);
		}
	}
}